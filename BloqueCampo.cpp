#include "BloqueCampo.h"

BloqueCampo::BloqueCampo(int t) : Bloque(t){
    campos = new Lista<Campo*>();
    cantCampos = 0;
}

bool BloqueCampo::addCampo(Campo * c){
    if(cantCampos >= 16)
        return false;
    campos->pushBack(c);
    cantCampos++;
    return true;
}

char * BloqueCampo::toChar(){
    int pos = 0;
    char * data = new char[sizeB];
    memcpy(&data[pos], &sizeB, 4);
    pos = pos + 4;
    memcpy(&data[pos], &num, 4);
    pos = pos + 4;
    memcpy(&data[pos], &sig, 4);
    pos = pos + 4;
    memcpy(&data[pos], &cantCampos, 4);
    pos = pos + 4;
    for(int i = 0; i < cantCampos; i++){
        memcpy(&data[pos], campos->index(i)->toChar(), campo_size);
        pos = pos + campo_size;
    }
    return data;
}

void BloqueCampo::load(char * data){
    int pos = 0;
    memcpy(&sizeB, &data[pos], 4);
    pos = pos + 4;
    memcpy(&num, &data[pos], 4);
    pos = pos + 4;
    memcpy(&sig, &data[pos], 4);
    pos = pos + 4;
    memcpy(&cantCampos, &data[pos], 4);
    pos = pos + 4;
    for(int i = 0; i < cantCampos; i++){
        Campo * c = new Campo();
        c->loadCampo(&data[pos]);
        campos->pushBack(c);
        pos = pos + campo_size;
    }
}

void BloqueCampo::write(){
    arch->open("rb+");
    char * data = toChar();
    arch->write(data, num*sizeB, sizeB);
    arch->close();
}

void BloqueCampo::read(){
    arch->open("rb");
    char * data = arch->read(num*sizeB, sizeB);
    load(data);
    arch->close();
}

void BloqueCampo::printBloque(){
    cout << "Bloque num " << num << endl;
    cout << "Num de campos " << cantCampos << endl;
    cout << "Sig " << sig << endl;
    cout << "------------------------" << endl;
}
