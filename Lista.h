#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"
#include <stdexcept>
#include <iostream>

template<class clase>
class Lista{
    public:

        void pushBack(clase d){
            Nodo<clase>* temp = new Nodo<clase>(d);
            if(head == 0){
                head = temp;
                tail = temp;
                cant = 1;
            }
            else{
                tail->next = temp;
                temp->prev = tail;
                tail = temp;
                cant++;
            }
        };

        void popBack(){
            Nodo<clase>* temp = tail->prev;
            temp->next = 0;
            tail = temp;
            cant--;
        };

        void pushFront(clase d){
            Nodo<clase>* temp = new Nodo<clase>(d);
            if(head == 0){
                pushBack(d);
            }
            else{
                head->prev = temp;
                temp->next = head;
                head = temp;
                cant++;
            }
        };

        void popFront(){
            Nodo<clase>* temp = head->next;
            temp->prev = 0;
            head = temp;
            cant--;
        };

        clase index(int x){
            return nodoAt(x)->data;
        };

        void insertAt(int x, clase d){
            if(x <= 0){
                pushFront(d);
                return;
            }
            else if(x >= cant){
                pushBack(d);
                return;
            }
            else{
                Nodo<clase>* nuevo = new Nodo<clase>(d);
                Nodo<clase>* temp = nodoAt(x);
                temp->prev->next = nuevo;
                nuevo->prev = temp->prev;
                nuevo->next = temp;
                temp->prev = nuevo;
                cant++;
            }
        };

        bool isEmpty(){
            return cant == 0;
        };

        void clearList(){
            head = 0;
            tail = 0;
            cant = 0;
        };

        int length(){
            return cant;
        }

        Lista(){
            head = 0;
            tail = 0;
            cant = 0;
        };

        Lista(clase d){
            head = 0;
            tail = 0;
            cant = 0;
            pushBack(d);
        };

        Lista(int x, clase d){
            head = 0;
            tail = 0;
            cant = 0;
            pushManyBack(x, d);
        };

    private:

        Nodo<clase>* head;
        Nodo<clase>* tail;
        int cant;

        void pushManyBack(int x, clase d){
            for(int i = 0; i < x; i++)
                pushBack(d);
        };

        Nodo<clase>* nodoAt(int x){
            if(x > cant || x < 0)
                throw std::out_of_range("Index is out of bounds");
            Nodo<clase>* temp = head;
            for(int i = 0; i < cant; i++){
                if(i == x)
                    return temp;
                temp = temp->next;
            }
            return 0;
        };
};

#endif // LISTA_H
