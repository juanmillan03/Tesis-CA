import sys
import matplotlib.pyplot as plt
import numpy as np
import heapq
from scipy.special import factorial
from scipy.stats import poisson 
from numpy import random
import seaborn as sns



def dijkstra(graph, start):
    distances = {node: float('inf') for node in range(len(graph))}
    distances[start] = 0
    queue = [(0, start)]
    
    while queue:
        current_distance, current_node = heapq.heappop(queue)
        
        if current_distance > distances[current_node]:
            continue
        
        # Corrected iteration over neighbors
        for neighbor_index in range(len(graph)):
            weight = graph[current_node][neighbor_index]
            if weight == 1:  # Assuming weight 1 means there's an edge between nodes
                distance = current_distance + weight
                if distance < distances[neighbor_index]:
                    distances[neighbor_index] = distance
                    heapq.heappush(queue, (distance, neighbor_index))
    
    return distances
        
if __name__ == "__main__":
    
    L,P,inhbi,Trest,Treltive,apha,t=np.loadtxt("input.txt")
    
    matriz = np.loadtxt('matriz.dat')
    
    # Crear y mostrar la primera figura
    plt.figure(1)        
    
    # d_ind=0
    # for i in range(int(L*L)):
    #     for j in range(int(L*L)):
    #         d_ind+=dijkstra(matriz, i)[j]
    # print(d_ind)
    plt.imshow(matriz, cmap='binary')
    plt.title(f"{int(L*L)} neuranas, probabilidad ={P}")
    plt.show(block=False)  # No bloquear la ejecución
    
    # Crear y mostrar la segunda figura
    plt.figure(2)
    
    
    
    
    k=np.zeros(len(matriz))
    for i in range(len(matriz)):
        k[i]=np.sum(matriz[i]) 
    
    
    
    unique_values, counts = np.unique(k, return_counts=True)
    k_main=sum(k)/len(matriz)
    
    
    
    sample1 = poisson.rvs(mu=k_main, size=100)    
    sns.kdeplot(x=sample1, fill=False,color="r", label=f'lambda={k_main}')
    plt.scatter(unique_values,counts/len(matriz),s=8,label=r"p_k")
    plt.axvline(sum(k)/len(matriz),c="r",linestyle="--")
    plt.grid()
    plt.legend()
    plt.xlabel("k")
    plt.ylabel(r"$p_k$")
    plt.title(f"{int(L*L)} neuranas, probabilidad ={P}")
    plt.text(sum(k)/len(matriz),max(counts/len(matriz))/4,r"$<k>$",c="r")
    plt.show(block=False)  # No bloquear la ejecución
    
    # Esperar a que ambas figuras se cierren antes de continuar
    plt.pause(0)




    

