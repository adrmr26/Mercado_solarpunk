#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "structs.h"

void insertar_lista (Nodo** lista,Producto *producto){
    Nodo* nuevo_producto = (Nodo*)malloc(sizeof(Nodo));
    nuevo_producto->producto = producto;
    nuevo_producto->siguiente = NULL;
    
    // Si esta vacia el primero se convierte en el inicio de la lista
    if (*lista == NULL) {
        *lista = nuevo_producto;
    } else {
        // Encuentra el ultimo nodo 
        Nodo* ultimo = *lista;
        while (ultimo->siguiente != NULL) {
            ultimo = ultimo->siguiente;
        }

        ultimo->siguiente = nuevo_producto;
    }
    
}

//Elimina un producto segun el codigo de este 
void eliminar_nodo(Nodo** lista, int codigo) {
    Nodo* actual = *lista;
    Nodo* anterior = NULL;

    // Recorre la lista buscando el producto con el codigo 
    while (actual != NULL && actual->producto.codigo != codigo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Si se encontró el producto, se elimina 
    if (actual != NULL) {
        if (anterior == NULL) {
            *lista = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }

        free(actual);
        printf("Producto eliminado.\n");
    } else {
        printf("No se encontró un producto con el código especificado.\n");
    }
}

//Imprime la lista completa 
void imprimir_lista (Nodo *lista){
   Nodo* actual = lista;
    
    // Recorrer la lista y mostrar cada producto
    while (actual != NULL) {
        printf("Nombre: %s\n", actual->producto.nombre);
        printf("Código: %d\n", actual->producto.codigo);
        printf("Disponibilidad: %d\n", actual->producto.disponibilidad);
         printf("Necesidad: %d\n", actual->producto.necesidad);
        printf("\n");
        
        actual = actual->siguiente;
    }
}

//Destruye la lista para liberar la memoria 
void destruir_lista(Nodo** lista) {
    Nodo* actual = *lista;
    Nodo* siguiente = NULL;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    *lista = NULL;
    printf("Lista de productos destruida.\n");
}

