//
//  corte.cpp
//  Grafos
//
//  Created by Lucas Bressan on 11/21/16.
//  Copyright © 2016 Lucas Bressan, Gabriell Lucas, Bruno Almeida, Claudio Lopes. All rights reserved.
//
//  Arquivo que implementa os algorítimos guloso, guloso randomizado e guloso randomizado reativo
//  para o problema de corte mínimo de vertices.

#include <fstream>
#include <algorithm>
#include <math.h>
#include <ctime>

#include "corte.h"

using namespace std;

/*
 
 *
    INSTÂNCIAS - TESTE 1
 *
 
 */
/*vector<string> instancias_pequenas = {"Instancias Grafos/grafo_1000_4.txt", "Instancias Grafos/grafo_1000_8.txt", "Instancias Grafos/grafo_10000_8.txt", "Instancias Grafos/grafo_10000_4.txt"};
vector<string> instancias_medias = {"Instancias Grafos/grafo_10000_3.txt", "Instancias Grafos/grafo_1000_3.txt", "Instancias Grafos/grafo_10000_7.txt"};
vector<string> instancias_grandes = {"Instancias Grafos/grafo_1000_6.txt", "Instancias Grafos/grafo_10000_6.txt", "Instancias Grafos/grafo_10000_2.txt"};*/

/*

 *
    INSTÂNCIAS - TESTE 2
 *

*/
vector<string> instancias_pequenas = {"Instancias02/pequena01 (11,20).txt", "Instancias02/pequena02 (23,71).txt", "Instancias02/pequena03 (37,72).txt", "Instancias02/pequena04 (20,20).txt"};
vector<string> instancias_medias = {"Instancias02/media01 (100,166).txt", "Instancias02/media02 (88,146).txt", "Instancias02/media03 (79,156).txt"};
vector<string> instancias_grandes = {"Instancias02/grande01 (87,406).txt", "Instancias02/grande02 (138,493).txt", "Instancias02/grande03 (149,541).txt"};

bool digrafo = false;

vector<int> corteVerticesGuloso(Grafo *g){
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
    // cout << "Num Candidatos = " << candidatos.size() << endl;
    int i = 0;
    // bool corteEncontrado = false;
    int numComponentesOriginal = (int)(g->getComponentesConexas()).size();
    int numComponentesAtual;
    vector<int> invisiveis;
    if (candidatos.size() == 1) {
        verticesCorte.push_back(candidatos[0][0]);
        return verticesCorte;
    }
    while (!candidatos.empty()){
        
        int candidatoAtual = candidatos[0][0];
        candidatos.erase(candidatos.begin());
        
        g->setInvisivel(candidatoAtual, true);
        invisiveis.push_back(candidatoAtual);
        
        // busca2 = g->buscaEmLargura(atual->getId());
        numComponentesAtual = (int)(g->getComponentesConexas()).size();
        
        verticesCorte.push_back(candidatoAtual);
        
        // if (busca1.size() - verticesCorte.size() != busca2.size()){
        if (numComponentesAtual > numComponentesOriginal){
            return verticesCorte;
        }
        i++;
    }
    
    for (int i = 0; i < invisiveis.size(); i++){
        g->setInvisivel(invisiveis[i], false);
    }
    
    return verticesCorte;
}

vector<int> corteVerticesGulosoRandomizado(Grafo *g, float alpha, int iteracoes){
    
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
    
    int numComponentesOriginal = (int)(g->getComponentesConexas()).size();
    
    for(int i=0; i<iteracoes; i++){
        
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
        
        // int caminhoInicial = (int)g->buscaEmLargura(verticeEscolhido).size();
        
        aux = auxLista->buscarNoVertical(verticeEscolhido);
        
        // ordena os vertices candidatos do vertice de maior grau para o de menor
        aux2 = aux->getProxHorizontal();
        while (aux2 != NULL){
            candidatos.push_back({aux2->getId(), (aux2->getVertice())->getGrau()});
            aux2 = aux2->getProxHorizontal();
        } sort(candidatos.begin(), candidatos.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[1] > b[1];});
        
        // Caso o tamanho do conjunto de vertices de corte encontrado seja 1 (valor ótimo), o algoritimo já retorna o conjunto achado
        // uma vez que não há um valor de corte melhor do que 1.
        if (candidatos.size() == 1){
            best.push_back(candidatos[0][0]);
            return best;
        }
        // cout << "Tam. candidatos = " << candidatos.size() << endl;
        
        while (!candidatos.empty()) {
            // escolhe um candidato aleatorio baseado no alpha e adiciona na solução e remove ele do grafo
            randomId = rand() % (int)candidatos.size()*alpha;
            
            //pega o candidato "remove" ele do grafo e do vetor, e faz uma busca em largura
            candidatoEscolhido = candidatos[randomId][0];
            verticesCorte.push_back(candidatoEscolhido);
            
            g->setInvisivel(candidatoEscolhido, true);
            candidatos.erase(candidatos.begin() + randomId);
            
            // int caminhoAtual = (int)g->buscaEmLargura(verticeEscolhido).size();
            
            int numComponentesAtual = (int)g->getComponentesConexas().size();
            
            // Verifica se o número de componentes aumentou após a remoção
            // if (candidatos.empty() || ((caminhoInicial - verticesCorte.size()) != caminhoAtual)){
            if (candidatos.empty() || (numComponentesAtual > numComponentesOriginal)){
                // Caso tenha aumentado e a nova solução seja menor do que a anterior, a nova solução vira a melhor
                if (verticesCorte.size() == 1){
                    return verticesCorte;
                }
                if ((verticesCorte.size() < best.size()) || best.size() == 0){
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

vector<int> corteVerticesGulosoRandomizadoReativo(Grafo *g){
    /*
     Inicialização de todas as variaveis utilizadas
     */
    vector<int> verticesCorte;
    vector<vector<int>> resultadosIteracoes;
    vector<vector<int>> melhoresSolucoes;
    vector<double> alphas;
    vector<int> iteracoes;
    vector<int> randomizado;
    int quantAlphas = 10;
    int iteracao = 75;
    int media=0;
    
    ofstream out("Resultados/guloso_rand_reativo_out.txt", ios_base::app);
    
    //insere os valores de alpha e o numero de iterações por posição do vetor
    for(int i=0; i<quantAlphas; i++){
        alphas.push_back(0.05*(i+1));
        iteracoes.push_back(iteracao);
        melhoresSolucoes.push_back({});
        resultadosIteracoes.push_back({});
    }
    
    //O algoritmo roda 30 vezes
    for(int j=0; j<30; j++){
        media = 0;
        // cout << endl << "Iniciando iteração " << j << " de 30" << endl;
        out << "    Iteração " << j + 1 << " de 30" << endl;
        
        clock_t start = clock();
        
        //roda o algoritmo randomizado
        for(int i=0; i<quantAlphas; i++){
            
            // cout << endl << "Rodando a função corte de vertices randomizado com alpha: " << alphas[i] << " e número de iterações: " << iteracoes[i] << endl;
            randomizado = corteVerticesGulosoRandomizado(g,alphas[i],iteracoes[i]);
            
            out << "        Corte: " << randomizado.size() << ", Alpha: " << alphas[i] << ", Iterações: " << iteracoes[i] << endl;
            resultadosIteracoes[i].swap(randomizado);
            
            
            //verifica se o tamanho do algoritmo randomizado é menor que a solução atual ou se a solução atual é nula
            if(randomizado.size() < melhoresSolucoes[i].size() || melhoresSolucoes[i].size() == 0)
                melhoresSolucoes[i].swap(randomizado);
        }
        
        //pega o tamanho das soluções e faz um somatório
        for(int i=0; i<quantAlphas; i++){
            media += resultadosIteracoes[i].size();
        }
        
        //refaz o número de iterações para cada alpha tendo como base, quanto menor o tamanho da solução maior o número de iterações
        for(int i=0; i<quantAlphas; i++){
            iteracoes.at(i) =  (int)ceil((float)((float)((float)(1-((float)resultadosIteracoes[i].size()/(float)media))/(float)(quantAlphas-1))*iteracao*quantAlphas));
        }
        media = 0;
        out << "            Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl << endl;
    }
    
    //define a solução final como a menor solução entre as soluções encontradas usando os alphas
    for(int i=0; i<quantAlphas; i++){
        if(verticesCorte.size() > melhoresSolucoes[i].size() || verticesCorte.size() == 0)
            verticesCorte.swap(melhoresSolucoes[i]);
    }
    
    out.close();
    
    // cout << "retornando melhor valor encontrado" << endl;
    return verticesCorte;
}


// Roda o algoritimo guloso para todas as instancias e escreve os resultados em um arquivo de texto
void rodar_guloso(){
    cout << "Rodando a abordagem gulosa. . ." << endl;
    ofstream out("Resultados/guloso_out.txt");
    
    out << "INSTANCIAS PEQUENAS:" << endl;
    
    for (int i = 0; i < instancias_pequenas.size(); i++){
        string instancia_atual = instancias_pequenas[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
        
        clock_t start = clock();
        
        Grafo *g = new Grafo(digrafo);
        g->criaLista(instancia_atual);
        
        out << "        Corte Mínimo: " << corteVerticesGuloso(g).size() << endl;
        out << "        Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl;
        
        delete g;
    }
    
    out << endl << "INSTANCIAS MEDIAS:" << endl;
    
    for (int i = 0; i < instancias_medias.size(); i++){
        string instancia_atual = instancias_medias[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
        
        clock_t start = clock();
        
        Grafo *g = new Grafo(digrafo);
        g->criaLista(instancia_atual);
        
        out << "        Corte Mínimo: " << corteVerticesGuloso(g).size() << endl;
        out << "        Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl;
        
        delete g;
    }
    
    out << endl << "INSTANCIAS GRANDES:" << endl;
    
    for (int i = 0; i < instancias_grandes.size(); i++){
        string instancia_atual = instancias_grandes[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
        
        clock_t start = clock();
        
        Grafo *g = new Grafo(digrafo);
        g->criaLista(instancia_atual);
        
        out << "        Corte Mínimo: " << corteVerticesGuloso(g).size() << endl;
        out << "        Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl;
        
        delete g;
    }
    
}

// Roda o algoritimo guloso randomizado para todas as intâncias 30 vezes
void rodar_guloso_rand(){
    ofstream out("Resultados/guloso_rand_out.txt");
    
    int iteracoes = 15;
    float alfa = 0.25;
    
    out << "INSTANCIAS PEQUENAS:" << endl;
    cout << "RODANDO INSTANCIAS PEQUENAS:" << endl;
    
    // Roda a abordagem gulosa randomica por 30 vezes para cada instância
    for (int i = 0; i < instancias_pequenas.size(); i++){
        string instancia_atual = instancias_pequenas[i];
         
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
         
        cout << "Instância: " << instancia_atual << endl;
        
        Grafo *g = new Grafo(digrafo);
        g->criaLista(instancia_atual);
         
        for (int j = 0; j < 30; j++){
             out << endl << "        Rodando pela " << j + 1 << "a vez de 30 vezes" << endl;
             
             clock_t start = clock();
             
             out << "            Corte Mínimo: " << corteVerticesGulosoRandomizado(g, alfa, iteracoes).size() << endl;
             out << "            Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl << endl;
        }
        
        delete g;
     }
     
     out << endl << "INSTANCIAS MEDIAS:" << endl;
     cout << endl << "RODANDO INSTANCIAS MEDIAS:" << endl;
    
    // Roda a abordagem gulosa randomica por 30 vezes para cada instância
    for (int i = 0; i < instancias_medias.size(); i++){
        string instancia_atual = instancias_medias[i];
         
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
         
         cout << "Instância: " << instancia_atual << endl;
         
        Grafo *g = new Grafo(digrafo);
        g->criaLista(instancia_atual);
         
         for (int j = 0; j < 30; j++){
             out << endl << "        Rodando pela " << j + 1 << "a vez de 30 vezes" << endl;
             
             clock_t start = clock();
             
             out << "            Corte Mínimo: " << corteVerticesGulosoRandomizado(g, alfa, iteracoes).size() << endl;
             out << "            Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl << endl;
         }
        
        delete g;
     }
    
    out << endl << "INSTANCIAS GRANDES:" << endl;
    cout << endl << "RODANDO INSTANCIAS GRANDES:" << endl;
    
    // Roda a abordagem gulosa randomica por 30 vezes para cada instância
    for (int i = 0; i < instancias_grandes.size(); i++){
        string instancia_atual = instancias_grandes[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
        
        cout << "Instância: " << instancia_atual << endl;
        
        Grafo *g = new Grafo(digrafo);
        g->criaLista(instancia_atual);
        
        for (int j = 0; j < 30; j++){
            out << endl << "        Rodando pela " << j + 1 << "a vez de 30 vezes" << endl;
            
            clock_t start = clock();
            
            out << "            Corte Mínimo: " << corteVerticesGulosoRandomizado(g, alfa, iteracoes).size() << endl;
            out << "            Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl << endl;
        }
        
        delete g;
    }
}

void rodar_guloso_rand_reativo(){
    ofstream out("Resultados/guloso_rand_reativo_out.txt");
    
    out << "INSTANCIAS PEQUENAS:" << endl;
    cout << "RODANDO INSTANCIAS PEQUENAS:" << endl;
    
    out.close();
    
    for (int i = 0; i < instancias_pequenas.size(); i++){
        out.open("Resultados/guloso_rand_reativo_out.txt", ios_base::app);
        
        string instancia_atual = instancias_pequenas[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl << endl;
        
        cout << "Instância: " << instancia_atual << endl;
        
        Grafo *g = new Grafo(digrafo);
        g->criaLista(instancia_atual);
        
        out.close();
        
        corteVerticesGulosoRandomizadoReativo(g);
        
        delete g;
    }
    
    out.close();
    out.open("Resultados/guloso_rand_reativo_out.txt", ios_base::app);
    
    out << "INSTANCIAS MEDIAS:" << endl;
    cout << "RODANDO INSTANCIAS MEDIAS:" << endl;
    
    out.close();
     
    for (int i = 0; i < instancias_medias.size(); i++){
        out.open("Resultados/guloso_rand_reativo_out.txt", ios_base::app);
        
        string instancia_atual = instancias_medias[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl << endl;
        
        cout << "Instância: " << instancia_atual << endl;
        
        Grafo *g = new Grafo(digrafo);
        g->criaLista(instancia_atual);
        
        corteVerticesGulosoRandomizadoReativo(g);
        
        out.close();
        
        delete g;
    }
    
    out.close();
    out.open("Resultados/guloso_rand_reativo_out.txt", ios_base::app);
    
    out << "INSTANCIAS GRANDES:" << endl;
    cout << "RODANDO INSTANCIAS GRANDES:" << endl;
    
    out.close();
    
    for (int i = 0; i < instancias_grandes.size(); i++){
        out.open("Resultados/guloso_rand_reativo_out.txt", ios_base::app);
        
        string instancia_atual = instancias_grandes[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl << endl;
        
        cout << "Instância: " << instancia_atual << endl;
        
        Grafo *g = new Grafo(digrafo);
        g->criaLista(instancia_atual);
        
        out.close();
        
        corteVerticesGulosoRandomizadoReativo(g);
        
        delete g;
    }
}
