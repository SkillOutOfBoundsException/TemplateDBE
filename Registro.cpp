#include "Registro.h"

Registro::Registro(int l){
    len = l;
    data = new char[len];
    celdas = new Lista<Celda*>();
}

void Registro::setAttributes(char * d){
    memcpy(&data[0], &d[0], len);
}

char * Registro::toChar(){
    char * reg = new char[len];
    int pos = 0;
    memcpy(&reg[pos], &data[0], len);
    memcpy(&reg[pos], &len, int_size);
    return reg;
}

void Registro::loadRegistro(char * reg){
    int pos = 0;
    memcpy(&len, &reg[pos], int_size);
    data = new char[len];
    memcpy(&data[0], &reg[pos], len);
    pos = pos + len;
}

void Registro::printRegistro(){
    cout << " ";
    for(int i = 0; i < celdas->length(); i++){
        cout << " | ";
        celdas->index(i)->printCelda();
    }
    cout << " |";
}
