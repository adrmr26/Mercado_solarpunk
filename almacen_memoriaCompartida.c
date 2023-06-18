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

void inicializar_almacen(Lista *lista_general) {

    srand(time(NULL));

    /* Abre el espacio de la memoria compartida */
    int fd_shm = shm_open(MC, O_RDWR | O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR);

    ftruncate(fd_shm, sizeof(Lista)); //NOSE SI ESTA BIEN

    lista_general = mmap(NULL, sizeof(Lista), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);

    if (lista_general == MAP_FAILED) {
        perror("Error al mapear la memoria compartida");
        exit(1);
    }
/*
    Producto* producto1 = &almacen[0]; 
    producto1->codigo = 1;
    sprintf(producto1->nombre, "Arroz");
    producto1->necesidad = 0;
    producto1->disponibilidad = 0;

    Producto* producto2 = &almacen[1]; 
    producto2->codigo = 2;
    sprintf(producto2->nombre, "Frijoles");
    producto2->necesidad = 0;
    producto2->disponibilidad = 0;

    Producto* producto3 = &almacen[2]; 
    producto3->codigo = 3;
    sprintf(producto3->nombre, "Maiz");
    producto3->necesidad = 0;
    producto3->disponibilidad = 0;
*/

    // Imprimir los productos en la memoria compartida
    printf("Productos en la memoria compartida:\n");
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        printf("Código: %d\n", lista_general[i].codigo);
        printf("Nombre: %s\n", lista_general[i].nombre);
        printf("Necesidad: %d\n", lista_general[i].necesidad);
        printf("Disponibilidad: %d\n", lista_general[i].disponibilidad);
        printf("------------------\n");
    }

    munmap(lista_general, sizeof(Lista));
    //close(fd_shm);
   // shm_unlink(MC);

}