#include <random>
#include <iostream>

int main(void)
{
  //std::random_device rd; // inicializacion con semilla aleatoria
  //std::mt19937 gen(rd()); // genera bits aleatorios
  std::mt19937 gen(1);
  std::uniform_real_distribution<> dis(0, 1); // distribucion
  for(int n = 0; n < 1600; ++n){
    int C;
    double pot=dis(gen);
    if (pot<0.2)C=0;
    else if (pot>=0.2 && pot<0.3)C=1;
    else if (pot>=0.3 && pot<0.4)C=2;
    else if (pot>=0.4 && pot<0.5)C=3;
    else if (pot>=0.5 && pot<0.6)C=4;
    else if (pot>=0.6 && pot<0.65)C=5;
    else if (pot>=0.65 && pot<0.72)C=6;
    else if (pot>=0.72 && pot<0.79)C=7;
    else if (pot>=0.79 && pot<0.86)C=8;
    else if (pot>=0.86 && pot<0.93)C=9;
    else if (pot>=0.93){C=10;}
    std::cout<<C<<std::endl;
  }
  for (size_t i = 0; i < count; i++)
  {
    /* code */
  }
  
}