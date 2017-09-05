#include "BloqueTabla.h"

BloqueTabla::BloqueTabla(int t) : Bloque(t){
    tablas = new Lista<Tabla*>();
    cantTablas = 0;
}

bool BloqueTabla::addTabla(Tabla * t){
    if(cantTablas >= 8)
        return false;
    tablas->pushBack(t);
    cantTablas++;
    return true;
}

char * BloqueTabla::toChar(){
    int pos = 0;
    char * data = new char[sizeB];
    memcpy(&data[pos], &sizeB, 4);
    pos = pos + 4;
    memcpy(&data[pos], &num, 4);
    pos = pos + 4;
    memcpy(&data[pos], &sig, 4);
    pos = pos + 4;
    memcpy(&data[pos], &cantTablas, 4);
    pos = pos + 4;
    for(int i = 0; i < cantTablas; i++){
        memcpy(&data[pos], tablas->index(i)->toChar(), tabla_size);
        pos = pos + tabla_size;
    }
    return data;
}

void BloqueTabla::load(char * data){
    int pos = 0;
    memcpy(&sizeB, &data[pos], 4);
    pos = pos + 4;
    memcpy(&num, &data[pos], 4);
    pos = pos + 4;
    memcpy(&sig, &data[pos], 4);
    pos = pos + 4;
    memcpy(&cantTablas, &data[pos], 4);
    pos = pos + 4;
    for(int i = 0; i < cantTablas; i++){
        Tabla * t = new Tabla(i);
        t->loadTabla(&data[pos]);
        tablas->pushBack(t);
        pos = pos + tabla_size;
    }
}

void BloqueTabla::write(){
    arch->open("rb+");
    char * data = toChar();
    arch->write(data, num*sizeB, sizeB);
    arch->close();
}

void BloqueTabla::read(){
    arch->open("rb+");
    char * data = arch->read(num*sizeB, sizeB);
    load(data);
    arch->close();
}

void BloqueTabla::printBloque(){
    cout << "Bloque num " << num << endl;
    cout << "Num de tablas " << cantTablas << endl;
    cout << "Sig " << sig << endl;
    cout << "------------------------" << endl;
}
