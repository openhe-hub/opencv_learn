import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    # read data
    fp = open("../out/kalman2.txt")
    lines, data, pred = [], [], []

    lines = fp.readlines()
    for line in lines[:20]:
        data.append(float(line[:-1]))
    for line in lines[20:]:
        pred.append(float(line[:-1]))
    print(data)
    print(pred)
    fp.close()

    # plot
    plt.scatter(np.arange(1, len(data) + 1), data, marker='o', c='g')
    plt.scatter(np.arange(2, len(pred) + 2), pred, marker='x', c='b')
    plt.legend(['data', 'pred'])
    plt.show()
