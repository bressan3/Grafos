//
//  corte.h
//  Grafos
//
//  Created by Lucas Bressan on 11/21/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//
//  Arquivo que implementa os algorítimos guloso, guloso randomizado e guloso randomizado reativo.

#ifndef corte_h
#define corte_h

#include <stdio.h>
#include "grafo.h"

vector<int> corteVerticesGuloso(Grafo *g, string nomeArquivo);

vector<int> corteVerticesGulosoRandomizado(Grafo *g, float alpha, int iteracoes, string nomeArquivo);

vector<int> corteVerticesGulosoRandomizadoReativo(Grafo *g, string nomeArquivo);

#endif /* corte_h */
