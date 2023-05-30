#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
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