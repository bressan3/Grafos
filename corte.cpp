//
//  corte.cpp
//  Grafos
//
//  Created by Lucas Bressan on 11/21/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//
//  Arquivo que implementa os algorítimos guloso, guloso randomizado e guloso randomizado reativo
//  para o problema de corte mínimo de vertices.

#include "corte.h"

using namespace std;

vector<int> corteVerticesGuloso(Grafo *g){
    vector<int> verticesCorte; // Vector contendo os vertices de corte da solução.
    
    vector<vector<int>> vertices; // Vector de todos os vertices de g de grau maior que zero ordenados pelo seus graus (do menor para o maior).
    
    Lista* auxLista = g->getLista();
    NoLista* aux = auxLista->getStart();
    
    // Cria a lista com todos os vertices de grau maior que zero do grafo e a ordena de acordo com o grau de cada vertice (do menor para o maior).
    cout << "Cria vector de vertices" << endl;
    while (aux != NULL){
        if ((aux->getVertice()->getGrau()) != 0){
            vertices.push_back({aux->getId(), (aux->getVertice())->getGrau()});
        }
        aux = aux->getProxVertical();
    } sort(vertices.begin(), vertices.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[1] < b[1];});
    cout << "Terminou criar vector de vertices" << endl;
    
    cout << "Encontra Corte" << endl;
    int i = 0;
    while (i < vertices.size()){
        verticesCorte = {};
        
        NoLista* atual = auxLista->buscarNoVertical(vertices[i][0]);
        aux = atual->getProxHorizontal();
        
        vector<vector<int>> candidatos; // Lista de todos os vizinhos de "NoLista* atual" ordenada do maior grau para o menor.
        
        while (aux != NULL){
            candidatos.push_back({aux->getId(), (aux->getVertice())->getGrau()});
            aux = aux->getProxHorizontal();
        } sort(candidatos.begin(), candidatos.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[1] > b[1];});
        
        /* 
            Para cada vizinho de "NoLista* atual", deletamos seu vizinho com maior grau e checamos se o grafo ficou desconexo.
            Caso não tenha ficado, deletamos o vizinho com o segundo maior grau e assim por diante.
        */
        bool corte = false;
        for (int j = 0; j < candidatos.size(); j++){
            vector<int> busca1 = g->buscaEmLargura(atual->getId());
            g->deletaVertice(candidatos[j][0]);
            vector<int> busca2 = g->buscaEmLargura(atual->getId());
            verticesCorte.push_back(candidatos[j][0]);
            if (busca1.size() - 1 != busca2.size()){
                corte = true;
                break;
            }
        }
        
        if (corte){
            break;
        }
        
        for (int j = 0; j < candidatos.size(); j++){
            g->addAresta(atual->getId(), candidatos[j][0], 1);
        }
        
        i++;
    }
    
    return verticesCorte;
}

vector<int> corteVerticesGulosoRandomizado(Grafo *g, float alpha){
    vector<int> verticesCorte;
    
    return verticesCorte;
}

vector<int> corteVerticesGulosoRandomizadoReativo(Grafo *g){
    vector<int> verticesCorte;
    
    return verticesCorte;
}
