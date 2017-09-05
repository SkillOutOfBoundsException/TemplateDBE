#include "BloqueMaster.h"

BloqueMaster::BloqueMaster() : Bloque(0){
    sig = -1;
    primerBloqueTabla = -1;
    actualBloqueTabla = -1;
    cantTablas = 0;
    cantBloqueTabla = 0;
    cantBloques = 1;
}

char * BloqueMaster::toChar(){
    int pos = 0;
    char * data = new char[sizeB];
    memcpy(&data[pos], &sizeB, 4);
    pos = pos + 4;
    memcpy(&data[pos], &num, 4);
    pos = pos + 4;
    memcpy(&data[pos], &sig, 4);
    pos = pos + 4;
    memcpy(&data[pos], &cantBloques, 4);
    pos = pos + 4;
    memcpy(&data[pos], &primerBloqueTabla, 4);
    pos = pos + 4;
    memcpy(&data[pos], &actualBloqueTabla, 4);
    pos = pos + 4;
    memcpy(&data[pos], &cantTablas, 4);
    pos = pos + 4;
    memcpy(&data[pos], &cantBloqueTabla, 4);
    pos = pos + 4;
    return data;
}

void BloqueMaster::load(char * data){
    int pos = 0;
    memcpy(&sizeB, &data[pos], 4);
    pos = pos + 4;
    memcpy(&num, &data[pos], 4);
    pos = pos + 4;
    memcpy(&sig, &data[pos], 4);
    pos = pos + 4;
    memcpy(&cantBloques, &data[pos], 4);
    pos = pos + 4;
    memcpy(&primerBloqueTabla, &data[pos], 4);
    pos = pos + 4;
    memcpy(&actualBloqueTabla, &data[pos], 4);
    pos = pos + 4;
    memcpy(&cantTablas, &data[pos], 4);
    pos = pos + 4;
    memcpy(&cantBloqueTabla, &data[pos], 4);
    pos = pos + 4;

}

void BloqueMaster::write(){
    arch->open("rb+");
    char * data = toChar();
    arch->write(data, num*sizeB, sizeB);
    arch->close();
}

void BloqueMaster::read(){
    arch->open("rb+");
    char * data = arch->read(num*sizeB, sizeB);
    load(data);
    arch->close();
}

void BloqueMaster::printSelf(){
    cout << "Acutal Bloque Tabla - " << actualBloqueTabla << endl;
    cout << "Cant Bloque Tabla - " << cantBloqueTabla << endl;
    cout << "Cant Bloques - " << cantBloques << endl;
    cout << "Cant Tablas - " << cantTablas << endl;
}
