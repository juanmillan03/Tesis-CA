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
    std::vector<double> Conecciones(L*L);
    int unos=0;
    for (int i = 0; i < L*L; i++) {
        Conecciones[i]=0;
        for (int j = 0; j < L*L; j++) {
            std::cout << matrix[i][j] << " ";
            if(matrix[i][j]==1)unos++;
            if(matrix[i][j]==1)Conecciones[i]++;
        }
        std::cout << std::endl;
    }
    double promedio=0;
    for (int i = 0; i < L*L; i++)
    {
       promedio=promedio+Conecciones[i]/(L*L); 
    }
    
    std::cout<<"conexiones por neurna="<<promedio<< std::endl;
    std::cout<<"conexiones/posibles conexiones= "<<(unos)/(double)(L*L*(L*L-1))*100<< std::endl;
    
    return 0;
}

