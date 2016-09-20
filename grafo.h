#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>
#include "lista.h"

using namespace std;

class Grafo {
private:
    int numNos;
    int numAresta;
    bool flagDir;
    int grauGrafo;
    Lista *l;
public:
    Grafo();
    void setNumNos(int numNos);
    void criaLista(string nomeArquivo);
    ~Grafo();
};

#endif
