import subprocess
import time

# Parámetros del estudio
threads_list = [1,2,3,4,5]  # Número de threads a probar
L_values = [20,30,40,50,60,70,80,90,100]  # Valores de L
P = 0.1  # Probabilidad de conexión
inhibidoras = 0.4
trest = 0.0
trelative = 1.0
alpha = 0.1
tmax = 1000
type_matrix = 1  # Tipo de matriz

# Archivo para guardar resultados
output_file = "estudio_optimizacion.txt"

# Bucle para el estudio
with open(output_file, "w") as f:
    f.write("Threads\tL\tTiempo (s)\n")
    
    for threads in threads_list:
        for L in L_values:
            command = f"OMP_NUM_THREADS={threads} ./main_py {L} {P} {inhibidoras} {trest} {trelative} {alpha} {tmax} {type_matrix}"
            print(f"Ejecutando: {command}")
            
            # Medir el tiempo de ejecución
            start_time = time.time()
            result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            end_time = time.time()
            elapsed_time = end_time - start_time
            
            if result.returncode == 0:
                # Si la ejecución fue exitosa, guardar el resultado
                output = result.stdout.strip()
                #print(f"Resultado: {output}")
                f.write(f"{threads}\t{L}\t{elapsed_time:.2f}\n")
            else:
                # Si hubo un error, guardar el mensaje de error
                #print(f"Error en la ejecución: {result.stderr.strip()}")
                f.write(f"{threads}\t{L}\t{elapsed_time:.2f}\n")
