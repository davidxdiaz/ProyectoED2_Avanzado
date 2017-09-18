//
// Created by David on 17/9/2017.
//

#include "Indice.h"
#include "BloqueIndice.h"
#include "HashTableEntry.h"
#include "BloqueLlave.h"


Indice::Indice(DataFile * a, int primer,int actual,int maximo)
{
    archivo=a;
    primerBIndice=primer;
    actualBIndice=actual;
    M=maximo;
}

bool Indice::insertar(char * id,int nBloque,int nRegistroR,ManejadordeBloques * mb)
{
    int pos= hash(id);
    if(buscar(id)!=0){
        Idx_Entry * entrada= new Idx_Entry(id,nBloque,nRegistroR);
        int cont=0;
        for(int x=0;x<pos;x+=62){
            cont++;
        }
        int bloqueActual = primerBIndice;
        for(int c=0;c<cont;c++)
        {
            BloqueIndice * bIndice= new BloqueIndice(archivo,bloqueActual);
            bIndice->cargar();
            bloqueActual=bIndice->siguiente;
            delete bIndice;
        }
        cont--;
        int posDef= pos - (cont * 62);
        BloqueIndice * bloque= new BloqueIndice(archivo,bloqueActual);
        bloque->cargar();
        HashTableEntry * entry= bloque->getEntrada(posDef);
        if(entry->primerBloqueLLave==-1)
        {
            Bloque * b = mb->asignarNueboBloque();
            BloqueLlave * bLlave= new BloqueLlave(archivo,b->nBloque);
            bLlave->llaves[0]=entrada;
            bLlave->actualizarCantidad();
            entry->primerBloqueLLave=bLlave->nBloque;
            entry->actualBloqueLLave=bLlave->nBloque;
            bloque->escribir();//Porque actualice uno de sus entry
            bLlave->escribir();
            return true;

        }
        int bloqueLlaves= entry->actualBloqueLLave;
        BloqueLlave * b = new BloqueLlave(archivo,bloqueLlaves);
        b->cargar();
        int posicion=b->cantidad;
        if(posicion<17)
        {
            b->llaves[posicion]=entrada;
            return true;
        }
        else
        {
            Bloque * block = mb->asignarNueboBloque();
            BloqueLlave *bLlave = new BloqueLlave(archivo,block->nBloque);
            bLlave->llaves[0]=entrada;
            bLlave->actualizarCantidad();
            entry->actualBloqueLLave=bLlave->nBloque;
            bloque->escribir();//Porque actualice uno de sus entry
            bLlave->escribir();
            return true;
        }
    }
    return false;
}

int Indice::hash(char * id)
{
    int clave=0;
    int ascii;
    for(int c=0;id[c]!='\0';c++)
    {
        ascii = (int)(id[c]);
        clave+=ascii;
    }
    return clave%M;
}

Idx_Entry * Indice::buscar(char * id)
{
    int pos = hash(id);
    int cont=0;
    for(int x=0;x<pos;x+=62){
        cont++;
    }
    int bloqueActual = primerBIndice;
    for(int c=0;c<cont;c++)
    {
        BloqueIndice * bIndice= new BloqueIndice(archivo,bloqueActual);
        bIndice->cargar();
        bloqueActual=bIndice->siguiente;
        delete bIndice;
    }
    cont--;
    int posDef= pos - (cont * 62);
    BloqueIndice * bloque= new BloqueIndice(archivo,bloqueActual);
    bloque->cargar();
    HashTableEntry * entry= bloque->getEntrada(posDef);
    int bloqueLlaves = entry->primerBloqueLLave;

    while (bloqueLlaves <= entry->actualBloqueLLave){
        BloqueLlave * b= new BloqueLlave(archivo,bloqueLlaves);
        b->cargar();
        for (int c = 0; c < b->cantidad; c++) {
            Idx_Entry *entrada = b->llaves[c];
            if (strcmp(entrada->id,id)==0) {
                return entrada;
            }
            delete entrada;
        }
        bloqueLlaves = b->siguiente;
        delete b;
    }
    return 0;
}