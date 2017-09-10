#ifndef REGISTRO_H
#define REGISTRO_H
#include "listcampodatos.h"

class Registro
{
    public:
        Registro(int longitud);
        ListCampoDatos * campoDatos;
        int longitudRegistro;
        Registro * sig;
        char * toChar();
        void initFromChar(char * data);

    private:
};

#endif // REGISTRO_H
