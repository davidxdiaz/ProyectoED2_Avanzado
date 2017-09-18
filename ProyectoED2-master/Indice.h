//
// Created by David on 17/9/2017.
//

#ifndef PROYECTOED2_MASTER_INDICE_H
#define PROYECTOED2_MASTER_INDICE_H

#include "registro.h"

class Indice {
public:
    bool insertar(char * id);
    Registro * buscar(char * id);
    void reHash();
    int M;
};


#endif //PROYECTOED2_MASTER_INDICE_H
