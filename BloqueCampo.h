#ifndef BLOQUECAMPO_H
#define BLOQUECAMPO_H
#include "Bloque.h"
#include "Campo.h"
#include "Lista.h"
#define tabla_size 40 //tabla size
#define campo_size 28
#define int_size sizeof(int)
#define str_size 20

class BloqueCampo : public Bloque{

    public:
        BloqueCampo(int t);
        Lista<Campo*> * campos;
        int cantCampos;

        bool addCampo(Campo*);

        char * toChar();
        void load(char *);

        void write();
        void read();

        void printBloque();
};

#endif // BLOQUECAMPO_H
