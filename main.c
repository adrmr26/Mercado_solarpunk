#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "structs.h"

// Función para insertar un producto al final de la lista
void insertarProducto(Nodo** cabeza, Producto *producto) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->producto = producto;
    nuevoNodo->siguiente = NULL;

    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else {
        Nodo* actual = *cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

// Función para buscar un producto por su código
Nodo* buscarProducto(Nodo* cabeza, int codigo) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        if (actual->producto->codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL; // Producto no encontrado
}

// Función para modificar la disponibilidad de un producto
void modificarDisponibilidad(Nodo* cabeza, int codigo, int nuevaDisponibilidad) {
    Nodo* nodo = buscarProducto(cabeza, codigo);
    if (nodo != NULL) {
        nodo->producto->disponibilidad = nuevaDisponibilidad;
        printf("Disponibilidad modificada correctamente.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}

// Función para modificar la necesidad de un producto
void modificarNecesidad(Nodo* cabeza, int codigo, int nuevaNecesidad) {
    Nodo* nodo = buscarProducto(cabeza, codigo);
    if (nodo != NULL) {
        nodo->producto->necesidad = nuevaNecesidad;
        printf("Necesidad modificada correctamente.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}

// Función para imprimir la lista de productos
void imprimirLista(Nodo* cabeza) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("Producto:\n");
        printf("Código: %d\n", actual->producto->codigo);
        printf("Nombre: %s\n", actual->producto->nombre);
        printf("Disponibilidad: %d\n", actual->producto->disponibilidad);
        printf("Necesidad: %d\n", actual->producto->necesidad);
        printf("------------------------\n");
        actual = actual->siguiente;
    }
}

// Función para liberar la memoria ocupada por la lista
void liberarLista(Nodo** cabeza) {
    Nodo* actual = *cabeza;
    while (actual != NULL) {
        Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}

void desvincularAlmacen(Almacen* almacen, int shmId){
    // Desadjunta el área de memoria compartida
    if (shmdt(almacen) == -1) {
        perror("Error al desadjuntar el área de memoria compartida");
        exit(1);
    }
    // Elimina el área de memoria compartida
    if (shmctl(shmId, IPC_RMID, NULL) == -1) {
        perror("Error al eliminar el área de memoria compartida");
        exit(1);
    }
    else{
        printf("\nSe ha desvinculado el área de memoria compartida del Almacén\n");
    }
}

// Ejemplo de uso
int main() {

    //Se crea el área de memoria compartida del Almacen

    // Genera una clave única para la memoria compartida
    key_t clave = ftok(".", 'a'); 

    // Crea/obtiene el ID de la memoria compartida
    int shmId = shmget(clave, sizeof(Almacen), IPC_CREAT | 0666); 

    // Adjunta el segmento de memoria compartida al puntero "almacen"
    Almacen* almacen = (Almacen*)shmat(shmId, NULL, 0);

    // Inicializar lista de productos de almacen
    almacen->lista_productos = NULL;

    // Creación de productos de prueba 
    Producto* producto1 = (Producto*)malloc(sizeof(Producto));
    producto1->codigo = 1;
    strcpy(producto1->nombre,"Arroz");
    producto1->disponibilidad= 5;
    producto1->necesidad = 0;

    Producto* producto2 = (Producto*)malloc(sizeof(Producto));
    producto2->codigo = 2;
    strcpy(producto2->nombre,"Frijoles");
    producto2->disponibilidad = 5;
    producto2->necesidad = 0;

    Producto* producto3 = (Producto*)malloc(sizeof(Producto));
    producto3->codigo = 3;
    strcpy(producto3->nombre,"Maiz");
    producto3->disponibilidad = 5;
    producto3->necesidad= 0;

    insertarProducto(&almacen->lista_productos, producto1);
    insertarProducto(&almacen->lista_productos, producto2);
    insertarProducto(&almacen->lista_productos, producto3);

    // Imprimir la lista de productos
    imprimirLista(almacen->lista_productos);

    // Modificar la disponibilidad de un producto
    modificarDisponibilidad(almacen->lista_productos, 2, 8);

    // Modificar la necesidad de un producto
    modificarNecesidad(almacen->lista_productos, 3, 2);

    // Imprimir la lista de productos
    imprimirLista(almacen->lista_productos);

    // Liberar la memoria ocupada por la lista
    liberarLista(&almacen->lista_productos);

    // Desvincula el segmento de memoria compartida
    desvincularAlmacen(almacen, shmId); 

    return 0;
}