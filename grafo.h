#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>
#include <vector>

#include "lista.h"

using namespace std;

class Grafo {

private:
    
    int numVertices;
    int numArestas;
    bool flagDir;
    int grauGrafo;
    Lista *l;

public:
    
    Grafo(bool flagDir);
    int getNumVertices();
    void setNumVertices(int numNos);
    
    int getNumArestas();
    void setNumArestas(int numArestas);
    
    void setGrauGrafo();
    int getGrauGrafo();
    
    Lista* getLista();
    
    void addVertice(int id);
    void addAresta(int id1, int id2, int peso);
    void deletaVertice(int id);
    void deletaAresta(int id1, int id2);
    
    void criaLista(string nomeArquivo);
    
    int* getSequenciaGraus();
    
    int verificaKRegular();
    
    bool verificaCompleto();
    
    bool verificaAdjacente(int id1, int id2);
    
    vector<int> buscaEmLargura(int id);
    
    void auxBuscaEmProfundidade(NoLista *aux, vector<int> lista, vector<int> *busca);
    vector<int> buscaEmProfundidade(int id);
    
    int* getVizinhancaAberta(int id);
    int* getVizinhancaFechada(int id);
    
    bool verificaFonte(int id);
    
    vector<int> getOrdenacaoTopologicaDAG();
    
    bool verificaConexo();
    bool verificaMesmaComponenteConexa(int id1, int id2);
    
    int buscaNoFonte();
    
    Grafo* copiaGrafo(Grafo *g);
    
    bool verificaArestaPonte(int id1, int id2);
    bool verificaNoArticulacao(int id);
    
    vector<int> dijkstra(int id1, int id2);
    
    int getPosicao(int id);
    int getIdLista(int pos);
    vector<vector<vector<int>>> floyd();
    
    vector<int> getFechoTransitivoDireto(int id);
    vector<int> getFechoTransitivoIndireto(int id);
    
    Grafo* getSubgrafo(vector<int> vertices);
    
    vector<vector<int>> getComponentesConexas();
    
    Grafo* produtoCartesiano(Grafo* g);
    
    Grafo* prim();
    
    Grafo* kruskal();
    
    bool verificaKConexo(int k);
    
    bool verificaEuleriano();
    
    // Debugging functions
    void printBusca(vector<int> lista);
    void print();
    
    ~Grafo();

};

#endif
