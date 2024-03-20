/*
 * Raccolta di tutte le definizioni chieste dal prof di tutte le funzioni fatte
 * */
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DELIMITATORI " ,.-"
#define ROWS 3
#define COLS 4
#define NUM_THREADS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int deCounter = 0;
// Lezione 1, lettura scrittura di interi dal terminale

int scannami() {
    int numero;
    printf("Digita un numero; ");
    scanf("%d", &numero);
    printf("Hai inserito %d\n", numero);
    return 0;
}

/**
 La famiglia di funzioni scanf, inclusa fscanf, vscanf, e
 vfscanf, viene utilizzata per leggere e interpretare l'input
 formattato da stdin o da altri flussi di dati.

Input
Per scanf e vscanf:

const char *restrict format: Una stringa di formato che
specifica come interpretare l'input. La stringa può contenere caratteri fissi,
specificatori di conversione (come %d per gli interi), e spazi bianchi che vengono
usati per interpretare e separare l'input.

Ritorno
In caso di successo: Restituisce il numero di elementi
 dell'input che sono stati correttamente interpretati e assegnati.
 Questo numero può essere inferiore a quello degli specificatori di
 formato se la lettura di un elemento fallisce prima di raggiungere la fine
 della stringa di formato.
EOF: Restituisce EOF se viene raggiunta la fine del flusso
 di input (EOF) prima di qualsiasi conversione riuscita o se si verifica
 un errore di lettura. In caso di errore di lettura, l'indicatore di errore
 per il flusso viene impostato (è possibile controllarlo con ferror(3)),
e errno viene impostato per riflettere l'errore specifico.
**/

//Lezione 2 malloc, free, realloc

int malloccami_realloccami() {
    int *arr = malloc(10*sizeof(int));
    if (arr == NULL){
        perror("Allocazione fallita");
        exit(EXIT_FAILURE);
    }

    int *new_arr = realloc(arr, 20 * sizeof(int));
    if (new_arr == NULL) {
        perror("Realloc Fallita");
        free(arr);
        exit(EXIT_FAILURE);
    }
    arr = new_arr;

    free(arr);
    return 0;
}

/**
 * Le funzioni malloc, free e realloc sono utilizzate in C per la gestione della memoria dinamica.

malloc
La funzione malloc è utilizzata per allocare una quantità specificata di memoria.

Input: size_t size - la quantità di memoria da allocare in byte.

Ritorno: Restituisce un puntatore al blocco di memoria
allocato se la funzione ha successo, altrimenti restituisce NULL se
la memoria non può essere allocata.

free
La funzione free è utilizzata per liberare la memoria allocata
 precedentemente con malloc, calloc o realloc.

Input: void *ptr - un puntatore alla memoria da liberare.
Ritorno: Non ritorna alcun valore.

realloc
La funzione realloc è utilizzata per ridimensionare la memoria allocata
precedentemente con malloc o calloc.

Input:
void *ptr: Un puntatore alla memoria attualmente allocata.
size_t new_size: La nuova dimensione della memoria in byte.
Ritorno: Restituisce un puntatore al nuovo blocco di memoria se la
funzione ha successo, altrimenti restituisce NULL se la memoria non può
essere allocata o ridimensionata.

 * */

// Lezione 3 puntatori, passaggio parametri per riferimento

void incrementa(int *p){
    (*p)++;
}

void attuaIncremento(){
    int numero = 68;
    incrementa(&numero);
    printf("attuaIncremento: %d\n", numero);
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void modifyPointers(int **ptr, int *newAddress){
    *ptr = newAddress;
}

int attuaSwap_Modify() {
    int x = 10, y = 20;
    int *ptrX = &x, *ptrY = &y;
    int **ptrToPtrX = &ptrX; // Puntatore a puntatore a int

    printf("Prima dello swap: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("Dopo lo swap: x = %d, y = %d\n", x, y);

    // Modifica l'indirizzo a cui ptrX punta (lo fa puntare a y)
    modifyPointers(ptrToPtrX, &y);
    printf("Dopo modifyPointer: *ptrX = %d\n", *ptrX);

    // Modifica il valore di y attraverso ptrX (ora puntano alla stessa locazione)
    *ptrX = 30;
    printf("Dopo la modifica di y attraverso ptrX: y = %d\n", y);

    return 0;
}

/**
 * & Operatore di Indirizzo: Quando posto davanti a una variabile,
 * & restituisce l'indirizzo di memoria dove la variabile è allocata.
 * Questo è spesso usato in combinazione con i puntatori per assegnare
 * l'indirizzo di una variabile a un puntatore.
 *
 * '*' Operatore di dereferenziazione: Quando usato con un puntatore,
 * '*' accede al valore memorizzato all'indirizzo a cui il puntatore punta.
 * '*' è usato anche nella dichiarazione di un puntatore per indicare che
 * una variabile è di tipo puntatore.
 * */

// Lezione 4 Stringhe in C, uso dei parametri argc/argv

char printMyString(){
    char name[] = "Gabriele";
    printf("What's your name? %s\n", name);
}

int takeArgs(int argc, char *argv[]){
    printf("Numero di argomenti passati: %d\n", argc);
    for(int i = 0; i < argc; i++) {
        printf("Argomento %d: %s\n", i, argv[i]);
    }
    return 0;
}

// Lezione 5 copia di un puntatore vs copia di un array: la funzione strdup(),
// fopen, fprinf, fclose

/**
* Cosa Prende strdup
strdup() prende un singolo argomento:

const char *s: Un puntatore a una stringa di caratteri terminata da null ('\0') che si desidera duplicare.
Cosa Ritorna strdup
Ritorno: Restituisce un puntatore alla nuova stringa, che è una
duplicata della stringa passata come argomento. Questa nuova stringa
avrà la propria copia dei dati della stringa originale, allocata dinamicamente sulla heap.
Se l'allocazione della memoria fallisce, strdup() ritorna NULL.
**/

int copiaDipendente(){
    char *original = "Testo";
    char *copia = original;
    // quello che fai a uno lo fai all'altro
    printf("L'originale Dipendente: %p\n", (void *)original);
    printf("   La copia Dipendente: %p\n", (void *)copia);
    return 0;
}

int copiaIndipendente(){
    char *original = "Testo";
    char *copia = strdup(original);

    printf("L'originale Indipendente: %p\n", (void *)original);
    printf("   La copia Indipendente: %p\n", (void *)copia);

    free(copia);
    return 0;
}

// Lezioni 6
// Uso di asserzioni

/**
 * L'assert prende in input una affermazione che dovrebbe
 * essere sempre vera
 * Return : non ha valore di ritorno, termina il programma se aff è falsa
 * **/
int useAssert() {
    int b = 0;
    b += 1;
    assert(b != 0);
    return 0;
}

// Lettura di un array di interi da un file
/**
 * fopen
 *
 * INPUT:
 * 1. const char *filename: Una stringa che
 *    rappresenta il nome del file da aprire. Il percorso può essere relativo
 *    o assoluto, a seconda dell'ambiente di esecuzione.
 * 2. const char *mode: Una stringa che specifica
 *    la modalità di apertura del file.
 * RETURN :
 * Restituisce un puntatore a un oggetto FILE che può essere usato per accedere al file.
 * Questo puntatore sarà utilizzato in altre operazioni di input/output sul file.
 * Se l'apertura del file fallisce per qualsiasi motivo (ad esempio,
 * se il file non esiste e si tenta di aprirlo in modalità "r", o non si
 * hanno i permessi necessari), fopen restituisce NULL
 *
 * fscanf
 *
 * INPUT:
 * 1. FILE *stream: Un puntatore a un oggetto FILE che identifica il flusso di input
 * 2. const char *format: Una stringa di formato che specifica i tipi
 *    degli argomenti ricevuti. La stringa può contenere specificatori di formato
 *    che determinano il tipo di dati che fscanf cercherà di leggere e come
 *    verrà interpretato.
 * 3. Gli argomenti che corrispondono ai specificatori di formato nella stringa
 *    di formato. Questi argomenti devono essere indirizzi di memoria dove fscanf
 *    scriverà i dati letti.
 *
 * RETURN
 * Restituisce il numero di argomenti assegnati con successo.
 * Questo numero può essere minore di quello degli specificatori di formato se
 * l'input non corrisponde o in caso di fallimento prima della fine della stringa di formato.
 * Restituisce EOF se si verifica un errore prima che qualsiasi dato sia assegnato
 * o se viene raggiunta la fine del file.
 *
 * fprintf
 *
 * INPUT:
 * 1. FILE *stream: Un puntatore a un oggetto FILE che identifica il flusso di output.
 * 2. const char *format: Una stringa di formato che specifica come convertire e
 *    scrivere i dati. La stringa può contenere specificatori di formato per vari
 *    tipi di dati, testo letterale e caratteri di controllo.
 * 3.  ...: Gli argomenti che corrispondono ai specificatori di formato
 *     nella stringa di formato. Questi forniranno i valori da scrivere nel flusso di output.
 *
 * RETURN:
 *
 * Restituisce il numero di caratteri trasmessi, escluso
 * il terminatore nullo, in caso di successo.
 * Restituisce un numero negativo in caso di errore.
 *
 *
 * fclose
 *
 * INPUT:
 *
 * 1. FILE *stream: Un puntatore a un oggetto FILE che identifica il flusso di file da chiudere.
 *
 * RETURN:
 *
 * Restituisce zero in caso di successo.
 * Restituisce EOF (tipicamente -1) in caso di errore.
 *
 * **/

// Lezione 6 stdout/stderr/stdin e loro ridirezione

/**
* stdin : Utilizzato per leggere l'input dall'utente tramite
*        tastiera o da un altro flusso di input ridiretto.
* int numero;
  printf("Inserisci un numero: ");
  fscanf(stdin, "%d", &numero);
*
* stdout :  Utilizzato per scrivere l'output destinato allo schermo o
*          a un flusso di output ridiretto.
*
* fprintf(stdout, "Hai inserito il numero: %d\n", numero);
* printf("Hai inserito il numero: %d\n", numero);
*
**/

// Lezione 6 funzione perror() e var globale errno

int provaErrno(){
    errno = 0;
    int res = 2;
    if (res == errno) {
        perror("Problems man");
    }
    return 0;
}

/**
* perror:
*  INPUT:
*  1. const char *s: Una stringa fornita dall'utente che sarà stampata prima
*  del messaggio di errore. Può essere utilizzata per fornire
*  contesto su dove o perché si è verificato l'errore.
*
* errno è una variabile globale che le funzioni utilizzano per indicare il codice di errore
* specifico quando falliscono.
**/

// Lezione 7 Equivalenza fra *a e a[0]

/**
* '*a' ed a[0] sono equivalenti quando a è un puntatore ad un array.
*
**/

int equivalenzaPuntatori() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;

    printf("Stiamo stampando indirizzo di memoria del primo el array usando   *ptr: %p\n", (void*)ptr);
    printf("tiamo stampando indirizzo di memoria del puntatore stesso usando   &ptr: %p\n", &ptr);
    printf("Usando ptr[0]: %d\n", ptr[0]);
    printf("Usando   *arr: %d\n", *arr); // Output: 10
    printf("Usando arr[0]: %d\n", arr[0]); // Output: 10

    return 0;
}

// Lezione 7 Equivalenza fra a e &a[0], significato di &a[i]

int equivalenzaPuntatori2(){
    int arr[] = {1, 2, 4};
    int *p = arr;
    size_t arr_length = sizeof(arr) / sizeof(arr[0]);

    // Stampa l'indirizzo del primo elemento di array
    printf("L'indirizzo di 'arr' è: %p\n", (void*)arr);
    printf("L'indirizzo di '&arr[0]' è: %p\n", (void*)&arr[0]);

    for(int i = 0; i < 5; i++){
        // Calcola l'indirizzo usando l'aritmetica dei puntatori
        printf("Indirizzo di arr[%d] con aritmetica dei puntatori: %p\n", i, (void*)(p + i));
        // Calcola l'indirizzo usando l'operatore &
        printf("Indirizzo di arr[%d] con & operator: %p\n", i, (void*)&arr[i]);
    }

    for(size_t i = 0; i < arr_length; i++ ){
        printf("Stampa array el by el %d\n", arr[i]);
    }
    return 0;
}

// Lezione 7 calcola lunghezza stringa con puntatori

size_t lunghezzaStringa(const char *str){
    const char *ptr = str;
    while(*ptr){
        ptr++;
    }
    return ptr - str;
}

int applyLunghezzaStringa(){
    const char *testString = "Hello People";
    printf("la lunghezza di %s è %zu\n", testString, lunghezzaStringa(testString));
    return 0;
}

// Lezione 7 Aritmetica puntatori con mergesort

void merge(int a[], int na, int c[], int nc, int b[]) {
    int ia = 0, ib = 0, ic = 0;

    while (ia < na && ic < nc) {
        if (a[ia] < c[ic]) {
            b[ib++] = a[ia++];
        } else {
            b[ib++] = c[ic++];
        }
    }

    while (ia < na) {
        b[ib++] = a[ia++];
    }

    while (ic < nc) {
        b[ib++] = c[ic++];
    }
}

void mergesort(int a[], int n) {
    if (n < 2) return;

    int n1 = n / 2;
    int n2 = n - n1;

    mergesort(a, n1);
    mergesort(a + n1, n2);

    int *b = malloc(n * sizeof(int)); // Corretto sizeof(int) invece di sizeof(b)
    if (b == NULL) {
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }

    merge(a, n1, a + n1, n2, b);

    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }

    free(b);
}


int applyMergeSort(){
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    mergesort(arr, n);

    printf("Sorted Array :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

// Lezione 8 Significato del const char *

/**
* const char *var
* è un puntatore a una stringa di caratteri immutabili
**/

void printString(const char *str){
    printf("%s\n", str);
}

int applyPrintString(){
    const char *message = "Hello People!";
    // posso solo leggere non modificare
    printString(message);
    return 0;
}

// Lezione 8 evitare buffer overflow, %Ns, %ms

int modifierBuffer(){
    FILE *file = fopen("text.txt", "r");
    char *elBuffer;
    char buffer[11]; // Può contenere al massimo 10 caratteri più quello temrinatore
    fscanf(file, "%10s", buffer); // Legge al massimo 10 caratteri
    fscanf(file, "%ms", &elBuffer);

    free(elBuffer);
    return 0;
}

// Lezione 8 Costruzione stringhe mediante asprintf

/**
* asprintf: int asprintf(char **strp, const char *format, ...);
* Input:
* 1. char **strp: Un puntatore a un puntatore a char.
*    asprintf allocherà un buffer e aggiusterà *strp per puntare a questo buffer.
* 2. const char *format: La stringa di formato,
*    che specifica il formato dell'output, simile a printf
* 3. Una lista di argomenti addizionali che verranno formattati e inseriti nella stringa finale
*
* Return: restituisce il numero di caratteri scritti,
* escluso il terminatore nullo oppure -1 in caso di errore
* Bisogna usare il free
*
**/

int useAsprintf(){
    char *str;
    int temp = 23;

    if(asprintf(&str, "La temperatura è di %d gradi Celsius.", temp) == -1){
        perror("Errore nella creazione della stringa");
        return EXIT_FAILURE;
    }

    printf("%s\n", str);
    free(str);

    return 0;
}

// Lezione 9 Struct, typedef, e combinati e accesso con il punto

typedef struct {
    char nome[50];
    int eta;
    float powerLevel;
    char super_saiyan[50];
} Saiyan;

int applySaiyanStructEasy(){
    Saiyan goku;
    strcpy(goku.nome,"Goku");
    goku.eta = 40;
    goku.powerLevel = 10000.1;
    strcpy(goku.super_saiyan,"Mastered UI");
    printf("Strongest transformation of %s is %s\n",goku.nome, goku.super_saiyan);
    return 0;
}

// Lezione 8 array di struct, array di coppie

typedef struct {
    int primo;
    int secondo;
} Coppia;

int initAndUseCoppia(){
    Coppia coppie[3] = {
            {1,2}, // prima coppia
            {3, 4}, // Seconda coppia
            {5,6} // terza coppia

    };
    for(int i = 0; i < 3; i++){
        printf("Coppia %d: (%d, %d)\n", i+1, coppie[i].primo, coppie[i].secondo);
    }
    return 0;
}

typedef struct {
    int x;
    int y;
} Punto;

int puntatoriAStruct(){
    Punto p1 = {10, 20}; // Crea struttura punto
    Punto *ptr = &p1; //crea un puntatore alla struttura punto creata

    printf("Pre modifica\n");
    printf("x = %d\ny = %d\n", ptr -> x, ptr -> y);

    ptr -> x = 30;
    ptr -> y = 40;

    printf("Post modifica\n");
    printf("x = %d\ny = %d\n", ptr -> x, ptr -> y);

    return 0;
}

typedef struct {
    char *nome;
    char *nazione;
} Capitale;

int useCapitale(){
    Capitale *capitali[3];

    for(int i = 0; i < 3; i++){
        capitali[i] = (Capitale *)malloc(sizeof(Capitale));
        if(capitali[i] == NULL){
            perror("Allocazione fallita");
            return EXIT_FAILURE;
        }
    }

    capitali[0] -> nome = strdup("Roma");
    capitali[0] -> nazione = strdup("Italia");

    capitali[1] -> nome = strdup("London");
    capitali[1] -> nazione = strdup("United Kingdom");

    capitali[2] -> nome = strdup("Amsterdam");
    capitali[2] -> nazione = strdup("Nederland");

    for(int i = 0; i < 3; i++){
        printf("La capitale di %s è %s. \n", capitali[i] -> nazione, capitali[i] -> nome);
    }

    for(int i = 0; i < 3; i++){
        free(capitali[i] -> nome);
        free(capitali[i] -> nazione);
        free(capitali[i]);
    }

    return 0;
}

// Lezione 10 Ordinamento array di (puntatori) a struct

typedef struct {
    char *nome;
    int eta;
} Person;

/**
 * qsort: richiede una funzione di controllo che confronti due elementi di array
 * la funzione deve restituire un valore intero che indichi la relazione tra i due elementi:
 * input: un puntatore alla base dell'array che deve essere ordinato,
 * questo è di tipo void per consentire la flessibilità nell ordinamento di array
 * poi prende il numero di elementi nell'array, size_t è un tip di dato intero senza segno
 * poi prede la funzione per il compare
 *
 * return: modifica l'array fornito come input se tutto va bene
**/

int comparaEta(const void *a, const void *b) {
    Person *personA = *(Person **) a;
    Person *personB = *(Person **) b;
    return personA->eta - personB->eta;
}

int applyComparaEta(){
    Person p1 = {"Alice", 30};
    Person p2 = {"Bob", 234};
    Person p3 = {"Genos", 54};

    Person *persons[3] = {&p1, &p2, &p3};
    qsort(persons, 3, sizeof(Person*), comparaEta);

    for(int i = 0; i < 3; i++){
        printf("%s ha %d anni\n", persons[i] -> nome, persons[i] -> eta);
    }
    return 0;
}

// Lezione 10 introduzione all'uso delle funzioni come parametri di altre funzioni

/**
 * Un puntatore a una funzione è una variabile che memorizza l'indirizzo di una funzione.
 * Puoi utilizzare questo puntatore per invocare la funzione a cui punta
 * La sintassi per dichiarare un puntatore a funzione è la seguente
 * tipo_di_ritorno (*nome_puntatore)(lista_parametri);
**/

int quadrato(int x){
    return x*x;
}

int doppio(int x){
    return 2*x;
}

int applicaFunzione(int x, int (*func)(int)) {
    return func(x);
}

int applyApplication(){
    int val = 5;
    printf("Il quadrato di %d è %d\n", val, applicaFunzione(val, quadrato));
    printf("Il doppio di %d è %d\n", val, applicaFunzione(val, doppio));

    return 0;
}

// Mergesort con funzione di confronto passatra come argomento

typedef int (*CompareFunc)(const int, const int);

void mergeCompare(int a[], int na, int c[], int nc, int b[], CompareFunc compare){
    int ia, ib, ic = 0;

    while (ia < na && ic < nc) {
        if(compare(a[ia], c[ic]) < 0) {
            b[ib++] = a[ia++];
        } else {
            b[ib++] = c[ic++];
        }
    }

    while (ia < na) {
        b[ib++] = a[ia++];
    }

    while (ic < nc) {
        b[ib++] = c[ic++];
    }
}

void mergesortCompare(int a[], int n, CompareFunc compare) {
    if (n < 2) return;

    int n1 = n / 2;
    int n2 = n - n1;

    mergesortCompare(a, n1, compare);
    mergesortCompare(a + n1, n2, compare);

    int *b = malloc(n*sizeof(int));
    if (b == NULL) {
        perror("Errore nell'allocazione");
        exit(EXIT_FAILURE);
    }

    mergeCompare(a, n1, a+n1, n2, b, compare);

    for(int i = 0; i < n; i++){
        a[i] = b[i];
    }

    free(b);
}

int compareInt(const int a, const int b){
    return (a - b);
}

int applyMergeSortCompare() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    mergesortCompare(arr, n, compareInt);

    printf("Sorted Array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

// Lezione 11 Introduzione alle linked list*

typedef struct Nodo {
    int valore;
    struct Nodo *prossimo;
} Nodo;

void inserisciInTesta(Nodo **testa, int nuovoValore) {
    Nodo *nuovoNodo = malloc(sizeof(Nodo)); // Alloca un nuovo nodo
    nuovoNodo -> valore = nuovoValore; // Imposta il valore del nodo
    nuovoNodo -> prossimo = *testa; // Il nuovo nodo punto al vecchio primo nodo della lista
    *testa = nuovoNodo; // La testa ora è il nuovo nodo
}

void inserisciInCoda(Nodo **testa, int nuovoValore){
    Nodo *nuovoNodo = malloc(sizeof (Nodo));
    nuovoNodo -> valore = nuovoValore;
    nuovoNodo -> prossimo = NULL;

    if(*testa == NULL){
        *testa = nuovoNodo;
        return;
    }

    Nodo *ultimo = *testa;
    while (ultimo -> prossimo != NULL){
        ultimo = ultimo -> prossimo;
    }

    ultimo -> prossimo = nuovoNodo;
}

void stampaLista(Nodo *nodo){
    while (nodo != NULL) {
        printf("%d -> ", nodo-> valore);
        nodo = nodo -> prossimo;
    }
    printf("NULL\n");
}

void distruggiLista(Nodo **testa){
    Nodo *attuale = *testa;
    Nodo *temp;

    while(attuale != NULL){
        temp = attuale;               // Salva il rif al nodo corrente
        attuale = attuale -> prossimo;// Sposta il riferimento al prossimo nodo
        free(temp);               // Libera la memoria del nodo corrente
    }

    *testa = NULL;                   // Dopo aver distrutto la lista imposta la testa a NULL
    printf("Lista distrutta con successo\n");
}

int applyListaNodi(){
    Nodo *testa = NULL; // Inizia con una lista vuota

    inserisciInTesta(&testa, 3);
    inserisciInTesta(&testa, 10);
    inserisciInTesta(&testa, 123);
    inserisciInTesta(&testa, 45);
    inserisciInCoda(&testa, 45);
    inserisciInCoda(&testa, 123);
    inserisciInCoda(&testa, 10);
    inserisciInCoda(&testa, 3);

    stampaLista(testa);

    distruggiLista(&testa);

    return 0;
}


// Lezione 12 Inserimento in lista ordinata, inserimeto ricorsivo e paramentrico

void inserisciOrdinatoRicorsivo(Nodo **testa, int nuovoValore){
    // Caso base: la testa è NULL o il valore del nuovo nodo
    // è minore o uguale al valore della testa
    if (*testa == NULL || nuovoValore <= (*testa) -> valore){
        Nodo *nuovoNodo = malloc(sizeof(Nodo));
        nuovoNodo -> valore = nuovoValore;
        nuovoNodo -> prossimo = *testa;
        *testa = nuovoNodo;
    }
    else {
        inserisciOrdinatoRicorsivo(&((*testa)-> prossimo), nuovoValore);
    }
}

typedef int (*Confronto)(int, int);

void inserisciOrdinatoRicorsivoParametrico(Nodo **testa, int nuovoValore, Confronto confronta) {
    if (*testa == NULL || confronta(nuovoValore, (*testa)->valore) <= 0) {
        Nodo *nuovoNodo = malloc(sizeof(Nodo));
        nuovoNodo->valore = nuovoValore;
        nuovoNodo->prossimo = *testa;
        *testa = nuovoNodo;
    } else {
        inserisciOrdinatoRicorsivoParametrico(&((*testa)->prossimo), nuovoValore, confronta);
    }
}

int confrontoCrescente(int a, int b) {
    return a - b;
}

int applyInserimentoRecPara(){
    Nodo *testa = NULL;

    inserisciOrdinatoRicorsivoParametrico(&testa, 5, confrontoCrescente);
    inserisciOrdinatoRicorsivoParametrico(&testa, 3, confrontoCrescente);
    inserisciOrdinatoRicorsivoParametrico(&testa, 4, confrontoCrescente);
    inserisciOrdinatoRicorsivoParametrico(&testa, 1, confrontoCrescente);
    inserisciOrdinatoRicorsivoParametrico(&testa, 2, confrontoCrescente);

    stampaLista(testa); // Dovrebbe stampare la lista ordinata: 1 -> 2 -> 3 -> 4 -> 5 -> NULL

    distruggiLista(&testa);

    return 0;
}

// Lezione 13 Cancellazione da una lista con e senza ricorsione

void cancellaNodo(Nodo **testa, int valoreDaCancellare) {
    Nodo *temp = *testa, *prev = NULL;

    // Caso 1: Il nodo da cancellare è in testa
    if (temp != NULL && temp->valore == valoreDaCancellare) {
        *testa = temp->prossimo; // Cambia testa
        free(temp); // Libera l'antica testa
        return;
    }

    // Caso 2: Il nodo da cancellare non è in testa
    while (temp != NULL && temp->valore != valoreDaCancellare) {
        prev = temp;
        temp = temp->prossimo;
    }

    // Se il valore non è stato trovato
    if (temp == NULL) return;

    // Bypassa il nodo da cancellare

    if(prev != NULL) {
        prev -> prossimo = temp -> prossimo;
    }

    free(temp); // Libera la memoria
}

void cancellaRicorsivamente(Nodo **nodo, int valoreDaCancellare) {
    // Caso base: lista vuota
    if (*nodo == NULL) return;

    // Se il nodo corrente deve essere cancellato
    if ((*nodo)->valore == valoreDaCancellare) {
        Nodo *temp = *nodo; // Nodo da cancellare
        *nodo = (*nodo)->prossimo; // Collega il precedente con il prossimo
        free(temp); // Libera la memoria del nodo cancellato
        cancellaRicorsivamente(nodo, valoreDaCancellare); // Continua a cercare e cancellare
    } else {
        // Passo ricorsivo: passa al prossimo nodo
        cancellaRicorsivamente(&((*nodo)->prossimo), valoreDaCancellare);
    }
}

int applyCancellazioneLista(){
    Nodo *testa = NULL;
    // Supponiamo che la lista sia già popolata...
    int valoreDaCancellare;

    cancellaNodo(&testa, valoreDaCancellare); // Senza Ricorsione
    // Oppure
    cancellaRicorsivamente(&testa, valoreDaCancellare); // Con Ricorsione

    return 0;
}

// Lezione 14 Lettura da file con getline(), parsing strtok(), variabili statiche

void processaLinea(char *linea){
    static int numeroLinea = 0; // Variabile statica
    char *token;

    numeroLinea++;
    printf("Linea %d: %s", numeroLinea, linea);

    token = strtok(linea, DELIMITATORI);
    while(token != NULL){
        printf("\tToken: %s\n", token);
        token = strtok(NULL, DELIMITATORI);
    }
}

int applyProcessaLinea(){
    FILE *file;
    char *linea = NULL;
    size_t lunghezza = 0;
    ssize_t lettura;

    file = fopen("esempio.txt", "r");
    if (file == NULL){
        perror("Errore leggere file");
        exit(EXIT_FAILURE);
    }

    while((lettura = getline(&linea, &lunghezza, file)) != -1) {
        processaLinea(linea);
    }

    free(linea);
    fclose(file);

    return 0;
}

/**
 * getline()
 * input: 1. un puntatore a un puntatore a char
 *        2. un puntatore a una variabile di tipo size_t che getline
 *        userà per sapere le dim del buffer allocato.
 *        3. il file stream da cui leggere
 * return: numero di caratteri letti + newline , -1 se errore
 *
 * strtok()
 * input: 1. una stringa da tokenizzare
 *        2. i caratteri delimitartori
 * return: puntatore al prossimo token oppure NULL
 *
 *
**/

// Lezione 15 Intro ai makefile: target, prerequisiti, comandi

/**
 *
 * # Makefile esempio per compilare 'programma'

programma: main.o utils.o
    gcc -o programma main.o utils.o

main.o: main.c utils.h
    gcc -c main.c

utils.o: utils.c utils.h
    gcc -c utils.c

clean:
    rm -f programma *.o

Il target principale è programma, che dipende da main.o e utils.o. Se uno di questi oggetti file è più recente del file eseguibile programma, make esegue il comando gcc -o programma main.o utils.o per ricompilare l'eseguibile.
I target main.o e utils.o sono oggetti file che dipendono rispettivamente dai file sorgente e dagli header. Se main.c o utils.h sono stati modificati, main.o verrà ricompilato con gcc -c main.c, e analogamente per utils.o.
Il target clean non dipende da alcun file e serve per rimuovere l'eseguibile programma e tutti i file oggetto. Viene eseguito manualmente con il comando make clean.
Questa struttura permette di automatizzare e ottimizzare il processo di build, assicurando che solo i componenti modificati siano ricompilati.

**/

// Lezione 16 makefile, variabili, automatiche, regole implicite

/**
 * Vedi immagine "makefile"
**/

// Lezione 17 Funzioni static. Creazione e manipolazione di matrici bidimensionali

int matrice[ROWS][COLS];

int **creaMatrice(int rows, int cols){
    int **matrice = malloc(rows*sizeof(int));
    for(int i = 0; i < rows; i++){
        matrice[i] = malloc(cols*sizeof(int));
    }
    return matrice;
}

void inizializzaMatrice(int **matrice, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrice[i][j] = i + j; // Esempio di inizializzazione
        }
    }
}

void stampaMatrice(int **matrice, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}

int applyMatrice(){
    int rows = 3, cols = 4;
    int **matrice = creaMatrice(rows, cols);

    inizializzaMatrice(matrice, rows, cols);
    stampaMatrice(matrice, rows, cols);

    // Libera la memoria
    for (int i = 0; i < rows; i++) {
        free(matrice[i]);
    }
    free(matrice);

    return 0;
}

// Lezione 18 fwrite, operatori bitwise, gdbgui

/**
 * size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
 * fwrite è una funzione della libreria standard C che scrive dati da un array
 * in memoria su un flusso di output (file). È particolarmente utile
 * per scrivere blocchi di dati binari.
 *
 * ptr: Puntatore ai dati da scrivere.
   size: Dimensione, in byte, di ciascun elemento da scrivere.
   nmemb: Numero di elementi, ciascuno di dimensione size, da scrivere.
   stream: Puntatore al file FILE su cui scrivere.
 *
 * Valore di ritorno: Restituisce il numero
 * di elementi scritti con successo, che può essere minore
 * di nmemb se si verifica un errore.
 */

int applyFwrite(){
    int numeri[] = {1,2,3,45};
    FILE *file = fopen("file.bin", "wb");
    if (file != NULL){
        fwrite(numeri, sizeof(int), 4, file);
        fclose(file);
    }
    return 0;
}

/**
 * Operatori bitwise
 * & (AND): a & b restituisce 1 per ciascun bit in cui entrambi i bit corrispondenti di a e b sono 1.
   | (OR): a | b restituisce 1 per ciascun bit in cui almeno uno dei bit corrispondenti di a o b è 1.
   ^ (XOR): a ^ b restituisce 1 per ciascun bit in cui i bit corrispondenti di a e b sono diversi.
   ~ (NOT): ~a inverte tutti i bit di a.
   << (shift a sinistra): a << n sposta tutti i bit di a di n posizioni a sinistra.
   >> (shift a destra): a >> n sposta tutti i bit di a di n posizioni a destra.
 */

/**
 *
 * gdbgui è un'interfaccia grafica basata su browser per gdb,
 * il GNU Debugger. Consente di eseguire il debug dei programmi
 * con una più accessibile interfaccia utente, fornendo funzionalità
 * come la visualizzazione dell'assembly, l'impilamento delle chiamate,
 * la gestione dei breakpoint e l'ispezione delle variabili.
 *
 */

// Lezione 19 Quicksort in c

/**
 *
 * QUICKSORT
 *
 */

void scambia(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

// Funzione che prende come ultimo elemento come pivot,
// posiziona il pivot nella sua posizione corretta in array ordinato,
// e posiziona tutti gli elementi più piccoli (minori del pivot)
// a sinistra del pivot e tutti gli elementi maggiori a destra

int partition(int arr[], int basso, int alto){
    int pivot = arr[alto];
    int i = (basso - 1);

    for (int j = basso; j <= alto - 1; j++){
        if (arr[j] < pivot) {
            i++;
            scambia(&arr[i], &arr[j]);
        }
    }

    scambia(&arr[i+1], &arr[alto]);
    return (i+1);
}

// Funzione principale per eseguire il QuickSort
// arr[] --> Array da ordinare,
// basso -> Indice di inizio,
// alto -> Indice di fine

void quicksort(int arr[], int basso, int alto){
    if (basso < alto){
        int pi= partition(arr, basso, alto);

        // Ordinamento separato degli elementi prima
        // e dopo la partizione
        quicksort(arr, basso, pi -1);
        quicksort(arr, pi+1, alto);
    }
}

void stampaArrayQuickSort(int arr[], int size){
    int i;
    for (i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int applyQuickSort(){
    int arr[] =  {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof (arr[0]);
    quicksort(arr, 0, n-1);
    printf("Array Ordinato \n");
    stampaArrayQuickSort(arr, n);
    return 0;
}

// Lezione 20 significato static, extern. Makefile: compilazione condizionale e pattern rules

/**
 * In C, le parole chiave static ed extern sono utilizzate per gestire la visibilità e la durata delle variabili e delle funzioni, influenzando come e dove possono essere accessi e modificati.

static
Variabili e funzioni a livello di file: quando static è applicato a una variabile o funzione a livello di file (fuori da qualsiasi funzione), rende quella variabile o funzione visibile solo all'interno di quel file sorgente. Questo aiuta a prevenire conflitti di nomi e a nascondere l'implementazione interna.

Variabili locali: se static viene utilizzato con una variabile locale all'interno di una funzione, tale variabile mantiene il suo valore tra le chiamate alla funzione. La variabile viene inizializzata solo una volta, e la sua durata si estende per tutta l'esecuzione del programma, pur rimanendo visibile solo all'interno della funzione.

extern
extern viene usato per dichiarare che una variabile o funzione è definita in un altro file sorgente, consentendo l'accesso ad essa da file sorgenti diversi. Questo è particolarmente utile per condividere variabili globali o funzioni tra diversi file all'interno di un progetto.

Dichiarazione vs. Definizione: extern dichiara l'esistenza di una variabile o funzione senza allocare spazio per essa. La definizione effettiva, che alloca lo spazio, deve essere fatta in un altro punto, tipicamente in un altro file sorgente.
Makefile
Compilazione Condizionale
La compilazione condizionale in Makefile può essere gestita tramite variabili e istruzioni condizionali. Questo permette di includere o escludere parti del codice sorgente dalla compilazione basandosi su certe condizioni.

makefile
Copy code
CFLAGS=-Wall -g

ifdef DEBUG
CFLAGS += -DDEBUG
endif

programma: main.c
    gcc $(CFLAGS) -o programma main.c
Nell'esempio, se si esegue make con DEBUG definito, -DDEBUG viene aggiunto alle opzioni del compilatore.

Pattern Rules
Le "pattern rules" in un Makefile consentono di definire regole generali per generare file target da file sorgenti, basandosi sui pattern dei loro nomi. Sono utili per specificare come costruire un tipo di file da un altro in modo generico.

makefile
Copy code
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

%.out: %.o
    $(CC) $(LDFLAGS) $< -o $@
Nell'esempio:

La prima regola compila i file .c in file oggetto .o.
La seconda regola collega i file oggetto .o per produrre eseguibili .out.
$< indica il primo prerequisito (ad esempio, il file sorgente) e $@ indica il target della regola.
Le pattern rules aumentano significativamente la potenza e flessibilità dei Makefile, riducendo la necessità di scrivere regole specifiche per ogni singolo file da compilare o collegare.
 *
 *
 *
 */


// Lezione 29 System calls vs library functions
/**
 * Le system call e le funzioni di libreria sono entrambe cruciali nell'ambito della programmazione in sistemi operativi come Unix e Linux, ma svolgono ruoli diversi e operano a livelli differenti.

System Calls
Definizione: Le system call sono interfacce di basso livello tra il sistema operativo e i programmi utente. Forniscono un modo per i programmi di richiedere servizi al kernel del sistema operativo, come la creazione e la gestione di processi, la lettura e scrittura di file, la gestione della memoria e la comunicazione di rete.
Esempi: open(), read(), write(), fork(), exec(), close().
Caratteristiche:
Operano a livello di kernel.
Sono implementate dal sistema operativo.
Costituiscono l'interfaccia fondamentale per l'accesso alle risorse gestite dal sistema operativo.
Possono avere un overhead significativo a causa del cambio di contesto tra modalità utente e modalità kernel.
Funzioni di Libreria
Definizione: Le funzioni di libreria sono collezioni di codice pre-scritto che possono essere utilizzate dai programmi per svolgere compiti comuni, come operazioni matematiche, manipolazione di stringhe, input/output standard e molto altro.
Esempi: printf(), scanf(), strcpy(), malloc(), sqrt().
Caratteristiche:
Operano a livello di spazio utente.
Sono fornite da librerie standard (come la Standard C Library) o da librerie di terze parti.
Sono costruite sopra le system call per fornire funzionalità più ricche e facili da usare, ma possono anche implementare funzionalità puramente all'interno dello spazio utente senza fare uso di system call.
Generalmente, hanno un overhead minore rispetto alle system call e possono essere ottimizzate per efficienza.
Confronto e Interazione
Prestazioni: Le system call comportano un cambio di contesto tra la modalità utente e la modalità kernel, il che può essere costoso in termini di prestazioni. Le funzioni di libreria, invece, eseguono nel contesto del processo chiamante e possono evitare questo overhead se non necessitano di servizi del kernel.
Uso: Le funzioni di libreria sono generalmente preferite per compiti di routine o per astrazioni di alto livello, dato che sono più semplici da usare e comprendere rispetto alle dirette system call. Tuttavia, per interagire direttamente con il sistema operativo o per utilizzare funzionalità che richiedono privilegi particolari, si devono utilizzare le system call.
Portabilità: Le funzioni di libreria tendono a essere più portabili tra diversi sistemi operativi rispetto alle system call, poiché le librerie possono offrire la stessa interfaccia su diversi sistemi. Le system call, d'altra parte, possono variare significativamente tra diversi sistemi operativi.
In conclusione, mentre le system call forniscono un'interfaccia essenziale al kernel e alle risorse del sistema operativo, le funzioni di libreria offrono un mezzo più accessibile e astratto per svolgere operazioni comuni, spesso costruendo su quelle interfacce di basso livello fornite dalle system call.

 */

// Lezione 29.1 fork(), pag 2 wait pag 2

/**
 *
 * @return pid_t fork(void);
 *
 * Valore di ritorno:
Ritorna -1 in caso di errore.
Ritorna 0 nel processo figlio.
Ritorna il PID (Process ID) del processo figlio al processo padre.
 *
 */

int applyFork(){
    pid_t pid = fork();

    if(pid == -1){
        perror("fork error");
    } else if(pid == 0){
        printf("Sono il processo figlio\n");
    } else {
        printf("Sono il processo padre, PID del figlio: %d\n", pid);
    }
    return 0;
}

/**
 * wait()
 * Valore di ritorno:

Ritorna il PID del processo figlio terminato.
Ritorna -1 in caso di errore.

* pid_t wait(int *status);

 */

int applyWait(){
    pid_t pid = fork();
    if (pid == -1) {
        // Errore nella fork
        perror("fork failed");
    } else if (pid == 0) {
        // Codice eseguito dal processo figlio
        printf("Sono il processo figlio\n");
    } else {
        // Codice eseguito dal processo padre
        int status;
        wait(&status); // Attende la terminazione del figlio
        printf("Sono il processo padre, il figlio è terminato\n");
    }

    return 0;
}

// Lezione 30 Significato e uso di umask
/**
 * Il comando umask (user file-creation mode mask) è uno strumento disponibile nei sistemi Unix e Linux che imposta i permessi di default per i nuovi file e directory creati dall'utente. In pratica, umask determina quali permessi saranno automaticamente "rimossi" da nuovi file e directory al momento della loro creazione.
 * I permessi in Unix/Linux sono assegnati usando tre cifre octal (es. 755, 644), che rappresentano rispettivamente i permessi del proprietario, del gruppo e di altri utenti. Ogni cifra può essere la somma di:

4 per la lettura (r),
2 per la scrittura (w),
1 per l'esecuzione (x).
 *
 */

//Lezione 30.1 Comandi waitpid e sleep, processi zombie.

/**
 * Un processo zombie in Unix e Linux è un processo che ha completato l'esecuzione (è "morto") ma rimane nella tabella dei processi perché il processo genitore non ha ancora rilevato la sua terminazione (non ha "letto" lo stato di terminazione del figlio con wait() o waitpid()). Questo può accadere se il genitore termina prima del figlio o se il genitore non esegue wait() per qualche motivo.
 * Processi Zombie
Un processo zombie in Unix e Linux è un processo che ha completato l'esecuzione (è "morto") ma rimane nella tabella dei processi perché il processo genitore non ha ancora rilevato la sua terminazione (non ha "letto" lo stato di terminazione del figlio con wait() o waitpid()). Questo può accadere se il genitore termina prima del figlio o se il genitore non esegue wait() per qualche motivo.

I processi zombie occupano uno spazio nella tabella dei processi, anche se non usano altre risorse del sistema. Se il numero di processi zombie diventa eccessivamente alto, potrebbero esaurirsi gli spazi nella tabella dei processi, impedendo la creazione di nuovi processi.

Per prevenire la formazione di processi zombie, il processo genitore deve usare wait() o waitpid() per leggere lo stato di terminazione dei processi figli. Un'altra soluzione è far adottare i processi orfani da init (o da systemd sui sistemi moderni), che periodicamente esegue wait() per prevenire la formazione di zombie.
 */

// Lezione 31 Contaprimi con uso di fork e pipe. Pagine 2 e 7 pipe

int isPrime(int n){
    if (n <= 1) return 0;
    for(int i = 2; i * i <= n; i++){
        if (n % i == 0) return 0;
    }
    return 1; // Il numero è primo
}

void ContaPrimi(int inizio, int fine){
    int pipefd[2];
    if (pipe(pipefd) == -1){
        perror("errore nella pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Errore nella fork");
        exit(EXIT_FAILURE);
    } else if(pid == 0){
        close(pipefd[0]);
        int conta = 0;
        for (int i = inizio; i <= fine; i++){
            if (isPrime(i)){
                conta++;
            }
        }
        write(pipefd[1], &conta, sizeof(conta));
        close(pipefd[1]); // Chiude il lato di scrittura della pipe
        exit(EXIT_SUCCESS);
    } else {
        close(pipefd[1]);
        int risultato;
        wait(NULL);
        read(pipefd[0], &risultato, sizeof(risultato));
        close(pipefd[0]);

        printf("Numeri primi trovati: %d\n", risultato);
    }
}

int applyContaPrimi(){
    int inizio = 1, fine = 100;
    ContaPrimi(inizio, fine);
    return 0;
}

/**
 * read()
Input:

int fd: Il file descriptor da cui leggere (per esempio, pipefd[0] se stai leggendo da una pipe).
void *buf: Un puntatore al buffer dove i dati letti saranno salvati.
size_t count: La dimensione massima del buffer, ovvero quanti byte leggere.
Valore di ritorno:

Numero positivo: Il numero di byte effettivamente letti.
0: Fine del file (EOF) o non ci sono dati disponibili nella pipe non bloccante.
-1: Errore durante la lettura. In questo caso, errno è impostato per indicare l'errore specifico.
 *
 *
 * pipe()
Input:

int pipefd[2]: Un array di due interi. pipe() inizializza questo array in modo che pipefd[0] sia il file descriptor per la lettura dalla pipe, mentre pipefd[1] sia il file descriptor per la scrittura nella pipe.
Valore di ritorno:

0: Successo. pipefd è inizializzato correttamente.
-1: Errore. In questo caso, errno è impostato per indicare l'errore specifico.
 *
 * write()
Input:

int fd: Il file descriptor su cui scrivere (per esempio, pipefd[1] se stai scrivendo su una pipe).
const void *buf: Un puntatore ai dati da scrivere.
size_t count: Il numero di byte da scrivere.
Valore di ritorno:

Numero positivo: Il numero di byte effettivamente scritti.
-1: Errore durante la scrittura. In questo caso, errno è impostato per indicare l'errore specifico.


 */

// Lezione 32 Comunicazione di processi tramite named pipe. mkfifo(1) e mkfifo(3),
// Fork() che lancia eseguibile con execl

int mkfifo(const char *pathname, mode_t mode);

/**
 * mkfifo
 * Parametri:

pathname: il percorso della named pipe da creare.
mode: i permessi della named pipe (simili ai permessi dei file, es. 0666).
Valore di ritorno:

0: successo.
-1: errore, e errno è impostato per indicare l'errore.
 */

int applyMkfifo(){
    const char *nome_pipe = "myfifo";

    if(mkfifo(nome_pipe, 0666) == -1){
        perror("Errore creazione fifo");
        exit(EXIT_FAILURE);
    }
    return 0;
}

void writer(const char *message){
    int fd;
    fd = open("myfifo", O_WRONLY);
    if (fd == -1){
        perror("error in open");
        exit(EXIT_FAILURE);
    }
    write(fd, message, strlen(message));
    close(fd);
}

void reader(){
    int fd;
    char buffer[128];
    ssize_t num;

    fd = open("myfifo", O_RDONLY);
    if (fd == -1){
        perror("Errore ad aprire fd");
        exit(EXIT_FAILURE);
    }

    num = read(fd, buffer, sizeof(buffer) - 1);
    if (num == -1) {
        perror("Errore a leggere");
        exit(EXIT_FAILURE);
    }
    buffer[num] = '\0';
    printf("Ricevuto: %s", buffer);
    close(fd);
}

int applyWriterReader(){
    mkfifo("myfifo", 0666);

    pid_t pid = fork();

    if (pid == 0) {
        // Processo figlio, scrive sulla pipe
        writer("Hello! speaking from named pipe!\n");
    }
    // Processo genitore: legge dalla pipe
    else {
        reader();
    }

    return 0;

}

// Lezione 33 Intro alla memoria condivisa, shm_overview(7)
// shm_open, ftruncate, mmap, munmap, shm_unlink
// Esempi d'uso di memoria condivisa

/**
 * shm_open
Input:

const char *name: Nome dell'oggetto di memoria condivisa.
int oflag: Flag per determinare il comportamento (es. O_CREAT, O_RDWR).
mode_t mode: I permessi per l'oggetto di memoria condivisa se viene creato.
Valore di ritorno:

File descriptor positivo: in caso di successo.
-1: in caso di errore.
Descrizione: Apre o crea un oggetto di memoria condivisa.

ftruncate
Input:

int fd: File descriptor dell'oggetto di memoria condivisa.
off_t length: Nuova dimensione dell'oggetto.
Valore di ritorno:

0: in caso di successo.
-1: in caso di errore.
Descrizione: Modifica la dimensione dell'oggetto di memoria condivisa.

mmap
Input:

void *addr: Indirizzo suggerito per la mappatura (tipicamente NULL).
size_t length: Numero di byte da mappare.
int prot: Protezione desiderata per la mappatura (es. PROT_READ | PROT_WRITE).
int flags: Flag per il tipo di mappatura (es. MAP_SHARED).
int fd: File descriptor dell'oggetto di memoria condivisa.
off_t offset: Offset dall'inizio dell'oggetto di memoria condivisa.
Valore di ritorno:

Puntatore alla zona di memoria mappata: in caso di successo.
MAP_FAILED ((void *) -1): in caso di errore.
Descrizione: Mappa un file o un oggetto di memoria condivisa nello spazio di indirizzi del processo.

munmap
Input:

void *addr: Indirizzo della mappatura.
size_t length: Dimensione della mappatura.
Valore di ritorno:

0: in caso di successo.
-1: in caso di errore.
Descrizione: Rimuove una mappatura da un'area di memoria.

shm_unlink
Input:

const char *name: Nome dell'oggetto di memoria condivisa da rimuovere.
Valore di ritorno:

0: in caso di successo.
-1: in caso di errore.
Descrizione: Rimuove un oggetto di memoria condivisa dal file system, rendendolo inaccessibile.


 */

const int SIZE = 4096;
const char *name = "/my_shared_memory";

void writerProcess(const char *message){
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1){
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    ftruncate(shm_fd, SIZE);

    void *ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED){
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    sprintf(ptr, "%s", message);

    munmap(ptr, SIZE);
    close(shm_fd);
}

void readerProcess(){
    int shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1){
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    void *ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    munmap(ptr, SIZE);
    close(shm_fd);

    shm_unlink(name);
}

void applyProcessoLettoreScrittore(){
    pid_t pid = fork();

    if(pid == 0){
        writer("Writing on shared memory");
    } else if (pid > 0){
        wait(NULL);
        reader();
    } else{
        perror("error in fork");
        exit(EXIT_FAILURE);
    }
}


// Lezione 34 Intro ai semafori
// uso e significato di sem_open, sem_post, sem_wait, sem_unlink
// Semafori per regolare accesso a una variabile condivisa
// Semafori per segnalare la terminazione di un compito al processo principale

/**
 * Uso e Significato delle Funzioni
sem_open
Crea o apre un semaforo nominato.

Input:

const char *name: Nome del semaforo.
int oflag: Flag di apertura (O_CREAT per crearlo se non esiste).
mode_t mode: Permessi del semaforo (se viene creato).
unsigned int value: Valore iniziale del semaforo (se viene creato).
Valore di ritorno:

Successo: Un puntatore al semaforo.
Errore: SEM_FAILED.
sem_wait
Decrementa (lock) il semaforo. Se il valore del semaforo è zero, il processo chiama sem_wait e si blocca fino a che il semaforo non viene incrementato.

Input:

sem_t *sem: Puntatore al semaforo.
Valore di ritorno:

0: Successo.
-1: Errore.
sem_post
Incrementa (unlock) il semaforo. Se altri processi o thread sono bloccati in attesa del semaforo, li sblocca.

Input:

sem_t *sem: Puntatore al semaforo.
Valore di ritorno:

0: Successo.
-1: Errore.
sem_unlink
Rimuove un semaforo nominato dal sistema.

Input:

const char *name: Nome del semaforo.
Valore di ritorno:

0: Successo.
-1: Errore.
 */

void childTask(sem_t *sem){
    printf("Figlio inizia il compito...\n");
    sleep(2);
    printf("Figlio ha completato compito!\n");
    sem_post(sem);
}
void parentTask(sem_t *sem) {
    printf("Genitore in attesa che il figlio completi il compito...\n");
    sem_wait(sem); // Attende il segnale dal figlio
    printf("Genitore rileva che il figlio ha completato il compito.\n");
}

int applySem(){
    const char *semName = "/mysem";
    sem_t *sem = sem_open(semName, O_CREAT, 0644, 0); // Inizializzato a 0 per aspettare il segnale

    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == 0) { // Processo figlio
        childTask(sem);
    } else if (pid > 0) { // Processo genitore
        parentTask(sem);
        wait(NULL); // Attende che il figlio finisca (buona pratica)
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    sem_close(sem);
    if (pid > 0) { // Solo il genitore elimina il semaforo
        sem_unlink(semName);
    }
    return 0;
}

// Lezione 35 SommaPrimi con semafori con nome e memoria
// condivisa tra processi generati da fork + exec

/**
 * // calcola_primo.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <numero>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num = atoi(argv[1]);
    const char *semName = "/mysem";
    const char *shmName = "/myshm";
    int shm_fd = shm_open(shmName, O_RDWR, 0666);
    sem_t *sem = sem_open(semName, 0);

    int *sum = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (isPrime(num)) {
        sem_wait(sem);
        *sum += num;
        sem_post(sem);
    }

    munmap(sum, sizeof(int));
    sem_close(sem);
    close(shm_fd);

    return EXIT_SUCCESS;
}

 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

int main() {
    const char *shm_name = "/my_shm";
    const char *sem_name = "/my_sem";
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(int));
    int *sum = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t *sem = sem_open(sem_name, O_CREAT, 0666, 1);

    pid_t pid = fork();
    if (pid == 0) { // Processo figlio
        char *args[] = {"./prime_calculator", "1", "100", shm_name, sem_name, NULL};
        execvp(args[0], args);
        exit(0);
    } else if (pid > 0) { // Processo principale
        wait(NULL); // Attende la terminazione del figlio
        printf("Somma dei numeri primi: %d\n", *sum);
    }

    // Pulizia
    munmap(sum, sizeof(int));
    shm_unlink(shm_name);
    sem_close(sem);
    sem_unlink(sem_name);
    return 0;
}
 */

// Lezione 36 Intro ai threads
// pthread_create, passaggio di parametri ai thread mediante puntatori a struct
// Sincronizzazione mediante semafori unnamed: sem_init, sem_wait, sem_post
// Terminazione di thread: pthread_join

/**
 * pthread_create
Input:

pthread_t *thread: Puntatore a un identificatore di thread.
const pthread_attr_t *attr: Attributi del thread (NULL per default).
void *(*start_routine) (void *): Funzione eseguita dal thread.
void *arg: Argomento passato alla funzione del thread.
Return:

0: Successo.
Valore diverso da 0: Codice di errore.
Descrizione: Crea un nuovo thread e lo rende eseguibile.

 pthread_join
Input:

pthread_t thread: Identificatore del thread.
void **retval: Puntatore al valore di ritorno del thread.
Return:

0: Successo.
Valore diverso da 0: Codice di errore.
Descrizione: Aspetta che un thread termini.
 */

typedef struct {
    int id;
    char name[100];
} ThreadArg;

void *threadFunction(void *arg){
    ThreadArg  *threadArg = (ThreadArg *)arg;
    printf("Thread %d: %s\n", threadArg->id, threadArg->name);
    return NULL;
}

int applyThreadsTheory(){
    pthread_t t;
    ThreadArg threadArg = {1, "Thread 1"};

    sem_t  sem;
    sem_init(&sem, 0, 1);

    pthread_create(&t, NULL, threadFunction, &threadArg);

    sem_wait(&sem);
    sem_post(&sem);

    pthread_join(t, NULL);
    sem_destroy(&sem);

    return 0;
}


// Lezione 37 Definizione e uso mutex, prod-cons tecnica
// Nota: potete osservare che il prototipo della funzione pthread_mutex_init
// contiene il modificatore restrict. Si tratta di un modificatore riferibile
// ai puntatori che se usato permette al codice di generare codice più efficiente

/**
 * pthread_mutex_init
Input:

pthread_mutex_t *mutex: Puntatore al mutex che deve essere inizializzato. Questo è un puntatore alla variabile mutex che hai dichiarato.
const pthread_mutexattr_t *attr: Puntatore agli attributi del mutex. Questo può essere NULL se vuoi usare gli attributi di default. Gli attributi possono includere, per esempio, se il mutex è ricorsivo, che permette allo stesso thread di bloccarlo più volte.
Valore di ritorno:

0: Successo.
Errore: Un codice di errore sarà restituito se la funzione fallisce.
pthread_mutex_lock
Input:

pthread_mutex_t *mutex: Puntatore al mutex da acquisire/bloccare. Il thread chiamante tenterà di acquisire un lock su questo mutex.
Valore di ritorno:

0: Successo. Il mutex è stato acquisito dal thread chiamante.
Errore: Un codice di errore sarà restituito se la funzione fallisce. Per esempio, potrebbe fallire se si tenta di bloccare un mutex in uno stato inconsistente o se il mutex è già stato distrutto.
pthread_mutex_unlock
Input:

pthread_mutex_t *mutex: Puntatore al mutex da rilasciare/sbloccare. Il mutex dovrebbe essere precedentemente bloccato dallo stesso thread che ora sta tentando di sbloccarlo.
Valore di ritorno:

0: Successo. Il mutex è stato rilasciato e può essere acquisito da un altro thread.
Errore: Un codice di errore sarà restituito se la funzione fallisce. Questo può accadere se si tenta di sbloccare un mutex che non è stato precedentemente bloccato dal thread chiamante.
pthread_mutex_destroy
Input:

pthread_mutex_t *mutex: Puntatore al mutex da distruggere. Dopo la chiamata a questa funzione, il mutex non dovrebbe più essere utilizzato fino a quando non viene nuovamente inizializzato.
Valore di ritorno:

0: Successo. Il mutex è stato distrutto e le sue risorse liberate.
Errore: Un codice di errore sarà restituito se la funzione fallisce. La distruzione può fallire se ci sono ancora thread bloccati sul mutex o se il mutex è già stato distrutto.
Queste operazioni sui mutex sono fondamentali per gestire l'accesso esclusivo a sezioni critiche del codice in programmi multithreading, prevenendo condizioni di gara e garantendo la consistenza dei dati.
 */

void *incrementCounter(void *arg){
    pthread_mutex_lock(&mutex);
    deCounter++;
    printf("Valore attuale del counter: %d\n", deCounter);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int applyMutex(){
    pthread_t threads[NUM_THREADS];

    // Creazione dei threads
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, incrementCounter, NULL);
    }

    // Attesa terminazione dei threads
    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Valore finale del counter: %d\n", deCounter);
    return 0;
}

// Lezione 40 Condition variables, gestione mem condivisa, heap.c,
// emulazione semafori, zem.c,
// la gestione di reader e writer rw.c

/**
 * Le variabili di condizione sono strumenti di sincronizzazione usati nei sistemi multithreading per permettere ai thread di sospendere l'esecuzione e attendere che certe condizioni diventino vere. Sono tipicamente usate insieme ai mutex per coordinare l'accesso a risorse condivise.

Definizione e Uso
Una variabile di condizione permette a uno o più thread di attendere ("wait") finché una certa condizione non diventa vera. Mentre un thread è in attesa sulla variabile di condizione, il mutex associato viene rilasciato. Quando un altro thread modifica lo stato e la condizione diventa vera, può segnalare ("signal") o trasmettere ("broadcast") sulla variabile di condizione per risvegliare i thread in attesa.

Funzioni Principali
pthread_cond_init
Input:

pthread_cond_t *cond: Puntatore alla variabile di condizione da inizializzare.
const pthread_condattr_t *attr: Puntatore agli attributi della variabile di condizione, o NULL per default.
Return:

0: Successo.
Errore: Codice di errore non-zero.
pthread_cond_wait
Input:

pthread_cond_t *cond: Puntatore alla variabile di condizione su cui attendere.
pthread_mutex_t *mutex: Mutex associato che viene rilasciato mentre il thread attende e ri-acquisito automaticamente dopo il risveglio.
Return:

0: Successo.
Errore: Codice di errore non-zero.
pthread_cond_signal
Input:

pthread_cond_t *cond: Puntatore alla variabile di condizione da segnalare.
Return:

0: Successo.
Errore: Codice di errore non-zero.
pthread_cond_broadcast
Input:

pthread_cond_t *cond: Puntatore alla variabile di condizione da trasmettere.
Return:

0: Successo.
Errore: Codice di errore non-zero.
pthread_cond_destroy
Input:

pthread_cond_t *cond: Puntatore alla variabile di condizione da distruggere.
Return:

0: Successo.
Errore: Codice di errore non-zero.
 */

int ready = 0;

void* condThreadFunc(void *arg){
    pthread_mutex_lock(&mutex);
    while(!ready) {
        printf("Thread in attesa ... \n");
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Thread risvegliato!\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int applyCondVariablesThreads(){
    pthread_t t;
    pthread_create(&t, NULL, condThreadFunc, NULL);

    sleep(2); // Aspetta per simulare il lavoro

    pthread_mutex_lock(&mutex);
    ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_join(t, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}

// Lezione 41 Condition variables, schema prod-cons
// introduzione ai segnali, segnali attraverso un handler,
// sigaction per definire un handler
// uso modificatore volatile su variabile globale
// Sleep per il busy waiting

/**
 * Uso di sigaction per Definire un Handler di Segnali
sigaction permette di specificare come un processo deve gestire un segnale. Fornisce più controllo rispetto alla funzione signal() e permette di definire un nuovo handler o di ripristinare l'azione predefinita per il segnale.

Struttura di sigaction:

c
Copy code
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};
sa_handler: Puntatore alla funzione handler per il segnale.
sa_mask: Set di segnali che sono bloccati durante l'esecuzione dell'handler.
sa_flags: Flag per modificare il comportamento di sigaction.
sa_sigaction: Alternativa a sa_handler, usata quando SA_SIGINFO è specificato in sa_flags.
Uso del Modificatore volatile
Quando una variabile globale può essere modificata da un handler di segnale, dovrebbe essere dichiarata con il modificatore volatile per indicare al compilatore che il valore della variabile può cambiare in qualsiasi momento, prevenendo ottimizzazioni che potrebbero ignorare modifiche asincrone alla variabile.
 */

volatile sig_atomic_t signal_flag = 0;

void signal_handler(int sig) {
    signal_flag = 1;
}

int applySignalHandler() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Premi CTRL+C\n");
    while (!signal_flag) {
        sleep(1); // Usato qui per evitare il busy waiting
        printf("In attesa di CTRL+C...\n");
    }

    printf("Segnale SIGINT ricevuto.\n");
    return 0;
}

// Lezione 42 Maschere di segnali di tip sigset_t,
// funzioni sigfillset e sigdelset
//Signal pending example
// uso di pthread_sigmask per bloccare i segnali di un thread.
// Thread dedicato alla gestione dei segnali mediante sigwait
// Differenza tra struct e union

/**
 * Introduciamo il concetto di segnali in programmazione Unix/Linux, l'uso delle maschere di segnali con sigset_t, le funzioni sigfillset e sigdelset, e l'approccio per gestire segnali pendenti, compresa la gestione dedicata dei segnali in thread con pthread_sigmask e sigwait. Concluderemo con una breve spiegazione sulla differenza tra struct e union.

sigset_t, sigfillset e sigdelset
sigset_t è un tipo di dato usato per rappresentare un insieme (o maschera) di segnali. È comunemente usato con varie funzioni per controllare quali segnali un processo o thread può ricevere.

sigfillset:

Input:

sigset_t *set: Puntatore a una variabile di tipo sigset_t che sarà modificata per includere tutti i segnali.
Return:

0: Successo.
-1: Errore.
sigdelset:

Input:

sigset_t *set: Puntatore alla variabile sigset_t da cui rimuovere un segnale.
int signum: Il segnale da rimuovere dalla maschera.
Return:

0: Successo.
-1: Errore.
Gestione dei Segnali Pendenti e pthread_sigmask
I segnali pendenti sono segnali che sono stati inviati a un processo o thread ma che non sono ancora stati consegnati. La funzione pthread_sigmask permette di bloccare o sbloccare segnali in un thread, influenzando così quali segnali diventano pendenti.

pthread_sigmask:

Input:

int how: Come modificare la maschera di segnali corrente (es. SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK).
const sigset_t *set: La nuova maschera di segnali da applicare.
sigset_t *oldset: Se non è NULL, viene salvata la vecchia maschera di segnali.
Return:

0: Successo.
Errore: Codice di errore non-zero.
sigwait
sigwait attende che uno dei segnali specificati nella maschera diventi pendente.

Input:

const sigset_t *set: Puntatore alla maschera di segnali che specifica i segnali che il thread sta attendendo.
int *sig: Puntatore a un intero dove sigwait memorizzerà l'identificatore del segnale ricevuto.
Return:

0: Successo.
Errore: Codice di errore non-zero.
 */

volatile int runLoop = 1;

void* signalHandlerThread(void *arg){
    sigset_t *set = (sigset_t *)arg;
    int sig;
    while(runLoop){
        sigwait(set, &sig);
        //Gestisci il segnale
        printf("Segnale %d ricevuto \n", sig);
        if (sig == SIGTERM) {
            runLoop = 0;
        }
    }
    printf("Thread gestore dei segnali in uscita\n");
    pthread_exit(NULL);
}

int applySignalHandlerThead(){
    pthread_t t;
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    pthread_create(&t, NULL, &signalHandlerThread, &set);

    // Invio di SIGUSR1 al processo, che sarà gestito dal thread dedicato
    pthread_kill(t, SIGUSR1);
    sleep(3);
    pthread_kill(t, SIGTERM);

    pthread_join(t, NULL);
    printf("Programma in uscita\n");
    return 0;
}

// Esempio di Struct vs Union

typedef struct {
    double x;
    double y;
} Puntino;

typedef union {
    int intero;
    float decimale;
    char carattere;
} Dato;

int applyStructVSUnion(){
    Puntino puntino = {6.9, 9.0};
    printf("Il mio puntino si è (%f, %f)\n", puntino.x, puntino.y);

    Dato dato;

    dato.intero = 42;

    printf("Un solo valore alla volta: %d\n", dato.intero);

    dato.decimale = 6.9;

    printf("Un solo valore alla volta: %f\n", dato.decimale);

    dato.carattere = 'l';
    printf("Un solo valore alla volta: %c\n", dato.carattere);

    return 0;
}


// Lezione 43 Funzioni MT-safe e async-signal-safe. Invio di segnali fra thread.

/**
 * Le funzioni MT-safe (Thread-Safe) e async-signal-safe sono due categorie importanti nella programmazione multithread e nella gestione dei segnali in sistemi Unix-like, come Linux. Capire la distinzione tra queste due può aiutare a scrivere codice più sicuro e affidabile in contesti multithreading e nella gestione dei segnali.

Funzioni MT-Safe (Thread-Safe)
Le funzioni MT-safe sono quelle che sono sicure da chiamare in contesti multithreading. Ciò significa che possono essere utilizzate senza causare problemi di concorrenza, come condizioni di gara o deadlock, quando vengono chiamate da più thread contemporaneamente. Ci sono due tipi principali di thread-safety:

Reentrancy: Una funzione è reentrant se può essere interrotta nel mezzo della sua esecuzione e chiamata di nuovo ("re-entered") in modo sicuro. Ciò richiede che la funzione non si affidi a dati statici o globali che potrebbero cambiare stato tra le chiamate.
Thread-local storage: Alcune funzioni gestiscono la thread-safety mantenendo i dati su cui operano confinati al thread che le ha chiamate, utilizzando lo storage locale al thread invece di variabili globali o statiche.
Esempio: strtok non è thread-safe perché utilizza un buffer interno statico tra le chiamate. Al contrario, strtok_r è una versione thread-safe che richiede al chiamante di fornire il proprio buffer.

Funzioni Async-Signal-Safe
Le funzioni async-signal-safe sono quelle che possono essere chiamate in modo sicuro all'interno di un gestore di segnali. Quando un segnale viene consegnato a un processo, può interrompere l'esecuzione corrente del processo e invocare un gestore di segnali. Solo un sottoinsieme limitato di funzioni è sicuro da invocare all'interno di questo gestore, poiché la chiamata ad altre funzioni può causare comportamenti indeterminati.

Esempio: Le funzioni di I/O standard come printf e malloc non sono async-signal-safe. Tuttavia, funzioni di basso livello come write (per scrivere in file descriptor) sono considerate sicure in questo contesto e possono essere utilizzate all'interno di gestori di segnali.

Invio di Segnali fra Thread
In Linux e sistemi Unix-like, i segnali possono essere inviati a processi specifici o a tutti i thread all'interno di un processo. Tuttavia, la gestione precisa dei segnali in contesti multithread può diventare complessa:

pthread_kill: Può essere usato per inviare un segnale a un thread specifico all'interno dello stesso processo. Questo permette di indirizzare la comunicazione dei segnali a thread specifici piuttosto che all'intero processo.
Mascherare i segnali: I thread possono usare pthread_sigmask per bloccare o sbloccare specifici segnali. Questo è utile per designare un thread specifico per gestire determinati segnali, mascherando quei segnali in tutti gli altri thread.
La programmazione con segnali e thread richiede attenzione per evitare condizioni di gara, deadlock e altri problemi di sincronizzazione. Utilizzare funzioni che sono thread-safe o async-signal-safe, a seconda del contesto, è essenziale per mantenere la correttezza del programma.

User

 */

// Funzioni thread_safe

void *threadSafeFun(void *arg){
    char str[] = "Hello,World,Example,String";
    char *saveptr;
    char *token = strtok_r(str, ",", &saveptr);
    while(token != NULL){
        printf("%s\n", token);
        token = strtok_r(NULL, ",", &saveptr);
    }
    return NULL;
}

int applyThreadSafeFunc(){
    pthread_t t1, t2;
    pthread_create(&t1, NULL, threadSafeFun, NULL);
    pthread_create(&t2, NULL, threadSafeFun, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

// Gestione dei Segnali Async-Signal-Safe

void signalHandlerSafe(int signum){
    const char msg[] = "Segnale ricevuto\n";
    write(STDOUT_FILENO, msg, strlen(msg));
}

int applySignalHandlerSafe(){
    signal(SIGINT, signalHandlerSafe);
    pause(); //Mette in attesa di segnali
    return 0;
}

// Invio di segnali tra thread con pthread_kill

void *anotherThreadFun(){
    // Attende indefinitamente. In un esempio reale, logica diversa
    pause();
    return NULL;
}

void setupSignalHandler() {
    // Qui potresti configurare un gestore di segnali specifico se necessario.
}

int applyAnotherSignalHandler() {
    pthread_t thread;
    pthread_create(&thread, NULL, anotherThreadFun, NULL);

    // Configura il gestore di segnali, se necessario.
    setupSignalHandler();

    // Invia un segnale al thread.
    pthread_kill(thread, SIGUSR1);

    pthread_join(thread, NULL);
    return 0;
}

// Lezione 44 Caratteristiche dei segnali realtime.
// Invio di informazioni con i segnali real time: sigqueue e sigwaitinfo.

/**
 * I segnali real-time sono un'estensione al tradizionale sistema di segnalazione UNIX e forniscono alcune caratteristiche avanzate:

Caratteristiche dei Segnali Real-Time
Gamma Estesa: I segnali real-time hanno numeri di segnali più alti rispetto ai segnali standard UNIX e offrono una gamma estesa (SIGRTMIN a SIGRTMAX).

Coda di Segnali: A differenza dei segnali standard che possono essere sovrascritti se più istanze dello stesso segnale vengono inviate a un processo, i segnali real-time vengono messi in coda. Ciò garantisce che nessun segnale venga perso a causa di sovraccarichi.

Priorità: Quando più segnali real-time sono in attesa di essere consegnati, vengono consegnati in base alla loro priorità (numerazione dei segnali). I segnali con numeri minori (più vicini a SIGRTMIN) hanno priorità più alta.

Invio di Informazioni: I segnali real-time permettono di inviare informazioni aggiuntive (dati o valori) al processo ricevente tramite meccanismi come sigqueue in Linux.

sigqueue
sigqueue è una funzione che invia segnali real-time a un processo consentendo anche di inviare dati aggiuntivi.

Input:

pid_t pid: ID del processo a cui inviare il segnale.
int sig: Numero del segnale (deve essere un segnale real-time).
const union sigval value: Dati da inviare con il segnale. sigval può essere un int o un puntatore void*.
Return:

0: Successo.
-1: Fallimento, con errno impostato per indicare l'errore.
sigwaitinfo
sigwaitinfo attende che uno dei segnali specificati sia ricevuto. A differenza di sigwait, può anche restituire informazioni sul segnale ricevuto, inclusi i dati inviati con sigqueue.

Input:

const sigset_t *set: Puntatore alla maschera di segnali che il thread sta aspettando.
siginfo_t *info: Puntatore a una struttura siginfo_t dove le informazioni sul segnale ricevuto saranno memorizzate.
Return:

Numero del segnale: Successo.
-1: Fallimento, con errno impostato per indicare l'errore.

 La funzione sigprocmask è utilizzata per modificare la maschera dei segnali bloccati per il thread chiamante. La maschera dei segnali di un processo determina quali segnali sono bloccati e quindi non consegnati al processo fino a quando non vengono sbloccati. Questo meccanismo è fondamentale per prevenire che un segnale interrompa una sezione critica del codice, permettendo al processo o al thread di gestire i segnali in modo controllato.

Definizione
c
Copy code
#include <signal.h>
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
Input
how: Specifica come modificare la maschera corrente dei segnali bloccati. Può assumere i seguenti valori:
SIG_BLOCK: L'insieme dei segnali bloccati è l'unione dell'insieme corrente e dell'insieme specificato da set.
SIG_UNBLOCK: I segnali in set sono rimossi dall'insieme corrente dei segnali bloccati.
SIG_SETMASK: L'insieme dei segnali bloccati viene impostato esattamente all'insieme specificato da set.
set: Puntatore a un insieme di segnali da bloccare, sbloccare o impostare. Se NULL, how viene ignorato e la maschera corrente non viene modificata (questo parametro è usato solo per recuperare la maschera corrente dei segnali bloccati se oldset non è NULL).
oldset: Se non è NULL, il puntatore a un insieme di segnali dove la funzione salverà la maschera dei segnali bloccati precedente alla chiamata.
Return
0: Successo.
-1: Errore, con errno impostato per indicare il tipo di errore.
Note
La funzione sigprocmask è utilizzata principalmente in contesti multithreading dove è essenziale bloccare segnali durante l'esecuzione di sezioni critiche per prevenire condizioni di gara o stati inconsistenti dovuti all'interruzione dei segnali. Non è garantito che funzioni come previsto in contesti multithread con più di un thread che manipola i segnali o usa sigprocmask.

Per utilizzare sigprocmask in un programma che esegue un fork, si può bloccare il segnale prima del fork e poi sbloccarlo nel processo figlio o genitore come necessario per controllare quando il segnale può essere gestito.


 */

void setUpRealTimeSignal(sigset_t *set){
    sigemptyset(set);
    sigaddset(set, SIGRTMIN);
    sigprocmask(SIG_BLOCK, set, NULL);
}

void handleRealTimeSignalFork(sigset_t *set){
    siginfo_t info;
    if(sigwaitinfo(set, &info) > 0){
        printf("Segnale real-time ricevuto, dato %d\n", info.si_value.sival_int);
    } else {
        perror("sigwaitinfo");
        exit(EXIT_FAILURE);
    }
}

int applyRealTimeSignaling(){
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processo figlio: attende il segnale real-time dal genitore
        sigset_t set;
        setUpRealTimeSignal(&set);
        printf("Processo figlio (PID=%d) in attesa di segnale...\n", getpid());
        handleRealTimeSignalFork(&set);
        exit(EXIT_SUCCESS);
    } else {
        // Processo genitore: invia un segnale real-time al figlio
        sleep(1); // Assicura che il figlio sia pronto a ricevere il segnale
        union sigval sv;
        sv.sival_int = 123; // Dato da inviare
        printf("Processo genitore invia segnale a (PID=%d)\n", pid);
        if (sigqueue(pid, SIGRTMIN, sv) == -1) {
            perror("sigqueue");
            exit(EXIT_FAILURE);
        }
        wait(NULL); // Attende la terminazione del processo figlio
    }
    return 0;
}

// Lezione 45 argparse, socket e connect in C.
// htons, htonl, htohl

/**
sigprocmask
La funzione sigprocmask viene utilizzata per aggiungere, rimuovere o controllare i segnali bloccati nel thread chiamante. Questa funzione consente di manipolare la maschera di segnali del thread, che determina quali segnali sono bloccati dal thread e quindi non consegnati fino a quando non vengono sbloccati.

Input:

int how: Specifica come modificare l'attuale maschera di segnali. Può assumere i valori SIG_BLOCK (aggiungi i segnali specificati alla maschera), SIG_UNBLOCK (rimuovi i segnali dalla maschera), o SIG_SETMASK (imposta la maschera di segnali ai segnali specificati).
const sigset_t *set: Puntatore a un insieme di segnali da bloccare, sbloccare o impostare. È NULL se how è SIG_SETMASK.
sigset_t *oldset: Puntatore a una struttura sigset_t dove verrà salvata la vecchia maschera di segnali del thread, se non è NULL.
Return:

0: Successo.
-1: Fallimento, con errno impostato per indicare l'errore.
struct.pack e struct.unpack in C
In C, non esistono direttamente funzioni equivalenti a struct.pack e struct.unpack di Python, che permettono di convertire valori in stringhe di byte e viceversa. Tuttavia, in C si lavora con la memoria e la rappresentazione binaria dei dati a basso livello, per esempio attraverso l'uso di puntatori, la lettura e scrittura in socket o file, e la conversione tra endianess di host e network.

argparse in C
Non esiste una libreria standard in C equivalente ad argparse di Python. Tuttavia, C offre la funzionalità di analizzare gli argomenti della riga di comando attraverso le variabili argc e argv passate alla funzione main. Per analisi più complesse, si possono utilizzare libreria terze come getopt o getopt_long.

socket e connect in C
La creazione di socket e la connessione a un server in C si fanno con le funzioni socket e connect della libreria socket.

socket:

Input: int domain (la famiglia di protocolli, es. AF_INET), int type (tipo di socket, es. SOCK_STREAM), int protocol (protocollo specifico, normalmente 0 per scegliere il default basato su domain e type).
Return: File descriptor del socket in caso di successo, -1 in caso di errore.
connect:

Input: int sockfd (file descriptor del socket), const struct sockaddr *addr (indirizzo del server a cui connettersi), socklen_t addrlen (dimensione della struttura addr).
Return: 0 in caso di successo, -1 in caso di errore.
htons, htonl, ntohs, ntohl
Queste funzioni convertono valori interi corti e lunghi da host byte order a network byte order e viceversa.

htons (host to network short)
htonl (host to network long)
ntohs (network to host short)
ntohl (network to host long)
Input:

Un valore intero corto o lungo.
Return:

Il valore convertito.
Queste funzioni sono utilizzate per assicurare che i dati inviati su network siano in un formato standard, indipendentemente dall'architettura dell'host.


 */

// htons, htonl, ntohs, ntohl

int applyHost(){
    uint16_t hostshort = 0x1234;
    uint32_t hostlong = 0x12345678;

    uint16_t networkshort = htons(hostshort);
    uint32_t networklong = htonl(hostlong);

    printf("Host short: %x, Network short: %x\n", hostshort, networkshort);
    printf("Host long: %x, Network long: %x\n", hostlong, networklong);

    return 0;
}

// Socket & Connect

int applySocketConnect(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("Errore creazione socket\n");
        return 1;
    }
    struct hostent *host = gethostbyname("gabsalvo.github.io");
    if (host == NULL){
        fprintf(stderr, "Errore nella risoluzine del nome host\n");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    memcpy(&server_addr.sin_addr.s_addr, host -> h_addr, host -> h_length);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Errore nella connessione");
        return 1;
    }

    printf("Connesso correttamente a gabsalvo.github.io\n");

    close(sock);
    return 0;
}


/**
 * __/\\\\\\\\\\\\\\\__/\\\\\_____/\\\__/\\\\\\\\\\\\____
 _\/\\\///////////__\/\\\\\\___\/\\\_\/\\\////////\\\__
  _\/\\\_____________\/\\\/\\\__\/\\\_\/\\\______\//\\\_
   _\/\\\\\\\\\\\_____\/\\\//\\\_\/\\\_\/\\\_______\/\\\_
    _\/\\\///////______\/\\\\//\\\\/\\\_\/\\\_______\/\\\_
     _\/\\\_____________\/\\\_\//\\\/\\\_\/\\\_______\/\\\_
      _\/\\\_____________\/\\\__\//\\\\\\_\/\\\_______/\\\__
       _\/\\\\\\\\\\\\\\\_\/\\\___\//\\\\\_\/\\\\\\\\\\\\/___
        _\///////////////__\///_____\/////__\////////////_____
 */


int main(int argc, char *argv[]){
  /* scannami();
    malloccami_realloccami();
    attuaIncremento();
    attuaSwap_Modify();
    printMyString();
    takeArgs(argc, argv);
    copiaDipendente();
    copiaIndipendente();
    useAssert();
    provaErrno();
    equivalenzaPuntatori();
    equivalenzaPuntatori2();
    applyLunghezzaStringa();
    applyMergeSort();
    applyPrintString;
    modifierBuffer();
    useAsprintf();
    applySaiyanStructEasy();
    initAndUseCoppia();
    puntatoriAStruct();
    useCapitale();
    applyComparaEta();
    applyApplication();
    applyMergeSortCompare();
    applyListaNodi();
    applyInserimentoRecPara();
    applyCancellazioneLista();
    applyProcessaLinea
    applyMatrice();
    applyQuickSort()
    applyFork();
    applyWait();
    //applyFwrite();
    applyContaPrimi();
    applyWriterReader();
    applyProcessoLettoreScrittore();
    applySem();
    applyThreadsTheory();
    applyMutex();
    applyCondVariablesThreads();
    applySignalHandler();
    applySignalHandlerThead();
    applyStructVSUnion();
    applyThreadSafeFunc();
    applySignalHandlerSafe();
    applyAnotherSignalHandler();
    applyRealTimeSignaling();
    applyHost();
    applySocketConnect();
    */
    return 0;
}
