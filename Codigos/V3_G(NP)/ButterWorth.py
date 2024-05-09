import sys
import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import butter, lfilter,welch

if __name__ == "__main__":
    
    L,P,inh,Trest,Treltive,apha,t=np.loadtxt("input.txt")
    
    
      
    order = 4 # 4th order filter
    sampling_rate = 500.0 # Hz
    # Define the low and high cutoff frequencies
    low_cutoff_frequency = 1.0 # Hz
    high_cutoff_frequency = 50.0 # Hz

    # Calculate the Nyquist frequency
    nyquist_frequency = 0.5 * sampling_rate
    # Normalize the frequencies
    low_cutoff_normalized = low_cutoff_frequency / nyquist_frequency
    high_cutoff_normalized = high_cutoff_frequency / nyquist_frequency

    # Design the Butterworth band-pass filter
    b, a = butter(order, [low_cutoff_normalized, high_cutoff_normalized], btype='band')

    # Replace this with your actual data
    data = np.loadtxt("data.dat")
    filtered_data_a = lfilter(b, a, data[:,0])
    filtered_data_b = lfilter(b, a, data[:,1])
    
    
    
    NFFT = 256
    OVERLAP = NFFT/2 # Time scale
    dt = 1.0 / 60.0 # Sampling rate
    fs = 1.0 / dt # Frequency scale



    # Calcular la PSD usando el método de Welch
    frequencies_a, psd_a = welch(data[:,0], fs, nperseg=NFFT, noverlap=OVERLAP)
    alplitud_a=np.zeros_like(psd_a)
    # Imprimir los resultados
    for i in range(len(frequencies_a)):
        alplitud_a[i]=10 * np.log10(psd_a[i])
    
    frequencies_b, psd_b = welch(data[:,1], fs, nperseg=NFFT, noverlap=OVERLAP)
    alplitud_b=np.zeros_like(psd_b)
    # Imprimir los resultados
    for i in range(len(frequencies_b)):
        alplitud_b[i]=10 * np.log10(psd_b[i])


    fig = plt.figure(figsize=(9, 6))
    
    plt.subplot(3, 2, 1)
    plt.plot(data[:,0], label='# Activadas')
    plt.title("#Activadas")
    plt.grid()
    
    plt.subplot(3, 2, 2)
    plt.plot(data[:,1], label='Potencial')
    plt.title("Potencial")
    plt.grid()
    

    plt.subplot(3, 2, 3)
    plt.plot(filtered_data_a, label='Filtro butter Activadas')
    plt.title("Filtro butter Activadas")
    plt.grid()


    plt.subplot(3, 2, 4)
    plt.plot(filtered_data_b, label='Filtro butter potencial')
    plt.title("Filtro butter potencial")
    plt.grid()
    
    plt.subplot(3, 2, 5)
    plt.plot(frequencies_a, alplitud_a, label='Potencial')
    plt.title("Periodograma activadas")
    plt.grid()
    
    plt.subplot(3, 2, 6)
    plt.plot(frequencies_b, alplitud_b, label='Potencial')
    delta=alplitud_b[0]-alplitud_a[0]
    plt.plot(frequencies_a, alplitud_a+delta, label='Potencial')
    plt.title("Periodograma potencial")
    plt.grid()


    plt.tight_layout() # Ajusta el layout para que las subgráficas no se solapen
    plt.savefig(f"random/{L}-{P}-{inh}-{Trest}-{Treltive}.png")
    plt.show()

