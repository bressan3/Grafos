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

void Grafo::setNumNos(int numNos){
    this->numNos = numNos;
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
        int pesoAresta = 0;
        
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
    
    l->print();
}


Grafo::~Grafo(){
    cout<<"Done!"<<endl;
}
