/**
 * Uso di Mutex: Pratica con pthread_mutex_lock e
 * pthread_mutex_unlock per scrivere un programma che previene
 * la race condition quando due thread cercano di modificare una variabile condivisa.
 * */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* changeSameVariable();
int x = 0;
pthread_mutex_t lock;

kc
int main(){
    int numOfThreads = 4;
    pthread_t t[numOfThreads];
    pthread_mutex_init(&lock, NULL);

    for(int i = 0; i < numOfThreads; i++){
        int thread = pthread_create(&t[i], NULL, changeSameVariable, NULL);
    }
    for(int i = 0; i < numOfThreads; i++){
        pthread_join(t[i], NULL);
    }
    pthread_mutex_destroy(&lock);

    printf("Valore finale della variabile condivisa: %d\n", x);
    return 0;
}

void* changeSameVariable() {
    pthread_mutex_lock(&lock);
    for(int i = 0; i < 10000; i++) {
        int currentValue = x;
        usleep(1);
        x = currentValue + 1;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}