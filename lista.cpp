//
//  lista.cpp
//  Grafos
//
//  Created by Lucas Bressan on 9/19/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//

#include <iostream>
#include "lista.h"
#include "no_lista.h"

using namespace std;

Lista::Lista(){
    this->start = NULL;
}

/*
 Busca um no na vertical dado um id. Caso este no já exista a funcão retorna um ponteiro
 para ele. Caso não a função retornará NULL.
 */
NoLista* Lista::buscarNoVertical(int valor){
    
    NoLista *aux = start;
    
    while (aux != NULL){
        if (aux->getValor() == valor)
            return aux;
        aux = aux->getProxVertical();
    }
    
    return NULL;
}

/*
 Adiciona um novo nó na coluna da lista de adjacência
 */
void Lista::addNoVertical(int valor){
    
    NoLista *novoNo = new NoLista(valor);
    
    if (start == NULL){
        start = novoNo;
    }
    else{
        NoLista *aux = start;
        while (aux->getProxVertical() != NULL)
            aux = aux->getProxVertical();
        aux->setProxVertical(novoNo);
    }
}

/*
 Dado um valor na coluna, esta funcão adiciona um valor à lista
 horizontal daquele item da coluna
 */
void Lista::addNoHorizontal(int valorVertical, int valor){
    
    NoLista *aux = buscarNoVertical(valorVertical);
    NoLista *novo = new NoLista(valor);
    
    while (aux->getProxHorizontal() != NULL)
        aux = aux->getProxHorizontal();
    
    aux->setProxHorizontal(novo);
    
    NoLista *auxVertical = buscarNoVertical(valor);
    novo->setNoVertical(auxVertical);
}

/*
 Arquivo valor1 valor2
 */
void Lista::addNo(int valor1, int valor2){
    NoLista *aux1 = buscarNoVertical(valor1);
    NoLista *aux2 = buscarNoVertical(valor2);
    
    if (aux1 == NULL){
        addNoVertical(valor1);
    }
    
    if (aux2 == NULL){
        addNoVertical(valor2);
    }
    
    addNoHorizontal(valor1, valor2);
    addNoHorizontal(valor2, valor1);
}

/*
 Inicio do arquivo só possui um vertice
 */
void Lista::addNo(int valor1){
    addNoVertical(valor1);
}

/*
 Imprime a lista de adjacência
 */
void Lista::print(){
    
    if (start == NULL){
        cout << "Lista vazia!";
        exit(0);
    }
    
    NoLista *auxVertical = start;
    NoLista *auxHorizontal = start;
    
    while (auxVertical != NULL){
        cout<<auxVertical->getValor();
        while (auxHorizontal->getProxHorizontal() != NULL){
            auxHorizontal = auxHorizontal->getProxHorizontal();
            cout<< "-" << auxHorizontal->getValor();
        }
        cout<<endl;
        
        auxVertical = auxVertical->getProxVertical();
        auxHorizontal = auxVertical;
    }
}

Lista::~Lista(){
    cout << "Deleted" << endl;
}
