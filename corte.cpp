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

vector<int> corteVerticesGuloso(Grafo *g, int criterio){
    vector<int> verticesCorte; // Vector contendo os vertices de corte da solução.
    
    vector<vector<int>> vertices; // Vector de todos os vertices (contendo o id do vertice e seu grau) de g de grau maior que zero ordenados pelo seus graus (do menor para o maior).
    
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
    verticesCorte = {};
    
    NoLista* atual = auxLista->buscarNoVertical(vertices[0][0]);
    aux = atual->getProxHorizontal();
    NoLista* auxVertical = aux->getVertical();
    
    vector<vector<int>> candidatos; // Lista de todos os vizinhos de "NoLista* atual" ordenada do maior grau para o menor.
    
    while (aux != NULL){
        candidatos.push_back({aux->getId(), (auxVertical->getVertice())->getGrau()});
        aux = aux->getProxHorizontal();
        if (aux != NULL){
            auxVertical = aux->getVertical();
        }
    } sort(candidatos.begin(), candidatos.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[1] > b[1];});
    
    /* 
        Para cada vizinho de "NoLista* atual", deletamos seu vizinho com maior grau e checamos se o grafo ficou desconexo.
        Caso não tenha ficado, deletamos o vizinho com o segundo maior grau e assim por diante.
    */
    cout << "Num Candidatos = " << candidatos.size() << endl;
    int i = 0;
    bool corteEncontrado = false;
    while (!candidatos.empty()){
        cout << "\r" << "Candidato " << i << ", ID = " << candidatos[0][0] << ", Grau = " << candidatos[0][1] << endl;
        vector<int> busca1 = g->buscaEmLargura(atual->getId());
        
        int candidatoAtual = candidatos[0][0];
        candidatos.erase(candidatos.begin());
        
        g->deletaVertice(candidatoAtual);
        
        vector<int> busca2 = g->buscaEmLargura(atual->getId());

        verticesCorte.push_back(candidatoAtual);
        
        if (busca1.size() - 1 != busca2.size()){
            corteEncontrado = true;
            break;
        }
        i++;
    }
    
    if (!corteEncontrado){
        verticesCorte = {};
    }
    
    return verticesCorte;
}

vector<int> corteVerticesGulosoRandomizado(Grafo *g, float alpha, int iteracoes, string nomeArquivo){
    vector<int> verticesCorte; // vetor solução
    
    vector<vector<int>> vertices; // Vector de todos os vertices de g de grau maior que zero ordenados pelo seus graus (do menor para o maior).
    
    //função para gerar aleatoriedade no rand()
    srand(time(NULL));
    
    Lista* auxLista = g->getLista();
    NoLista* aux = auxLista->getStart();
    NoLista* aux2;
    
    // ordena os vertices do grafo
    cout << "Cria vector de vertices" << endl;
    while (aux != NULL){
        if ((aux->getVertice()->getGrau()) != 0){
            vertices.push_back({aux->getId(), (aux->getVertice())->getGrau()});
        }
        aux = aux->getProxVertical();
    } sort(vertices.begin(), vertices.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[1] < b[1];});
    cout << "Terminou criar vector de vertices" << endl;
    
    // escolhe um vertice baseado no alpha
    int verticeEscolhido;
    verticeEscolhido = vertices[(int)(rand() % (int)vertices.size()*alpha)][0];
    // verticeEscolhido = vertices[0][0];
    cout << "vertice selecionado para fazer o corte: " << verticeEscolhido << endl;
    aux = auxLista->buscarNoVertical(verticeEscolhido);
    
    //faz busca em largura para ver quantos vertices existem
    vector<int> buscaInicial = g->buscaEmLargura(verticeEscolhido);
    vector<int> buscaConexo;
    
    //vetor onde irá ficar todos os candidatos
    vector<vector<int>> candidatos;
    
    // ordena os vertices candidatos
    cout << "Cria vector de vizinhos" << endl;
    aux2 = aux->getProxHorizontal();
    while (aux2 != NULL){
        candidatos.push_back({aux2->getId(), (aux2->getVertice())->getGrau()});
        aux2 = aux2->getProxHorizontal();
    } sort(candidatos.begin(), candidatos.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[1] > b[1];});
    cout << "Terminou de criar o vector de vizinhos" << endl;
    
    // faz a busca e o corte
    int candidatoEscolhido;
    int randomId;
    vector<int> best;
    cout << "Número de Candidatos = " << candidatos.size() << endl;
    for(int i=0; i<iteracoes; i++){
        // escolhe um candidato aleatorio baseado no alpha e adiciona na solução e remove ele
        if (candidatos.size() == 0) break;
        randomId = rand() % (int)candidatos.size()*alpha;
        cout << "Posição do candidato selecionado: " << randomId << endl;
        candidatoEscolhido = candidatos[randomId][0];
        verticesCorte.push_back(candidatoEscolhido);
        g->deletaVertice(candidatoEscolhido);
        candidatos.erase(candidatos.begin() + randomId);
        buscaConexo = g->buscaEmLargura(verticeEscolhido);
        
        //verifica se a componente ainda é conexa
        if(buscaInicial.size() > buscaConexo.size()){
            if ((verticesCorte.size() < best.size()) && best.size() == 0){
                g->criaLista(nomeArquivo);
                best.swap(verticesCorte);
            }
        }
    }
    
    return best;
    
}

vector<int> corteVerticesGulosoRandomizadoReativo(Grafo *g){
    vector<int> verticesCorte;
    
    return verticesCorte;
}
