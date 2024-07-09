import sys
import matplotlib.pyplot as plt
import numpy as np
import heapq
from scipy.special import factorial
from scipy.stats import poisson 
from numpy import random
import seaborn as sns
import signal
import time

        
if __name__ == "__main__":
    
        
    L,P,inhbi,Trest,Treltive,apha,t=np.loadtxt("input.txt")
    
    matriz = np.loadtxt('matriz.dat')
    
    # Crear y mostrar la primera figura
    plt.figure(1)        
    
    plt.imshow(matriz, cmap='cividis')
    plt.title(f"{int(L*L)} neuranas, probabilidad ={P}")
    plt.show(block=False)  # No bloquear la ejecución
    
    # Crear y mostrar la segunda figura
    plt.figure(2)
    
    
    
    
    k=np.zeros(len(matriz))
    for i in range(len(matriz)):
        k[i]=np.sum(abs(matriz[i]))
        
        
        
    unique_values, counts = np.unique(k, return_counts=True)
    k_main=sum(k)/len(matriz)
        
    
    
    sample1 = poisson.rvs(mu=k_main, size=100)    
    ##sns.kdeplot(x=sample1, fill=False,color="r", label=f'Media={k_main}')
    plt.scatter(unique_values,counts/len(matriz),s=10,label=r"p_k")
    plt.axvline(sum(k)/len(matriz),c="r",linestyle="--")
    plt.grid()
    plt.legend()
    plt.xlabel("k")
    plt.ylabel(r"$p_k$")
    plt.title(f"{int(L*L)} neuranas, probabilidad ={P}")
    plt.text(sum(k)/len(matriz),max(counts/len(matriz))/4,f"$<k>=${sum(k)/len(matriz)}" ,c="r")
    plt.show(block=False)  # No bloquear la ejecución
    plt.pause(0)