#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Struttura per passare dati al thread
typedef struct {
    int thread_id;
} t_data;

void* printThis(void* arg);
int getNumberOfCores();

int main() {
    int numThread = getNumberOfCores();
    printf("The max number of threads is convenient to use is %d\n", numThread);
    pthread_t t[numThread];

    for(int i = 0; i < numThread; i++){
    t_data* data = malloc(sizeof(t_data));
    if(data == NULL) {
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }
    data->thread_id = i;

    //crea i thread passando la struttura dati
    int rc = pthread_create(&t[i], NULL, printThis, (void*)data);
    if(rc) {
        printf("ERROR; return code from pthread create is %d\n", rc);
        exit(EXIT_FAILURE);
    }
 }
    for(int i = 0; i < numThread; i++) {
        pthread_join(t[i], NULL);
    }
    pthread_exit(NULL);
}

// Funzione da passare al thread
void* printThis(void* arg){
    t_data* data = (t_data*)arg;
    printf("Hello, I`am thread number:%d\n", data->thread_id);

    //libero la memoria allocata per i dati del thread
    free(data);
    pthread_exit(NULL);
}

//Optimize Number of Cores
int getNumberOfCores(){
    int numCores;
    char result[1024];

    // Apri il comando per la lettura
    FILE *fp = popen("nproc", "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(EXIT_FAILURE);
    }

    //leggi output del comando
    if (fgets(result, sizeof(result), fp) != NULL) {
        numCores = atoi(result);
    } else {
        perror("Failed to read command output");
        pclose(fp);
        exit(EXIT_FAILURE);
    }

    //chiudi il file pointer
    pclose(fp);

    return numCores;

}