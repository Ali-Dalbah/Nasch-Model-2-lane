import re
import matplotlib.pyplot as plt


def plot(x, y, color='red'):
    plt.rcParams["figure.autolayout"] = True
    plt.scatter(x, y, color=color, s=1)


if __name__ == "__main__":
    file = open("data.txt")
    lines = file.readlines()
    MeanV1_sto_0_sw_0 = []
    MeanO1_sto_0_sw_0 = []
    MeanV1_sto_2_sw_0 = []
    MeanO1_sto_2_sw_0 = []
    MeanV2_sto_0_sw_0 = []
    MeanO2_sto_0_sw_0 = []
    MeanV2_sto_2_sw_0 = []
    MeanO2_sto_2_sw_0 = []

    MeanV1_sto_0_sw_5 = []
    MeanO1_sto_0_sw_5 = []
    MeanV1_sto_2_sw_5 = []
    MeanO1_sto_2_sw_5 = []
    MeanV2_sto_0_sw_5 = []
    MeanO2_sto_0_sw_5 = []
    MeanV2_sto_2_sw_5 = []
    MeanO2_sto_2_sw_5 = []
    take = 0
    count = 0
    for line in lines:
        line_data = re.findall(r'(\w+)\s*=\s*([\d.]+)', line)
        for key, value in line_data:
            if take == 0:
                if key == 'MeanV1':
                    MeanV1_sto_0_sw_0.append(float(value))
                elif key == 'MeanO1':
                    MeanO1_sto_0_sw_0.append(float(value))
                elif key == 'MeanV2':
                    MeanV2_sto_0_sw_0.append(float(value))
                elif key == 'MeanO2':
                    MeanO2_sto_0_sw_0.append(float(value))
            elif take == 1:
                if key == 'MeanV1':
                    MeanV1_sto_0_sw_5.append(float(value))
                elif key == 'MeanO1':
                    MeanO1_sto_0_sw_5.append(float(value))
                elif key == 'MeanV2':
                    MeanV2_sto_0_sw_5.append(float(value))
                elif key == 'MeanO2':
                    MeanO2_sto_0_sw_5.append(float(value))
            elif take == 2:
                if key == 'MeanV1':
                    MeanV1_sto_2_sw_0.append(float(value))
                elif key == 'MeanO1':
                    MeanO1_sto_2_sw_0.append(float(value))
                elif key == 'MeanV2':
                    MeanV2_sto_2_sw_0.append(float(value))
                elif key == 'MeanO2':
                    MeanO2_sto_2_sw_0.append(float(value))
            elif take == 3:
                if key == 'MeanV1':
                    MeanV1_sto_2_sw_5.append(float(value))
                elif key == 'MeanO1':
                    MeanO1_sto_2_sw_5.append(float(value))
                elif key == 'MeanV2':
                    MeanV2_sto_2_sw_5.append(float(value))
                elif key == 'MeanO2':
                    MeanO2_sto_2_sw_5.append(float(value))
        take = (take + 1) % 4
    length = len(MeanV1_sto_0_sw_0)
    flux1_sto_0_sw_0 = [0] * length
    flux2_sto_0_sw_0 = [0] * length
    flux1_sto_2_sw_0 = [0] * length
    flux2_sto_2_sw_0 = [0] * length
    joint_flux_0_sw_0 = [0] * length
    joint_occ_0_sw_0 = [0] * length
    joint_flux_2_sw_0 = [0] * length
    joint_occ_2_sw_0 = [0] * length

    flux1_sto_0_sw_5 = [0] * length
    flux2_sto_0_sw_5 = [0] * length
    flux1_sto_2_sw_5 = [0] * length
    flux2_sto_2_sw_5 = [0] * length
    joint_flux_0_sw_5 = [0] * length
    joint_occ_0_sw_5 = [0] * length
    joint_flux_2_sw_5 = [0] * length
    joint_occ_2_sw_5 = [0] * length

    for i in range(length):
        flux1_sto_0_sw_0[i] = MeanV1_sto_0_sw_0[i] * MeanO1_sto_0_sw_0[i]
        flux2_sto_0_sw_0[i] = MeanV2_sto_0_sw_0[i] * MeanO2_sto_0_sw_0[i]
        flux1_sto_2_sw_0[i] = MeanV1_sto_2_sw_0[i] * MeanO1_sto_2_sw_0[i]
        flux2_sto_2_sw_0[i] = MeanV2_sto_2_sw_0[i] * MeanO2_sto_2_sw_0[i]
        joint_flux_0_sw_0[i] = (flux1_sto_0_sw_0[i] + flux2_sto_0_sw_0[i]) 
        joint_flux_2_sw_0[i] = (flux1_sto_2_sw_0[i] + flux2_sto_2_sw_0[i]) 
        joint_occ_0_sw_0[i] = (MeanO1_sto_0_sw_0[i] + MeanO2_sto_0_sw_0[i]) / 2
        joint_occ_2_sw_0[i] = (MeanO1_sto_2_sw_0[i] + MeanO2_sto_2_sw_0[i]) / 2

        flux1_sto_0_sw_5[i] = MeanV1_sto_0_sw_5[i] * MeanO1_sto_0_sw_5[i]
        flux2_sto_0_sw_5[i] = MeanV2_sto_0_sw_5[i] * MeanO2_sto_0_sw_5[i]
        flux1_sto_2_sw_5[i] = MeanV1_sto_2_sw_5[i] * MeanO1_sto_2_sw_5[i]
        flux2_sto_2_sw_5[i] = MeanV2_sto_2_sw_5[i] * MeanO2_sto_2_sw_5[i]
        joint_flux_0_sw_5[i] = (flux1_sto_0_sw_5[i] + flux2_sto_0_sw_5[i]) 
        joint_flux_2_sw_5[i] = (flux1_sto_2_sw_5[i] + flux2_sto_2_sw_5[i]) 
        joint_occ_0_sw_5[i] = (MeanO1_sto_0_sw_5[i] + MeanO2_sto_0_sw_5[i]) / 2
        joint_occ_2_sw_5[i] = (MeanO1_sto_2_sw_5[i] + MeanO2_sto_2_sw_5[i]) / 2

    plot(MeanO1_sto_0_sw_0, flux1_sto_0_sw_0)
    plot(MeanO1_sto_0_sw_5, flux1_sto_0_sw_5, "green")
    plt.title("flux vs. occupancy for lane number 1, sto = 0")
    plt.figure()

    plot(MeanO1_sto_2_sw_0, flux1_sto_2_sw_0)
    plot(MeanO1_sto_2_sw_5, flux1_sto_2_sw_5, 'green')
    plt.title("flux vs. occupancy for lane number 1, sto = 0.2")
    plt.figure()

    plot(MeanO2_sto_0_sw_0, flux2_sto_0_sw_0)
    plot(MeanO2_sto_0_sw_5, flux2_sto_0_sw_5, "green")
    plt.title("flux vs. occupancy for lane number 2, sto = 0")
    plt.figure()

    plot(MeanO2_sto_2_sw_0, flux2_sto_2_sw_0)
    plot(MeanO2_sto_2_sw_5, flux2_sto_2_sw_5, "green")
    plt.title("flux vs. occupancy for lane number 2, sto = 0.2")
    plt.figure()

    plot(joint_occ_0_sw_0, joint_flux_0_sw_0)
    plot(joint_occ_0_sw_5, joint_flux_0_sw_5, "green")
    plt.title("flux vs. occupancy for both lanes, sto = 0")
    plt.figure()

    plot(joint_occ_2_sw_0, joint_flux_2_sw_0)
    plot(joint_occ_2_sw_5, joint_flux_2_sw_5, "green")
    plt.title("flux vs. occupancy for both lanes, sto = 0.2")


    plt.show()