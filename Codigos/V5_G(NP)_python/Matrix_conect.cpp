#include "Matrix_conect.hpp"
std::vector<std::vector<int>> Regular_1(int L, double Inh){
    std::vector<std::vector<int>> Matrix (L*L,std::vector<int>(L*L,0));
    std::random_device rd;
    std::mt19937 gen(1);
    std::uniform_real_distribution<>inh(0.0,1.0);
    double I;
    for (int i = 0; i<L; i++)
    {   
        for (int j = 0; j < L; j++)
        {
            
            int ia=i,ji=j,id=i,jd=j;
            if (ia+1==L)ia=-1;
            if (id==0)id=L;
            if (jd+1==L)jd=-1;
            if (ji==0)ji=L;
            I=inh(gen);if(I<Inh)I=0;else I=1;
            Matrix[i*L+j][i*L+jd+1]=1*(2*I-1);// derecha I=0 -1,I=1 1
            I=inh(gen);if (I<Inh)I=0;else I=1;
            Matrix[i*L+j][i*L+ji-1]=-1*(2*I-1);// izquieda
            I=inh(gen);if (I<Inh)I=0;else I=1;
            Matrix[i*L+j][(ia+1)*L+j]=-1*(2*I-1);// arriba 
            I=inh(gen);if (I<Inh)I=0;else I=1;
            Matrix[i*L+j][(id-1)*L+j]=-1*(2*I-1);// Abajo         
        }
    }
    return Matrix;
}


std::vector<std::vector<int>> small_word_uni(int L, double P, double Inh){
    std::vector<std::vector<int>> matrix= Regular_1(L, Inh);
    std::random_device rd;
    std::mt19937 gen(1); // Mersenne Twister 19937
    std::uniform_real_distribution <>dis(0,1);
    for (int i = 0; i<L*L; i++)
    {
        for (int j = 0; j<L*L; j++)
        {
            if ((i!=j && (matrix[i][j]!=1 || matrix[i][j]!=-1)) && dis(gen)<P)
            {
                matrix[i][j]=1;
            }
        }
    }
    return matrix;
}
std::vector<std::vector<int>> small_word_Bi(int L, double P, double Inh){
    std::vector<std::vector<int>> matrix= Regular_1(L,Inh);
    std::random_device rd;
    std::mt19937 gen(1); // Mersenne Twister 19937
    std::uniform_real_distribution <>dis(0.0,1.0);
    std::uniform_int_distribution <>neu(0,L*L-1);
    int jj;
    for (int i = 0; i < L*L; i++)
    {
        for (int j = 0; j < L*L; j++)
        {
            if (matrix[i][j]==1 && dis(gen)<P)
            {
                matrix[i][j]=0;
                matrix[j][i]=0;
                jj=neu(gen);
                if (jj==i || jj==j)
                {
                    jj=neu(gen);
                    matrix[jj][i]=2;
                    matrix[i][jj]=2;
                }
                else{
                    matrix[jj][i]=2;
                    matrix[i][jj]=2;
                }
            }
            if (matrix[i][j]==-1 && dis(gen)<P)
            {
                matrix[i][j]=0;
                matrix[j][i]=0;
                jj=neu(gen);
                if (jj==i || jj==j)
                {
                    jj=neu(gen);
                    matrix[jj][i]=-2;
                    matrix[i][jj]=-2;
                }
                else{
                    matrix[jj][i]=-2;
                    matrix[i][jj]=-2;
                }
            }
        }
    }
    for (int i = 0; i < L*L; i++)
    {
        for (int j = 0; j < L*L; j++)
        {
            if (matrix[i][j]==2)
            {
                matrix[i][j]=1;
                matrix[j][i]=1;
            }
            if (matrix[i][j]==-2)
            {
                matrix[i][j]=-1;
                matrix[j][i]=-1;
            }
        }
    }
    return matrix;
}
std::vector<std::vector<int>> Random_bi(int L, double P, double Inh){
    std::vector<std::vector<int>> matrix (L*L,std::vector<int>(L*L,0));
    std::random_device rd;
    std::mt19937 gen(1); // Mersenne Twister 19937
    std::uniform_real_distribution <>dis(0.0,1.0);
    std::uniform_real_distribution<>inh(0.0,1.0);
    double I;
    for (int i = 0; i < L*L; i++)
    {
        for (int j = 0; j < L*L; j++)
        {
            I=inh(gen);
            if (I<Inh)I=0;
            else I=1;
            if (i!=j && (matrix[i][j]!=1 || matrix[i][j]!=-1) && dis(gen)<P)
            {
                matrix[i][j]=-1*(2*I-1);
                matrix[j][i]=-1*(2*I-1);
            }
        }
    }
    return matrix;
}
std::vector<std::vector<int>> Random_uni(int L, double P, double Inh){
    std::vector<std::vector<int>> matrix (L*L,std::vector<int>(L*L,0));
    std::random_device rd;
    std::mt19937 gen(1); // Mersenne Twister 19937
    std::uniform_real_distribution <>dis(0.0,1.0);
    std::uniform_real_distribution<>inh(0.0,1.0);
    double I;
    for (int i = 0; i < L*L; i++)
    {
        for (int j = 0; j < L*L; j++)
        {
            I=inh(gen);
            if (I<Inh)I=0;
            else I=1;
            if (i!=j && (matrix[i][j]!=1 || matrix[i][j]!=-1) && dis(gen)<P)
            {
                matrix[i][j]=-1*(2*I-1);
            }
        }
    }
    return matrix;
}

    
