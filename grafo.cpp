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
#include <vector>
#include <limits>

#include "grafo.h"
#include "lista.h"

using namespace std;

Grafo::Grafo(bool flagDir){
    this->numVertices = 0;
    this->numArestas = 0;
    this->flagDir = flagDir;
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
 Dado um Id a função cria um novo vertice com o Id passado como parametro
 */
void Grafo::addVertice(int id){
    l->addNoVertical(id);
    this->numVertices++;
}

/*
 Dado o id de dois vertices, esta função cria uma aresta entre o vertice id1 e id2 com peso pesoAresta
 Caso um dos vertices dados não exista (e o grafo nao seja direcionado), esta função o cria.
 */
void Grafo::addAresta(int id1, int id2, int pesoAresta){
    l->addNo(id1, id2, pesoAresta, this->flagDir);
    this->numArestas++;
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
    if (anterior->getId() == id){
        l->setStart(anterior->getProxVertical());
        delete(anterior);
    } else {
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
    setNumVertices(getNumVertices() - 1);
}

/*
 Dado os IDs de dois vertices, esta função deleta a aresta entre os dois
 */
void Grafo::deletaAresta(int id1, int id2){
    
    if (!this->flagDir){
        for (int i = 0; i < 2; i++) {
            
            int idVertical = id1;
            int idHorizontal = id2;
            
            if (i == 1){
                idVertical = id2;
                idHorizontal = id1;
            }
            
            NoLista *startId = l->buscarNoVertical(idVertical);
            
            if (startId->getProxHorizontal() == NULL){
                continue;
            }
            
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
            startId->getVertice()->diminuiGrau();
        }
    } else {
        int idHorizontal = id2;
        
        NoLista *startId = l->buscarNoVertical(id1);
        
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
    } setNumArestas(getNumArestas() - 1);
}

/*
 Dado um arquivo e uma lista, esta função popula a lista de adjacência dada
 com as informações obtidas a aprtir da leitura deste arquivo
 */
void Grafo::criaLista(string nomeArquivo){
    ifstream arquivo(nomeArquivo.c_str());
    char str[255];
    
    // Adiciona o numero de vertices descrito no arquivo no grafo
    arquivo.getline(str, 255);
    int numVerticesArquivo = stoi(str);
    
    for (int i = 1; i <= numVerticesArquivo; i++) {
        addVertice(i);
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
            
            addAresta(valor1, valor2, pesoAresta);
            
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

/* Função auxiliar da buscaEmProfundidade*/
void Grafo::auxBuscaEmProfundidade(NoLista *aux, vector<int> visitados, vector<int> *busca){
    
    while (aux != NULL){
        vector<int>::iterator it = find(visitados.begin(), visitados.end(), aux->getId());
        if (it == visitados.end()){
            visitados.push_back(aux->getId());
            busca->push_back(aux->getId());
            auxBuscaEmProfundidade(aux->getVertical(), visitados, busca);
        }
        aux = aux->getProxHorizontal();
    }
}

/* Dado o id de um nó, função chama uma função auxiliar para retornar um vetor de id's fazendo uma busca em profundidade*/
vector<int> Grafo::buscaEmProfundidade(int id){
    NoLista *aux = (this->l)->buscarNoVertical(id);
    vector<int> visitados;
    vector<int> *lista = new vector<int>;
    
    auxBuscaEmProfundidade(aux, visitados, lista);
    
    return *lista;
}

/*
 Dado o id de um nó, função chama uma função auxiliar para retornar um vetor de id's fazendo uma busca em largura
 */
vector<int> Grafo::buscaEmLargura(int id){
    vector<int> sequencia;
    vector<int> visitados;
    
    vector<int> fila;
    visitados.push_back(id);
    fila.push_back(id);
    
    NoLista* aux = (this->l)->buscarNoVertical(id)->getProxHorizontal();
    
    while (fila.size() != 0){
        sequencia.push_back(fila[0]);
        fila.erase(fila.begin());
        
        while (aux != NULL){
            vector<int>::iterator it = find(visitados.begin(), visitados.end(), aux->getId());
            
            if (it == visitados.end()){
                visitados.push_back(aux->getId());
                fila.push_back(aux->getId());
            }
            
            aux = aux->getProxHorizontal();
        }
        
        aux = this->l->buscarNoVertical(fila[0]);
    }
    
    return sequencia;
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

/*
 Dado um vertice, esta função verifica se ele é fonte ou não (digrafo)
 */
bool Grafo::verificaFonte(int id){
    
    if (!this->flagDir){
        return false;
    }
    
    NoLista* aux = (this->l)->getStart();

    
    while (aux != NULL) {
        if((this->l)->buscarNoHorizontal(aux, id) != NULL){
            return false;
        }
        aux = aux->getProxVertical();
    }
    
    return true;
}

/*
 Dado um grafo direcionado esta função retorna um vecotor<int> contendo
 a ordenação topologica do grafo caso este seja um DAG. Caso contrário, a função retorna um vecotor<int> com um único
 elemento com o valor de -1.
 */
vector<int> Grafo::getOrdenacaoTopologicaDAG(){
    
    vector<int> dag;
    vector<int> nosFonte;
    vector<int> retornaNaoDAG;
    
    retornaNaoDAG.push_back(-1);
    
    if (!this->flagDir){
        return retornaNaoDAG;
    }
    
    Grafo *gAux = copiaGrafo(this);
    NoLista *auxVertical = (gAux->l)->getStart();
    
    while (auxVertical != NULL){
        if (gAux->verificaFonte(auxVertical->getId())){
            nosFonte.push_back(auxVertical->getId());
        }
        auxVertical = auxVertical->getProxVertical();
    }
    
    while (!nosFonte.empty()){
        int noAtual = nosFonte[0];
        dag.push_back(nosFonte[0]);
        nosFonte.erase(nosFonte.begin());
        
        auxVertical = gAux->l->buscarNoVertical(noAtual);
        NoLista *auxHorizontal = auxVertical->getProxHorizontal();
        
        while (auxHorizontal != NULL){
            int idHorizontalAtual = auxHorizontal->getId();
            gAux->deletaAresta(noAtual, idHorizontalAtual);
            if (gAux->verificaFonte(idHorizontalAtual)){
                nosFonte.push_back(idHorizontalAtual);
            }
            auxHorizontal = auxHorizontal->getProxHorizontal();
        }
    }
    
    // cout << gAux->getNumArestas() << endl;
    // gAux->print();
    
    if (gAux->numArestas > 0){
        return retornaNaoDAG;
    } else {
        return dag;
    }
}

/*Verifica se o grafo é conexo retorna um bool */
bool Grafo::verificaConexo(){
    vector<int> vetor = this->buscaEmLargura((this->l->getStart())->getId());
    if(vetor.size() == this->numVertices){
        return true;
    }
    else return false;
}

/*
 Dado dois nos esta funcao verifica se ambos pertencem a mesma componente conexa
 */
bool Grafo::verificaMesmaComponenteConexa(int id1, int id2){
    vector<int> vetor = this->buscaEmLargura((this->l)->getStart()->getId());
    vector<int>::iterator it1 = find(vetor.begin(), vetor.end(), id1);
    vector<int>::iterator it2 = find(vetor.begin(), vetor.end(), id2);
    if((it1 != vetor.end()) && (it2 != vetor.end()))
        return true;
    else return false;
}

/*
 Faz uma busca no grafo e caso encontre um no fonte, retorna seu id (retorna sempre o primeiro nó fonte encontrado). Caso não encontre nenhum, retorna -1.
 Caso o grafo não seja direcionado, esta funcao retorna o primeiro vertice que possua adjacentes encontrado.
 */
int Grafo::buscaNoFonte(){
    
    if (!this->flagDir){
        NoLista* verticalAux = l->getStart();
        
        while (verticalAux != NULL){
            if (verticalAux->getProxHorizontal() != NULL){
                return verticalAux->getId();
            }
            verticalAux = verticalAux->getProxVertical();
        }
        return -1;
    }
    
    vector<int> nosNaoFonte;
    NoLista* verticalAux = l->getStart();
    
    for (int i = 0; i < this->numVertices; i++){
        
        NoLista* horizontalAux = verticalAux->getProxHorizontal();
        
        while (horizontalAux != NULL){
            
            vector<int>::iterator it = find(nosNaoFonte.begin(), nosNaoFonte.end(), horizontalAux->getId());
            
            if (it == nosNaoFonte.end()){
                nosNaoFonte.push_back(horizontalAux->getId());
            }
            
            horizontalAux = horizontalAux->getProxHorizontal();
        }
        
        verticalAux = verticalAux->getProxVertical();
    }
    
    verticalAux = l->getStart();
    
    for (int i = 0; i < this->numVertices; i++){
        
        vector<int>::iterator it = find(nosNaoFonte.begin(), nosNaoFonte.end(), verticalAux->getId());
        if ((it == nosNaoFonte.end()) && (verticalAux->getProxHorizontal() != NULL)) {
            return verticalAux->getId();
        }
        
        verticalAux = verticalAux->getProxVertical();
    }
    
    return -1;
}

/*
 Retorna um novo grafo identico ao grafo g passado como parametro
 */
Grafo* Grafo::copiaGrafo(Grafo* g){
    Grafo* novo = new Grafo(g->flagDir);
    
    novo->l = new Lista();
    
    NoLista* verticalAux = (g->l)->getStart();
    NoLista* horizontalAux;
    
    while (verticalAux != NULL){
        (novo->l)->addNoVertical(verticalAux->getId());
        verticalAux = verticalAux->getProxVertical();
    }
    
    verticalAux = (g->l)->getStart();
    
    while (verticalAux != NULL){
        
        horizontalAux = verticalAux->getProxHorizontal();
        
        while (horizontalAux != NULL){
            if (!(novo->verificaAdjacente(verticalAux->getId(), horizontalAux->getId()))){
                novo->addAresta(verticalAux->getId(), horizontalAux->getId(), horizontalAux->getPesoAresta());
            }
            horizontalAux = horizontalAux->getProxHorizontal();
        }
        
        verticalAux = verticalAux->getProxVertical();
    }
    
    novo->numVertices = g->numVertices;
    novo->numArestas = g->numArestas;
    novo->grauGrafo = g->grauGrafo;
    
    return novo;
}

/*
 Dado um id de um no, esta função retorna se o nó passado como parametro é de articulacao ou não (retorna true caso o vertice seja de articulacao)
 */
bool Grafo::verificaNoArticulacao(int id){
    
    // Cria grafo auxiliar identico ao nosso grafo original
    Grafo *aux = copiaGrafo(this);
    
    // Encontra um nó que seja fonte
    NoLista *verticeAux = (aux->l)->buscarNoVertical(aux->buscaNoFonte());
    
    vector<int> antes = aux->buscaEmProfundidade(verticeAux->getId());
    
    aux->deletaVertice(id);
    verticeAux = (aux->l)->buscarNoVertical(aux->buscaNoFonte());
    vector<int> depois = aux->buscaEmProfundidade(verticeAux->getId());
    
    if(antes.size() == depois.size() + 1)
        return false;
    
    else return true;
}

/*
 Dado dois nós com uma aresta entre eles, esta funcao retorna se a aresta é ponte ou não (retorna true caso a aresta seja ponte)
 */
bool Grafo::verificaArestaPonte(int id1, int id2){
    
    // Cria grafo auxiliar identico ao nosso grafo original
    Grafo *aux = copiaGrafo(this);
    
    // Encontra um nó que seja fonte
    NoLista *verticeAux = (aux->l)->buscarNoVertical(aux->buscaNoFonte());
    
    vector<int> antes = aux->buscaEmProfundidade(verticeAux->getId());
    
    
    aux->deletaAresta(id1, id2);
    verticeAux = (aux->l)->buscarNoVertical(aux->buscaNoFonte());
    vector<int> depois = aux->buscaEmProfundidade(verticeAux->getId());
    
    if(antes.size() == depois.size())
        return false;
    
    else return true;
}

/*
 Retorna um vector contendo o caminho minimo entre id1 e id2.
 */
vector<int> Grafo::dijkstra(int id1, int id2){
    vector<int> caminho;
    vector<int> visitado;
    
    visitado.push_back(id1);
    
    return caminho;
}

/*
 Retorna uma matriz de vectors contendo o caminho minimo entre todos os pares de vertices do grafo. O valor 100000 na matriz corresponde a infinito.
 */
vector<vector<int>> Grafo::floyd(){
    vector<vector<int>> dist(numVertices, vector<int> (numVertices, 100000));
    
    for (int i = 0; i < this->numVertices; i++){
        dist[i][i] = 0;
    }
    
    NoLista *verticalAux = (this->l)->getStart();
    NoLista *horizontalAux;
    
    while (verticalAux != NULL){
        horizontalAux = verticalAux->getProxHorizontal();
        while (horizontalAux != NULL){
            dist[verticalAux->getId() - 1][horizontalAux->getId() - 1] = horizontalAux->getPesoAresta();
            horizontalAux = horizontalAux->getProxHorizontal();
        }
        verticalAux = verticalAux->getProxVertical();
    }
    
    for (int k = 0; k < this->numVertices; k++){
        for (int i = 0; i < this->numVertices; i++){
            for (int j = 0; j < this->numVertices; j++){
                if (dist[i][j] > dist[i][k] + dist[k][j] && i != j){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    return dist;
}

/*
 Dado um subconjunto de vertices de um grafo, esta função retorna o subgrafo induzido pelo conjunto passado.
 */
Grafo* Grafo::getSubgrafo(vector<int> vertices){
    Grafo *novo = new Grafo(this->flagDir);
    novo = novo->copiaGrafo(this);
    
    vector<int> verticesParaRemover;
    
    NoLista *auxVertical = (novo->l)->getStart();
    vector<int>::iterator it;
    
    while (auxVertical != NULL){
        it = find(vertices.begin(), vertices.end(), auxVertical->getId());
        
        if (it == vertices.end()){
            verticesParaRemover.push_back(auxVertical->getId());
        }
        
        auxVertical = auxVertical->getProxVertical();
    }
    
    printBusca(verticesParaRemover);
    
    for (int i = 0; i < verticesParaRemover.size(); i++){
        novo->deletaVertice(verticesParaRemover[i]);
    }
    
    return novo;
}

/*
 Retorna um vector bi-dimensional contendo todas as componentes conexas do grafo.
 */
vector<vector<int>> Grafo::getComponentesConexas(){
    vector<vector<int>> componentesConexas;
    int numComponentesConexas = 0;
    
    vector<int> caminhoAtual;
    
    NoLista *aux = (this->l)->getStart();
    
    caminhoAtual = this->buscaEmLargura(aux->getId());
    componentesConexas.push_back(vector<int>());
    componentesConexas[0] = caminhoAtual;
    numComponentesConexas++;
    aux = aux->getProxVertical();
    
    vector<int>::iterator it;
    
    while (aux != NULL){
        int j = 0;
        for (j = 0; j < numComponentesConexas; j++){
            it = find(componentesConexas[j].begin(), componentesConexas[j].end(), aux->getId());
            if (it != componentesConexas[j].end()){
                break;
            }
        }
        
        if (j == numComponentesConexas){
            caminhoAtual = this->buscaEmLargura(aux->getId());
            componentesConexas.push_back(vector<int>());
            componentesConexas[numComponentesConexas] = caminhoAtual;
            numComponentesConexas++;
        }
        
        aux = aux->getProxVertical();
    }
    
    return componentesConexas;
}

/*
 Verifica se o grafo é Euleriano (verifica se o grafo é conexo e se todos os graus de seus vertices são pares)
 */
bool Grafo::verificaEuleriano(){
    NoLista *aux = (this->l)->getStart();
    
    if (!this->verificaConexo()){
        return false;
    }
    
    while (aux != NULL){
        if ((aux->getVertice())->getGrau() % 2 != 0){
            return false;
        }
        aux = aux->getProxVertical();
    }
    
    return true;
}

/*Dado um vetor de inteiros imprime a mesma*/
void Grafo::printBusca(vector<int> lista){
    for(int i=0;i<lista.size();i++){
        cout << lista.at(i) << " ";
    }
    cout << endl;
}

void Grafo::print(){
    l->print();
}

Grafo::~Grafo(){
    cout<<"Done!"<<endl;
}
