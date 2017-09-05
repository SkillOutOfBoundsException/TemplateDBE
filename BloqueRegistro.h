#ifndef BLOQUEREGISTRO_H
#define BLOQUEREGISTRO_H
#include "Bloque.h"
#include "Lista.h"
#include "Registro.h"
#define int_size sizeof(int)
#define str_size 20


class BloqueRegistro : public Bloque{
    public:
        BloqueRegistro(int t, int r);
        Lista<Registro*> * registros;
        int cantReg;
        int tamReg;

        bool addReg(Registro * r);

        char * toChar();
        void load(char*);

        void write();
        void read();

        void printBloque();
};

#endif // BLOQUEREGISTRO_H
