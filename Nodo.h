#ifndef NODO_H
#define NODO_H

template <class clase>
class Nodo{
    public:
        clase data;
        Nodo* next;
        Nodo* prev;
        Nodo(clase d){
            data = d;
            next = 0;
            prev = 0;
        };
};

#endif // NODO_H
