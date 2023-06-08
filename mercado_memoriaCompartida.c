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
#define MC "/memoria_compartida_mercado"



void call_mum_for_cakes(Mercado *mercado) {
    sleep((rand() % 5) + 2);

    mercado->available_pieces = 3;
    printf("I'm mum, and I have brought a new cake\n");
}

void main() {

    srand(time(NULL));
    
    //Abre la memoria compartida
    int fd_shm = shm_open(SHM_SEMS, O_RDWR | O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR);

    ftruncate(fd_shm, sizeof(Mercado)); //Tamaño de la memoria compartida

    Mercado *mercado = mmap(NULL, sizeof(Mercado), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);

    // Initializing values
    //                    1 to share between processes    Initial value of the sem
    sem_init(&mercado->mutex,1,1);
    mercado->available_pieces=3;


    for(int i = 0; i < Numero_comunas; i++) {
        if (fork() == 0) { // Es un proceso que crea una copia /hijo
            sleep((rand() % 9) + 1);
            printf("Kid %d entered\n", i+1);
            for (int n = 0; n < (rand() % 4) + 1; n++) {


                sem_wait(&mercado->mutex);

                if (mercado->available_pieces <= 0)  //consulto disponibilidad de producto
                    call_mum_for_cakes(mercado);   //llamo encargado

                mercado->available_pieces -= 1;

                printf("I'm the kid %d and I'm taking my peace of cake. There are %d left\n", i+1, mercado->available_pieces);
                sleep((rand() % 4) + 1);

                sem_post(&mercado->mutex);

                printf("I'm the kid %d and I'm eating\n", i+1);
                sleep((rand() % 3) + 3);

            }

            munmap(mercado, sizeof(Mercado));
            return;
        }
    }

    /* Waiting for the children */
    for (int i = 0; i < Numero_comunas; i++) 
        while (wait(NULL) == -1);

    munmap(mercado, sizeof(Mercado));
    shm_unlink(SHM_SEMS);
}
