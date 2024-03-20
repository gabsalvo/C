//
// Created by gab on 18/03/24.
/*
 * Leggere e Scrivere su File: Pratica la lettura da file utilizzando fscanf e la scrittura
 * su file con fprintf. Ad esempio, leggi numeri da un file e scrivili su un altro file.
*/
//
#include <stdlib.h>
#include <stdio.h>

void read_write(const char *input, const char *output);

int main(){
    read_write("numbers.txt", "write_numbers.txt");
    return 0;
}

void read_write(const char *input, const char *output){
    FILE *inputFile = fopen(input, "r");
    if (inputFile == NULL) {
        perror("Errore a leggere il file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(output, "w");
    if (outputFile == NULL) {
        perror("Errore ad aprire/creare il file");
        exit(EXIT_FAILURE);
    }

    int number;
    while( 1 == fscanf(inputFile, "%d", &number)) {
        fprintf(outputFile,"%d\n", number);
    }

    fclose(inputFile);
    fclose(outputFile);
}

