#ifndef CELDA_H
#define CELDA_H
#include <stdio.h>
#include <string.h>
#include "Campo.h"
#define int_size sizeof(int)
#define str_size 20

using namespace std;

class Celda{
    public:
        Celda(Campo * c, char * d);
        Campo * campo;
        char * data;

        int getInt();

        void printCelda();
};

#endif // CELDA_H
