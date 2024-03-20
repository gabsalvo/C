/*
 * Creazione e Join di Thread: Crea un singolo thread secondario,
 * fai eseguire al thread una semplice funzione (come stampare qualcosa),
 * e poi fai un join del thread dal main.
 * */
#include <stdio.h>
#include <pthread.h>

void *sayHi();

int main(){
    pthread_t t;
    int result;

    result= pthread_create(&t, NULL, sayHi, NULL);
    if (result != 0) {
        perror("Impossibile creare il thread");
    }

    result = pthread_join(t, NULL);
    if (result != 0) {
        perror("Join del thread fallito");
        return -2;
    }
    return 0;
}

void *sayHi() {
    printf("Hello people, this is my first thead!\n");
    return 0;
}
