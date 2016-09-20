/*
    * Arquivo de testes
*/

#include <iostream>
#include <string>
#include "grafo.h"
#include "lista.h"

using namespace std;

string nomeArquivo = "/Users/Lucas/Documents/Github/Grafos/Grafos/list_debugging_file";

int main(int argc, char const *argv[])
{
    
    Grafo *g = new Grafo();
    
    g->criaLista(nomeArquivo);
    
    return 0;
}
