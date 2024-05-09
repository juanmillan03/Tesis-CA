#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include "Modulacion/Matrix_conect.hpp"
#include "Modulacion/NeuralNetwork.hpp"




int main(int argc, char* argv[]) {

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Unable to open file input.txt" << std::endl;
        return 1; // Exit the program if the file cannot be opened
    }

    std::vector<double> integers;
    double number;
    while (file >> number) {
        integers.push_back(number);
    }

    file.close();
    int L=integers[0]; // longuitud de la matriz N=L*L 40
    int Q=integers[1]; // Nuneor de conecciones 30
    double Trest=integers[2];//0
    double Trelative=integers[3];// 1   
    double alpha=integers[4];// 0.1
    double tmax=integers[5];//1000
    std::vector<std::vector<int>> matrix= Conecciones(L);
    // Random(matrix,L,Q);// problema
    Random_V2(matrix,L,Q);
    NeuralNetwork Red(L,matrix,Trest,Trelative,alpha);
    Red.Inicio();

    for (int t = 0; t < tmax; t++)
    {
        std::cout<<Red.Paso_temporal().first<<" "<<Red.Paso_temporal().second<<std::endl;
        Red.Evolucion();
    }
    
    return 0;
}

