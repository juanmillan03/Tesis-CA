#pragma once
#include <vector>
#include<iostream>
#include <random>


std::vector<std::vector<int>> Conecciones(int L);
void Random_uni(std::vector<std::vector<int>> & matrix,int L , double P);
void Random_Bi(std::vector<std::vector<int>> & matrix,int L, double P);
