#include <iostream>
#include "Lista.h"
#include "Bloque.h"
#include "BloqueTabla.h"
#include "BloqueMaster.h"
#include "BloqueCampo.h"
#include "Campo.h"
#include "Engine.h"
#include "Archivo.h"
#include "json11.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;
using namespace json11;

int main(){

    Engine * e = new Engine();

//    e->addTabla("tablaTest");
//
//    e->addCampoToTabla(0, "Nombre", 1);
//    e->addCampoToTabla(0, "Edad", 0);
//
//    e->addRegistroToTabla(0);
//    e->addRegistroToTabla(0);
//    e->addRegistroToTabla(0);

    //e->writeJson();

    e->readJson();
    e->printTablas();

    return 0;
}


/*
    Master Bloque:
        primerBloqueTabla;
        actualBloqueTabla;
        sizeBloque;

    Manejador de Bloque (DBEngine):
        maneja el blockManager;
        maneja todas las tablas y organiza;
        debe poder formatear la db;

    BloqueTabla:
        numBloque;
        sigBloqueTabla;

    Tablas:
        Poder crearlas:
            crear Tablas en 1 bloque;
            crear N Tablas en N bloques;

    Registros:
        Tamaño Variable;
        Tamaño depende de la cantidad  tipo de campos;

    Hash Tables:
        Propiedades:
            -Insertar O(1)
            -Buscar O(1)
            -Eliminar O(1)

        Hash Function:
            Buscamos mayor dispercion posible;

            Ejemplo para examen:
                int fnHash(char * k){
                    return keytoInt(k)%m;
                }

            fnHash pronostica C colisiones para tablas de tamano M con N elementos;

            Formas de manejar colisiones:
                Sumarle 1 a fnHash(k);

    Upcoming changes:

        void Registro::insertar(){
            ...
            int nBloque = ...
            int numDeRegRel = ...
            ...
            IdxEntry * entry = new IdxEntry(tabla, nBloque, numDeRegRel, llave);
            tabla->indice->agregarEntrada(entry); //indice es tipo HashTable
         }

         Registro * Tabla::buscarRegistro(char * id){
            IdxEntry * entry = indice->buscar(id);
            if(entry == null)
                return null;
            Registro * reg = cargarRegistro(entry->nB, entry->nRR);
            return reg;
         }

    Nuevas classes para manejar indices:

        IdxEntry{
            int numBloque;
            int numRegistroRelativo;
        }

        HashTableEntry{
            int primerBloqueLlave;
            int actualBloqueLlave;
        }

        IdxEntry * Indice::Buscar(char * id){
            int pos = fnHash(id);
            int bloqueRelativo = pos/CANT_HASH_TABLE_ENTRIES_POR_BLOQUE;
            int entradaRelativa = pos%CANT_HASH_TABLE_ENTRIES_POR_BLOQUE;
            int bloqueActual = tabla->primerBloqueIndice;
            for(int i = 0; i < bloqueRelativo; i++){
                BloqueHashTable * bht = new BloqueHashTable(bloqueActual);
                bht->load();
                bloqueActual = bht->sig;
                delete bht;
            }
            BloqueHashTable * bht = new BloqueHashTAble(bloqueAcutal);
            bht->load();
            HashTableEntry * hte = bht->entradas->get(entradaRelativa);
            int bloqueLlaves = hte->primerBloqueLlaves;
            while(bloqueLlave != hte->actualBloqueLlave){
                BloqueIdxEntries * bie = new BloqueIdxEntries(bloqueLlave);
                bie->load();
                for(int i = 0; i < bie->cantEntradas; i++){
                    IdxEntry * entry = bie->entradas->get(i);
                    if(entry->id ?==? id)
                        return entry;
                    delete entry;
                }
                bloqueLlaves = b->sig;
                delete b;
            }
            return null;
        }

        mit ocw introduction to algorithm
            buscar hash tables;
*/
