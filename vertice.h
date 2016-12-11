//
//  vertice.hpp
//  Grafos
//
//  Created by Lucas Bressan on 9/20/16.
//  Copyright © 2016 Lucas Bressan. All rights reserved.
//

#ifndef vertice_hpp
#define vertice_hpp

#include <iostream>

using namespace std;

class Vertice {

private:
    
    int id;
    int peso;
    int grau;
    bool invisivel;

public:

    Vertice(int id, int peso);
    Vertice(int id);
    int getId();
    int getPeso();
    int getGrau();
    void incrementaGrau();
    void diminuiGrau();
    void setInvisivel(bool trueOrFalse);
    bool getInvisivel();
    // ~Vertice();

};

#endif /* vertice_hpp */
