//
//  corte.cpp
//  Grafos
//
//  Created by Lucas Bressan on 11/21/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//
//  Arquivo que implementa os algorítimos guloso, guloso randomizado e guloso randomizado reativo
//  para o problema de corte mínimo de vertices.

#include <fstream>
#include "corte.h"

using namespace std;

vector<int> corteVerticesGuloso(Grafo *g, string nomeArquivo){
    vector<int> verticesCorte; // Vector contendo os vertices de corte da solução.
    
    vector<vector<int>> vertices; // Vector de todos os vertices (contendo o id do vertice e seu grau) de g de grau maior que zero ordenados pelo seus graus (do menor para o maior).
    
    Lista* auxLista = g->getLista();
    NoLista* aux = auxLista->getStart();
    
    // Cria a lista com todos os vertices de grau maior que zero do grafo e a ordena de acordo com o grau de cada vertice (do menor para o maior).
    while (aux != NULL){
        if ((aux->getVertice()->getGrau()) != 0){
            vertices.push_back({aux->getId(), (aux->getVertice())->getGrau()});
        }
        aux = aux->getProxVertical();
    } sort(vertices.begin(), vertices.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[1] < b[1];});
    
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
    // bool corteEncontrado = false;
    vector<int> busca1 = g->buscaEmLargura(atual->getId());
    vector<int> busca2;
    if (candidatos.size() == 1) {
        verticesCorte.push_back(candidatos[0][0]);
        return verticesCorte;
    }
    while (!candidatos.empty()){
        // cout << "\r" << "Candidato " << i << ", ID = " << candidatos[0][0] << ", Grau = " << candidatos[0][1] << endl;
        
        int candidatoAtual = candidatos[0][0];
        candidatos.erase(candidatos.begin());
        
        g->deletaVertice(candidatoAtual);
        
        busca2 = g->buscaEmLargura(atual->getId());

        verticesCorte.push_back(candidatoAtual);
        
        if (busca1.size() - verticesCorte.size() != busca2.size()){
            return verticesCorte;
        }
        i++;
    }
    
    // Retorna uma lista vazia caso não tenha encontrado um corte no while
    return verticesCorte;
}

vector<int> corteVerticesGulosoRandomizado(Grafo *g, float alpha, int iteracoes, string nomeArquivo){
    
    /*
     Inicialização de todas as variaveis utilizadas
     */
    vector<int> verticesCorte;
    vector<vector<int>> vertices;
    Lista *auxLista;
    NoLista *aux, *aux2;
    int verticeEscolhido;
    vector<vector<int>> componentesInicial;
    vector<int> buscaConexo;
    vector<vector<int>> candidatos;
    int candidatoEscolhido;
    int randomId;
    vector<int> best;
    
    //função para gerar aleatoriedade no rand()
    srand(time(NULL));
    
    for(int i=0; i<iteracoes; i++){
        // cout << endl << "Iter: " << i + 1 << endl;
        
        auxLista = g->getLista();
        aux = auxLista->getStart();
        
        // ordena os vertices do grafo
        while (aux != NULL){
            if ((aux->getVertice()->getGrau()) != 0){
                vertices.push_back({aux->getId(), (aux->getVertice())->getGrau()});
            }
            aux = aux->getProxVertical();
        } sort(vertices.begin(), vertices.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[1] < b[1];});
        
        // escolhe um vertice baseado no alpha
        verticeEscolhido = vertices[(int)(rand() % (int)vertices.size()*alpha)][0];
        
        int caminhoInicial = (int)g->buscaEmLargura(verticeEscolhido).size();
        
        aux = auxLista->buscarNoVertical(verticeEscolhido);
        
        // ordena os vertices candidatos
        aux2 = aux->getProxHorizontal();
        while (aux2 != NULL){
            candidatos.push_back({aux2->getId(), (aux2->getVertice())->getGrau()});
            aux2 = aux2->getProxHorizontal();
        } sort(candidatos.begin(), candidatos.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[1] > b[1];});
        
        // cout << "Número de Candidatos = " << candidatos.size() << endl;
        
        // Caso o tamanho do conjunto de vertices de corte encontrado seja 1 (valor ótimo), o algoritimo já retorna o conjunto achado
        // uma vez que não há um valor de corte melhor do que 1.
        if (candidatos.size() == 1){
            // cout << "Nova solução = " << candidatos.size() << endl;
            best.push_back(candidatos[0][0]);
            // cout << "Mudou a solucao" << endl;
            return best;
        }
        
        while (!candidatos.empty()) {
            // escolhe um candidato aleatorio baseado no alpha e adiciona na solução e remove ele do grafo
            randomId = rand() % (int)candidatos.size()*alpha;
            
            //pega o candidato remove ele do grafo e do vetor, e faz uma busca em largura
            candidatoEscolhido = candidatos[randomId][0];
            verticesCorte.push_back(candidatoEscolhido);
            
            // g->deletaVertice(candidatoEscolhido);
            
            g->setInvisivel(candidatoEscolhido, true);
            candidatos.erase(candidatos.begin() + randomId);
            
            // cout << "Vertice Deletado" << endl;
            
            int caminhoAtual = (int)g->buscaEmLargura(verticeEscolhido).size();
            
            // Verifica se o número de componentes aumentou após a remoção
            if (candidatos.empty() || (caminhoInicial - verticesCorte.size() != caminhoAtual)){
                // Caso tenha aumentado e a nova solução seja menor do que a anterior, a nova solução vira a melhor
                // cout << "Nova solução = " << verticesCorte.size() << endl;
                if (verticesCorte.size() == 1){
                    // cout << "Mudou a solucao" << endl;
                    return verticesCorte;
                }
                if ((verticesCorte.size() < best.size()) || best.size() == 0){
                    // cout << "Mudou a solucao" << endl;
                    best = verticesCorte;
                }
                for (int i = 0; i < verticesCorte.size(); i++){
                    g->setInvisivel(verticesCorte[i], false);
                }
                verticesCorte = {};
                break;
            }
        }
        
    }
    return best;
    
}

vector<int> corteVerticesGulosoRandomizadoReativo(Grafo *g, string nomeArquivo){
    cout << "iniciando a função corteVerticesGulosoRandomizadoReativo" << endl;
    /*
     Inicialização de todas as variaveis utilizadas
     */
    vector<int> verticesCorte;
    vector<vector<int>> melhoresSolucoes;
    vector<double> alphas;
    vector<int> iteracoes;
    vector<int> randomizado;
    int iteracao = 25;
    int media=0;
    
    //insere os valores de alpha e o numero de iterações por posição do vetor
    for(int i=0; i<10; i++){
        alphas.push_back(0.05*(i+1));
        iteracoes.push_back(iteracao);
        melhoresSolucoes.push_back({});
    }
        
    // roda o algoritmo randomizado
    for(int i=0; i<alphas.size(); i++){
        cout << endl << "Rodando a função corte de vertices randomizado com alpha: " << alphas[i] << " e número de iterações: " << iteracoes[i] << endl;
        randomizado = corteVerticesGulosoRandomizado(g,alphas[i],iteracoes[i],nomeArquivo);
        
        //verifica se o tamanho do algoritmo randomizado é menor que a solução atual ou se a solução atual é nula
        if(randomizado.size() < melhoresSolucoes[i].size() || melhoresSolucoes[i].size() == 0)
            melhoresSolucoes[i].swap(randomizado);
    }
    
    //pega o tamanho das soluções e faz um somatório
    for(int i=0; i<10; i++){
        media += melhoresSolucoes[i].size();
    }
    
    //refaz o número de iterações para cada alpha tendo como base, quanto menor o tamanho da solução maior o número de iterações
    for(int i=0; i<10; i++){
        iteracoes.at(i) = (int) (1-(melhoresSolucoes[i].size()/media))*iteracao;
    }
    
    //define a solução final como a menor solução entre as soluções encontradas usando os alphas
    for(int i=0; i<10; i++){
        if(verticesCorte.size() > melhoresSolucoes[i].size() || verticesCorte.size() == 0)
            verticesCorte.swap(melhoresSolucoes[i]);
    }
    
    cout << "retornando melhor valor encontrado" << endl;
    return verticesCorte;
}
