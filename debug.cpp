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
    bool digrafo = false;
    
    Grafo *g = new Grafo(digrafo);
    
    g->criaLista(nomeArquivo);
    
    g->print();
    
    // cout << g->buscaNoFonte() << endl;
    
    cout << "É de articulação? " << g->verificaNoArticulacao(2) << endl;
    
    cout << "É ponte? " << g->verificaArestaPonte(2, 6) << endl;
    
    return 0;
}
