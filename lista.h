#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include "no_lista.h"

using namespace std;

class Lista {
private:
    
    NoLista *start;
    
    void addNoVertical(int valor);
    void addNoHorizontal(int valorVertical, int valor);

public:

    Lista();
    NoLista* buscarNoVertical(int valor);
    void addNo(int valor1, int valor2);
    void addNo(int valor1);
    void print();
    ~Lista();
};

#endif
