#include "listadlc.h"

dllista *crear_elemento(DATO dato) {
    dllista *nuevo = (dllista *)malloc(sizeof(dllista));
    if (nuevo == NULL)
        return NULL;
    nuevo->dato = dato;
    nuevo->previo = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

ListaDL *crear_lista(void) {
    ListaDL *lista = (ListaDL *)malloc(sizeof(ListaDL));
    if (lista == NULL)
        return NULL;
    lista->cabeza = NULL;
    lista->longitud = 0;
    return lista;
}

void insertar_inicio(ListaDL *lista, DATO dato) {
    dllista *nuevo = crear_elemento(dato);
    if (nuevo == NULL)
        return;

    if (lista->cabeza == NULL) {
        nuevo->siguiente = nuevo;
        nuevo->previo = nuevo;
        lista->cabeza = nuevo;
    } else {
        dllista *ultimo = lista->cabeza->previo;
        nuevo->siguiente = lista->cabeza;
        nuevo->previo = ultimo;
        lista->cabeza->previo = nuevo;
        ultimo->siguiente = nuevo;
        lista->cabeza = nuevo;
    }
    lista->longitud++;
}

void insertar_final(ListaDL *lista, DATO dato) {
    dllista *nuevo = crear_elemento(dato);
    if (nuevo == NULL)
        return;

    if (lista->cabeza == NULL) {
        nuevo->siguiente = nuevo;
        nuevo->previo = nuevo;
        lista->cabeza = nuevo;
    } else {
        dllista *ultimo = lista->cabeza->previo;
        nuevo->siguiente = lista->cabeza;
        nuevo->previo = ultimo;
        ultimo->siguiente = nuevo;
        lista->cabeza->previo = nuevo;
    }
    lista->longitud++;
}

void insertar_en_posicion(ListaDL *lista, DATO dato, int posicion) {
    if (posicion < 0 || posicion > lista->longitud)
        return;

    if (posicion == 0) {
        insertar_inicio(lista, dato);
        return;
    }
    if (posicion == lista->longitud) {
        insertar_final(lista, dato);
        return;
    }

    dllista *nuevo = crear_elemento(dato);
    if (nuevo == NULL)
        return;

    dllista *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++)
        actual = actual->siguiente;

    nuevo->previo = actual->previo;
    nuevo->siguiente = actual;
    actual->previo->siguiente = nuevo;
    actual->previo = nuevo;
    lista->longitud++;
}

DATO eliminar_inicio(ListaDL *lista) {
    if (lista->cabeza == NULL)
        return -1;

    dllista *eliminado = lista->cabeza;
    DATO dato = eliminado->dato;

    if (lista->longitud == 1) {
        lista->cabeza = NULL;
    } else {
        dllista *ultimo = lista->cabeza->previo;
        lista->cabeza = lista->cabeza->siguiente;
        lista->cabeza->previo = ultimo;
        ultimo->siguiente = lista->cabeza;
    }

    free(eliminado);
    lista->longitud--;
    return dato;
}

DATO eliminar_final(ListaDL *lista) {
    if (lista->cabeza == NULL)
        return -1;

    dllista *eliminado = lista->cabeza->previo;
    DATO dato = eliminado->dato;

    if (lista->longitud == 1) {
        lista->cabeza = NULL;
    } else {
        dllista *nuevo_ultimo = eliminado->previo;
        nuevo_ultimo->siguiente = lista->cabeza;
        lista->cabeza->previo = nuevo_ultimo;
    }

    free(eliminado);
    lista->longitud--;
    return dato;
}

DATO eliminar_en_posicion(ListaDL *lista, int posicion) {
    if (posicion < 0 || posicion >= lista->longitud)
        return -1;

    if (posicion == 0)
        return eliminar_inicio(lista);
    if (posicion == lista->longitud - 1)
        return eliminar_final(lista);

    dllista *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++)
        actual = actual->siguiente;

    DATO dato = actual->dato;
    actual->previo->siguiente = actual->siguiente;
    actual->siguiente->previo = actual->previo;
    free(actual);
    lista->longitud--;
    return dato;
}

int buscar(ListaDL *lista, DATO dato) {
    if (lista->cabeza == NULL) 
        return -1;
        
    dllista *actual = lista->cabeza;
    int posicion = 0;
    do {
        if (actual->dato == dato)
            return posicion;
        actual = actual->siguiente;
        posicion++;
    } while (actual != lista->cabeza);
    
    return -1;
}

DATO obtener(ListaDL *lista, int posicion) {
    if (posicion < 0 || posicion >= lista->longitud)
        return -1;

    dllista *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++)
        actual = actual->siguiente;
    return actual->dato;
}

int esta_vacia(ListaDL *lista) {
    return lista->cabeza == NULL;
}

int longitud(ListaDL *lista) {
    return lista->longitud;
}

void imprimir_lista(ListaDL *lista) {
    if (lista->cabeza == NULL) {
        printf(" -> NULL\n");
        return;
    }
    
    dllista *actual = lista->cabeza;
    do {
        printf("[%d]", actual->dato);
        printf(" <-> ");
        actual = actual->siguiente;
    } while (actual != lista->cabeza);
    printf("CABEZA\n");
}

void imprimir_lista_reversa(ListaDL *lista) {
    if (lista->cabeza == NULL) {
        printf(" -> NULL\n");
        return;
    }
    
    dllista *actual = lista->cabeza->previo;
    do {
        printf("[%d]", actual->dato);
        printf(" <-> ");
        actual = actual->previo;
    } while (actual != lista->cabeza->previo);
    printf("COLA\n");
}

void liberar_lista(ListaDL *lista) {
    if (lista->cabeza != NULL) {
        dllista *actual = lista->cabeza;
        do {
            dllista *siguiente = actual->siguiente;
            free(actual);
            actual = siguiente;
        } while (actual != lista->cabeza);
    }
    free(lista);
}
