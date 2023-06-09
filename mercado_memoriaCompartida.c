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

//Aqui viene la función del encargado cuando cambia un anaquel
void cambio_producto(Mercado *mercado) {
    sleep((rand() % 5) + 2);

    mercado->available_pieces = 3;
    printf("I'm mum, and I have brought a new cake\n");
}

//Genera los productos de los anaqueles de forma aleatoria 
void generar_productos_anaqueles(Mercado* mercado, char nombre_productos[11][10]) { 
    int i; 
    
    for (i = 0; i < Numero_anaqueles; i++) { 
        int index_producto = rand() % 11; 
        mercado->lista_productos_anaqueles[i].codigo = i + 1; 
        sprintf(mercado->lista_productos_anaqueles[i].nombre,nombre_productos[index_producto]); 
        mercado->lista_productos_anaqueles[i].disponibilidad = rand() % 100; 
        mercado->lista_productos_anaqueles[i].necesidad = 0; 
    } 
    mercado->cantidad_anaqueles = Numero_anaqueles; 
} 

void main() {

    srand(time(NULL));
    
    //Abre la memoria compartida
    int fd_shm = shm_open(MC, O_RDWR | O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR);

    ftruncate(fd_shm, sizeof(Mercado)); //Tamaño de la memoria compartida

    Mercado *mercado = mmap(NULL, sizeof(Mercado), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);

    // Se inicializan los valores
    sem_init(&mercado->mutex,1,1);
    mercado->cantidad_anaqueles = 3;
    char nombre_comida[11][10] = {"Arroz","Frijoles","Maiz","Papa","Zanahoria","Yuca","Lentejas","Tomate","Brocoli","Coliflor","Aguacate"} ; 

    //Inicializar los productos 
    generar_productos_anaqueles(mercado,nombre_comida);


    for(int i = 0; i < Numero_comunas; i++) {
        if (fork() == 0) { // Es un proceso que crea una copia /hijo
            sleep((rand() % 9) + 1);
            printf("Comuna %d entrando\n", i+1);
            for (int n = 0; n < (rand() % 4) + 1; n++) {


                sem_wait(&mercado->mutex);

                if (mercado->cantidad_anaqueles <= 0)  //consulto disponibilidad de producto
                    //cambio_producto(mercado);   //llamo encargado
                    printf("Aqui viene el encargado\n");

                mercado->cantidad_anaqueles -= 1;

                printf("Soy la comuna  %d y estoy tomando producto\n", i+1);
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
    shm_unlink(MC);//se borra la memoria 
}
