#include "Matrix_conect.hpp"


std::vector<std::vector<int>> Conecciones(int L){
    std::vector<std::vector<int>> Matix (L*L,std::vector<int>(L*L,0));

    for (int i = 0; i<L; i++)
    {   
        for (int j = 0; j < L; j++)
        {
            int ia=i,ji=j,id=i,jd=j;
            if (ia+1==L)ia=-1;
            if (id==0)id=L;
            if (jd+1==L)jd=-1;
            if (ji==0)ji=L;
            Matix[i*L+j][i*L+jd+1]=1;// derecha
            Matix[i*L+j][i*L+ji-1]=1;// izquieda
            Matix[i*L+j][(ia+1)*L+j]=1;// arriba 
            Matix[i*L+j][(id-1)*L+j]=1;// Abajo         
        }
    }
    return Matix;
}
void Random(std::vector<std::vector<int>> & matrix,int L, int Q){
    std::random_device rd;
    std::mt19937 gen(1); // Mersenne Twister 19937
    std::uniform_int_distribution<> dis(0,(L*L)-1);
    for (int Neu = 0; Neu<Q*L*L; Neu++)
    {
        int neurona=dis(gen),conexion=dis(gen);
        if (neurona==conexion || matrix[neurona][conexion]==1)Neu=Neu-1;
        else matrix[neurona][conexion]=1;
    }
}
void Random_V2(std::vector<std::vector<int>> & matrix,int L, int Q){
    std::random_device rd;
    std::mt19937 gen(1); // Mersenne Twister 19937
    std::uniform_int_distribution<> dis(0,(L*L)-1);
    for (int Neu = 0; Neu<Q*Q; Neu++)
    {
        int neurona=dis(gen),conexion=dis(gen);
        if (neurona==conexion || matrix[neurona][conexion]==1)Neu=Neu-1;
        else 
        {
            matrix[neurona][conexion]=1;
            matrix[conexion][neurona]=1;
        }
    }
}
