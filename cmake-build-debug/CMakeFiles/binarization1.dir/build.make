# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/opencv_learn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/opencv_learn/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/binarization1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/binarization1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/binarization1.dir/flags.make

CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.o: CMakeFiles/binarization1.dir/flags.make
CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.o: ../src/binarization/binarization1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/opencv_learn/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.o -c /tmp/opencv_learn/src/binarization/binarization1.cpp

CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/opencv_learn/src/binarization/binarization1.cpp > CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.i

CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/opencv_learn/src/binarization/binarization1.cpp -o CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.s

# Object files for target binarization1
binarization1_OBJECTS = \
"CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.o"

# External object files for target binarization1
binarization1_EXTERNAL_OBJECTS =

binarization1: CMakeFiles/binarization1.dir/src/binarization/binarization1.cpp.o
binarization1: CMakeFiles/binarization1.dir/build.make
binarization1: /usr/local/lib/libopencv_gapi.so.4.6.0
binarization1: /usr/local/lib/libopencv_stitching.so.4.6.0
binarization1: /usr/local/lib/libopencv_alphamat.so.4.6.0
binarization1: /usr/local/lib/libopencv_aruco.so.4.6.0
binarization1: /usr/local/lib/libopencv_barcode.so.4.6.0
binarization1: /usr/local/lib/libopencv_bgsegm.so.4.6.0
binarization1: /usr/local/lib/libopencv_bioinspired.so.4.6.0
binarization1: /usr/local/lib/libopencv_ccalib.so.4.6.0
binarization1: /usr/local/lib/libopencv_dnn_objdetect.so.4.6.0
binarization1: /usr/local/lib/libopencv_dnn_superres.so.4.6.0
binarization1: /usr/local/lib/libopencv_dpm.so.4.6.0
binarization1: /usr/local/lib/libopencv_face.so.4.6.0
binarization1: /usr/local/lib/libopencv_freetype.so.4.6.0
binarization1: /usr/local/lib/libopencv_fuzzy.so.4.6.0
binarization1: /usr/local/lib/libopencv_hfs.so.4.6.0
binarization1: /usr/local/lib/libopencv_img_hash.so.4.6.0
binarization1: /usr/local/lib/libopencv_intensity_transform.so.4.6.0
binarization1: /usr/local/lib/libopencv_line_descriptor.so.4.6.0
binarization1: /usr/local/lib/libopencv_mcc.so.4.6.0
binarization1: /usr/local/lib/libopencv_quality.so.4.6.0
binarization1: /usr/local/lib/libopencv_rapid.so.4.6.0
binarization1: /usr/local/lib/libopencv_reg.so.4.6.0
binarization1: /usr/local/lib/libopencv_rgbd.so.4.6.0
binarization1: /usr/local/lib/libopencv_saliency.so.4.6.0
binarization1: /usr/local/lib/libopencv_sfm.so.4.6.0
binarization1: /usr/local/lib/libopencv_stereo.so.4.6.0
binarization1: /usr/local/lib/libopencv_structured_light.so.4.6.0
binarization1: /usr/local/lib/libopencv_superres.so.4.6.0
binarization1: /usr/local/lib/libopencv_surface_matching.so.4.6.0
binarization1: /usr/local/lib/libopencv_tracking.so.4.6.0
binarization1: /usr/local/lib/libopencv_videostab.so.4.6.0
binarization1: /usr/local/lib/libopencv_wechat_qrcode.so.4.6.0
binarization1: /usr/local/lib/libopencv_xfeatures2d.so.4.6.0
binarization1: /usr/local/lib/libopencv_xobjdetect.so.4.6.0
binarization1: /usr/local/lib/libopencv_xphoto.so.4.6.0
binarization1: /usr/local/lib/libopencv_shape.so.4.6.0
binarization1: /usr/local/lib/libopencv_highgui.so.4.6.0
binarization1: /usr/local/lib/libopencv_datasets.so.4.6.0
binarization1: /usr/local/lib/libopencv_plot.so.4.6.0
binarization1: /usr/local/lib/libopencv_text.so.4.6.0
binarization1: /usr/local/lib/libopencv_ml.so.4.6.0
binarization1: /usr/local/lib/libopencv_phase_unwrapping.so.4.6.0
binarization1: /usr/local/lib/libopencv_optflow.so.4.6.0
binarization1: /usr/local/lib/libopencv_ximgproc.so.4.6.0
binarization1: /usr/local/lib/libopencv_video.so.4.6.0
binarization1: /usr/local/lib/libopencv_videoio.so.4.6.0
binarization1: /usr/local/lib/libopencv_imgcodecs.so.4.6.0
binarization1: /usr/local/lib/libopencv_objdetect.so.4.6.0
binarization1: /usr/local/lib/libopencv_calib3d.so.4.6.0
binarization1: /usr/local/lib/libopencv_dnn.so.4.6.0
binarization1: /usr/local/lib/libopencv_features2d.so.4.6.0
binarization1: /usr/local/lib/libopencv_flann.so.4.6.0
binarization1: /usr/local/lib/libopencv_photo.so.4.6.0
binarization1: /usr/local/lib/libopencv_imgproc.so.4.6.0
binarization1: /usr/local/lib/libopencv_core.so.4.6.0
binarization1: CMakeFiles/binarization1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/opencv_learn/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable binarization1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/binarization1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/binarization1.dir/build: binarization1

.PHONY : CMakeFiles/binarization1.dir/build

CMakeFiles/binarization1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/binarization1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/binarization1.dir/clean

CMakeFiles/binarization1.dir/depend:
	cd /tmp/opencv_learn/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/opencv_learn /tmp/opencv_learn /tmp/opencv_learn/cmake-build-debug /tmp/opencv_learn/cmake-build-debug /tmp/opencv_learn/cmake-build-debug/CMakeFiles/binarization1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/binarization1.dir/depend

