#include <iostream>
#include "datafile.h"
#include "bloque.h"
#include "manejadrotablas.h"
#include "manejadordebloques.h"
#include "bloquecampo.h"
#include "bloquetabla.h"
#include <stdio.h>
#include "masterblock.h"
#include "tabla.h"
#include "registro.h"
#include "campodatos.h"
#include "bloque.h"
#include "bloquecampo.h"
#include "bloqueregistro.h"
#include "campo.h"
#include "campodatos.h"
#include "BloqueIndice.h"
using namespace std;

int main()
{
    //Creo la base de Datos
    DataFile * archivo = new DataFile("C:\\Users\\David\\Desktop\\BaseDatos.data");
    archivo->abrir();
    ManejadordeBloques * mbloques= new ManejadordeBloques(archivo);
    ManejadroTablas * mtablas=new ManejadroTablas(archivo,mbloques->masterBlock);


    /*for(int c=0;c<1;c++)
    {
        char * nombre= new char[20];
        nombre[0]='t';
        nombre[1]='a';
        nombre[2]='b';
        nombre[3]='l';
        nombre[4]='a';
        nombre[5]='_';
        char cadena[1000];
        sprintf(cadena, "%d", c);
        for(int x=0;cadena[x]!='\0';x++)
        {
            nombre[x+6]=cadena[x];
        }
        mtablas->crearTabla(nombre,c,mbloques);
        string id="ID";
        string name="Nombre";
        string edad="Edad";
        //ostringstream nom;
        //ostringstream i;
        //ostringstream e;
        char * nom = const_cast<char *>(name.c_str());
        char * i = const_cast<char *>(id.c_str());
        char * e = const_cast<char *>(edad.c_str());
        mtablas->crearCampo(c,i,0,mbloques);
        mtablas->crearCampo(c,nom,0,mbloques);
        mtablas->crearCampo(c,e,1,mbloques);

    }
    for(int c=0;c<1000;c++)
    {
        Registro * r= new Registro(mtablas->buscarTabla(0)->getLongitudRegistros());
        string id="id";
        string name="nombre";
        char edad= (char) (c+48);
        ostringstream nomb;
        stringstream idd;
        ostringstream ed;
        idd<<id<<'_'<<c;
        nomb<<name<<'_'<<c;
        ed<<c;
        char * nom = const_cast<char *>(nomb.str().c_str());
        char * i = const_cast<char *>(idd.str().c_str());
        char * e = const_cast<char *>(ed.str().c_str());
        CampoDatos * d1=new CampoDatos(i,mtablas->buscarTabla(0)->campos->get(0));
        CampoDatos * d2=new CampoDatos(nom,mtablas->buscarTabla(0)->campos->get(1));
        CampoDatos * d3=new CampoDatos(e,mtablas->buscarTabla(0)->campos->get(2));
        r->campoDatos->add(d1);
        r->campoDatos->add(d2);
        r->campoDatos->add(d3);
        mtablas->addRegistro(0,mbloques,r);
    }//*/

    //Probando la hashTable
    //mtablas->buscarTabla(0)->toString();
    /*BloqueIndice * b = new BloqueIndice(archivo,3);
    b->cargar();
    b->listarElementos();//*/
    mtablas->buscarTabla(0)->buscarRegistro("id_900")->printRegistro();


    //Probando Json
    /*mtablas->exportar(0);
    mtablas->mj->guardar();//*/
    /*mtablas->mj->cargar();
    mtablas->importar(mbloques,0);//*/


    archivo->cerrar();
    return 0;
}
