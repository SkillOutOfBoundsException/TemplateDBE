#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class Archivo
{
    public:
        Archivo();
        FILE * myFile;

        void open(char*);
        void close();
        void write(char * data, int pos = 0, int length = 0);
        char * read(int pos, int length);
        bool exists();


};

#endif // ARCHIVO_H
