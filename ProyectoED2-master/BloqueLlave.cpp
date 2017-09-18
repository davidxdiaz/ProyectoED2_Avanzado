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
    for(int c=0;c<17;c++)
        llaves[c]=0;
    archivo=a;
}


void BloqueLlave::actualizarCantidad()
{
    cantidad++;
}

char * BloqueLlave::toChar()
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
    for(int c=0;c<17;c++)
    {
        if(llaves[c] != 0)
            memcpy(&data[pos],llaves[c]->toChar(),28);
        pos+=28;
    }
    return data;
}

void BloqueLlave::initFromChar(char * data)
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

void BloqueLlave::escribir()
{
    char * data= this->toChar();
    int pos= nBloque * tamano+20;
    archivo->escribir(data,pos,tamano);
}

void BloqueLlave::cargar()
{
    int pos= nBloque * tamano+20;
    char * data= archivo->leer(pos,tamano);
    initFromChar(data);
}