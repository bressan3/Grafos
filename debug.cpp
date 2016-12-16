/*
    * Arquivo de testes
    * COMIPLAR USANDO C++ 11: g++ -std=c++11 *.cpp -o bin
*/

#include <iostream>
#include <string>

#include "grafo.h"
#include "corte.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Grafo *g = new Grafo(false);
    
    rodar_guloso();
    
    delete g;
    g = new Grafo(false);
    
    rodar_guloso_rand(g);
    
    delete g;
    g = new Grafo(false);
    
    rodar_guloso_rand_reativo(g);
    
    return 0;
}
