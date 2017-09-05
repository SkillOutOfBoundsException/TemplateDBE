#include "Campo.h"

Campo::Campo(){
    nombre = new char[20];
    tipo = 0;
    regSize = 4;
}

void Campo::setAttributes(char * n, int t){
    memset(nombre, 0, 20);
    memcpy(&nombre[0], &n[0], strlen(n));
    tipo = t;
    regSize = t == 1 ? 20 : 4;
}

Json Campo::to_json(){
    Json js = Json::object{
        {"nombre", nombre},
        {"tipo", tipo}
    };
    return js;
}

void Campo::loadCampo(char* data){
    int pos = 0;
    memcpy(&nombre[0], &data[pos], 20);
    pos = pos + 20;
    memcpy(&tipo, &data[pos], 4);
    pos = pos + 4;
    memcpy(&regSize, &data[pos], 4);
    pos = pos + 4;
}

char * Campo::toChar(){
    char * data = new char[campo_size];
    int pos = 0;
    memcpy(&data[pos], &nombre[0], 20);
    pos = pos + 20;
    memcpy(&data[pos], &tipo, 4);
    pos = pos + 4;
    memcpy(&data[pos], &regSize, 4);
    pos = pos + 4;
    return data;
}

void Campo::printCampo(){
    char * t = new char[10];
    if(tipo == 1)
        memcpy(&t[0], "STRING" , 10);
    else
        memcpy(&t[0], "INT" , 10);
    //cout << "->" <<nombre << " - " << t << " - size: " << regSize << endl;
    cout << nombre << "(" << t << ")";
}
