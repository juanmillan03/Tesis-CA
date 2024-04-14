#include <iostream>
#include<vector>
<<<<<<< HEAD
=======
#include "Random64.h"
>>>>>>> 0a8f7e7093af1ad9c6c3ed83b4e9a7ae85d18554

int main(){
    int variable = 169;
    int *pointer1 = &variable;
    int **pointer2 = &pointer1;
<<<<<<< HEAD

    int C[2][2];
    std::cout << "Valor de variable: " << C[0][0] << "\n";
    std::cout << "Valor de variable usando un puntero simple: " << *pointer1 << "\n";
    std::cout << "Valor de variable usando un puntero doble: " << **pointer2 << "\n";
=======
    Crandom ranita(100);
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Valor de variable: " << ranita.r()<< "\n";
 
    }
    

    // int C[2][2];
    // std::cout << "Valor de variable: " << C[0][0] << "\n";
    // std::cout << "Valor de variable usando un puntero simple: " << *pointer1 << "\n";
    // std::cout << "Valor de variable usando un puntero doble: " << **pointer2 << "\n";
>>>>>>> 0a8f7e7093af1ad9c6c3ed83b4e9a7ae85d18554
    

    return 0;

}
