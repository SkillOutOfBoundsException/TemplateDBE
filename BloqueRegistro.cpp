#include "BloqueRegistro.h"

BloqueRegistro::BloqueRegistro(int t, int r) : Bloque(t){
    registros = new Lista<Registro*>();
    cantReg = 0;
    tamReg = r;
}

bool BloqueRegistro::addReg(Registro * r){
    int maxRegs = (sizeB - int_size*5)/tamReg;
    if(cantReg >= maxRegs)
        return false;
    registros->pushBack(r);
    cantReg++;
    return true;
}

char * BloqueRegistro::toChar(){
    int pos = 0;
    char * data = new char[sizeB];
    memcpy(&data[pos], &sizeB, 4);
    pos = pos + 4;
    memcpy(&data[pos], &num, 4);
    pos = pos + 4;
    memcpy(&data[pos], &sig, 4);
    pos = pos + 4;
    memcpy(&data[pos], &cantReg, 4);
    pos = pos + 4;
    memcpy(&data[pos], &tamReg, 4);
    pos = pos + 4;
    for(int i = 0; i < cantReg; i++){
        memcpy(&data[pos], registros->index(i)->toChar(), tamReg);
        pos = pos + tamReg;
    }
    return data;
}

void BloqueRegistro::load(char * data){
    int pos = 0;
    memcpy(&sizeB, &data[pos], 4);
    pos = pos + 4;
    memcpy(&num,&data[pos], 4);
    pos = pos + 4;
    memcpy(&sig, &data[pos], 4);
    pos = pos + 4;
    memcpy(&cantReg, &data[pos], 4);
    pos = pos + 4;
    memcpy(&tamReg, &data[pos], 4);
    pos = pos + 4;
    for(int i = 0; i < cantReg; i++){
        Registro * r = new Registro(tamReg);
        r->loadRegistro(&data[pos]);
        registros->pushBack(r);
        pos = pos + tamReg;
    }
}

void BloqueRegistro::write(){
    arch->open("rb+");
    char * data = toChar();
    arch->write(data, num*sizeB, sizeB);
    arch->close();
}

void BloqueRegistro::read(){
    arch->open("rb");
    char * data = arch->read(num*sizeB, sizeB);
    load(data);
    arch->close();
}

void BloqueRegistro::printBloque(){
    cout << "Bloque num " << num << endl;
    cout << "Num de registros " << cantReg << endl;
    cout << "Sig " << sig << endl;
    cout << "------------------------" << endl;
}
