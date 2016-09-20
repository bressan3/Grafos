//
//  aresta.hpp
//  Grafos
//
//  Created by Lucas Bressan on 9/20/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//

#ifndef aresta_hpp
#define aresta_hpp

#include <iostream>

using namespace std;

class Aresta {

private:
    int peso;
    
public:
    Aresta();
    Aresta(int peso);
    int getPeso();

};


#endif /* aresta_hpp */
