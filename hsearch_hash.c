#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define Num_elem 1000000

typedef struct Node {
    char *key;
    struct Node *next;
} Node;

Node *head = NULL;

void add_to_linked_list(const char *key) {
    Node *new_node = malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->next = head;
    head = new_node;
}

void free_linked_list() {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
}

void init_hash_table() {
    if (!hcreate(Num_elem)) {
        perror("hcreate");
        exit(EXIT_FAILURE);
    }
}

void insert_into_hash_table(const char *name, int age) {
    ENTRY e, *ep;
    e.key = strdup(name);
    e.data = (void *)(intptr_t)age;

    ep = hsearch(e, ENTER);
    if (ep == NULL) {
        perror("hsearch: inserimento");
        exit(EXIT_FAILURE);
    }

    add_to_linked_list(e.key);
}

int lookup_in_hash_table(const char *name) {
    ENTRY e, *ep;
    e.key = (char *)name;

    ep = hsearch(e, FIND);
    if (ep != NULL) {
        return (int)(intptr_t)ep->data;
    } else {
        return -1;
    }
}

void destroy_hash_table() {
    free_linked_list();
    hdestroy();
}
