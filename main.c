#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "structs.h"


#define Numero_comunas 6
#define Numero_productos 4
#define Numero_anaqueles 3
#define Numero_total_productos 10


//Funcion para liberar la memoria compartida y sus datos 
void desvincularAlmacen(Almacen* almacen, int shmId) {
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



// Función para insertar un producto al final de la lista
void insertarProducto(Nodo** primero, Producto *producto) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->producto = producto;
    nuevoNodo->siguiente = NULL;

    if (*primero == NULL) {
        *primero = nuevoNodo;
    } else {
        Nodo* actual = *primero;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

// Función para buscar un producto por su código establecido 
Nodo* buscarProducto(Nodo* primero, int codigo) {
    Nodo* actual = primero;
    while (actual != NULL) {
        if (actual->producto->codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL; //En caso de no encontrarlo devuelve null
}

// Función para modificar la disponibilidad de un producto
void modificarDisponibilidad(Nodo* primero, int codigo, int nueva_disponibilidad) {
    Nodo* nodo = buscarProducto(primero, codigo);
    if (nodo != NULL) {
        nodo->producto->disponibilidad = nueva_disponibilidad;
        printf("La disponibilidad fue modificada de forma correcta.\n");
    } else {
        printf("Error en mercado:El producto no fue encontrado.\n");
    }
}

// Función para modificar la necesidad de un producto
void modificarNecesidad(Nodo* primero, int codigo, int nueva_necesidad) {
    Nodo* nodo = buscarProducto(primero, codigo);
    if (nodo != NULL) {
        nodo->producto->necesidad = nueva_necesidad;
        printf("La necesidad modificada correctamente.\n");
    } else {
        printf("Error en mercado:El producto no fue encontrado.\n");
    }
}

// Función para imprimir la lista de productos con su respectivas caracteristicas 
void imprimirLista(Nodo* primero) {
    Nodo* actual = primero;
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

// Función para liberar la memoria ocupada por la lista , se eliminan los datos
void liberarLista(Nodo** primero) {
    Nodo* actual = *primero;
    while (actual != NULL) {
        Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *primero = NULL; //Inicializamos el primer nodo 
}

// Ejemplo de uso
int main() {

      // Genera una clave única para la memoria compartida
    key_t clave = ftok(".", 'a'); 

    // Crea/obtiene el ID de la memoria compartida
    int shmId = shmget(clave, sizeof(Almacen), IPC_CREAT | 0666); 

    // Adjunta el segmento de memoria compartida al puntero "almacen"
    Almacen* almacen = (Almacen*)shmat(shmId, NULL, 0);


    // Inicializar lista de productos de almacen
    almacen->lista_productos = NULL;


  // Creación de productos
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


    //Inicializa las comunas 
/*
    int i, j;
    for (i = 0; i < Numero_comunas; i++) {  //Crea la comuna con su numero
        lista_comunas[i].numero_comuna = i;

        //SELECCIONAR PRODUCTOS inicializarProductos(lista_comunas[i].productos);

        for (j = 0; j < Numero_personas; j++) {     //Crea la persona que seria un hilo
            int persona_index = i * Numero_personas + j;
            int* puntero = malloc(sizeof(int));
            *puntero = persona_index;
            pthread_create(&(lista_comunas[i].personas[j]), NULL, crearPersona, puntero);
        }
    }

    for (i = 0; i < Numero_comunas; i++) {      //Une la persona con la comuna 
        for (j = 0; j < Numero_personas; j++) {
            pthread_join(lista_comunas[i].personas[j], NULL);
        }
    }*/


    

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