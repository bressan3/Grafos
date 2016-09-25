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
    int getNumNos();
    void setNumNos(int numNos);
    
    void deletaVertice(int id);
    void deletaAresta(int id1, int id2);
    
    void criaLista(string nomeArquivo);
    
    int* getSequenciaGraus();
    
    bool verificaCompleto();
    
    bool verificaAdjacente(int id1, int id2);
    
    void print();
    ~Grafo();

};

#endif
