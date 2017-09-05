#include "Archivo.h"

Archivo::Archivo(){
}

void Archivo::write(char * data, int pos, int length){
    fseek(myFile, pos, SEEK_SET);
    fwrite(data, 1, length, myFile);
}

char * Archivo::read(int pos, int length){
    fseek(myFile, pos, SEEK_SET);
    char * data = new char[length];
    fread(data, 1, length, myFile);
    return data;
}

void Archivo::close(){
    fclose(myFile);
}

void Archivo::open(char * mode){
    myFile = fopen("db.txt", mode);
}

bool Archivo::exists(){
    if(myFile = fopen("db.txt", "r")){
        close();
        return true;
    }
    return false;
}
