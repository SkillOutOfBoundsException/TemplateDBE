#ifndef BLOQUEMASTER_H
#define BLOQUEMASTER_H
#include "Bloque.h"
#include <string.h>
#include <iostream>
#define int_size sizeof(int)
#define str_size 20

using namespace std;

class BloqueMaster : public Bloque{

    public:

        BloqueMaster();
        int primerBloqueTabla;
        int actualBloqueTabla;
        int cantTablas;
        int cantBloqueTabla;
        int cantBloques;

        char * toChar();
        void load(char*);

        void write();
        void read();

        void printSelf();
};

#endif // BLOQUEMASTER_H
