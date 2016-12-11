/*
    * Arquivo de testes
    * COMIPLAR USANDO C++ 11: g++ -std=c++11 *.cpp -o bin
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "grafo.h"
#include "lista.h"
#include "corte.h"

using namespace std;

// string nomeArquivo = "list_debugging_file";

string nomeArquivo = "Instancias Grafos/grafo_1000_6.txt";

vector<string> instancias_pequenas = {"Instancias Grafos/grafo_1000_4.txt", "Instancias Grafos/grafo_1000_8.txt", "Instancias Grafos/grafo_10000_8.txt", "Instancias Grafos/grafo_10000_4.txt"};
vector<string> instancias_medias = {"Instancias Grafos/grafo_10000_3.txt", "Instancias Grafos/grafo_1000_3.txt", "Instancias Grafos/grafo_10000_7.txt"};
vector<string> instancias_grandes = {"Instancias Grafos/grafo_1000_6.txt", "Instancias Grafos/grafo_10000_6.txt", "Instancias Grafos/grafo_10000_2.txt"};

bool digrafo = false;

// Roda o algoritimo guloso para todas as instancias e escreve os resultados em um arquivo de texto
void rodar_guloso(){
    ofstream out("Resultados/guloso_out.txt");
    
    out << "INSTANCIAS PEQUENAS:" << endl;
    
    for (int i = 0; i < instancias_pequenas.size(); i++){
        string instancia_atual = instancias_pequenas[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl;

        clock_t start = clock();
        
        Grafo *g = new Grafo(digrafo);
        g->criaLista(instancia_atual);
        
        out << "        Corte Mínimo: " << corteVerticesGuloso(g, instancia_atual).size() << endl;
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
        
        out << "        Corte Mínimo: " << corteVerticesGuloso(g, instancia_atual).size() << endl;
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
        
        out << "        Corte Mínimo: " << corteVerticesGuloso(g, instancia_atual).size() << endl;
        out << "        Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl;
        
        delete g;
    }
    
}

// Roda o algoritimo guloso randomizado para todas as intâncias 30 vezes cada uma com o alfa = 0.5 e 5 interações
void rodar_guloso_rand(Grafo* g){
    ofstream out("Resultados/guloso_rand_out.txt");
    
    /*out << "INSTANCIAS PEQUENAS:" << endl;
    cout << "RODANDO INSTANCIAS PEQUENAS:" << endl;
    
    for (int i = 0; i < instancias_pequenas.size(); i++){
        string instancia_atual = instancias_pequenas[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
        
        cout << "Instância: " << instancia_atual << endl;
        
        delete g->getLista();
        g->criaLista(instancia_atual);
        
        for (int j = 0; j < 30; j++){
            out << endl << "        Rodando pela " << j + 1 << "a vez de 30 vezes" << endl;
            
            clock_t start = clock();

            out << "            Corte Mínimo: " << corteVerticesGulosoRandomizado(g, 0.25, 5, instancia_atual).size() << endl;
            out << "            Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl << endl;
        }
    }
    
    out << endl << "INSTANCIAS MEDIAS:" << endl;
    cout << endl << "RODANDO INSTANCIAS MEDIAS:" << endl;
    
    for (int i = 0; i < instancias_medias.size(); i++){
        string instancia_atual = instancias_medias[i];
     
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
     
        cout << "Instância: " << instancia_atual << endl;
        
        delete g->getLista();
        g->criaLista(instancia_atual);
        
        for (int j = 0; j < 30; j++){
            out << endl << "        Rodando pela " << j + 1 << "a vez de 30 vezes" << endl;
     
            clock_t start = clock();
     
            out << "            Corte Mínimo: " << corteVerticesGulosoRandomizado(g, 0.25, 5, instancia_atual).size() << endl;
            out << "            Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl << endl;
        }
     }*/
    
    out << endl << "INSTANCIAS GRANDES:" << endl;
    cout << endl << "RODANDO INSTANCIAS GRANDES:" << endl;
    
    for (int i = 0; i < 1; i++){
        string instancia_atual = "Instancias Grafos/grafo_10000_6.txt"; // instancias_grandes[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
        
        cout << "Instância: " << instancia_atual << endl;
        
        delete g;
        Grafo *g = new Grafo(false);
        g->criaLista(instancia_atual);
        
        for (int j = 0; j < 30; j++){
            out << endl << "        Rodando pela " << j + 1 << "a vez de 30 vezes" << endl;
            
            clock_t start = clock();
            
            out << "            Corte Mínimo: " << corteVerticesGulosoRandomizado(g, 0.25, 5, instancia_atual).size() << endl;
            out << "            Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl << endl;
        }
    }
}

void rodar_guloso_rand_reativo(Grafo *g){
    ofstream out("Resultados/guloso_rand_reativo_out.txt");
    
    /*out << "INSTANCIAS PEQUENAS:" << endl;
    cout << "RODANDO INSTANCIAS PEQUENAS:" << endl;
    
    for (int i = 0; i < instancias_pequenas.size(); i++){
        string instancia_atual = instancias_pequenas[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
        
        cout << "Instância: " << instancia_atual << endl;
        
        delete g->getLista();
        g->criaLista(instancia_atual);
        
        for (int j = 0; j < 30; j++){
            out << endl << "        Rodando pela " << j + 1 << "a vez de 30 vezes" << endl;
            
            clock_t start = clock();
            
            out << "            Corte Mínimo: " << corteVerticesGulosoRandomizadoReativo(g, instancia_atual).size() << endl;
            out << "            Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl << endl;
        }
    }
    
    out << "INSTANCIAS MEDIAS:" << endl;
    cout << "RODANDO INSTANCIAS MEDIAS:" << endl;
    
    for (int i = 0; i < instancias_medias.size(); i++){
        string instancia_atual = instancias_medias[i];
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
        
        cout << "Instância: " << instancia_atual << endl;
        
        delete g->getLista();
        g->criaLista(instancia_atual);
        
        for (int j = 0; j < 30; j++){
            out << endl << "        Rodando pela " << j + 1 << "a vez de 30 vezes" << endl;
            
            clock_t start = clock();
            
            out << "            Corte Mínimo: " << corteVerticesGulosoRandomizadoReativo(g, instancia_atual).size() << endl;
            out << "            Tempo: " << (clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << endl << endl;
        }
    }*/
    
    out << "INSTANCIAS GRANDES:" << endl;
    cout << "RODANDO INSTANCIAS GRANDES:" << endl;
    
    for (int i = 0; i < 1; i++){
        string instancia_atual = "Instancias Grafos/grafo_10000_3.txt";
        
        out << endl;
        out << "    Instância: " << instancia_atual << endl;
        
        cout << "Instância: " << instancia_atual << endl;
        
        delete g->getLista();
        g->criaLista(instancia_atual);
        
        corteVerticesGulosoRandomizadoReativo(g, instancia_atual);
    }
}

int main(int argc, char const *argv[])
{
    Grafo *g = new Grafo(digrafo);
    
    // g->criaLista(nomeArquivo);
    
    // g->printBusca(corteVerticesGulosoRandomizado(g, 0.25, 5, nomeArquivo));
    
    /*cout << g->getComponentesConexas().size() << endl;
    
    g->deletaVertice(3);
    g->deletaVertice(4);
    
    cout << g->getComponentesConexas().size() << endl;*/
    
    // rodar_guloso();
    
    // rodar_guloso_rand(g);
    
    rodar_guloso_rand_reativo(g);
    
    return 0;
}
