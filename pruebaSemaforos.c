#include <stdio.h>
#include <pthread.h>
#include "semaforos.c"


/* Este archivo es un archivo que prueba el funcionamiento de la biblioteca de semáforos creada por 
   nosotros */

Semaforo semaforo;
int recurso_compartido = 0;

void* proceso(void* arg) {
    wait_semaforo(&semaforo);
    
    // Sección crítica (recurso compartido)
    printf("Hilo %ld accediendo al recurso compartido: %d\n", pthread_self(), recurso_compartido);
    recurso_compartido++;
    
    signal_semaforo(&semaforo);
    
    return NULL;
}

int main() {
    int num_hilos = 5;
    pthread_t hilos[num_hilos];
    
    init_semaforo(&semaforo, 1);
    
    for (int i = 0; i < num_hilos; i++) {
        pthread_create(&hilos[i], NULL, proceso, NULL);
    }
    
    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], NULL);
    }
    
    return 0;
}
