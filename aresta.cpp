//
//  aresta.cpp
//  Grafos
//
//  Created by Lucas Bressan on 9/20/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//

#include <iostream>
#include "aresta.h"

using namespace std;

Aresta::Aresta(){
    this->peso = 0;
}

Aresta::Aresta(int peso){
    this->peso = peso;
}
