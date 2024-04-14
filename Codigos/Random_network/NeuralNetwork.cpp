#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(int N2,int C){
    AP=new int[N2];
    APNew=new int[N2];
    std::vector<std::vector<int>> Con(C, std::vector<int>(2)); 
    connection_count= std::vector<int>(N2, 0);

    //LLenar todo el vector de contador 
    for (int  ix = 0; ix < C; ix++)
    {
        connection_count[Con[ix][0]]++;
        connection_count[Con[ix][1]]++;
    }
    Connection_per_neuron = new int*[N2];
    for (int ix = 0 ; ix < N2 ; ix++){
        Connection_per_neuron[ix] = new int [connection_count[ix]];
    }





}