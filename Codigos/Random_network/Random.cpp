#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Random64.h"
#include "NeuralNetwork.hpp"

const int N=40;// Tamaño cuadrticula NxN
const int N2=N*N;
const int Q=20; // numero de synapsis por cell(no constante)
const int C=N2*Q;// Numero de conecciones en el sistema 


const double Trest=3;// rest threshold reposo 
const double Trelative=5;//  threshold refractante 
const double Alpha= 0.1; // hyperpolarization coefficient


const double factor_cell_hini=0.5;// idea de TDAH

int main(void)
{
    NeuralNetwork Red(N2,C,Alpha,Trest,Trelative);
    int t=0,tmax=1000;
    Red.Estado_inicial();
    for(t=0;t<tmax;t++)
    {
        Red.evolucion();
        if(t>30){std::cout<<Red.Serie_temportal()<<std::endl;}
    }
    return 0;
}






