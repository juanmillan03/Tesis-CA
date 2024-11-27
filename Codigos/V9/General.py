import sys
import numpy as np
import subprocess
from scipy import signal
from mne.time_frequency import psd_array_multitaper
import optuna
import numpy as np  
from scipy.stats import chisquare
import os


low_cutoff = 0.01  # Low cut-off frequency (Hz)
high_cutoff = 80.0  # High cut-off frequency (Hz)
order = 4  # Order of the filter
sampling_rate_equipo= 500 
b, a = signal.butter(order, [low_cutoff / (0.5 * sampling_rate_equipo), high_cutoff / (0.5 * sampling_rate_equipo)], btype='band')
fs = 500  # Sampling rate
sampling_rate = 1666 ### simulacion 

def Simulado_EGG(params,Normalizacion):
    L, P, inhibidoras, trest, trelative, alpha, tmax, type_matrix = params
    
    resultado_ejecucion = subprocess.run(f" OMP_NUM_THREADS={Threads} ./main {L} {P} {inhibidoras} {trest} {trelative} {alpha} {tmax} {type_matrix}", shell=True, stdout=subprocess.PIPE, text=True)
    if resultado_ejecucion.returncode != 0:
        print("Error durante la ejecución:")
        print(resultado_ejecucion.stderr)
        return None
    
    # Procesamiento de los datos
    lines = resultado_ejecucion.stdout.strip().split('\n')

    # Convertir cada línea en un valor flotante porque hay solo una columna
    data_list = [float(line) for line in lines]

    # Convertir la lista a un array de NumPy
    data = np.array(data_list)[50:]  # Ignorar las primeras 50 filas 
     
    if(Normalizacion=="max_global"):    
        data=data / max(data)
    elif(Normalizacion=="max_global_abs"):
        data=data / max(abs(data))
    elif(Normalizacion=="zscore"):
        data=(data - np.mean(data)) / np.std(data)

    n_samples_resampled = int(len(data)*(fs/sampling_rate))
    data_resampled = signal.resample(data, n_samples_resampled)

    butter = signal.filtfilt(b, a,data_resampled)

    psd,frequencies = psd_array_multitaper(butter, fs, fmin=0, fmax=60, adaptive=True, verbose=False ,n_jobs=1)
    frequencies=np.array(frequencies)

    welch_data = np.array([10 * np.log10(psd[i]) for i in range(len(frequencies))])
    
    delta = welch_data[np.logical_and(frequencies > 0, frequencies <= 3)]
    theta = welch_data[np.logical_and(frequencies > 3, frequencies <= 7)]
    alpha = welch_data[np.logical_and(frequencies > 7, frequencies <= 14)]
    beta = welch_data[np.logical_and(frequencies >14, frequencies <= 30)]

    return {
        'data': data,"data_resample":data_resampled,"butter": butter,
        "frequencies": frequencies,"welch_data":welch_data,
        'delta':[delta.mean(),delta.std()],
        'theta':[theta.mean(), theta.std()],
        'alpha':[ alpha.mean(),alpha.std()],
        'beta': [beta.mean(), beta.std()]
    }

def read_all_signals_from_folders(parent_folder):

    all_signals = []
    
    # Iterar sobre las subcarpetas en la carpeta principal
    for folder_name in sorted(os.listdir(parent_folder)):
        folder_path = os.path.join(parent_folder, folder_name)
        if os.path.isdir(folder_path):  # Asegurarse de que es una carpeta
            # Leer señales de la carpeta actual
            senal_uni, _ = read_signals(folder_path)
            all_signals.extend(senal_uni)  # Agregar todas las señales de esta carpeta
    
    # Concatenar todas las señales en un solo array
    all_signals_array = np.concatenate(all_signals)
    
    # Calcular valores globales
    global_min = np.min(all_signals_array)
    global_max = np.max(all_signals_array)
    global_mean = np.mean(all_signals_array)
    global_std = np.std(all_signals_array)
    
    return all_signals_array, global_min, global_max, global_mean, global_std

def read_signals(folder_path):
    signals = []
    file_names = []
    for file_name in sorted(os.listdir(folder_path)):  # Ordenar los archivos por nombre
        if file_name.endswith(".txt"):  # Filtrar solo archivos de texto
            file_path = os.path.join(folder_path, file_name)
            signal_i = np.loadtxt(file_path)  # Leer los datos del archivo
            signals.append(signal_i)
            file_names.append(file_name)  # Guardar el nombre del archivo
    return signals, file_names

def euclidean_distance(function1, function2):
    return np.sqrt(np.sum((np.array(function1) - np.array(function2))**2))


def Datos_reales(directorio,Normalizacion, global_min, global_max, global_mean, global_std):
    Datos,nombres= read_signals(directorio)
    Butter = np.empty(len(nombres), dtype=object)
    welch_datos = np.empty(len(nombres), dtype=object)
    Frequencies = np.empty(len(nombres), dtype=object)
    Delta = np.zeros((len(nombres), 2)) 
    Theta = np.zeros((len(nombres), 2)) 
    Alpha = np.zeros((len(nombres), 2)) 
    Beta = np.zeros((len(nombres), 2)) 
    if(Normalizacion=="max_global"):    
            Datos=Datos/global_max
    elif(Normalizacion=="zscore"):
        Datos=(Datos-global_mean) / global_std
    for i in range(len(Datos)):
        Butter[i]=butter= signal.filtfilt(b, a,Datos[i])
        psd,frequencies = psd_array_multitaper(butter, fs, fmin=0, fmax=60, adaptive=True,verbose=False,n_jobs=1)
        Frequencies[i]=frequencies=np.array(frequencies)
        welch_data = np.array([10 * np.log10(psd[i]) for i in range(len(frequencies))])
        welch_datos[i]=welch_data
        delta = welch_data[np.logical_and(frequencies >= 0, frequencies <= 3)]
        theta = welch_data[np.logical_and(frequencies >= 3, frequencies <= 7)]
        alpha = welch_data[np.logical_and(frequencies >= 7, frequencies <= 14)]
        beta = welch_data[np.logical_and(frequencies >= 14, frequencies <= 30)]
        Delta[i]=np.array([delta.mean(),delta.std()])
        Theta[i]=[theta.mean(),theta.std()]
        Alpha[i]=[alpha.mean(),alpha.std()]
        Beta[i]=[beta.mean(),beta.std()]
    mean_welch=np.mean(welch_datos)
    mean_Delta=[Delta[:,0].mean(),np.mean(Delta[:,1])]
    mean_Theta=[Theta[:,0].mean(),np.mean(Theta[:,1])]
    mean_Alpha=[Alpha[:,0].mean(),np.mean(Alpha[:,1])]
    mean_Beta=[Beta[:,0].mean(),np.mean(Beta[:,1])]
    return {
        "Nombres":nombres,"Zona":directorio,
        'datos': Datos, "frequencies": Frequencies,  "welch_data":welch_datos,"mean_welch":mean_welch,
        'delta':Delta,'theta':Theta,'alpha':Alpha,'beta':Beta,
        'mean_Delta': mean_Delta,'mean_Theta':mean_Theta,"mean_Alpha":mean_Alpha,"mean_Beta":mean_Beta
    }

def objective(trial):
    params = np.zeros(8)
    params[0] = trial.suggest_int('L',10,100)
    params[1] = trial.suggest_float('P', 0.0, Pmax)
    params[2] = trial.suggest_float('Inh', 0.0, 1.0)
    params[3] = trial.suggest_float('Trest',0,10.0)###, step=0.05 difernecia entre datos 
    params[4] = trial.suggest_float('Trelative',params[3],params[3]+10)  
    params[5] = trial.suggest_float('C_h', 0, 1)
    params[6] = 6716
    params[7] = trial.suggest_int('Tipo_red',Tmin,Tmax)

        
    generated= Simulado_EGG(params,Normalizacion)
    if generated["delta"][1]-generated["delta"][1]==0:
        hi2_stat=euclidean_distance(generated["welch_data"][:121],reales_total["mean_welch"][:121])
        trial.report(hi2_stat, step=trial.number)### general
        return hi2_stat
    else:
        return float('inf')  

def main():
    # Verificar si se pasaron los comandos necesarios
    if len(sys.argv) != 5:
        print("Uso: python comandos.py Threads Normalizacion Zona T_red")
        sys.exit(1)
    
    threads = sys.argv[1]
    Norma=sys.argv[2]
    Zona=sys.argv[3]
    Tipo_de_red=sys.argv[4]
    if Norma not in ["max_global","zscore"]:
        print("Mal parametro de Normalizacion")
        sys.exit(1)
    if Tipo_de_red not in ["Regular","Random","SW"]:
        print("Mal parametro de tipo de red")
        sys.exit(1)
    
    global Tmin
    global Tmax
    global Pmax
    global Threads
    global Normalizacion
    global reales_total

    if Tipo_de_red=="Regular":
        Tmin=0
        Tmax=0
        Pmax=0.0
    elif Tipo_de_red=="Random":
        Tmin=3
        Tmax=4
        Pmax=1.0
    elif Tipo_de_red=="SW":
        Tmin=1
        Tmax=2
        Pmax=1.0
    Threads=threads
    print(f"Threas: {Threads}")
    print(f"Norma: {Norma}")
    print(f"Zona: {Zona}")
    print(f"Tipo de red: {Tipo_de_red}")
    

    resultado_compilacion = subprocess.run("g++ -fopenmp -O3 main.cpp Matrix_conect.cpp -o main", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if resultado_compilacion.returncode != 0:
        print("Error durante la compilación:")
        print(resultado_compilacion.stderr)

    parent_folder = "Datos_reales"
    all_signals_array, global_min, global_max, global_mean, global_std = read_all_signals_from_folders(parent_folder)
    Normalizacion=Norma
    reales_total = Datos_reales(f"Datos_reales/{Zona}",Normalizacion, global_min, global_max, global_mean, global_std)

    # Create and optimize the study
    study_name = f"Chi30_{Tipo_de_red}_{Normalizacion}"
    study = optuna.create_study(study_name=study_name, 
                                storage=f"sqlite:///Estudios/{Zona}/{study_name}.db", 
                                   load_if_exists=True,
                                direction="minimize",
                                pruner= optuna.pruners.MedianPruner(n_startup_trials=5, n_warmup_steps=10, interval_steps=1)
                                
                                )
    n_trials = 500  # Total de pruebas
    sampler_distribution = {"random": 0.2, "tpe": 0.5, "cmaes": 0.3}  # Porcentaje de cada sampler
    # Configuración de los samplers
    random_sampler = optuna.samplers.RandomSampler()
    tpe_sampler = optuna.samplers.TPESampler()
    cmaes_sampler = optuna.samplers.CmaEsSampler()

    # Calcular los límites de los samplers
    n_random = int(sampler_distribution["random"] * n_trials)
    n_tpe = int(sampler_distribution["tpe"] * n_trials)
    n_cmaes = n_trials - n_random - n_tpe  # Restante
    study.sampler = random_sampler
    study.optimize(objective, n_trials=n_random)

    # Segunda etapa: TPESampler
    study.sampler = tpe_sampler
    study.optimize(objective, n_trials=n_tpe)

    # Tercera etapa: CmaEsSampler
    study.sampler = cmaes_sampler
    study.optimize(objective, n_trials=n_cmaes)    

if __name__ == "__main__":
    main()
