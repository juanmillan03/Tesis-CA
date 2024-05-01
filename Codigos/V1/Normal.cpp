#include<iostream>
#include<fstream>
#include<cmath>
#include <random>
#include "Random64.h"
#include<vector>

const int N=40;
const int N2=N*N;
const int Q=20;
const int C=N2*Q;

const double Trest=3;
const double Trelative=5;
const double alpha=0.1;

class NeuralNetwork{
private :
    std::vector<int> AP, APNew;
    std::vector<std::vector<int>> Connections_per_neuron;
    std::vector <bool> IE;// tipo de neurona 
    std::vector<std::vector<int>> Con; 
    std::vector <int> connection_count;
public :
    NeuralNetwork(void);
    void Start(Crandom & ran64);
    void ConnectionGenerator(void);
    enum state{rest,firing,hyperpolarization,refractory};
    state GetState(int ix);
    double Query(int neu);
    double Potential(int ix);
    double TemporalSeries();
    double ActiveNeurons();
    void Evolve();
};
NeuralNetwork::NeuralNetwork(void){
    AP = std::vector<int>(N2);
    APNew = std::vector<int>(N2);
    Con.resize(C, std::vector<int>(2)); // Assuming C is the number of connections
    IE=std::vector<bool>(N2);
    connection_count=std::vector<int>(N2,0); // Assuming N2 is the number of neurons
    Connections_per_neuron.resize(N2);
    ConnectionGenerator();
    for (int  ix = 0; ix < C; ix++)
    {
        connection_count[Con[ix][0]]++;
        connection_count[Con[ix][1]]++;
    }
    for (int ix=0;ix<N2;ix++)
    {
        Connections_per_neuron[ix].resize(connection_count[ix]);
    }

}

void NeuralNetwork::Start(Crandom & ran64)
{
    double pot,inhib;

    for (int ix = 0; ix < N2; ix++)
    {
        pot=ran64.r();
        if (pot<0.2){AP[ix]=0;}
        else if (pot>=0.2 && pot<0.3){AP[ix]=1;}
        else if (pot>=0.3 && pot<0.4){AP[ix]=2;}
        else if (pot>=0.4 && pot<0.5){AP[ix]=3;}
        else if (pot>=0.5 && pot<0.6){AP[ix]=4;}
        else if (pot>=0.6 && pot<0.65){AP[ix]=5;}
        else if (pot>=0.65 && pot<0.72){AP[ix]=6;}
        else if (pot>=0.72 && pot<0.79){AP[ix]=7;}
        else if (pot>=0.79 && pot<0.86){AP[ix]=8;}
        else if (pot>=0.86 && pot<0.93){AP[ix]=9;}
        else if (pot>=0.93){AP[ix]=10;}
        APNew[ix]=0;
    }
    for (int ix = 0; ix < N2; ix++)
    {
        inhib=ran64.r();
        if(inhib<0.5){IE[ix]=true;}
        else
        {IE[ix]=false;}
    }
    int counter;

    for (int neu = 0; neu < N2; neu++)
    {
        counter=0;
        for (int conex = 0; conex < C; conex++)
        {
            if (Con[conex][0]==neu)
            {
                Connections_per_neuron[neu][counter]=Con[conex][1];
                counter++;
            }
            else if(Con[conex][1]==neu)
            {
                Connections_per_neuron[neu][counter]=Con[conex][0];
                counter++;
            }   
        }   
    }  
}
void NeuralNetwork::ConnectionGenerator(void)
{
    Crandom ranita(9);
    int iran=0;
    int  jran=0;
    int coni=0;
    // excoge una posible coneccion de neurona
    while (coni<C)
    {   
        // ??????
        iran=(int)(ranita.r()*N2);
        jran=(int)(ranita.r()*(N2-1));
        if (jran>=iran)jran++;
        bool Noexistia=true;
        for(int i=0;i<coni;i++)
        {
            if ((Con[i][0]==iran && Con[i][1]==jran)||
                (Con[i][0]==jran&&Con[i][1]==iran))
            {Noexistia=false;break;}
        }
        if(Noexistia)
        {
            Con[coni][0]=iran;Con[coni][1]=jran;
            coni++;
        }   
    }
}

NeuralNetwork::state NeuralNetwork::GetState(int ix)
{
    state S;
    if(AP[ix]==0) S=rest;
    else if(1<=AP[ix] && AP[ix]<=4)S=firing;
    else if(AP[ix]==5)S=hyperpolarization;
    else if(6<=AP[ix] && AP[ix]<=10)S=refractory;
    return S;
}


double NeuralNetwork::Query(int neu){

    state Sconexion, Svecino;
    /* contador para saber cuantos vecinos son 
    Ce (neuronas excitatoriasactivas) ,
    cuantos son Ci (neuranas inhibitoriasactivas) y cuantos Ch
    hiperpolarizado
    */
    double Ca,Ce,Ci,Ch; 
    Ca=Ce=Ci=Ch=0.0;

    for (int  conex = 0;conex< connection_count[neu]; conex++)
    {
        Sconexion=GetState(Connections_per_neuron[neu][conex]);
        if (Sconexion==firing)
        {
            if (IE[conex]==true){Ci++;}//se puregunta que tipo de neurona es ya SABIENDO SI ESTA activada 
            else {Ce++;}
        }
        else if (Sconexion==hyperpolarization){Ch++;}       
    }
    for (int vecina = 1; vecina <=2 ; vecina++)
    {
        // influencia de las neruanas vecinas proximas 
        int vecina_dera =(neu+vecina)%N2;
        int vecina_izqui=(neu+N2-vecina)%N2;
        Svecino=GetState(Connections_per_neuron[neu][vecina_dera]);
        if (Svecino==firing)
        {
            if (IE[vecina_dera]==true){Ci++;}//se puregunta que tipo de neurona es ya SABIENDO SI ESTA activada 
            else {Ce++;}
        }
        else if (Sconexion==hyperpolarization){Ch++;} 
        Svecino=GetState(Connections_per_neuron[neu][vecina_izqui]);
        if (Svecino==firing)
        {
            if (IE[vecina_izqui]==true){Ci++;}//se puregunta que tipo de neurona es ya SABIENDO SI ESTA activada 
            else {Ce++;}
        }
        else if (Sconexion==hyperpolarization){Ch++;}   
    }
    Ca=Ce-Ci-alpha*Ch;// regla de activacion
    return Ca;
}


double NeuralNetwork::Potential(int ix)
{
    double pote=0.0;

    state St= GetState(ix);
    if (St==rest){pote=-70;}
    else if (St==firing){pote=40;}
    else if (St==hyperpolarization){pote=-90;}
    else if (St==refractory){pote=-75;}
    return pote; //se puede hacer que el activado tenga diferentes niveles de 

}


double NeuralNetwork::TemporalSeries()
{
    double y_t=0;
    int butter_order=1;
    for (int ix = 0; ix < N2; ix++)
    {
        y_t+=Potential(ix);

    }
    return ActiveNeurons();
}

double NeuralNetwork::ActiveNeurons()
{
    state Sa;
    double Ca=0;
    for (int ix = 0; ix < N2; ix++)
    {
        Sa=GetState(ix);
        if(Sa==firing){Ca++;}
    }
    return Ca;
}
void NeuralNetwork::Evolve()
{
    state St;
    double Ct=0;
    std::vector<int> Aux(N2);
    for (int ix = 0; ix < N2; ix++)
    {
        St=GetState(ix);
        if (St==rest)
        {
            Ct==Query(ix);
            if(Ct>=Trest)
            APNew[ix]=AP[ix]+1;
            else APNew[ix]=0;
        }
        else if (St==firing || St==hyperpolarization)
        {
            APNew[ix]=AP[ix]+1;
        }
        else if (St == refractory)
        {
            Ct=Query(ix);
            if(Ct<Trelative)APNew[ix]=AP[ix];
            else if (Ct>=Trelative)
            {
                if(AP[ix]==10)APNew[ix]=0;
                else APNew[ix]=AP[ix]+1;
            }
        } 
    }
    Aux=AP; AP=APNew;APNew=Aux;
}

int main(void)
{
    NeuralNetwork Red;
    Crandom ran64(1);
    int t=0,tmax=1000;
    Red.Start(ran64);
    for ( t = 0; t < tmax; t++)
    {
        std::cout<<Red.TemporalSeries()<<std::endl;
        Red.Evolve();
        
    }
    return 0;
}
