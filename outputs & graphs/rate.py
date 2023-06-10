import re
import matplotlib.pyplot as plt


def plot(x, y, color='red'):
    plt.rcParams["figure.autolayout"] = True
    plt.plot(x, y, color=color)

def get_data(file_name: str) -> tuple:
    file = open(file_name)
    lines = file.readlines()
    rate = []
    p = []
    for line in lines:
        line_data = re.findall(r'(\w+)\s*=\s*([\d.]+)', line)
        p.append(float(line_data[0][1]))
        rate.append(float(line_data[1][1]))
    file.close()
    return (p, rate)

if __name__ == "__main__":
    p_100, r_100     = get_data("rate/100.txt")
    p_1000, r_1000   = get_data("rate/1000.txt")
    p_5000, r_5000   = get_data("rate/5000.txt")
    p_9000, r_9000   = get_data("rate/9000.txt")
    p_13000, r_13000 = get_data("rate/13000.txt")
    plot(p_100,   r_100,    color = (0,    1,    0))
    plot(p_1000,  r_1000,   color = (0.25, 0.75, 0))
    plot(p_5000,  r_5000,   color = (0.5,  0.5,  0))
    plot(p_9000,  r_9000,   color = (0.75, 0.25, 0))
    plot(p_13000, r_13000,  color = (1,    0,    0))
    plt.title("lane changing rate vs. p")
    plt.figure()
    plot([0, 0.5, 1], [5, 5, 5],   color = (0,    1,    0))
    plot([0, 0.5, 1], [4, 4, 4],   color = (0.25, 0.75, 0))
    plot([0, 0.5, 1], [3, 3, 3],   color = (0.5,  0.5,  0))
    plot([0, 0.5, 1], [2, 2, 2],   color = (0.75, 0.25, 0))
    plot([0, 0.5, 1], [1, 1, 1],   color = (1,    0,    0))
    plot([0, 0.5, 1], [-12, -12, -12],  color = (1,    0,    0))
    plt.show()