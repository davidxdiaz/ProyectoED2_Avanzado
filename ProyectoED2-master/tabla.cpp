#include "tabla.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "listcampos.h"
#include "bloquecampo.h"
#include "datafile.h"
#include "bloqueregistro.h"
#include "registro.h"
#include "campodatos.h"
#include "listregistros.h"
#include "manejadordebloques.h"
#include "listbloquetablas.h"
#include "bloquecampo.h"
#include "registro.h"
using namespace std;

tabla::tabla(char name[20],int i,int pBCampos,int actualBCampos,int pBDatos,int actualBDatos,int nB,DataFile *a)
{
    archivo=a;
    strncpy(nombre,name,20);
    id=i;
    primerBloqueCampos=pBCampos;
    actualBloqueCampos=actualBCampos;
    primerBloqueDatos=pBDatos;
    actualBloqueDatos=actualBDatos;
    nBloque=nB;
    sig=0;
    campos= new ListCampos();
    registros= new ListRegistros();
}


char * tabla::toChar()
{
    char * data= new char[44];
    int pos=0;
    memcpy(&data[pos],nombre,20);
    pos+=20;
    memcpy(&data[pos],&id,4);
    pos+=4;
    memcpy(&data[pos],&primerBloqueCampos,4);
    pos+=4;
    memcpy(&data[pos],&actualBloqueCampos,4);
    pos+=4;
    memcpy(&data[pos],&primerBloqueDatos,4);
    pos+=4;
    memcpy(&data[pos],&actualBloqueDatos,4);
    pos+=4;
    memcpy(&data[pos],&nBloque,4);
    pos+=4;
    return data;
}

void tabla::charToTabla(char * data)
{
    int pos=0;
    memcpy(nombre,&data[pos],20);
    pos+=20;
    memcpy(&id,&data[pos],4);
    pos+=4;
    memcpy(&primerBloqueCampos,&data[pos],4);
    pos+=4;
    memcpy(&actualBloqueCampos,&data[pos],4);
    pos+=4;
    memcpy(&primerBloqueDatos,&data[pos],4);
    pos+=4;
    memcpy(&actualBloqueDatos,&data[pos],4);
    pos+=4;
    memcpy(&nBloque,&data[pos],4);
    pos+=4;
}

void tabla::crearRegistro(ManejadordeBloques * mbloques,Registro *r)
{
    if(primerBloqueDatos==-1)
    {
        Bloque *b = mbloques->asignarNueboBloque();
        BloqueRegistro * br= new BloqueRegistro(archivo,b->nBloque);
        br->registros->add(r);
        br->actualizarCantidad();
        br->escribir();
        registros->add(r);
        primerBloqueDatos=b->nBloque;
        actualBloqueDatos=b->nBloque;
        return;
    }
    int actual=primerBloqueDatos;
    while(actual!=-1)
    {
        BloqueRegistro *br = new BloqueRegistro(archivo,actual);
        br->cargar(r->longitudRegistro);
        int maximo=496/r->longitudRegistro;
        if(br->registros->cantidad < 2)
        {

            br->registros->add(r);
            br->actualizarCantidad();
            br->escribir();
            registros->add(r);
            return;
            //Tenqo que guardar la tabla o por lo menos el bloqueTabla como tal
        }
        cout<<actual<<endl;
        actual=br->siguiente;

    }

    Bloque *b=mbloques->asignarNueboBloque();
    BloqueRegistro * br = new BloqueRegistro(archivo,b->nBloque);
    BloqueRegistro * tmp = new BloqueRegistro(archivo,actualBloqueDatos);
    tmp->cargar(r->longitudRegistro);
    tmp->siguiente=br->nBloque;
    tmp->escribir();
    br->registros->add(r);
    registros->add(r);
    br->actualizarCantidad();
    br->escribir();
    actualBloqueDatos=b->nBloque;
}

void tabla::crearCampo(ManejadordeBloques * mbloques,char name[20],int tipo)
{
    campo * c= new campo(name,tipo);
    if(primerBloqueCampos==-1)
    {
        Bloque * b =mbloques->asignarNueboBloque();
        BloqueCampo * bc= new BloqueCampo(archivo,b->nBloque);
        bc->campos->add(c);
        bc->cantidad++;
        bc->escribir();
        campos->add(c);
        primerBloqueCampos=bc->nBloque;
        actualBloqueCampos=bc->nBloque;


        //Tengo que guardar la tabla en el archivo o por lo menos el bloqueTabla
        return;
    }
    int actual=primerBloqueCampos;
    while(actual!=-1)
    {
        BloqueCampo *bc = new BloqueCampo(archivo,actual);
        bc->cargar();
        int maximo=17;
        if(bc->cantidad<maximo)
        {
            bc->campos->add(c);
            bc->cantidad++;
            bc->escribir();
            campos->add(c);
            return;
            //Tenqo que guardar la tabla o por lo menos el bloqueTabla como tal
        }
        actual=bc->siguiente;

    }
    Bloque *b=mbloques->asignarNueboBloque();
    BloqueCampo * bc = new BloqueCampo(archivo,b->nBloque);
    BloqueCampo * tmp = new BloqueCampo(archivo,actualBloqueCampos);
    tmp->cargar();
    tmp->siguiente=bc->nBloque;
    tmp->escribir();
    bc->campos->add(c);
    bc->cantidad++;
    bc->escribir();
    actualBloqueCampos=bc->nBloque;
    //Tengo que guardar la tabla o el Bloque Tabla
}

void tabla::cargarCampos()
{
    int actual=primerBloqueCampos;
    while(actual!=-1)
    {
        BloqueCampo *bc= new BloqueCampo(archivo,actual);
        bc->cargar();
        for(int c=0;c<bc->cantidad;c++)
        {
            campos->add(bc->campos->get(c));
        }
        actual=bc->siguiente;
    }
}

void tabla::cargarRegistros()
{
    int actual=primerBloqueDatos;
    while(actual!=-1)
    {
        BloqueRegistro *br= new BloqueRegistro(archivo,actual);
        int longitudReg=this->getLongitudRegistros();
        br->cargar(longitudReg);

        for(int c=0;c< br->cantidad;c++)
        {
            registros->add(interpretarRegistro(br->registros->get(c)->toChar(),longitudReg));
        }
        actual=br->siguiente;
    }
}

Registro * tabla::interpretarRegistro(char * data,int longitud)
{
    int pos=0;
    Registro * reg= new Registro(longitud);
    for(int c=0;c<campos->cantidad;c++)
    {
        CampoDatos * campDatos= new CampoDatos("",0);
        campo * defCampo= campos->get(c);
        campDatos->defCampos=defCampo;
        memcpy(campDatos->valor,&data[pos],20);
        //campDatos->valor=&data[pos];
        //memcpy(campDatos->valor,&data[pos],defCampo->longitud);
        pos+=defCampo->longitud;
        reg->campoDatos->add(campDatos);
    }
    return reg;
}

int tabla::getLongitudRegistros()
{
    int sum=0;
    for(int c=0;c<campos->cantidad;c++)
    {
        sum+=campos->get(c)->longitud;
    }
    return sum;

}

void tabla::toString()
{
    cout<<"Nombre: "<<nombre<<"  ID: "<<id<<"  PrimerBloqueCampo: "<<primerBloqueCampos<<"  ActualBloqueCampo: "<<actualBloqueCampos<<"  PrimerBloqueDatos: "<<primerBloqueDatos<<"  ActualBloqueDatos: "<<actualBloqueDatos<<"  Numero de Bloque: "<<nBloque<<endl<<endl;
}

void tabla::printTabla()
{
    cout<<"Nombre de la Tabla: "<<nombre<<endl;
    for(int c=0;c<campos->cantidad;c++)
    {
        cout<<" "<<campos->get(c)->nombre<<"    ";
    }
    cout<<endl;
    for(int c=0;c<registros->cantidad;c++)
    {
        Registro * r= registros->get(c);
        for(int x=0;x<r->campoDatos->cantidad;x++)
        {
            CampoDatos * camDatos=r->campoDatos->get(x);
            //camDatos->printValor();
            if(camDatos->defCampos->tipo==1)
            {
                cout<<"   ";
            }
            cout<<" "<<camDatos->valor;
            cout<<"     ";
             if(camDatos->defCampos->tipo==1)
            {
                cout<<"   ";
            }

        }
        cout<<endl;
    }
}

