#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_KEY 256
#define TABLE_SIZE 10

typedef struct Entry {
    char key[MAX_KEY];
    int value;
    struct Entry *next;
} Entry;

Entry *hash_table[TABLE_SIZE];

unsigned int hash(char *key) {
    int len = strnlen(key, MAX_KEY);
    unsigned int hash_value = 0;
    for (int i = 0; i < len; i++) {
        hash_value += key[i];
        hash_value = (hash_value * key[i]) % TABLE_SIZE;
    }

    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void print_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t", i);
            Entry *tmp = hash_table[i];
            while (tmp != NULL) {
                printf("%s",tmp->key);
                if (tmp->next != NULL) {
                    printf(" - ");
                }
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
}

bool insert(Entry *entry) {
    if (entry == NULL) return false;
    int index = hash(entry->key);
    entry->next=hash_table[index];
    hash_table[index] = entry;
    return false;
}

Entry *delete(char* key) {
    int index = hash(key);
    Entry *tmp = hash_table[index];
    Entry *prev = NULL;

    while (tmp != NULL && strncmp(tmp->key, key, MAX_KEY) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    if (prev == NULL) {
        hash_table[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }

    return tmp;
}

Entry *find(char* key) {
    int index = hash(key);
    Entry *tmp = hash_table[index];

    while (tmp != NULL && strncmp(tmp->key, key, MAX_KEY) == 0) {
        tmp = tmp->next;
    }

    return tmp;
}

int main() {
    init_hash_table();

    Entry josh = {.key="Josh", .value=16};
    Entry emily = {.key="Joshie", .value=16};
    insert(&josh);
    insert(&emily);
    
    printf("Table before deleting Josh:\n");
    print_table();

    delete("Joshie");
    printf("Table after deleting Joshie:\n");
    print_table();


    return 0;
}