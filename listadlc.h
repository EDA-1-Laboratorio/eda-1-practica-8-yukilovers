#ifndef LISTADLC_H
#define LISTADLC_H

#include <stdio.h>
#include <stdlib.h>

typedef int DATO;

typedef struct dllista {
    DATO dato;
    struct dllista *previo;
    struct dllista *siguiente;
} dllista;

typedef struct lista_dl {
    dllista *cabeza;
    int longitud;
} ListaDL;

dllista *crear_elemento(DATO dato);
ListaDL *crear_lista(void);
void insertar_inicio(ListaDL *lista, DATO dato);
void insertar_final(ListaDL *lista, DATO dato);
void insertar_en_posicion(ListaDL *lista, DATO dato, int posicion);
DATO eliminar_inicio(ListaDL *lista);
DATO eliminar_final(ListaDL *lista);
DATO eliminar_en_posicion(ListaDL *lista, int posicion);
int buscar(ListaDL *lista, DATO dato);
DATO obtener(ListaDL *lista, int posicion);
int esta_vacia(ListaDL *lista);
int longitud(ListaDL *lista);
void imprimir_lista(ListaDL *lista);
void imprimir_lista_reversa(ListaDL *lista);
void liberar_lista(ListaDL *lista);

#endif
