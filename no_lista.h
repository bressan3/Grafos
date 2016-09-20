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
    NoLista *noVertical; // Caso um nó esteja na lista de adjacência de outro, este no apontará para o seu identico na lista vertical
    // Teste
    int valor;
    
public:

    NoLista(int valor);
    NoLista* getProxHorizontal();
    NoLista* getProxVertical();
    NoLista* getVertical();
    int getValor();
    void setProxVertical(NoLista *proxVertical);
    void setProxHorizontal(NoLista *proxHorizontal);
    void setNoVertical(NoLista *noVertical);
    ~NoLista();

};

#endif
