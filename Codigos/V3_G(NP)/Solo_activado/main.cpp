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
    std::ofstream outfile;
    outfile.open("matriz.dat");
    int L=integers[0]; // longuitud de la matriz N=L*L 40
    double P=integers[1]; // probailidad de conexion 0.1
    double inhibidoras=integers[2]; // 0.4

    double Trest=integers[3];//0
    double Trelative=integers[4];// 1   
    
    double alpha=integers[5];// 0.1
    double tmax=integers[6];//1000
    
    std::vector<std::vector<int>> matrix= Random_bi(L,P);

    NeuralNetwork Red(L,matrix,Trest,Trelative,alpha);
    Red.Inicio(inhibidoras);
    std::vector<double> Conecciones(L*L);
    int unos=0;
    for (int i = 0; i < L*L; i++) {
        Conecciones[i]=0;
        for (int j = 0; j < L*L; j++) {
            outfile << matrix[i][j] << " ";
            if(matrix[i][j]==1)unos++;
            if(matrix[i][j]==1)Conecciones[i]++;
        }
        outfile<< std::endl;
    }
    outfile.close();

    for (int t = 0; t < tmax; t++)
    {
        std::cout<<Red.Paso_temporal().first<<" "<<Red.Paso_temporal().second<<std::endl;
        Red.Evolucion();
    }

    return 0;
}

