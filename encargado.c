
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

#include "almacen_memoriaCompartida.c"
#include "mercado_memoriaCompartida.c"
/* srand */
#include <time.h>

/* DEFINES */
//#define MC "/memoria_compartida_almacen"
#define MAX_PRODUCTOS 3

int fd_shm = -1;
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