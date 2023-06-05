#include <pthread.h>

// Hay que poner un spinlock (while(true) para que no se hagan dos señales al mismo tiempo) 
// cuado se pase a memoria compartida

typedef struct {
    int valor;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
} Semaforo;

void crear_semaforo(Semaforo* sem, int valor_inicial) {
    sem->valor = valor_inicial;
    pthread_cond_init(&sem->cond, NULL);
    pthread_mutex_init(&sem->mutex, NULL);
}

void espera_semaforo(Semaforo* sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->valor--;
    if (sem->valor < 0) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    pthread_mutex_unlock(&sem->mutex);
}

void señal_semaforo(Semaforo* sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->valor++;
    if (sem->valor <= 0) {
        pthread_cond_signal(&sem->cond);
    }
    pthread_mutex_unlock(&sem->mutex);
}

void eliminar_semaforo(Semaforo* sem) {
    pthread_mutex_destroy(&sem->mutex);
    pthread_cond_destroy(&sem->cond);
}

