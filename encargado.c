/* Semáforos */
#include <semaphore.h>

/* Memoria compartida */
#include <sys/mman.h>
#include <sys/stat.h>       
#include <fcntl.h>           

/* Generales */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* FORK */
#include <sys/types.h>
#include <unistd.h>

/* Wait de los procesos */
#include <sys/wait.h>

/* srand */
#include <time.h>

/* lista.c */
#include "lista.c"

/* DEFINES */
#define MCA "/memoria_compartida_almacen"
#define MCM "/memoria_compartida_mercado"
#define MAX_PRODUCTOS 11  //Máximo de productos en la lista general
#define NUM_ANAQUELES 3  // Número de anaqueles

Producto *almacen;
Producto *mercado;

int fd_shm_almacen;
int fd_shm_mercado;

// Se crea la memoria compartida de almacen
void inicializar_almacen(Nodo *lista_general) {

    srand(time(NULL));

    //Abre el espacio de la memoria compartida 
    fd_shm_almacen = shm_open(MCA, O_RDWR | O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR);

    ftruncate(fd_shm_almacen, sizeof(Producto)); 

    almacen = mmap(NULL, sizeof(Producto), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm_almacen, 0);

    if (almacen == MAP_FAILED) {
        perror("\nError al mapear la memoria compartida del almacén");
        exit(1);
    }
    
    Nodo* actual = lista_general;

    // Se agrega la lista de productos en la memoria compartida del almacen
    for(int i = 0; actual != NULL; i++){
        Producto* producto = &almacen[i];
        producto->codigo = actual->producto.codigo;
        strcpy(producto->nombre, actual->producto.nombre);
        producto->necesidad = actual->producto.necesidad;
        producto->disponibilidad = actual->producto.disponibilidad;
        actual = actual->siguiente;
    }
}

// Desvincula la memoria compartida del almacen
void desvincular_MC_almacen(){
    munmap(almacen, sizeof(Producto));
    if (close(fd_shm_almacen) == -1) {
        perror("Error al cerrar la memoria compartida");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink(MCA) == -1) {
        perror("Error al eliminar la memoria compartida");
        exit(EXIT_FAILURE);
    }
    printf("\nSe ha desvinculado correctamente la memoria compartida del almacén\n");
}

// Imprimir los productos en la memoria compartida del almacen
void imprimir_productos_almacen(){
    printf("\nProductos en la memoria compartida de almacen:\n");
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        printf("Nombre: %s\n", almacen[i].nombre);
        printf("Código: %d\n", almacen[i].codigo);
        printf("Disponibilidad: %d\n", almacen[i].disponibilidad);
        printf("Necesidad: %d\n", almacen[i].necesidad);
        printf("------------------\n");
    }
}

// Se crea la memoria compartida de mercado
void inicializar_mercado(Nodo *lista_general){

    srand(time(NULL));
    
    //Abre la memoria compartida
    fd_shm_mercado = shm_open(MCM, O_RDWR | O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR);

    ftruncate(fd_shm_mercado, sizeof(Producto)); //Tamaño de la memoria compartida

    mercado = mmap(NULL, sizeof(Producto), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm_mercado, 0);
  
    if (mercado == MAP_FAILED) {
        perror("\nError al mapear la memoria compartida del mercado");
        exit(1);
    }
    
    Nodo* actual = lista_general;

    // Se agrega la lista de productos que funciona como anaqueles en el mercado
    for(int i = 0; i < NUM_ANAQUELES; i++){
        Producto* producto = &mercado[i];
        producto->codigo = actual->producto.codigo;
        strcpy(producto->nombre, actual->producto.nombre);
        producto->necesidad = actual->producto.necesidad;
        producto->disponibilidad = actual->producto.disponibilidad;
        actual = actual->siguiente;
    }

}

// Desvincula la memoria compartida del mercado
void desvincular_MC_mercado(){
    munmap(mercado, sizeof(Producto));
    if (close(fd_shm_mercado) == -1) {
        perror("Error al cerrar la memoria compartida");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink(MCM) == -1) {
        perror("Error al eliminar la memoria compartida");
        exit(EXIT_FAILURE);
    }
    printf("\nSe ha desvinculado correctamente la memoria compartida del mercado\n");
}

// Imprimir los anaqueles en la memoria compartida del mercado
void imprimir_anaqueles(){
    printf("\nAnaqueles en la memoria compartida de mercado:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nombre: %s\n", mercado[i].nombre);
        printf("Código: %d\n", mercado[i].codigo);
        printf("Disponibilidad: %d\n", mercado[i].disponibilidad);
        printf("Necesidad: %d\n", mercado[i].necesidad);
        printf("------------------\n");
    }
}
/*
void crearMemoriaCompartida() {
    // Crear y configurar la memoria compartida
    fd_shm = shm_open(MC, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd_shm == -1) {
        perror("Error al crear la memoria compartida");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd_shm, MAX_PRODUCTOS * sizeof(Producto)) == -1) {
        perror("Error al ajustar el tamaño de la memoria compartida");
        exit(EXIT_FAILURE);
    }
}

void borrarMemoriaCompartida() {
    // Liberar recursos
    if (close(fd_shm) == -1) {
        perror("Error al cerrar la memoria compartida");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink(MC) == -1) {
        perror("Error al eliminar la memoria compartida");
        exit(EXIT_FAILURE);
    }
}
*/
/*
void* inicializar_encargado_principal(Lista *lista_principal) { 
    inicializar_almacen(lista_principal);
    Mercado* anaqueles = inicializar_mercado(lista_principal);
    

    while (1) { //De esta forma el loop es infinito hasta que se encuentre un break  
      //vE LISTAS 

    } 
} 
*/
/*
int main() {
    // Crear la memoria compartida
    crearMemoriaCompartida();

    printf("Memoria compartida creada correctamente\n");

    // Borrar la memoria compartida
    borrarMemoriaCompartida();

    return 0;
}   */