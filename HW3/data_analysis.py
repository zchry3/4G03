import numpy as np
import matplotlib.pyplot as plt

E = -4.515446354
Ex211 = np.loadtxt('HW3/EX2_1_10.txt', delimiter=',', skiprows=1)
M = []
E0 = []
E1 = []
for i in range(10):
    M.append(Ex211[i][1])
    E0.append(Ex211[i][2])
    E1.append(Ex211[i][3])
M = np.array(M)
E0 = np.array(E0)
E1 = np.array(E1)

fig1, ax1 = plt.subplots()
ax1.plot(M, E0)
ax1.set_title('Ground State Energy versus Lanczos Matrix Size for $L=10$')
ax1.set_xlabel('Matrix Size')
ax1.set_ylabel('$E_0$')

fig2, ax2 = plt.subplots()
ax2.plot(M, E1)
ax2.set_title('E1 versus Lanczos Matrix Size for $L=10$')
ax2.set_xlabel('Matrix Size')
ax2.set_ylabel('$E_1$')

fig3, ax3 = plt.subplots()
ax3.plot(M, np.abs(E0-E))
ax3.set_title('Ground State Energy Error for $L=10$')
ax3.set_xlabel('Matrix Size')
ax3.set_ylabel('|$E_0-E^0_{L=10}$|')

Ex212 = np.loadtxt('HW3/EX2_1_14.txt', delimiter=',', skiprows=1)
M = []
E0 = []
E1 = []
for i in range(10):
    M.append(Ex212[i][1])
    E0.append(Ex212[i][2])
    E1.append(Ex212[i][3])
M = np.array(M)
E0 = np.array(E0)
E1 = np.array(E1)

fig4, ax4 = plt.subplots()
ax4.plot(M, E0)
ax4.set_title('Ground State Energy versus Lanczos Matrix Size for $L=14$')
ax4.set_xlabel('Matrix Size')
ax4.set_ylabel('$E_0$')

fig5, ax5 = plt.subplots()
ax5.plot(M, E1)
ax5.set_title('E1 versus Lanczos Matrix Size for $L=14$')
ax5.set_xlabel('Matrix Size')
ax5.set_ylabel('$E_1$')

Ex22 = np.loadtxt('HW3/EX2_2.txt', delimiter=',', skiprows=1)
L = []
M = []
E0 = []
E1 = []
for i in range(10):
    L.append(Ex22[i][0])
    M.append(Ex22[i][1])
    E0.append(Ex22[i][2])
    E1.append(Ex22[i][3])
L = np.array(L)
M = np.array(M)
E0 = np.array(E0)
E1 = np.array(E1)

fig6, ax6 = plt.subplots()
ax6.plot(L, np.abs(E1-E0))
ax6.set_yscale('log')
ax6.set_title('Energy Gap versus System Size')
ax6.set_xlabel('System Size')
ax6.set_ylabel('$\log(|E_1-E_0|)$')

fig1.tight_layout()
fig2.tight_layout()
fig3.tight_layout()
fig4.tight_layout()
fig5.tight_layout()
fig6.tight_layout()

plt.show()
