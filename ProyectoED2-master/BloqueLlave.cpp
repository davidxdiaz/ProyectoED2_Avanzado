//
// Created by David on 17/9/2017.
//

#include "BloqueLlave.h"
#include "string.h"

BloqueLlave::BloqueLlave(DataFile * a,int nB)
{
    nBloque=nB;
    siguiente=-1;
    tamano=512;
    cantidad=0;
    for(int c=0;c<62;c++)
        llaves[c]=0;
    archivo=a;
}


void BloqueLlave::actualizarCantidad()
{
    cantidad++;
}

char * BloqueIndice::toChar()
{
    int pos=0;
    char * data= new char[tamano];
    memcpy(&data[pos],&nBloque,4);
    pos+=4;
    memcpy(&data[pos],&tamano,4);
    pos+=4;
    memcpy(&data[pos],&siguiente,4);
    pos+=4;
    memcpy(&data[pos],&cantidad,4);
    pos+=4;
    for(int c=0;c<62;c++)
    {
        if(indice[c] != 0)
            memcpy(&data[pos],indice[c]->toChar(),8);
        pos+=8;
    }
    return data;
}

void BloqueIndice::initFromChar(char * data)
{
    int pos=0;
    memcpy(&nBloque,&data[pos],4);
    pos+=4;
    memcpy(&tamano,&data[pos],4);
    pos+=4;
    memcpy(&siguiente,&data[pos],4);
    pos+=4;
    memcpy(&cantidad,&data[pos],4);
    pos+=4;
}

void BloqueIndice::escribir()
{
    char * data= this->toChar();
    int pos= nBloque * tamano+20;
    archivo->escribir(data,pos,tamano);
}

void BloqueIndice::cargar()
{
    int pos= nBloque * tamano+20;
    char * data= archivo->leer(pos,tamano);
    initFromChar(data);
}