#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include <random>
#include "Matrix_conect.hpp"


int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " L P Inh matrix_type" << std::endl;
        return 1;
    }

    int L = std::stoi(argv[1]);
    double P = std::stod(argv[2]);
    double Inh = std::stod(argv[3]);
    std::string matrix_type = argv[4];

    std::vector<std::vector<int>> matrix;

    if (matrix_type == "regular") {
        matrix = Regular_1(L, Inh);
    } else if (matrix_type == "small_word_uni") {
        matrix = small_word_uni(L, P, Inh);
    } else if (matrix_type == "small_word_Bi") {
        matrix = small_word_Bi(L, P, Inh);
    } else if (matrix_type == "random_bi") {
        matrix = Random_bi(L, P, Inh);
    } else if (matrix_type == "random_uni") {
        matrix = Random_uni(L, P, Inh);
    } else {
        std::cerr << "Tipo de matriz desconocido: " << matrix_type << std::endl;
        return 1;
    }

    // Imprimir la matriz
    for (const auto& row : matrix) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}