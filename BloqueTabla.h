#ifndef BLOQUETABLA_H
#define BLOQUETABLA_H
#include "Bloque.h"
#include "Lista.h"
#include "Tabla.h"
#define tabla_size 56 //tabla size
#define int_size sizeof(int)
#define str_size 20


class BloqueTabla : public Bloque{

    public:
        BloqueTabla(int t);
        Lista<Tabla*> *tablas;
        int cantTablas;

        bool addTabla(Tabla*);

        char * toChar();
        void load(char* data);

        void write();
        void read();

        void printBloque();
};

#endif // BLOQUETABLA_H
