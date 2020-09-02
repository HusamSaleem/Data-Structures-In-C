#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int key;
	int val;
	struct Node *next;
} Node;

typedef struct {
	int size, capacity;
	Node **arr;
} HashMap;

HashMap *createHashMap(int initialCapacity) {
	HashMap *map = (HashMap *) malloc(sizeof(HashMap));
	map->size = 0;
	map->capacity = initialCapacity;
	
	map->arr = (Node **) malloc(sizeof(Node) * map->capacity);
	
	// Set each block to NULL
	for (int i = 0; i < map->capacity; i++) {
		map->arr[i] = NULL;
	}

	return map;
}

int hashKey(HashMap *map, int key) {
	if (key < 0) {
		return -(key % map->capacity);
	}
	return key % map->capacity;	
}

void put(HashMap *map, int key, int value) {
	if (map->size == map->capacity) {
		printf("Hashmap is already full\n");
		return;
	}

	int index = hashKey(map, key);

	Node *newNode = malloc(sizeof(Node));
	newNode->key = key;
	newNode->val = value;
	newNode->next = NULL;

	Node *block = map->arr[index];
	Node *curNode = map->arr[index];

	while (curNode != NULL) {
		if (curNode->key == key) {
			// Overwrite
			curNode->val = value;
			map->size++;
			free(newNode);
			return;
		}

		curNode = (Node *) curNode->next;
	}	

	newNode->next = (struct Node *) block;
	map->arr[index] = newNode;
	map->size++;
}

int search(HashMap *map, int key) {
	int index = hashKey(map, key);

	Node *curNode = map->arr[index];
	
	while (curNode != NULL && curNode->key != key) {
		curNode = (Node *) curNode->next;
	}

	if (curNode == NULL) {
		return -1;
	} else if (curNode->key == key) {
		printf("Found key %d, Value is %d\n", key, curNode->val);
		return key;
	}

	printf("Key not found\n");
	return -1;
}

int main() {
	HashMap *map = createHashMap(4);
	put(map, 1, 1);
	put(map, 2, 3);

	search(map, 2);
	search(map, 3);
	search(map,1);

	put(map, 9, 5);

	search(map, 9);

	return 0;
}
