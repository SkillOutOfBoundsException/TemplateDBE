#include "Bloque.h"

Bloque::Bloque(int t){
    num = t;
    sizeB = 512;
    sig = -1;
    arch = new Archivo();
}

char * Bloque::toChar(){
    int pos = 0;
    char * data = new char[sizeB];
    memcpy(&data[pos], &sizeB, 4);
    pos = pos + 4;
    memcpy(&data[pos], &num, 4);
    pos = pos + 4;
    memcpy(&data[pos], &sig, 4);
    pos = pos + 4;
    return data;
}

void Bloque::load(char * data){
    int pos = 0;
    memcpy(&sizeB, &data[pos], 4);
    pos = pos + 4;
    memcpy(&num, &data[pos], 4);
    pos = pos + 4;
    memcpy(&sig, &data[pos], 4);
    pos = pos + 4;
}

void Bloque::write(){
    arch->open("rb+");
    char * data = toChar();
    arch->write(data, num*sizeB, sizeB);
    arch->close();
}

void Bloque::read(){
    arch->open("rb+");
    char * data = arch->read(num*sizeB, sizeB);
    load(data);
    arch->close();
}
