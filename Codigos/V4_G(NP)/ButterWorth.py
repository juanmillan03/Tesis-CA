import sys
import matplotlib.pyplot as plt
import numpy as np
import heapq
from scipy.stats import poisson 
import seaborn as sns
from scipy.signal import butter, filtfilt,welch


if __name__ == "__main__":
    
    L,P,inh,Trest,Treltive,apha,t=np.loadtxt("input.txt")
    
    low_cutoff = 0.5  # Low cut-off frequency (Hz)
    high_cutoff = 50.0  # High cut-off frequency (Hz)
    order = 4  # Order of the filter
    sampling_rate = 400  # Example sampling rate in Hz

    # Create the Butterworth band-pass filter
    b, a = butter(order, [low_cutoff / (0.5 * sampling_rate), high_cutoff / (0.5 * sampling_rate)], btype='band')

    data = np.loadtxt("data.dat")[50:,:]
    filtered_data_a = filtfilt(b, a, data[:,0])
    filtered_data_b = filtfilt(b, a, data[:,1])
        
    
    NFFT = 256
    OVERLAP = NFFT/2 # Time scale
    dt = 1.0 / 100.0 # Sampling rate
    fs = 1.0 / dt # Frequency scale



    # Calcular la PSD usando el método de Welch
    frequencies_a, psd_a = welch(filtered_data_a, fs, nperseg=fs*4)
    alplitud_a=np.zeros_like(psd_a)
    # Imprimir los resultados
    for i in range(len(frequencies_a)):
        alplitud_a[i]=10 * np.log10(psd_a[i])
    
    frequencies_b, psd_b = welch(filtered_data_b, fs, nperseg=fs*4)
    alplitud_b=np.zeros_like(psd_b)
    # Imprimir los resultados
    for i in range(len(frequencies_b)):
        alplitud_b[i]=10 * np.log10(psd_b[i])


    reales=np.loadtxt("real.txt")[:1000]
    f_reales, psd_reales = welch(reales, fs, nperseg=fs*4)
    alplitud_rea=np.zeros_like(psd_reales)
    # Imprimir los resultados
    for i in range(len(f_reales)):
        alplitud_rea[i]=10 * np.log10(psd_reales[i])
    

    fig = plt.figure(figsize=(9, 6),num=f"L{L}p{P}in{inh}tr{Trest}te{Treltive}")
    
    plt.subplot(3, 3, 1)
    plt.plot(data[:,0], label='# Activadas')
    plt.title("#Activadas")
    plt.grid()
    
    plt.subplot(3, 3, 4)
    plt.plot(data[:,1], label='Potencial')
    plt.title("Potencial")
    plt.grid()
    

    plt.subplot(3, 3, 2)
    plt.plot(filtered_data_a, label='Filtro butter Activadas')
    plt.title("Filtro butter Activadas")
    plt.grid()


    plt.subplot(3, 3, 5)
    plt.plot(filtered_data_b, label='Filtro butter potencial')
    plt.title("Filtro butter potencial")
    plt.grid()
    
    plt.subplot(3, 3, 3)
    plt.plot(frequencies_a, alplitud_a, label='Potencial')
    plt.title("Periodograma activadas")
    plt.grid()
    
    plt.subplot(3, 3, 6)
    plt.plot(frequencies_b, alplitud_b, label='Potencial')
    plt.title("Periodograma potencial")
    plt.grid()
    
    plt.subplot(3, 3, 8)
    plt.plot(reales, label='reales')
    plt.title("Real")
    plt.grid()
    
    plt.subplot(3, 3, 9)
    plt.plot(f_reales, alplitud_rea, label='real')
    plt.title("Periodograma reales")
    plt.grid()
    

    plt.tight_layout() # Ajusta el layout para que las subgráficas no se solapen
    #plt.savefig(f"random/{L}-{P}-{inh}-{Trest}-{Treltive}.png")
    plt.show(block=False)
    plt.pause(0.001)
    
        
    fig2 = plt.figure(figsize=(9, 6),num=f"Bandas_L{L}p{P}in{inh}tr{Trest}te{Treltive}")
    
    plt.subplot(3, 2, 1)
    D_low, D_high = 0.1, 4
    delta_r = alplitud_rea[np.logical_and(f_reales >= D_low, f_reales <= D_high)]
    delta_b = alplitud_b[np.logical_and(frequencies_b >= D_low, frequencies_b <= D_high)]
    delta_a = alplitud_a[np.logical_and(frequencies_a >= D_low, frequencies_a <= D_high)]
    plt.boxplot([delta_r,delta_a,delta_b],labels=['Real', 'Activadas',"potencial"])
    plt.grid()
    plt.title('Banda Delta (0-4)Hz')
    
    plt.subplot(3, 2, 2)
    th_low, th_high = 4, 8
    theta_r = alplitud_rea[np.logical_and(f_reales > th_low, f_reales <= th_high)]
    theta_b = alplitud_b[np.logical_and(frequencies_b > th_low, frequencies_b <= th_high)]
    theta_a = alplitud_a[np.logical_and(frequencies_a > th_low, frequencies_a <= th_high)]
    plt.boxplot([theta_r,theta_a,theta_b],labels=['Real', 'Activadas',"potencial"])
    plt.grid()
    plt.title('Banda Thta (4-8)Hz')
    

    plt.subplot(3, 2, 3)
    Al_low, Al_high = 8, 12
    Al_r = alplitud_rea[np.logical_and(f_reales > Al_low, f_reales <= Al_high)]
    Al_b = alplitud_b[np.logical_and(frequencies_b > Al_low, frequencies_b <= Al_high)]
    Al_a = alplitud_a[np.logical_and(frequencies_a > Al_low, frequencies_a <= Al_high)]
    plt.boxplot([Al_r,Al_a,Al_b],labels=['Real', 'Activadas',"potencial"])
    plt.grid()
    plt.title('Banda Alpha (8-12)Hz')


    plt.subplot(3, 2, 4)
    sig_low, sig_high = 12, 16
    sig_r = alplitud_rea[np.logical_and(f_reales > sig_low, f_reales <= sig_high)]
    sig_b = alplitud_b[np.logical_and(frequencies_b > sig_low, frequencies_b <= sig_high)]
    sig_a = alplitud_a[np.logical_and(frequencies_a > sig_low, frequencies_a <= sig_high)]
    plt.boxplot([sig_r,sig_a,sig_b],labels=['Real', 'Activadas',"potencial"])
    plt.grid()
    plt.title('Banda Sigma (12-16)Hz')
    
    plt.subplot(3, 2, 5)
    be_low, be_high = 16, 24
    be_r = alplitud_rea[np.logical_and(f_reales > be_low, f_reales <= be_high)]
    be_b = alplitud_b[np.logical_and(frequencies_b > be_low, frequencies_b <= be_high)]
    be_a = alplitud_a[np.logical_and(frequencies_a > be_low, frequencies_a <= be_high)]
    plt.boxplot([be_r,be_a,be_b],labels=['Real', 'Activadas',"potencial"])
    plt.grid()
    plt.title('Banda Beta (16-24)Hz')
    
    plt.subplot(3, 2, 6)
    gam_low, gam_high = 24, 30
    gam_r = alplitud_rea[np.logical_and(f_reales > gam_low, f_reales <= gam_high)]
    gam_b = alplitud_b[np.logical_and(frequencies_b > gam_low, frequencies_b <= gam_high)]
    gam_a = alplitud_a[np.logical_and(frequencies_a > gam_low, frequencies_a <= gam_high)]
    plt.boxplot([be_r,be_a,be_b],labels=['Real', 'Activadas',"potencial"])
    plt.grid()
    plt.title('Banda Gamma (24-30)Hz')
    
    plt.tight_layout() # Ajusta el layout para que las subgráficas no se solapen
    plt.show(block=False)
    plt.pause(0)    
    

