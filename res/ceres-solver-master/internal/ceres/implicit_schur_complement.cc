// Ceres Solver - A fast non-linear least squares minimizer
// Copyright 2015 Google Inc. All rights reserved.
// http://ceres-solver.org/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of Google Inc. nor the names of its contributors may be
//   used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Author: sameeragarwal@google.com (Sameer Agarwal)

#include "ceres/implicit_schur_complement.h"

#include "Eigen/Dense"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/internal/eigen.h"
#include "ceres/linear_solver.h"
#include "ceres/types.h"
#include "glog/logging.h"

namespace ceres::internal {

ImplicitSchurComplement::ImplicitSchurComplement(
    const LinearSolver::Options& options)
    : options_(options) {}

void ImplicitSchurComplement::Init(const BlockSparseMatrix& A,
                                   const double* D,
                                   const double* b) {
  // Since initialization is reasonably heavy, perhaps we can save on
  // constructing a new object everytime.
  if (A_ == nullptr) {
    A_ = PartitionedMatrixViewBase::Create(options_, A);
  }

  D_ = D;
  b_ = b;

  compute_ftf_inverse_ =
      options_.use_spse_initialization ||
      options_.preconditioner_type == JACOBI ||
      options_.preconditioner_type == SCHUR_POWER_SERIES_EXPANSION;

  // Initialize temporary storage and compute the block diagonals of
  // E'E and F'E.
  if (block_diagonal_EtE_inverse_ == nullptr) {
    block_diagonal_EtE_inverse_ = A_->CreateBlockDiagonalEtE();
    if (compute_ftf_inverse_) {
      block_diagonal_FtF_inverse_ = A_->CreateBlockDiagonalFtF();
    }
    rhs_.resize(A_->num_cols_f());
    rhs_.setZero();
    tmp_rows_.resize(A_->num_rows());
    tmp_e_cols_.resize(A_->num_cols_e());
    tmp_e_cols_2_.resize(A_->num_cols_e());
    tmp_f_cols_.resize(A_->num_cols_f());
  } else {
    A_->UpdateBlockDiagonalEtE(block_diagonal_EtE_inverse_.get());
    if (compute_ftf_inverse_) {
      A_->UpdateBlockDiagonalFtF(block_diagonal_FtF_inverse_.get());
    }
  }

  // The block diagonals of the augmented linear system contain
  // contributions from the diagonal D if it is non-null. Add that to
  // the block diagonals and invert them.
  AddDiagonalAndInvert(D_, block_diagonal_EtE_inverse_.get());
  if (compute_ftf_inverse_) {
    AddDiagonalAndInvert((D_ == nullptr) ? nullptr : D_ + A_->num_cols_e(),
                         block_diagonal_FtF_inverse_.get());
  }

  // Compute the RHS of the Schur complement system.
  UpdateRhs();
}

// Evaluate the product
//
//   Sx = [F'F - F'E (E'E)^-1 E'F]x
//
// By breaking it down into individual matrix vector products
// involving the matrices E and F. This is implemented using a
// PartitionedMatrixView of the input matrix A.
void ImplicitSchurComplement::RightMultiplyAndAccumulate(const double* x,
                                                         double* y) const {
  // y1 = F x
  tmp_rows_.setZero();
  A_->RightMultiplyAndAccumulateF(
      x, tmp_rows_.data(), options_.context, options_.num_threads);

  // y2 = E' y1
  tmp_e_cols_.setZero();
  A_->LeftMultiplyAndAccumulateE(tmp_rows_.data(), tmp_e_cols_.data());

  // y3 = -(E'E)^-1 y2
  tmp_e_cols_2_.setZero();
  block_diagonal_EtE_inverse_->RightMultiplyAndAccumulate(tmp_e_cols_.data(),
                                                          tmp_e_cols_2_.data(),
                                                          options_.context,
                                                          options_.num_threads);
  tmp_e_cols_2_ *= -1.0;

  // y1 = y1 + E y3
  A_->RightMultiplyAndAccumulateE(tmp_e_cols_2_.data(),
                                  tmp_rows_.data(),
                                  options_.context,
                                  options_.num_threads);

  // y5 = D * x
  if (D_ != nullptr) {
    ConstVectorRef Dref(D_ + A_->num_cols_e(), num_cols());
    VectorRef(y, num_cols()) =
        (Dref.array().square() * ConstVectorRef(x, num_cols()).array())
            .matrix();
  } else {
    VectorRef(y, num_cols()).setZero();
  }

  // y = y5 + F' y1
  A_->LeftMultiplyAndAccumulateF(tmp_rows_.data(), y);
}

void ImplicitSchurComplement::InversePowerSeriesOperatorRightMultiplyAccumulate(
    const double* x, double* y) const {
  CHECK(compute_ftf_inverse_);
  // y1 = F x
  tmp_rows_.setZero();
  A_->RightMultiplyAndAccumulateF(
      x, tmp_rows_.data(), options_.context, options_.num_threads);

  // y2 = E' y1
  tmp_e_cols_.setZero();
  A_->LeftMultiplyAndAccumulateE(tmp_rows_.data(), tmp_e_cols_.data());

  // y3 = (E'E)^-1 y2
  tmp_e_cols_2_.setZero();
  block_diagonal_EtE_inverse_->RightMultiplyAndAccumulate(tmp_e_cols_.data(),
                                                          tmp_e_cols_2_.data(),
                                                          options_.context,
                                                          options_.num_threads);
  // y1 = E y3
  tmp_rows_.setZero();
  A_->RightMultiplyAndAccumulateE(tmp_e_cols_2_.data(),
                                  tmp_rows_.data(),
                                  options_.context,
                                  options_.num_threads);

  // y4 = F' y1
  tmp_f_cols_.setZero();
  A_->LeftMultiplyAndAccumulateF(tmp_rows_.data(), tmp_f_cols_.data());

  // y += (F'F)^-1 y4
  block_diagonal_FtF_inverse_->RightMultiplyAndAccumulate(
      tmp_f_cols_.data(), y, options_.context, options_.num_threads);
}

// Given a block diagonal matrix and an optional array of diagonal
// entries D, add them to the diagonal of the matrix and compute the
// inverse of each diagonal block.
void ImplicitSchurComplement::AddDiagonalAndInvert(
    const double* D, BlockSparseMatrix* block_diagonal) {
  const CompressedRowBlockStructure* block_diagonal_structure =
      block_diagonal->block_structure();
  for (const auto& row : block_diagonal_structure->rows) {
    const int row_block_pos = row.block.position;
    const int row_block_size = row.block.size;
    const Cell& cell = row.cells[0];
    MatrixRef m(block_diagonal->mutable_values() + cell.position,
                row_block_size,
                row_block_size);

    if (D != nullptr) {
      ConstVectorRef d(D + row_block_pos, row_block_size);
      m += d.array().square().matrix().asDiagonal();
    }

    m = m.selfadjointView<Eigen::Upper>().llt().solve(
        Matrix::Identity(row_block_size, row_block_size));
  }
}

// Similar to RightMultiplyAndAccumulate, use the block structure of the matrix
// A to compute y = (E'E)^-1 (E'b - E'F x).
void ImplicitSchurComplement::BackSubstitute(const double* x, double* y) {
  const int num_cols_e = A_->num_cols_e();
  const int num_cols_f = A_->num_cols_f();
  const int num_cols = A_->num_cols();
  const int num_rows = A_->num_rows();

  // y1 = F x
  tmp_rows_.setZero();
  A_->RightMultiplyAndAccumulateF(
      x, tmp_rows_.data(), options_.context, options_.num_threads);

  // y2 = b - y1
  tmp_rows_ = ConstVectorRef(b_, num_rows) - tmp_rows_;

  // y3 = E' y2
  tmp_e_cols_.setZero();
  A_->LeftMultiplyAndAccumulateE(tmp_rows_.data(), tmp_e_cols_.data());

  // y = (E'E)^-1 y3
  VectorRef(y, num_cols).setZero();
  block_diagonal_EtE_inverse_->RightMultiplyAndAccumulate(
      tmp_e_cols_.data(), y, options_.context, options_.num_threads);

  // The full solution vector y has two blocks. The first block of
  // variables corresponds to the eliminated variables, which we just
  // computed via back substitution. The second block of variables
  // corresponds to the Schur complement system, so we just copy those
  // values from the solution to the Schur complement.
  VectorRef(y + num_cols_e, num_cols_f) = ConstVectorRef(x, num_cols_f);
}

// Compute the RHS of the Schur complement system.
//
// rhs = F'b - F'E (E'E)^-1 E'b
//
// Like BackSubstitute, we use the block structure of A to implement
// this using a series of matrix vector products.
void ImplicitSchurComplement::UpdateRhs() {
  // y1 = E'b
  tmp_e_cols_.setZero();
  A_->LeftMultiplyAndAccumulateE(b_, tmp_e_cols_.data());

  // y2 = (E'E)^-1 y1
  Vector y2 = Vector::Zero(A_->num_cols_e());
  block_diagonal_EtE_inverse_->RightMultiplyAndAccumulate(
      tmp_e_cols_.data(), y2.data(), options_.context, options_.num_threads);

  // y3 = E y2
  tmp_rows_.setZero();
  A_->RightMultiplyAndAccumulateE(
      y2.data(), tmp_rows_.data(), options_.context, options_.num_threads);

  // y3 = b - y3
  tmp_rows_ = ConstVectorRef(b_, A_->num_rows()) - tmp_rows_;

  // rhs = F' y3
  rhs_.setZero();
  A_->LeftMultiplyAndAccumulateF(tmp_rows_.data(), rhs_.data());
}

}  // namespace ceres::internal
