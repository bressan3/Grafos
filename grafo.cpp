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
    this->numNos = 0;
    this->numAresta = 0;
    this->flagDir = false;
    this->grauGrafo = 0;
    this->l = new Lista();
}

int Grafo::getNumNos(){
    return this->numNos;
}

void Grafo::setNumNos(int numNos){
    this->numNos = numNos;
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
}

/*
 Dado um arquivo e uma lista, esta função popula a lista de adjacência dada
 com as informações obtidas a aprtir da leitura deste arquivo
 */
void Grafo::criaLista(string nomeArquivo){
    ifstream arquivo(nomeArquivo);
    char str[255];
    
    bool primeiraLinha = true;
    
    while (arquivo) {
        arquivo.getline(str, 255);
        // cout << str << endl;
    
        // Atribui o valor da primeira linha ao parametro numNos
        if (primeiraLinha){
            setNumNos(stoi(str));
            primeiraLinha = false;
        }
        
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
        
        // cout << spacesCount << " " << spacesPos[0] << endl;
        
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
            
            // cout << valor1 << " " << valor2 << " " << peso << endl;
        }
        
        delete[] spacesPos;
    }
    
    arquivo.close();
}

/*
    Retorna um array contendo a sequencia de graus do grafo
 */
int* Grafo::getSequenciaGraus(){
    
    int *array = new int[this->numNos];
    
    NoLista *aux = l->getStart();
    
    int contVertice = 0;
    
    while (aux != NULL){
        array[contVertice] = (aux->getVertice())->getGrau();
        
        aux = aux->getProxVertical();
        contVertice++;
    }
    
    // Ordena array de forma decrescente
    sort(array, array+this->numNos, std::greater<int>());
    
    return array;
}

/*
    Retorna verdadeiro se o grafo é completo e falso caso contrário
 */
bool Grafo::verificaCompleto(){
    
    NoLista *aux = l->getStart();
    Vertice *vAtual = aux->getVertice();
    
    while (aux != NULL){
        if (vAtual->getGrau() < numNos - 1){
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

void Grafo::print(){
    l->print();
}

Grafo::~Grafo(){
    cout<<"Done!"<<endl;
}
