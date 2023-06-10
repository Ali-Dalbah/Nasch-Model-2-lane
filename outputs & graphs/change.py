import re
import matplotlib.pyplot as plt
import math

def plot(x, y, color='red'):
    plt.rcParams["figure.autolayout"] = True
    plt.scatter(x, y, color=color, s=3)


if __name__ == "__main__":
    file = open("change/12000.txt")
    lines = file.readlines()
    change = []
    time = []
    time_ln = []
    lines.pop(0)
    for line in lines:
        line_data = re.findall(r'(\w+)\s*=\s*([\d.]+)', line)
        time.append(float(line_data[0][1]))
        time_ln.append(math.log(float(line_data[0][1])))
        change.append(float(line_data[1][1]))
    plt.subplot(2, 2, 1)
    plot(time, change)
    plt.title("Lane Switching Count vs. time")
    plt.ylabel(r"Lane Switching Count")
    plt.xlabel(r"time")
    plt.subplot(2, 2, 2)
    plot(time_ln, change)
    plt.xlabel(r"$\ln\left({time}\right)$")
    plt.ylabel(r"Lane Switching Count")
    plt.title(r"Lane Switching Count vs. $\ln\left({time}\right)$")
    plt.show()