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
void Random_uni(std::vector<std::vector<int>> & matrix,int L, double P){
    std::random_device rd;
    std::mt19937 gen(1); // Mersenne Twister 19937
    std::uniform_real_distribution <>dis(0,1);
    for (int i = 0; i<L*L; i++)
    {
        for (int j = 0; j<L*L; j++)
        {
            if ((i!=j && matrix[i][j]!=1) && dis(gen)<P)
            {
                matrix[i][j]=1;
            }
        }
    }
}
void Random_Bi(std::vector<std::vector<int>> & matrix,int L, double P){
    std::random_device rd;
    std::mt19937 gen(1); // Mersenne Twister 19937
    std::uniform_real_distribution <>dis(0.0,1.0);
    for (int i = 0; i < L*L; i++)
    {
        for (int j = 0; j < L*L; j++)
        {
            if (i!=j && matrix[i][j]!=1 && dis(gen)<P)
            {
                matrix[i][j]=1;
                matrix[j][i]=1;
            }
        }
    }
}
