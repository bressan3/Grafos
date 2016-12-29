/*
    * COMIPLAR USANDO C++ 11: g++ -std=c++11 *.cpp -o bin
*/

#include <iostream>
#include <string>

#include "grafo.h"
#include "corte.h"

using namespace std;

int main(int argc, char const *argv[])
{
    rodar_guloso();
    
    rodar_guloso_rand();
    
    rodar_guloso_rand_reativo();
    
    return 0;
}
