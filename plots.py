import numpy as np
import matplotlib.pyplot as plt

#AQUI IMPORTO EL ARCHOVO CREADO
archivo = np.genfromtxt('datos.txt', delimiter=' ' )

#AQUI DEFINO VARIABLES
x=archivo[:,0]
periodo1=archivo[:,1]
periodo2=archivo[:,2]
periodo3=archivo[:,3]
periodo4=archivo[:,4]

#AQUI HAGO LA GRAFICA
plt.plot(x,periodo1, c='darkmagenta', label='t=0')
plt.plot(x,periodo2, c='limegreen', label='t=periodo/8')
plt.plot(x,periodo3, c='slateblue', label='t=periodo/4')
plt.plot(x,periodo4, c='tomato', label='t=periodo/2')
plt.legend(loc='upper right')
plt.title('Cuerda para diferentes tiempos')
plt.show()

