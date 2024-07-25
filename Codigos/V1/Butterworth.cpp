#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// Función para leer el contenido de un archivo en un vector de strings
bool getFileContent(const std::string& filename, std::vector<std::string>& vecOfStr) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        vecOfStr.push_back(line);
    }
    file.close();
    return true;
}

int main() {
    // Definición del filtro de paso banda de orden 4
    const int order = 4; // 4to orden (=2 biquads)
    std::cout<<order<<" ";
    
    Iir::Butterworth::BandPass<order> filter;

    // // Configuración del filt   ro
    // const float samplingRate = 500.0; // Hz
    // const float lowCutoffFrequency = 1.0; // Hz
    // const float highCutoffFrequency = 50.0; // Hz
    // filter.setup( samplingRate, lowCutoffFrequency, highCutoffFrequency);

    // // Lectura de datos del archivo
    // std::vector<std::string> vecOfStr;
    // bool result = getFileContent("salida.dat", vecOfStr);


    // if (!result) {
    //     std::cerr << "Error al leer el archivo." << std::endl;
    //     return 1;
    // }


    // // Conversión de datos a enteros
    // std::vector<int> Data(vecOfStr.size());
    // for (size_t i = 0; i < vecOfStr.size(); ++i) {
    //     Data[i] = std::stoi(vecOfStr[i]);
    // }

    // // Aplicación del filtro a los datos de entrada
    // std::vector<double> outputSignal(Data.size());
    // for (size_t i = 0; i < Data.size(); ++i) {
    //     outputSignal[i] = filter.filter(static_cast<double>(Data[i]));
    // }

    // // Impresión de la salida filtrada
    // for (const auto& value : outputSignal) {
    //     std::cout << value << std::endl;
    // }
    return 0;
}
