//
//  no_lista.cpp
//  Grafos
//
//  Created by Lucas Bressan on 9/19/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//

#include <iostream>
#include "no_lista.h"
#include "vertice.h"

using namespace std;

NoLista::NoLista(int id){
    this->proxVertical = NULL;
    this->proxVertical = NULL;
    this->noVertical = NULL;
    
    // Cria um novo vertice com o Id passado e o guarda no nó
    this->v = new Vertice(id);
    
    this->a = NULL;
}

NoLista* NoLista::getProxHorizontal(){
    return this->proxHorizontal;
}

NoLista* NoLista::getProxVertical(){
    return this->proxVertical;
}

NoLista* NoLista::getVertical(){
    return this->noVertical;
}

int NoLista::getId(){
    return (this->v)->getId();
}

int NoLista::getPesoAresta(){
    return (this->a)->getPeso();
}

void NoLista::setProxVertical(NoLista *proxVertical){
    this->proxVertical = proxVertical;
}

void NoLista::setProxHorizontal(NoLista *proxHorizontal){
    this->proxHorizontal = proxHorizontal;
}

void NoLista::setNoVertical(NoLista *noVertical){
    this->noVertical = noVertical;
}

void NoLista::setAresta(Aresta *a){
    this->a = a;
}

NoLista::~NoLista(){
    cout << "Deleted" << endl;
}
