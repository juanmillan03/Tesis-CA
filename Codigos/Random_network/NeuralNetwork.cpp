#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(int n2,int c){
    C=c;N2=n2;
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
NeuralNetwork::~NeuralNetwork(void){

    delete[]AP;
    delete[]APNew;
    for (int ix = 0; ix < std::sqrt(N2); ix++)
    {
        delete[]Connection_per_neuron[ix];
    }
    delete[ ] Connection_per_neuron ;
}
void NeuralNetwork::Estado_inicial(Crandom &ran64){

    double potencial,inhibidora;

    /* genera la matriz que asigna 
    los phi(potencial) estados*/
    for (int ix = 0; ix < N2; ix++)
    {
        potencial=ran64.r();
        /*Nrest=20%, Nfiring=40%, Nrefractory=35% and
        Nhyperpolarization = 5%.*/ 
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
        APNew[ix]=0;

    }
    //ahora la eleccion de inhibidora o exitadora 
    for (int ix = 0; ix < N2; ix++)
    {
        inhibidora=ran64.r();
        if(inhibidora<0.5){IE[ix]=true;}
        else
        {IE[ix]=false;}
    }
    int contador;

    for (int neu = 0; neu < N2; neu++)
    {
        contador=0;
        for (int conexiones = 0; conexiones < C; conexiones++)
        {
            if (Con[conexiones][0]==neu)
            {
                Connection_per_neuron[neu][contador]=Con[conexiones][1]++;
                contador++;
            }
            else if(Con[conexiones][1]==neu)
            {
                Connection_per_neuron[neu][contador]=Con[conexiones][0]++;
                contador++;
            }   
        }   
    }
}

void NeuralNetwork::Generador_coneciones(void)
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
            {
                Noexistia=false;break;
            }
            if(Noexistia)
            {
                Con[coni][0]=iran;Con[coni][1]=jran;
                coni++;
            }
        }   
    }
}
NeuralNetwork::Estado NeuralNetwork::Get_estado(int ix)
{
    Estado S;
    if(AP[ix]==0) S=reposo;
    else if(1<=AP[ix] && AP[ix]<=4)S=activado;
    else if(1<=AP[ix] && AP[ix]<=4)S=activado;
    else if(AP[ix]==5)S=hyperpolarizado;
    else if(6<=AP[ix] && AP[ix]<=10)S=activado;



}