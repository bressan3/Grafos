/*
    * Arquivo de testes
    * COMIPLAR USANDO C++ 11: g++ -std=c++11 *.cpp -o bin
*/

#include <iostream>
#include <string>
#include "grafo.h"
#include "lista.h"

using namespace std;

string nomeArquivo = "list_debugging_file";

int main(int argc, char const *argv[])
{
    
    Grafo *g = new Grafo();
    
    g->criaLista(nomeArquivo);
    
    g->print();
    
    int *i0 = g->getVizinhancaFechada(5);
    
    for (int i = 0; i < 5; i++){
        cout << i0[i] << ", ";
    } cout << endl;
    
    cout << g->verificaKRegular() << endl;
    
    return 0;
}
