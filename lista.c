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

void crear_lista_general(char nombre_comida){
 // Crea los productos generales 
    Producto producto1;
    strcpy(producto1.nombre, nombre_comida[0]);
    producto1.codigo = 1001;
    producto1.disponibilidad = rand() % 10 + 1;
    producto1.necesidad = rand() % 10 + 1;
    
    Producto producto2;
    strcpy(producto2.nombre, nombre_comida[1]);
    producto2.codigo = 1002;
    producto2.disponibilidad = rand() % 10 + 1;
    producto2.necesidad = rand() % 10 + 1;
    
    Producto producto3;
    strcpy(producto3.nombre, nombre_comida[2]);
    producto3.codigo = 1003;
    producto3.disponibilidad = rand() % 10 + 1;
    producto3.necesidad = rand() % 10 + 1;
    
    Producto producto4;
    strcpy(producto4.nombre, nombre_comida[3]);
    producto4.codigo = 1001;
    producto4.disponibilidad = rand() % 10 + 1;
    producto4.necesidad = rand() % 10 + 1;
     
    Producto producto5;
    strcpy(producto5.nombre, nombre_comida[4]);
    producto5.codigo = 1002;
    producto5.disponibilidad = rand() % 10 + 1;
    producto5.necesidad = rand() % 10 + 1;
    
    Producto producto6;
    strcpy(producto6.nombre, nombre_comida[5]);
    producto6.codigo = 1003;
    producto6.disponibilidad = rand() % 10 + 1;
    producto6.necesidad = rand() % 10 + 1;

    Producto producto7;
    strcpy(producto7.nombre, nombre_comida[6]);
    producto7.codigo = 1002;
    producto7.disponibilidad = rand() % 10 + 1;
    producto7.necesidad = rand() % 10 + 1;
    
    Producto producto8;
    strcpy(producto8.nombre, nombre_comida[7]);
    producto8.codigo = 1003;
    producto8.disponibilidad = rand() % 10 + 1;
    producto8.necesidad = rand() % 10 + 1;
    
    Producto producto9;
    strcpy(producto9.nombre, nombre_comida[8]);
    producto9.codigo = 1001;
    producto9.disponibilidad = rand() % 10 + 1;
    
    Producto producto10;
    strcpy(producto10.nombre, nombre_comida[9]);
    producto10.codigo = 1002;
    producto10.disponibilidad = rand() % 10 + 1;
    
    Producto producto11;
    strcpy(producto11.nombre, nombre_comida[10]);
    producto11.codigo = 1003;
    producto11.disponibilidad = rand() % 10 + 1;
    
    // Insertar los productos en la lista
    insertarProducto(&cabeza, producto1);
    insertarProducto(&cabeza, producto2);
    insertarProducto(&cabeza, producto3);
    insertarProducto(&cabeza, producto4);
    insertarProducto(&cabeza, producto5);
    insertarProducto(&cabeza, producto6);
    insertarProducto(&cabeza, producto7);
    insertarProducto(&cabeza, producto8);
    insertarProducto(&cabeza, producto9);
    insertarProducto(&cabeza, producto10);
    insertarProducto(&cabeza, producto11);
}