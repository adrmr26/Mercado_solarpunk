#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N_THREADS 5

int contador = 0;
sem_t semaforo;

void *funcion_hilo(void *arg) {
    int id = *(int *) arg;
    printf("Hilo %d iniciado\n", id);
    for (int i = 0; i < 8; i++) {
        sem_wait(&semaforo); // esperar a que el semáforo sea mayor que cero
        contador++; // sección crítica
        printf("Hilo %d: contador = %d\n", id, contador);
        sem_post(&semaforo); // incrementar el semáforo en uno
        sleep(1); // esperar un segundo
    }
    printf("Hilo %d finalizado\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[N_THREADS];
    int ids[N_THREADS];
    sem_init(&semaforo, 0, 1); // inicializar el semáforo con valor 1
    for (int i = 0; i < N_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&hilos[i], NULL, funcion_hilo, (void *) &ids[i]);
    }
    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(hilos[i], NULL);
    }
    sem_destroy(&semaforo); // liberar el semáforo
    printf("Valor final del contador: %d\n", contador);
    return 0;
}
