#include "Tabla.h"


Tabla::Tabla(int n){
    id = n;
    nombre = new char[20];
    primerBloqueCampo = -1;
    primerBloqueReg = -1;
    actualBloqueCampo = -1;
    actualBloqueReg = -1;
    cantCampos = 0;
    cantReg = 0;
    cantBloqueCampos = 0;
    cantBloqueReg = 0;
    campos = new Lista<Campo*>();
    registros = new Lista<Registro*>();
}

void Tabla::addCampo(char * nombre, int tipo, BloqueMaster * bm){
    if(primerBloqueReg != -1){
        cout << "No se pueden agregar campos a una tabla con registros existentes" << endl;
        return;
    }
    Campo * c = new Campo();
    c->setAttributes(nombre, tipo);
    if(!campoSpace(c)){
        cout << "No hay espacio para mas campos" << endl;
        return;
    }

    cantCampos++;
    if(primerBloqueCampo == -1){
        BloqueCampo * bc = new BloqueCampo(bm->cantBloques);
        cantBloqueCampos++;
        bm->cantBloques++;
        primerBloqueCampo = bc->num;
        actualBloqueCampo = bc->num;
        bc->addCampo(c);
        bc->write();
    }
    else{
        BloqueCampo * bc = new BloqueCampo(actualBloqueCampo);
        bc->read();
        if(!bc->addCampo(c)){
            BloqueCampo * bc2 = new BloqueCampo(bm->cantBloques);
            cantBloqueCampos++;
            bm->cantBloques++;
            bc->sig = bc2->num;
            actualBloqueCampo = bc2->num;
            bc2->addCampo(c);
            bc2->write();
        }
        bc->write();
    }
    bm->write();
}

bool Tabla::campoSpace(Campo * c){
    int bRegTaken = 20 + tamReg() + c->regSize;
    return !(bRegTaken > 512);
}

void Tabla::addRegistro(char * data, BloqueMaster * bm){
    if(primerBloqueCampo == -1){
        cout << "No se pueden agregar registros a una tabla sin campos" << endl;
        return;
    }
    int tReg = tamReg();
    Registro * r = new Registro(tReg);
    r->setAttributes(data);
    cantReg++;
    if(primerBloqueReg == -1){
        BloqueRegistro * br = new BloqueRegistro(bm->cantBloques, tReg);
        cantBloqueReg++;
        bm->cantBloques++;
        primerBloqueReg = br->num;
        actualBloqueReg = br->num;
        br->addReg(r);
        br->write();
    }
    else{
        BloqueRegistro * br = new BloqueRegistro(actualBloqueReg, tReg);
        br->read();
        if(!br->addReg(r)){
            BloqueRegistro * br2 = new BloqueRegistro(bm->cantBloques, tReg);
            cantBloqueReg++;
            bm->cantBloques++;
            br->sig = br2->num;
            actualBloqueReg = br2->num;
            br2->addReg(r);
            br2->write();
        }
        br->write();
    }
    bm->write();
}

char * Tabla::generateReg(){
    loadCampos();
    char * data = new char[tamReg()];
    int pos = 4;
    cout << "Creando nuevo registro para la tabla " << nombre << endl;
    for(int i = 0; i < cantCampos; i++){
        Campo * c = campos->index(i);
        cout << "Ingrese la info del campo: ";
        c->printCampo();
        cout << endl;
        if(c->tipo == 1){
            char * d = new char[str_size];

            cin >> d;
            memcpy(&data[pos], &d[0], strlen(d));
            pos = pos + str_size;
        }
        else{
            int x;
            cin >> x;
            memcpy(&data[pos], &x, int_size);
            pos = pos + int_size;
        }
    }
    return data;
}

int Tabla::tamReg(){
    loadCampos();
    int tam = 4;
    for(int i = 0; i < cantCampos; i ++){
        tam = tam + campos->index(i)->regSize;
    }
    return tam;
}

Json Tabla::registrosToJson(){
    loadRegs();
    vector<vector<Json>> jRegistros;
    for(int i = 0; i < cantReg; i++){
        vector<Json> celdasDeRegs;
        for(int k = 0; k < cantCampos; k++){
            int tipo = campos->index(k)->tipo;
            if(tipo == 1){
                string data = registros->index(i)->celdas->index(k)->data;
                Json celda = Json::object{
                    {"tipo", tipo},
                    {"data", data}
                };
                celdasDeRegs.push_back(celda);
            }
            else{
                int data = registros->index(i)->celdas->index(k)->getInt();
                Json celda = Json::object{
                    {"tipo", tipo},
                    {"data", data}
                };
                celdasDeRegs.push_back(celda);
            }
        }
        jRegistros.push_back(celdasDeRegs);
    }
    Json regs = Json::object{
        {"cantReg", cantReg},
        {"Registros", jRegistros}
    };
    return regs;
}

Json Tabla::camposToJson(){
    loadCampos();
    vector<Json> jCampos;
    for(int i = 0; i < cantCampos; i++){
        jCampos.push_back(campos->index(i)->to_json());
    }
    Json cams = Json::object{
        {"cantCampos", cantCampos},
        {"Campos", jCampos}
    };
    return cams;
}

Json Tabla::tablaToJson(){
    Json tab = Json::object{
        {"Nombre", nombre},
        {"Campos", camposToJson()},
        {"Registros", registrosToJson()}
    };
    return tab;
}

void Tabla::jsonToCampos(Json jcampos, BloqueMaster * bm){
    int cc = jcampos["cantCampos"].int_value();
    for(int k = 0; k < cc; k++){
        Json campo = jcampos["Campos"][k];
        char * cNom = new char[20];
        strcpy(cNom, campo["nombre"].string_value().c_str());
        int tipo = campo["tipo"].int_value();
        addCampo(cNom, tipo, bm);
    }
}

void Tabla::jsonToRegistros(Json jregistros, BloqueMaster * bm){
    int cr = jregistros["cantReg"].int_value();
    for(int k = 0; k < cr; k++){
        char * data = new char[tamReg()];
        int pos = 4;
        for(int j = 0; j < cantCampos; j++){
            Json celda = jregistros["Registros"][k][j];
            int tipo = celda["tipo"].int_value();
            if(tipo == 1){
                char * cData = new char[20];
                strcpy(cData, celda["data"].string_value().c_str());
                memcpy(&data[pos], &cData[0], str_size);
                pos = pos + str_size;
            }
            else{
                int cData = celda["data"].int_value();
                memcpy(&data[pos], &cData, int_size);
                pos = pos + int_size;
            }
        }
        addRegistro(data, bm);
    }
}

void Tabla::loadTabla(char * data){
    int pos = 0;
    memcpy(&nombre[0], &data[pos], 20);
    pos = pos + 20;
    memcpy(&id, &data[pos], 4);
    pos = pos + 4;
    memcpy(&primerBloqueCampo, &data[pos], 4);
    pos = pos + 4;
    memcpy(&actualBloqueCampo, &data[pos], 4);
    pos = pos + 4;
    memcpy(&primerBloqueReg, &data[pos], 4);
    pos = pos + 4;
    memcpy(&actualBloqueReg, &data[pos], 4);
    pos = pos + 4;
    memcpy(&cantCampos, &data[pos], 4);
    pos = pos + 4;
    memcpy(&cantReg, &data[pos], 4);
    pos = pos + 4;
    memcpy(&cantBloqueCampos, &data[pos], 4);
    pos = pos + 4;
    memcpy(&cantBloqueReg, &data[pos], 4);
    pos = pos + 4;
}

char* Tabla::toChar(){
    char * data = new char[tabla_size];
    int pos = 0;
    memcpy(&data[pos], &nombre[0], 20);
    pos = pos + 20;
    memcpy(&data[pos], &id, 4);
    pos = pos + 4;
    memcpy(&data[pos], &primerBloqueCampo, 4);
    pos = pos + 4;
    memcpy(&data[pos], &actualBloqueCampo, 4);
    pos = pos + 4;
    memcpy(&data[pos], &primerBloqueReg, 4);
    pos = pos + 4;
    memcpy(&data[pos], &actualBloqueReg, 4);
    pos = pos + 4;
    memcpy(&data[pos], &cantCampos, 4);
    pos = pos + 4;
    memcpy(&data[pos], &cantReg, 4);
    pos = pos + 4;
    memcpy(&data[pos], &cantBloqueCampos, 4);
    pos = pos + 4;
    memcpy(&data[pos], &cantBloqueReg, 4);
    pos = pos + 4;
    return data;
}

void Tabla::setNombre(char* n){
    memset(nombre, 0, 20);
    memcpy(&nombre[0], &n[0], strlen(n));
}

void Tabla::loadCampos(){
    campos->clearList();
    if(primerBloqueCampo == -1)
        return;
    int i = primerBloqueCampo;
    while(i != -1){
        BloqueCampo * bc = new BloqueCampo(i);
        bc->read();
        for(int k = 0; k < bc->cantCampos; k++)
            campos->pushBack(bc->campos->index(k));
        i = bc->sig;
    }
}

void Tabla::loadRegs(){
    registros->clearList();
    if(primerBloqueReg == -1)
        return;
    loadCampos();
    int i = primerBloqueReg;
    int tR = tamReg();
    while(i != -1){
        BloqueRegistro * br = new BloqueRegistro(i, tR);
        br->read();
        for(int k = 0; k < br->cantReg; k++){
            Registro * r = br->registros->index(k);
            r->celdas->clearList();
            int pos = 4;
            for(int j = 0; j < cantCampos; j++){
                Campo * c = campos->index(j);
                r->celdas->pushBack(new Celda(c, &r->data[pos]));
                pos = pos + c->regSize;
            }
            registros->pushBack(r);
        }
        i = br->sig;
    }
}

void Tabla::printTabla(){
    loadCampos();
    loadRegs();
    cout << "Tabla - " << nombre << endl;
    cout << "ID - " << id << " - ";
    cout << cantCampos << " Campo(s): " << endl;
    for(int i = 0; i < cantCampos; i ++){
        cout << " | ";
        campos->index(i)->printCampo();
    }
    cout << " |" << endl;
    for(int i = 0; i < cantReg; i++){
        registros->index(i)->printRegistro();
        cout << endl;
    }

    //cout << primerBloqueCampo << endl;
    //cout << actualBloqueCampo << endl;
    //cout << primerBloqueReg << endl;
    //cout << actualBloqueReg << endl;

    cout << endl << "------------------------" << endl;
}
