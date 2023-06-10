import re
import matplotlib.pyplot as plt


def plot(x, y, color='red'):
    plt.rcParams["figure.autolayout"] = True
    plt.scatter(x, y, color=color, s=2, alpha=0.05)


if __name__ == "__main__":
    file = open("density/3000.txt")
    lines = file.readlines()
    occ_1 = []
    occ_2 = []
    time = []
    lines.pop(0)
    lines.pop(0)
    for line in lines:
        line_data = re.findall(r'(\w+)\s*=\s*([\d.]+)', line)
        for key, value in line_data:
            if key == "MeanO1":
                occ_1.append(float(value))
            elif key == "time":
                time.append(float(value))
            elif key == "MeanO2":
                occ_2.append(float(value))
    plot(time, occ_1)
    plot(time, occ_2, 'green')
    plt.xlabel(r"time")
    plt.ylabel(r"$\rho$")
    plt.title(r"$\rho$ vs. time")
    plt.show()