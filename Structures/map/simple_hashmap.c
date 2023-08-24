#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

typedef struct KeyValuePair {
        char* key;
        int value;
        struct KeyValuePair* next;
} KeyValuePair;

typedef struct {
        struct KeyValuePair *buckets[HASH_SIZE];
} HashMap;

size_t hash(const char* key) {
        size_t hash = 0;

        while (*key) {
                int ch = (int)*key++;

                hash = (hash << 5) + ch;
        }

        return hash % HASH_SIZE;
}

HashMap* hashmap_init() {
        HashMap* map = malloc(sizeof(HashMap));
        memset(map->buckets, 0, sizeof(map->buckets));

        return map;
}

void hashmap_insert(HashMap* map, const char* key, int value) {
        size_t index = hash(key);

        KeyValuePair *new_pair = malloc(sizeof(KeyValuePair));
        new_pair->key = strdup(key);
        new_pair->value = value;
        new_pair->next = NULL;

        if (map->buckets[index] == NULL) {
                map->buckets[index] = new_pair;
        } else {
                KeyValuePair *current = map->buckets[index];
                while (current->next != NULL) {
                        current = current->next;
                }

                current->next = new_pair;
        }
}

int hashmap_get(HashMap* map, const char* key) {
        size_t index = hash(key);

        KeyValuePair *current = map->buckets[index];
        while (current != NULL) {
                if (strcmp(current->key, key) == 0) {
                        return current->value;
                }

                current = current->next;
        }

        return -1; // Key not found
}

int main() {
        HashMap* map = hashmap_init();

        // Insert key-value pairs
        hashmap_insert(map, "apple", 5);
        hashmap_insert(map, "banana", 10);
        hashmap_insert(map, "cherry", 7);

        // Retrieve values
        printf("Value for apple: %d\n", hashmap_get(map, "apple"));
        printf("Value for banana: %d\n", hashmap_get(map, "banana"));
        printf("Value for cherry: %d\n", hashmap_get(map, "cherry"));
        printf("Value for grape: %d\n", hashmap_get(map, "grape")); // Key not found

        return 0;
}
