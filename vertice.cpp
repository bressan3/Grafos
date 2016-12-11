//
//  vertice.cpp
//  Grafos
//
//  Created by Lucas Bressan on 9/20/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//

#include "vertice.h"

Vertice::Vertice(int id, int peso){
    this->id = id;
    this->peso = peso;
    this->grau = 0;
    this->invisivel = false;
}

Vertice::Vertice(int id){
    this->id = id;
    this->peso = 0;
    this->grau = 0;
}

int Vertice::getId(){
    return this->id;
}

int Vertice::getPeso(){
    return this->peso;
}

int Vertice::getGrau(){
    return this->grau;
}

void Vertice::incrementaGrau(){
    this->grau++;
}

void Vertice::diminuiGrau(){
    this->grau--;
}

void Vertice::setInvisivel(bool trueOrFalse){
    this->invisivel = trueOrFalse;
}

bool Vertice::getInvisivel(){
    return this->invisivel;
}
