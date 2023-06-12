
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

/* structs.h*/
#include "structs.h"

/* DEFINES */
#define MC "/memoria_compartida_almacen"
#define MAX_PRODUCTOS 3

void crearMemoriaCompartida(int *fd_shm) {
    // Crear y configurar la memoria compartida
    *fd_shm = shm_open(MC, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (*fd_shm == -1) {
        perror("Error al crear la memoria compartida");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(*fd_shm, MAX_PRODUCTOS * sizeof(Producto)) == -1) {
        perror("Error al ajustar el tamaño de la memoria compartida");
        exit(EXIT_FAILURE);
    }
}

void borrarMemoriaCompartida(int fd_shm) {
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

int main() {
    int fd_shm;

    // Crear la memoria compartida
    crearMemoriaCompartida(&fd_shm);

    printf("Memoria compartida creada correctamente\n");

    // Realizar operaciones con la memoria compartida

    // Borrar la memoria compartida
    borrarMemoriaCompartida(fd_shm);

    return 0;
}
