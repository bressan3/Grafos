#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>
#include "lista.h"

using namespace std;

class Grafo {

private:
    
    int numVertices;
    int numArestas;
    bool flagDir;
    int grauGrafo;
    Lista *l;

public:
    
    Grafo();
    int getNumVertices();
    void setNumVertices(int numNos);
    
    int getNumArestas();
    void setNumArestas(int numArestas);
    
    void deletaVertice(int id);
    void deletaAresta(int id1, int id2);
    
    void criaLista(string nomeArquivo);
    
    int* getSequenciaGraus();
    
    bool verificaCompleto();
    
    bool verificaAdjacente(int id1, int id2);
    
    int* getVizinhancaAberta(int id);
    int* getVizinhancaFechada(int id);
    
    void print();
    ~Grafo();

};

#endif
