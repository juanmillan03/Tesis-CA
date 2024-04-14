#include <iostream>
#include<vector>

int main(){
    int variable = 169;
    int *pointer1 = &variable;
    int **pointer2 = &pointer1;

    int C[2][2];
    std::cout << "Valor de variable: " << C[0][0] << "\n";
    std::cout << "Valor de variable usando un puntero simple: " << *pointer1 << "\n";
    std::cout << "Valor de variable usando un puntero doble: " << **pointer2 << "\n";
    

    return 0;

}
