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

NoLista* Lista::getStart(){
    return this->start;
}

/*
 Busca um no na vertical dado um id. Caso este no já exista a funcão retorna um ponteiro
 para ele. Caso não a função retornará NULL.
 */
NoLista* Lista::buscarNoVertical(int id){
    
    NoLista *aux = start;
    
    while (aux != NULL){
        if (aux->getId() == id)
            return aux;
        aux = aux->getProxVertical();
    }
    
    return NULL;
}

/*
    Busca um nó na lista horizontal de adjacentes de "inicioListaHorizontal" e o retorna caso encontrado
 */
NoLista* Lista::buscarNoHorizontal(NoLista *inicioListaHorizontal, int id){
    NoLista* aux = inicioListaHorizontal->getProxHorizontal();
    
    while (aux != NULL) {
        if(aux->getId() == id)
            return aux;
        aux = aux->getProxHorizontal();
    }
    
    return NULL;
}

/*
 Adiciona um novo nó na coluna da lista de adjacência
 */
NoLista* Lista::addNoVertical(int id){
    
    NoLista *novoNo = new NoLista(id);
    
    if (start == NULL){
        start = novoNo;
    }
    else{
        NoLista *aux = start;
        while (aux->getProxVertical() != NULL)
            aux = aux->getProxVertical();
        aux->setProxVertical(novoNo);
    }
    
    return novoNo;
}

/*
 Dado um valor na coluna, esta função adiciona um valor à lista
 horizontal daquele item da coluna
 */
void Lista::addNoHorizontal(int idVertical, int id, Aresta *a){
    
    NoLista *aux = buscarNoVertical(idVertical);
    NoLista *novo = new NoLista(id);
    
    novo->setAresta(a);
    
    while (aux->getProxHorizontal() != NULL){
        aux = aux->getProxHorizontal();
    }
    
    aux->setProxHorizontal(novo);
    
    NoLista *auxVertical = buscarNoVertical(id);
    novo->setNoVertical(auxVertical);
}

/*
 Arquivo: valor1 valor2 pesoAresta
 */
void Lista::addNo(int id1, int id2, int pesoAresta, bool digrafo){
    NoLista *aux1 = buscarNoVertical(id1);
    NoLista *aux2 = buscarNoVertical(id2);
    
    if (aux1 == NULL){
        aux1 = addNoVertical(id1);
    }
    
    if (aux2 == NULL){
        aux2 = addNoVertical(id2);
    }
    
    // Cria a aresta que conectará id1 à id2
    Aresta *a = new Aresta(pesoAresta);
    
    addNoHorizontal(id1, id2, a);
    
    Vertice *vAux1 = aux1->getVertice();
    vAux1->incrementaGrau();
    
    if (!digrafo){
        addNoHorizontal(id2, id1, a);
    
        Vertice *vAux2 = aux2->getVertice();
        vAux2->incrementaGrau();
    }
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
        cout<< "[" << auxVertical->getId() << " G=" << (auxVertical->getVertice())->getGrau() << "]";
        while (auxHorizontal->getProxHorizontal() != NULL){
            auxHorizontal = auxHorizontal->getProxHorizontal();
            cout<< "-(" << auxHorizontal->getPesoAresta() << ")-" << auxHorizontal->getId();
        }
        cout<<endl;
        
        auxVertical = auxVertical->getProxVertical();
        auxHorizontal = auxVertical;
    }
}

Lista::~Lista(){
    cout << "Deleted" << endl;
}
