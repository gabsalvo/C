#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;
int x = 0;

void* increment();

int main(){
    pthread_t t1, t2;

    sem_init(&sem, 0, 1);
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);

    return 0;
}

void* increment(){
    // Aspetta sul semaforo
    sem_wait(&sem);
    for(int i = 0; i < 10000; i++){
        x++;
    }
    printf("Valore attuale della variabile condivisa: %d\n", x);
    sem_post(&sem);
    return NULL;
}