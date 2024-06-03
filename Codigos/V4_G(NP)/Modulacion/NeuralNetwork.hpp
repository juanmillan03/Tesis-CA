#pragma once
#include <vector>
#include<iostream>
#include <random>

class NeuralNetwork
{
    private:
        int L2;
        double Trest, Trelative,Alpha,inhibidoras;
        std::vector<std::vector<int>> matrix;
        std::vector<int> AP;// potencial de la neurana
        std::vector<bool> IE;// Tipo de neurona
        std::random_device rd;

    
    public:
        NeuralNetwork(int L,std::vector<std::vector<int>> Matrix,double trest
        ,double trelative, double alpha);
        void Inicio(double inhibidoras);
        enum Estado{Reposo,Activado,hyperpolarizado,refractario};
        Estado Cual_Estado(int ix);
        double Reglas(int ix);
        double Potencial(int ix);
        std::pair<double, double> Paso_temporal();
        void Evolucion();
    
};