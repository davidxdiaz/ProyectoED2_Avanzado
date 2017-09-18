//
// Created by David on 17/9/2017.
//

#ifndef PROYECTOED2_MASTER_INDICE_H
#define PROYECTOED2_MASTER_INDICE_H
#include "Idx_Entry.h"
#include "datafile.h"
#include "manejadordebloques.h"
class Indice {
public:
    Indice(DataFile * a,int primerBIndice,int actualBIndice,int maximo);
    int primerBIndice;
    int actualBIndice;
    bool insertar(char * id,int nBloque,int nRegistroR,ManejadordeBloques * mb);
    Idx_Entry * buscar(char * id);
    void reHash(ManejadordeBloques * mB);
    int hash(char *id);
    int M;
    DataFile * archivo;
};


#endif //PROYECTOED2_MASTER_INDICE_H
