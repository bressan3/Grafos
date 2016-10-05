//
//  grafo.cpp
//  Grafos
//
//  Created by Lucas Bressan on 9/19/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>

#include "grafo.h"
#include "lista.h"

using namespace std;

Grafo::Grafo(){
    this->numVertices = 0;
    this->numArestas = 0;
    this->flagDir = false;
    this->grauGrafo = 0;
    this->l = new Lista();
}

int Grafo::getNumVertices(){
    return this->numVertices;
}

void Grafo::setNumVertices(int numVertices){
    this->numVertices = numVertices;
}

int Grafo::getNumArestas(){
    return this->numArestas;
}

void Grafo::setNumArestas(int numArestas){
    this->numArestas = numArestas;
}

/*
 Dado um Id de vertice a função o deletará do grafo juntamente com todas as suas arestas.
 */
void Grafo::deletaVertice(int id){
    
    NoLista *auxVertical = l->getStart();
    
    while (auxVertical != NULL){
        if (verificaAdjacente(auxVertical->getId(), id) && auxVertical->getId() != id){
            deletaAresta(auxVertical->getId(), id);
        }
        auxVertical = auxVertical->getProxVertical();
    }
    
    NoLista *anterior = l->getStart();
    NoLista *atual = anterior->getProxVertical();
    NoLista *prox = atual->getProxVertical();
    
    while (atual->getProxVertical() != NULL && atual->getId() != id){
        anterior = anterior->getProxVertical();
        atual = atual->getProxVertical();
        prox = prox->getProxVertical();
    }
    
    anterior->setProxVertical(prox);
    delete(atual);
    setNumVertices(getNumVertices() - 1);
}

/*
 Dado os IDs de dois vertices, esta função deleta a aresta entre os dois. ACHO QUE FUNCIONA -> ERRO DEVE ESTAR NA FUNCAO DE CIMA
 */
void Grafo::deletaAresta(int id1, int id2){
    
    for (int i = 0; i < 2; i++) {
        
        int idVertical = id1;
        int idHorizontal = id2;
        
        if (i == 1){
            idVertical = id2;
            idHorizontal = id1;
        }
        
        NoLista *startId = l->buscarNoVertical(idVertical);
        
        NoLista *anterior = startId;
        NoLista *atual = anterior->getProxHorizontal();
        NoLista *prox = atual->getProxHorizontal();
    
        while (atual->getProxHorizontal() != NULL && atual->getId() != idHorizontal){
            anterior = anterior->getProxHorizontal();
            atual = atual->getProxHorizontal();
            prox = prox->getProxHorizontal();
        }
    
        anterior->setProxHorizontal(prox);
        delete(atual);
    }
    setNumArestas(getNumArestas() - 1);
}

/*
 Dado um arquivo e uma lista, esta função popula a lista de adjacência dada
 com as informações obtidas a aprtir da leitura deste arquivo
 */
void Grafo::criaLista(string nomeArquivo){
    ifstream arquivo(nomeArquivo.c_str());
    char str[255];
    
    // Atribui o valor da primeira linha ao parametro numNos
    arquivo.getline(str, 255);
    setNumVertices(stoi(str));
    
    for (int i = 1; i <= numVertices; i++) {
        l->addNoVertical(i);
    }
    
    while (arquivo) {
        arquivo.getline(str, 255);
        
        int spacesCount = 0;
        
        for (int i = 0; i < string(str).length(); i++) {
            if (str[i] == ' '){
                spacesCount++;
            }
        }
        
        int *spacesPos = new int[spacesCount];
        int j = 0;
        
        for (int i = 0; i < string(str).length(); i++) {
            if (str[i] == ' '){
                spacesPos[j] = i;
                j++;
            }
        }
        
        int valor1;
        int valor2;
        int pesoAresta = 1;
        
        if (spacesCount >= 1){
            valor1 = stoi(string(str).substr(0, spacesPos[0] + 1));
            
            if (spacesCount == 1){
                valor2 = stoi(string(str).substr(spacesPos[0] + 1, string(str).length() - 1));
            }
            else if (spacesCount == 2){
                valor2 = stoi(string(str).substr(spacesPos[0] + 1, spacesPos[1] - 1));
                pesoAresta = stoi(string(str).substr(spacesPos[1] + 1, string(str).length() - 1));
            }
            
            l->addNo(valor1, valor2, pesoAresta);
            this->numArestas++;
            
        }
        
        delete[] spacesPos;
    }
    
    arquivo.close();
}

/*
    Retorna um array contendo a sequencia de graus do grafo
 */
int* Grafo::getSequenciaGraus(){
    
    int *array = new int[this->numVertices];
    
    NoLista *aux = l->getStart();
    
    int contVertice = 0;
    
    while (aux != NULL){
        array[contVertice] = (aux->getVertice())->getGrau();
        
        aux = aux->getProxVertical();
        contVertice++;
    }
    
    // Ordena array de forma decrescente
    sort(array, array+this->numVertices, std::greater<int>());
    
    return array;
}

/*
    Retorna 0 caso o grafo não seja k-regular. Retorna k caso o grafo seja k-regular.
 */
int Grafo::verificaKRegular(){
    
    NoLista *aux = l->getStart();
    
    int grauStart = (aux->getVertice())->getGrau();
    
    while (aux != NULL){
        aux = aux->getProxVertical();
        if (grauStart != (aux->getVertice())->getGrau()){
            return 0;
        }
    }
    
    return grauStart;
}

/*
    Retorna verdadeiro se o grafo é completo e falso caso contrário
 */
bool Grafo::verificaCompleto(){
    
    NoLista *aux = l->getStart();
    Vertice *vAtual = aux->getVertice();
    
    while (aux != NULL){
        if (vAtual->getGrau() < numVertices - 1){
            return false;
        }
    }
    
    return true;
}

/*
    Retorna verdadeiro se dois vértices (v1 e v2 com id1 e id2) são adjacentes e falso caso contrário
 */
bool Grafo::verificaAdjacente(int id1, int id2){
    
    NoLista *aux1 = l->buscarNoVertical(id1);
    NoLista *aux2 = l->buscarNoVertical(id2);
    
    if (aux1 == NULL || aux2 == NULL){
        return false;
    }
    
    // Verifica se aux1 tem aux2 como seu adjacente
    if (l->buscarNoHorizontal(aux1, id2) != NULL && l->buscarNoHorizontal(aux2, id1) != NULL){
        return true;
    }
    
    return false;
}

/*
 Dado o id de um nó, esta funcao retorna um vetor contendo sua vizinhança aberta (os Ids dos seus vizinhos)
 */
int* Grafo::getVizinhancaAberta(int id){
    
    NoLista *aux = (l->buscarNoVertical(id))->getProxHorizontal();
    
    int *vizinhancaAberta = new int[ (aux->getVertice())->getGrau() ];
    
    int i = 0;
    
    while (aux != NULL){
        vizinhancaAberta[i] = aux->getId();
        aux = aux->getProxHorizontal();
        i++;
    }
    
    return vizinhancaAberta;
}

/*
 Dado o id de um nó, esta funcao retorna um vetor contendo sua vizinhança fechada (os Ids dos seus vizinhos)
 */
int* Grafo::getVizinhancaFechada(int id){
    
    NoLista *aux = l->buscarNoVertical(id);
    
    if (aux == NULL){
        exit(-1);
    }
    
    int *vizinhancaFechada = new int[ (aux->getVertice())->getGrau() + 1 ];
    
    int i = 0;
    
    while (aux != NULL){
        vizinhancaFechada[i] = aux->getId();
        aux = aux->getProxHorizontal();
        i++;
    }
    
    return vizinhancaFechada;

}

void Grafo::print(){
    l->print();
}

Grafo::~Grafo(){
    cout<<"Done!"<<endl;
}
