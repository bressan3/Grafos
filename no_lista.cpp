//
//  no_lista.cpp
//  Grafos
//
//  Created by Lucas Bressan on 9/19/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//

#include <iostream>
#include "no_lista.h"

using namespace std;

NoLista::NoLista(int valor){
    this->proxVertical = NULL;
    this->proxVertical = NULL;
    this->noVertical = NULL;
    this->valor = valor;
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

int NoLista::getValor(){
    return this->valor;
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

NoLista::~NoLista(){
    cout << "Deleted" << endl;
}
