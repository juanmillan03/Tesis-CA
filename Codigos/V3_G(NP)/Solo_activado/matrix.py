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


def handler(signum, frame):
    print("\nTiempo de espera agotado. Interrumpiendo la ejecución...")
    sys.exit(1)

def dijkstra_optimized(graph, start):
    # Convierte la matriz de adyacencia en una lista de vecinos para cada nodo
    neighbors = [[] for _ in range(len(graph))]
    for i in range(len(graph)):
        for j in range(i+1, len(graph)):
            if graph[i][j] == 1:  # Asume que 1 significa que hay una arista entre los nodos
                neighbors[i].append(j)
                neighbors[j].append(i)

    distances = {node: float('inf') for node in range(len(graph))}
    distances[start] = 0
    queue = [(0, start)]

    while queue:
        current_distance, current_node = heapq.heappop(queue)

        if current_distance > distances[current_node]:
            continue

        # Itera sobre los vecinos directos del nodo actual
        for neighbor in neighbors[current_node]:
            distance = current_distance + 1  # Asume que el peso de la arista es 1
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(queue, (distance, neighbor))

    return distances
        
if __name__ == "__main__":
    
    

    # Configura el tiempo de espera
    signal.signal(signal.SIGALRM, handler)
    signal.alarm(0)  # Establece un tiempo de espera de 300 segundos (5 minutos)

    try:
        # Aquí va tu código que puede tardar mucho tiempo
        print("Ejecutando tarea larga...")
        time.sleep(3600)  # Simula una tarea que dura 1 hora
    except KeyboardInterrupt:
        print("\nProceso interrumpido manualmente.")
    finally:
        print("Fin de la ejecución.")
        
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
    
    # Esperar a que ambas figuras se cierren antes de continuar
    
    
    plt.figure(3)
    
    from collections import defaultdict

    # Asumiendo que 'matriz' ya está definida y es una matriz cuadrada de tamaño L x L
    distances = defaultdict(int)  # Usaremos defaultdict para facilitar el conteo de frecuencias

    for i in range(int(L*L)): 
        distances[i] = dijkstra_optimized(matriz, i)  # Asume que esta función devuelve un diccionario de distancias

    all_distances = []
    for value_dict in distances.values():
        all_distances.extend(value_dict.values())

    # Ahora, contamos las frecuencias de las distancias únicas
    unique_distances = set(all_distances)
    total_frequencies = len(unique_distances)

    # Preparando los datos para el histograma
    hist_data = [(distance, all_distances.count(distance)) for distance in unique_distances]
    hist_data.sort()  # Ordenamos los datos para un histograma ordenado

    # Creando el histograma
    total=sum([item[1] for item in hist_data])
    plt.scatter([item[0] for item in hist_data], np.array([item[1] for item in hist_data])/total,s=8)
    plt.xlabel('Distancia Mínima')
    plt.ylabel(r'$P_d$')
    plt.grid()
    plt.title('Frecuencias de Distancias Mínimas')
    plt.show(block=False)
    plt.pause(0)







    

