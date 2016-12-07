/*
    * Arquivo de testes
    * COMIPLAR USANDO C++ 11: g++ -std=c++11 *.cpp -o bin
*/

#include <iostream>
#include <string>
#include "grafo.h"
#include "lista.h"
#include "corte.h"

using namespace std;

// string nomeArquivo = "list_debugging_file";

string nomeArquivo = "Instancias Grafos/grafo_10000_4.txt";

int main(int argc, char const *argv[])
{
    bool digrafo = false;
    
    Grafo *g = new Grafo(digrafo);
    
    g->criaLista(nomeArquivo);
    
    // cout << g->getComponentesConexas().size() << endl;
    
    // g->deletaVertice(5664);
    
    // cout << g->getComponentesConexas().size() << endl;
    
    // g->print();
    
    cout << "Lista criada!" << endl;
    
    // cout << corteVerticesGuloso(g, nomeArquivo).size() << endl;
    
    vector<int> corte = corteVerticesGulosoRandomizado(g, 0.25, 1, nomeArquivo);
    g->printBusca(corte);
    
    return 0;
}
