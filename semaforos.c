#include <pthread.h>

typedef struct {
    int value;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
} Semaforo;

void init_semaforo(Semaforo* sem, int initial_value) {
    sem->value = initial_value;
    pthread_cond_init(&sem->cond, NULL);
    pthread_mutex_init(&sem->mutex, NULL);
}

void wait_semaforo(Semaforo* sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->value--;
    if (sem->value < 0) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    pthread_mutex_unlock(&sem->mutex);
}

void signal_semaforo(Semaforo* sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->value++;
    if (sem->value <= 0) {
        pthread_cond_signal(&sem->cond);
    }
    pthread_mutex_unlock(&sem->mutex);
}

