#include <iostream>
#include<vector>
#include "Random64.h"

int main(){
    int variable = 169;
    int *pointer1 = &variable;
    int **pointer2 = &pointer1;
    Crandom ranita(100);
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Valor de variable: " << ranita.r()<< "\n";
 
    }
    

    // int C[2][2];
    // std::cout << "Valor de variable: " << C[0][0] << "\n";
    // std::cout << "Valor de variable usando un puntero simple: " << *pointer1 << "\n";
    // std::cout << "Valor de variable usando un puntero doble: " << **pointer2 << "\n";
    

    return 0;

}
