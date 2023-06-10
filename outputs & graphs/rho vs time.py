import re
import matplotlib.pyplot as plt


def plot(x, y, color='red'):
    plt.rcParams["figure.autolayout"] = True
    plt.scatter(x, y, color=color, s=2)


if __name__ == "__main__":
    occ1_2 = []
    occ1_5 = []
    time_2 = []
    occ2_2 = []
    occ2_5 = []
    time_5 = []
    file = open("density/800.200012.txt")
    lines = file.readlines()
    for line in lines:
        line_data = re.findall(r'(\w+)\s*=\s*([\d.]+)', line)
        for key, value in line_data:
            if key == "MeanO1":
                occ1_2.append(float(value))
            elif key == "time":
                time_2.append(float(value))
            elif key == "MeanO2":
                occ2_2.append(float(value))
    file.close()
    file = open("density/800.500000.txt")
    lines = file.readlines()
    for line in lines:
        line_data = re.findall(r'(\w+)\s*=\s*([\d.]+)', line)
        for key, value in line_data:
            if key == "MeanO1":
                occ1_5.append(float(value))
            elif key == "time":
                time_5.append(float(value))
            elif key == "MeanO2":
                occ2_5.append(float(value))
    file.close()
    line = []
    line2 = []
    for i in range(len(occ1_2)):
        line.append((occ1_2[i] + occ2_2[i]) / 2)
    for i in range(len(occ1_5)):
        line2.append((occ1_5[i] + occ2_5[i]) / 2)
    plot(time_2, occ1_2, 'green')
    plot(time_2, occ2_2, 'red')
    plt.plot(time_2, line, 'black')
    plt.title(r"$\rho$"+ " vs. time")
    plt.figure()
    plot(time_5, occ1_5, 'green')
    plot(time_5, occ2_5, 'red')
    plt.plot(time_5, line2, 'black')
    plt.title(r"$\rho$"+ " vs. time")
    plt.show()