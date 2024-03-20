#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void* myturn( void * arg) {
    int *iprt = (int *)malloc(sizeof(int));
    *iprt = 5;
   for(int i=0; i < 8; i++){
        sleep(1);
        printf("My turn! %d %d\n", i, *iprt);
        (*iprt)++; 
    }
    return iprt;
}

void yourturn() {
    for(int i = 0; i < 3; i++){
        sleep(2);
        printf("Your Turn! %d\n", i);
    }
}

int main() {
    pthread_t newthread;
    int *result;


    pthread_create(&newthread, NULL, myturn, NULL);
    yourturn();
    pthread_join(newthread, (void *)&result);
    printf("thread's done: *result=%d\n", *result);
}