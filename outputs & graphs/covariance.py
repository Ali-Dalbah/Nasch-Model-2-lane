import re
import matplotlib.pyplot as plt
import math


def plot(x, y, color='red'):
    plt.rcParams["figure.autolayout"] = True
    plt.scatter(x, y, color=color, s=2)


if __name__ == "__main__":
    r = []
    co1 = []
    co2 = []
    co1_1 = []
    co2_1 = []
    ln_co1 = []
    ln_co2 = []
    ln_co1_1 = []
    ln_co2_1 = []
    x = []
    file = open("12000co.txt")
    lines = file.readline()
    line_data = re.findall(r'(\w+)\s*=\s*-?([\d.]+)', lines)
    print(len(line_data))
    for i in range(300):
        r.append(i)
        co1.append(float(line_data[i][1]))
        ln_co1.append(math.log10(abs(co1[i])+0.00000001))
    for i in range(300, 600):
        co2.append(float(line_data[i][1]))
        ln_co2.append(math.log(abs(co2[i-300])+0.00000001))
    lines = file.readline()
    line_data = re.findall(r'(\w+)\s*=\s*-?([\d.]+)', lines)
    for i in range(300):
        co1_1.append(float(line_data[i][1]))
        ln_co1_1.append(math.log(abs(co1_1[i])+0.00000001))
    for i in range(300, 600):
        co2_1.append(float(line_data[i][1]))
        ln_co2_1.append(math.log(abs(co2_1[i-300])+0.00000001))
    plot(r, co1)
    plot(r, co2, color='green')
    plt.figure()
    plot(r, co1_1 )
    plot(r, co2_1, color='green')
    plt.show()