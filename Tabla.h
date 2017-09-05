#ifndef TABLA_H
#define TABLA_H
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "Lista.h"
#include "Campo.h"
#include "Celda.h"
#include "Registro.h"
#include "BloqueMaster.h"
#include "BloqueCampo.h"
#include "BloqueRegistro.h"
#include "json11.hpp"
#define tabla_size 56 //tablaSize
#define int_size sizeof(int)
#define str_size 20

using namespace std;
using namespace json11;

class Tabla{
    public:
        Tabla(int n);

        char * nombre;
        int id;
        int primerBloqueCampo;
        int actualBloqueCampo;
        int primerBloqueReg;
        int actualBloqueReg;

        int cantCampos;
        int cantReg;

        int cantBloqueCampos;
        int cantBloqueReg;

        Lista<Campo*> * campos;
        Lista<Registro*> * registros;

        bool campoSpace(Campo *);
        void addCampo(char* nombre, int tipo, BloqueMaster * bm);

        void addRegistro(char * data, BloqueMaster * bm);
        char * generateReg();
        int tamReg();

        Json registrosToJson();
        Json camposToJson();
        Json tablaToJson();

        void jsonToCampos(Json jcampos, BloqueMaster * bm);
        void jsonToRegistros(Json jregistros, BloqueMaster * bm);

        char * toChar();
        void loadTabla(char*);

        void loadCampos();
        void loadRegs();

        void setNombre(char*);
        void printTabla();

};

#endif // TABLA_H
