#ifndef BLOQUE_H
#define BLOQUE_H
#include <string.h>
#include <iostream>
#include "Archivo.h"
#define int_size sizeof(int)
#define str_size 20

using namespace std;

class Bloque{
    public:
        Bloque(int t);
        int sig;
        int num;
        int sizeB;

        Archivo * arch;

        char * toChar();
        void load(char * data);

        void write();
        void read();
};

#endif // BLOQUE_H
