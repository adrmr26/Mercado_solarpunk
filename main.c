#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura Producto
typedef struct {
    int codigo;
    char nombre[50];
    int disponibilidad;
    int necesidad;
} Producto;

// Definición de la estructura Nodo
typedef struct Nodo {
    Producto producto;
    struct Nodo* siguiente;
} Nodo;

// Función para insertar un producto al final de la lista
void insertarProducto(Nodo** cabeza, Producto producto) {
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
        if (actual->producto.codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL; // Producto no encontrado
}

// Función para modificar la disponibilidad de un producto
void modificarDisponibilidad(Nodo* cabeza, int codigo, int nuevaDisponibilidad) {
    Nodo* producto = buscarProducto(cabeza, codigo);
    if (producto != NULL) {
        producto->producto.disponibilidad = nuevaDisponibilidad;
        printf("Disponibilidad modificada correctamente.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}

// Función para modificar la necesidad de un producto
void modificarNecesidad(Nodo* cabeza, int codigo, int nuevaNecesidad) {
    Nodo* producto = buscarProducto(cabeza, codigo);
    if (producto != NULL) {
        producto->producto.necesidad = nuevaNecesidad;
        printf("Necesidad modificada correctamente.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}

// Función para imprimir la lista de productos
void imprimirLista(Nodo* cabeza) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("Código: %d\n", actual->producto.codigo);
        printf("Nombre: %s\n", actual->producto.nombre);
        printf("Disponibilidad: %d\n", actual->producto.disponibilidad);
        printf("Necesidad: %d\n", actual->producto.necesidad);
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

// Ejemplo de uso
int main() {
    Nodo* lista_productos = NULL;

    // Insertar productos de ejemplo
    Producto producto1 = {1, "Producto 1", 10, 5};
    Producto producto2 = {2, "Producto 2", 5, 2};
    Producto producto3 = {3, "Producto 3", 3, 1};

    insertarProducto(&lista_productos, producto1);
    insertarProducto(&lista_productos, producto2);
    insertarProducto(&lista_productos, producto3);

    // Modificar la disponibilidad de un producto
    modificarDisponibilidad(lista_productos, 2, 8);

    // Modificar la necesidad de un producto
    modificarNecesidad(lista_productos, 3, 2);

    // Imprimir la lista de productos
    imprimirLista(lista_productos);

    // Liberar la memoria ocupada por la lista
    liberarLista(&lista_productos);

    return 0;
}