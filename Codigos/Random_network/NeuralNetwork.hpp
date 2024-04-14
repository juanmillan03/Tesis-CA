#pragma once
#include <vector>
#include "Random64.h"
class NeuralNetwork{
    private:
    int N2,C;
    double Alpha;
    int *AP, *APNew;// Powwr vector
    int **Connection_per_neuron; // Matriz de connecciones 
    std::vector <bool> IE;// tipo de neurona 
    std::vector<std::vector<int>> Con; 
    std::vector <int> connection_count;
    public:
    NeuralNetwork(int n2,int c,double alpha);
    ~NeuralNetwork(void);
    void Estado_inicial(Crandom &ran64); /* genera la matriz que asigna 
    los phi(potencial) estados y tipo de neurona inhibidora o excitadora */
    void Generador_coneciones(void);// coneciones random 
    enum Estado{reposo,activado, hyperpolarizado,refractario};// que estado esta 
    Estado Get_estado(int ix);// en que estado esta la neurona segun su potencial phi
    double Consulta(int neu);// en que estados estan las vecinas y las suma
    double Potencial(int ix); // traduce los estados a un potencial fisico
    double Serie_temportal();// suma de potenciales en un tiempo t
    double Activas();// numero de neuronas activas en un tiempo t
    void evolucion();// evolucion temporal 
    

        
};