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
const double alpha= 0.1; // hyperpolarization coefficient


const double factor_cell_hini=0.5;// idea de TDAH

NeuralNetwork neurona(N2,C);





