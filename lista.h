#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include "no_lista.h"
#include "aresta.h"

using namespace std;

class Lista {
private:
    
    NoLista *start;

public:

    Lista();
    NoLista* getStart();
    void setStart(NoLista* no);
    NoLista* addNoVertical(int id);
    void addNoHorizontal(int idVertical, int id, Aresta *a);
    NoLista* buscarNoVertical(int id);
    NoLista* buscarNoHorizontal(NoLista *inicioListaHorizontal, int id);
    void addNo(int id1, int id2, int pesoAresta, bool digrafo);
    void print();
    ~Lista();
};

#endif
