import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    # read data
    fp = open("../out/kalman1.txt")
    lines, data = [], []
    lines = fp.readlines()
    for line in lines:
        data.append(float(line[:-1]))
    print(data)
    fp.close()
    # plot
    plt.plot(np.arange(1, len(data)+1), data)
    plt.legend('v pred by kalman')
    plt.show()

