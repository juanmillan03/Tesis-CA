import sys
import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
    
    L,P,inhbi,Trest,Treltive,apha,t=np.loadtxt("input.txt")
    
    matriz = np.loadtxt('matriz.dat')
    
    # Crear y mostrar la primera figura
    plt.figure(1)
    plt.imshow(matriz, cmap='binary')
    plt.title(f"{int(L*L)} neuranas, probabilidad ={P}")
    plt.show(block=False)  # No bloquear la ejecución
    
    # Crear y mostrar la segunda figura
    plt.figure(2)
    k=np.zeros(len(matriz))
    for i in range(len(matriz)):
        k[i]=np.sum(matriz[i])
        
    unique_values, counts = np.unique(k, return_counts=True)
    plt.scatter(unique_values,counts/len(matriz),s=8)
    plt.axvline(sum(k)/len(matriz),c="r",linestyle="--")
    plt.grid()
    plt.xlabel("d")
    plt.ylabel(r"$p_k$")
    plt.title(f"{int(L*L)} neuranas, probabilidad ={P}")
    plt.text(sum(k)/len(matriz),max(counts/len(matriz))/4,r"$<d>$",c="r")
    plt.show(block=False)  # No bloquear la ejecución
    
    # Esperar a que ambas figuras se cierren antes de continuar
    plt.pause(0)




    

