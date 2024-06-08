#include <random>
#include <iostream>

int main(void)
{
  //std::random_device rd; // inicializacion con semilla aleatoria
  //std::mt19937 gen(rd()); // genera bits aleatorios
  std::mt19937 gen(1);
  std::uniform_int_distribution<> dis(0, 1); // distribucion
  for(int n = 0; n < 3; ++n){
    std::cout<<dis(gen)<<" ";
    std::cout<<dis(gen)<<" ";
    std::cout<<std::endl;
  }
  
  
}