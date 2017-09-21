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
using namespace std;

int main()
{
    //Creo la base de Datos
    DataFile * archivo = new DataFile("C:\\Users\\David\\Desktop\\BaseDatos.data");
    archivo->abrir();
    ManejadordeBloques * mbloques= new ManejadordeBloques(archivo);
    ManejadroTablas * mtablas=new ManejadroTablas(archivo,mbloques->masterBlock);


    for(int c=0;c<1;c++)
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
        int tipo=0;
        for(int i=0;i<10;i++)
        {
            char * nombreC= new char[20];
            nombreC[0]='C';
            nombreC[1]='a';
            nombreC[2]='m';
            nombreC[3]='p';
            nombreC[4]='o';
            nombreC[5]='_';
            char cadena1[10];
            sprintf(cadena1, "%d", i);
            for(int x=0;cadena1[x]!='\0';x++)
            {
                nombreC[x+6]=cadena1[x];
            }
            if(i==4)
                tipo=1;
            if(i==9)
                tipo=1;
            mtablas->crearCampo(c,nombreC,tipo,mbloques);
            tipo=0;
        }
    }

        for(int c=0;c<1;c++)
        {

            Registro * r= new Registro(mtablas->buscarTabla(c)->getLongitudRegistros());
            for(int i=0;i<10;i++)
            {
                char * datos= new char[20];
                for(int a=0;a<20;a++)
                {
                    datos[a]='\0';
                }
                datos[0]='d';
                datos[1]='a';
                datos[2]='t';
                datos[3]='o';
                datos[4]='_';

                char cadena2[10];
                for(int a=0;a<10;a++){
                    cadena2[a]='\0';
                }
                sprintf(cadena2, "%d", i);
                for(int x=0;cadena2[x]!='\0';x++)
                {
                    datos[x+5]=cadena2[x];
                }
                if(i==4 || i==9)
                {
                    datos=new char[20];
                    sprintf(datos, "%d", i);
                }
                CampoDatos * datosN=new CampoDatos(datos,mtablas->buscarTabla(c)->campos->get(i));
                r->campoDatos->add(datosN);

            }
            mtablas->addRegistro(c,mbloques,r);
        }//*/

    //Probando la hashTable

    //mtablas->buscarTabla(0)->buscarRegistro("dato_0")->printRegistro();


    //Probando Json
    /*mtablas->exportar(0);
    mtablas->mj->guardar();//*/
    /*mtablas->mj->cargar();
    mtablas->importar(mbloques,0);//*/





   //mtablas->buscarTabla(10)->toString();
    //*/
    //mtablas->listarTablas();
  //  mtablas->buscarTabla(1)->printTabla();
    archivo->cerrar();

    /*
    tmp->primerBloqueCampos=bc->nBloque;
    tmp->actualBloqueCampos=bc->nBloque;*/
    /*
    int op=1;
    while(op!=0)
    {
        cout<<"Ingrese una opcion"<<endl;
        cout<<"1. Crear Base de Datos"<<endl;
        cout<<"2. Crear Tabla"<<endl;
        cout<<"3. Crear Campo"<<endl;

        cin>> op;
        cout<<endl;
        if(op==1)
        {
             cout<<"Ingrese el path"<<endl;
             char * path;
             cin>> path;
             DataFile * archivo = new DataFile(path);
        }
        else if(op==2)
        {
             cout<<"Ingrese el path"<<endl;
             char * path;
             cin>> path;
             DataFile * archivo = new DataFile(path);
             cout<<"Ingrese el nombre de la tabla"<<endl;
             char name[20];
             cin>> name;
             cout<<"Ingrese el ID de la tabla"<<endl;
             int id;
             cin>> id;
             ManejadroTablas * mtablas= new ManejadroTablas(archivo);
             mtablas->crearTabla(name,id,0,0,0,0);
        }
        else if(op==3)
        {
             cout<<"Ingrese el path"<<endl;
             char * path;
             cin>> path;
             DataFile * archivo = new DataFile(path);
             cout<<"Ingrese el nombre de la tabla a la que le asignara el campo"<<endl;
             char name[20];
             cin>> name;
             ManejadroTablas * mtablas= new ManejadroTablas(archivo);
             tabla * t =mtablas->buscarTabla(name);
        }




    }*/
    return 0;
}
