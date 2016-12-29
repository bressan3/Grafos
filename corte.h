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

vector<int> corteVerticesGuloso(Grafo *g);

vector<int> corteVerticesGulosoRandomizado(Grafo *g, float alpha, int iteracoes);

vector<int> corteVerticesGulosoRandomizadoReativo(Grafo *g);

void rodar_guloso();

void rodar_guloso_rand();

void rodar_guloso_rand_reativo();

#endif /* corte_h */
