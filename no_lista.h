#ifndef NO_LISTA_H
#define NO_LISTA_H

#include <iostream>
#include "vertice.h"
#include "aresta.h"

using namespace std;

class NoLista {

private:
    
    NoLista *proxHorizontal;
    NoLista *proxVertical;
    NoLista *noVertical; // Caso um nó esteja na lista de adjacência de outro (horizontal), este no apontará para o seu identico na lista vertical
    
    Vertice *v;
    Aresta *a; // Somente um nó na lista horizontal apontará para uma aresta
    
public:

    NoLista(int id);
    NoLista* getProxHorizontal();
    NoLista* getProxVertical();
    NoLista* getVertical();
    int getId();
    int getPesoAresta();
    Vertice* getVertice();
    void setProxVertical(NoLista *proxVertical);
    void setProxHorizontal(NoLista *proxHorizontal);
    void setNoVertical(NoLista *noVertical);
    void setAresta(Aresta *a);
    ~NoLista();

};

#endif
