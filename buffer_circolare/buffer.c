#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 5

typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count; //elementi nel buffer
} circular_buffer;


void init_buffer(circular_buffer *cb);
bool buffer_is_full(circular_buffer *cb);
bool buffer_is_empty(circular_buffer *cb);
void buffer_insert(circular_buffer *cb, int item);
int buffer_remove(circular_buffer *cb);

int main(){
    circular_buffer cb;
    init_buffer(&cb);

    for(int i = 1; i <= 6; i++) {
        buffer_insert(&cb, i);
        printf("Elemento inserito: %d\n", i);
    }

    for(int i = 0; i <6; i++){
        int item = buffer_remove(&cb);
        if (-1 != item) {
            printf("Elemento rimosso: %d\n", item);
        }
    }

    return 0;
}

void init_buffer(circular_buffer *cb){
    cb -> head = 0;
    cb -> tail = 0;
    cb -> count = 0;
}

bool buffer_is_full(circular_buffer *cb) {
    return cb -> count == BUFFER_SIZE;
}

bool buffer_is_empty(circular_buffer *cb) {
    return cb -> count == 0;
}

void buffer_insert(circular_buffer *cb, int item) {
    if(!buffer_is_full(cb)) {
        cb -> buffer[cb -> tail] = item;
        cb -> tail = (cb -> tail + 1) % BUFFER_SIZE;
        cb -> count++;
    } else {
        printf("Buffer pieno\n");
    }
}

int buffer_remove(circular_buffer *cb) {
    int item = -1;
    if(!buffer_is_empty(cb)){
        item = cb -> buffer[cb-> head];
        cb -> head = (cb -> head +1) % BUFFER_SIZE;
        cb -> count--;
    } else {
        printf("Buffer vuoto!\n");
    }
    return item;
}


