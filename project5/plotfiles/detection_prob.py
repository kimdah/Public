
import numpy as np
import matplotlib.pyplot as plt

#Adjusting text size
# SMALL_SIZE = 14
# MEDIUM_SIZE = 17
# BIGGER_SIZE = 17
#
# plt.rc('font', size=SMALL_SIZE)          # controls default text sizes
# plt.rc('axes', titlesize=SMALL_SIZE)     # fontsize of the axes title
# plt.rc('axes', labelsize=MEDIUM_SIZE)    # fontsize of the x and y labels
# plt.rc('xtick', labelsize=SMALL_SIZE)    # fontsize of the tick labels
# plt.rc('ytick', labelsize=SMALL_SIZE)    # fontsize of the tick labels
# plt.rc('legend', fontsize=SMALL_SIZE)    # legend fontsize
# plt.rc('figure', titlesize=BIGGER_SIZE)  # fontsize of the figure title


for i in range(0,3):
    data = np.loadtxt('./datafiles/prob9_slits_%d.txt' %i, skiprows=1)
    y = np.array(data[:,0])
    p = np.array(data[:,1]) # assumed already normalized
    # normalized_p = p / np.sqrt(np.sum(p**2))

    plt.plot(y, p)
    plt.title("Detection probability for %d slit(s)"%i)
    plt.xlabel("y")
    plt.ylabel("p(y|x=0.8; t=0.002)")


    # plt.subplots_adjust(
    # top=0.915,
    # bottom=0.165,
    # left=0.0,
    # right=1,
    # hspace=0.0,
    # wspace=0.0
    # )

    plt.show()
    plt.savefig("prob_vs_t_slits_%d.pdf" %i)
