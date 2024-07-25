#include "NeuralNetwork.hpp"


NeuralNetwork::NeuralNetwork(int L, std::vector<std::vector<int>> Matrix, double trest
,double trelative, double alpha)
{
    Trest=trest;
    Trelative=trelative; 
    Alpha=alpha;
    L2=L*L;
    matrix=Matrix;
    AP=std::vector<int>(L2);
    IE= std::vector<bool>(L2);
}

void NeuralNetwork::Inicio(){

    double potencial;
    std::mt19937 gen(1); // Mersenne Twister 19937
    std::uniform_real_distribution<> pot(0.0,1.0);
    for (int ix = 0; ix < L2; ix++)
    {
        double potencial =pot(gen);
        if (potencial<0.2){AP[ix]=0;}
        else if (potencial>=0.2 && potencial<0.3){AP[ix]=1;}
        else if (potencial>=0.3 && potencial<0.4){AP[ix]=2;}
        else if (potencial>=0.4 && potencial<0.5){AP[ix]=3;}
        else if (potencial>=0.5 && potencial<0.6){AP[ix]=4;}
        else if (potencial>=0.6 && potencial<0.65){AP[ix]=5;}
        else if (potencial>=0.65 && potencial<0.72){AP[ix]=6;}
        else if (potencial>=0.72 && potencial<0.79){AP[ix]=7;}
        else if (potencial>=0.79 && potencial<0.86){AP[ix]=8;}
        else if (potencial>=0.86 && potencial<0.93){AP[ix]=9;}
        else if (potencial>=0.93){AP[ix]=10;}  
    } 
}
NeuralNetwork::Estado NeuralNetwork::Cual_Estado(int ix){
    Estado S;
    if(AP[ix]==0) S=Reposo;
    else if(1<=AP[ix] && AP[ix]<=4)S=Activado;
    else if(AP[ix]==5)S=hyperpolarizado;
    else if(6<=AP[ix] && AP[ix]<=10)S=refractario;
    return S;   
}
double NeuralNetwork::Reglas(int ix){
    Estado Sconexion, Svecino;
    /* contador para saber cuantos vecinos son 
    Ce (neuronas excitatoriasactivas) ,
    cuantos son Ci (neuranas inhibitoriasactivas) y cuantos Ch
    hiperpolarizado
    */
    double Ca,Ce,Ci,Ch; 
    Ca=Ce=Ci=Ch=0.0;

    // Va a ver que conexiones tiene la neurona ix
    for (int i = 0; i < L2; i++)
    {
        if (matrix[ix][i]==1 || matrix[ix][i]==-1)
        {
            Sconexion=Cual_Estado(i);
            if (Sconexion==Activado)
            {
                if (matrix[ix][i]==-1)Ci++;//se puregunta que tipo de neurona 
                else Ce++;
            }
            else if (Sconexion==hyperpolarizado)
            {
                Ch++;
            }
        }
    }
    Ca=Ce-Ci-Alpha*Ch;// regla de activacion
    return Ca;
}

double NeuralNetwork::Potencial(int ix){
    double potencial =0.0;
    Estado St= Cual_Estado(ix);
    if (St==Reposo){potencial=-70;}
    else if (St==Activado)
    {
        switch (AP[ix])
        {
        case 1:
            potencial=15;
            break;
        case 2:
            potencial=30;
            break;
        case 3:
            potencial=30;
            break;
        case 4:
            potencial=15;
            break;
        }    
    }
    else if (St==hyperpolarizado){potencial=-90;}
    else if (St==refractario){potencial=-75;}
    return potencial;
}
std::pair<double, double> NeuralNetwork::Paso_temporal(){
    double potencial_t=0.0,Ca=0;
    Estado Sa;
    for (int ix = 0; ix < L2; ix++)
    {
        potencial_t+=Potencial(ix);
        Sa = Cual_Estado(ix);
        if (Sa==Activado)Ca++;
    }
    return std::make_pair(Ca,potencial_t);
}

void NeuralNetwork::Evolucion(){

    Estado St;
    std::vector<int> Aux(L2,0);
    for (int ix = 0; ix < L2; ix++)
    {
        St=Cual_Estado(ix);
        if (St==Reposo)
        {
            if (Reglas(ix)>=Trest)Aux[ix]=AP[ix]+1;
            else Aux[ix]=0; 
        }
        else if (St==Activado||St==hyperpolarizado)
        {
            Aux[ix]=AP[ix]+1;
        }
        else if(St==refractario)
        {
            if(Reglas(ix)>=Trelative)Aux[ix]=1;
            else
            {
                if(AP[ix]==10)Aux[ix]=0;
                else Aux[ix]=AP[ix]+1;
            }
        }
    }
    AP=Aux;
}