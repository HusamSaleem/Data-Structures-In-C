#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Max-heap implementation, but can be easily turned into min-heap

typedef struct {
	int size, capacity;
	int *arr;
} Heap;

Heap* createHeap(int maxSize) {
	Heap *heap = (Heap *)malloc(sizeof(Heap));

	heap->capacity = maxSize;
	heap->size = 0;

	heap->arr = (int *) malloc(maxSize * sizeof(int));

	return heap;
}

void printHeap(Heap *heap) {
	for (int i = 0; i < heap->size; i++) {
		printf("%d ", heap->arr[i]);
	}

	printf("\n");
}

void createMoreMemory(Heap *heap) {
	heap->arr = (int *)realloc(heap->arr, heap->size * 2 * sizeof(int));
	heap->capacity *= 2;
}

// Returns index
int getRightNode(int index) {
	return (index * 2) + 2;
}

// Returns index
int getLeftNode(int index) {
	return (index * 2) + 1;
}

// Returns index
int getParent(int index) {
	return (index - 1) / 2;
}

void swap(int *arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void heapifyUp(Heap *heap) {
	int curInd = heap->size - 1;
	
	int parentInd = getParent(curInd);
	while (heap->arr[parentInd] < heap->arr[curInd]) {
		if (parentInd < 0) {
			break;
		}

		swap(heap->arr, parentInd, curInd);
		curInd = parentInd;
		parentInd = getParent(curInd);
	}
}

void heapifyDown(Heap *heap, int i) {
	int leftInd = getLeftNode(i);
	int rightInd = getRightNode(i);

	if (heap->size -1 >= leftInd) {
		int leftVal = heap->arr[leftInd];
		int rightVal = INT_MIN;

		if (heap->size - 1 >= rightInd) {
			rightVal = heap->arr[rightInd];
		}

		if (leftVal >= rightVal) {
			swap(heap->arr, leftInd, i);
			i = leftInd;
			heapifyDown(heap, i);
		} else {
			swap(heap->arr, rightInd, i);
			i = rightInd;
			heapifyDown(heap, i);
		}
	}
}

int pop(Heap *heap) {
	if (heap->size == 0) {
		printf("Nothing in heap\n");
		return -1;
	}

	int poppedItem = heap->arr[0];
	swap(heap->arr, 0, heap->size - 1);

	heap->arr[heap->size - 1] = 0;
	// B/c the current size is at the next empty slot
	// So we now point to the last slot after we deleted the maximum element
	heap->size -= 2;

	heapifyDown(heap, 0);

	// This will now point to the last slot + 1 so it points to an empty slot for the next element
	heap->size++;
	printf("Popped item: %d\n", poppedItem);

 	return poppedItem;
}

void insert(Heap *heap, int data) {
	if (heap->size == 0) {
		heap->arr[0] = data;
		heap->size++;
		return;
	}
	
	if (heap->size == heap->capacity) {
		createMoreMemory(heap);
	}

	heap->arr[heap->size] = data;
	heap->size++;
	heapifyUp(heap);	
}

int main() {
	Heap* heap = createHeap(4);
	
	// Insertions
	insert(heap, 10);
	printHeap(heap);
	insert(heap, -1);
	printHeap(heap);
	insert(heap, 20);
	printHeap(heap);
	
	// Popping the maximum element
	pop(heap);
	printHeap(heap);
	pop(heap);
	printHeap(heap);


	// Insert again but to the max to create more memory
	insert(heap, 2);
	insert(heap, 300);
	insert(heap, -203);
	insert(heap, 106);
	printHeap(heap);

	pop(heap);
	printHeap(heap);

	printf("Current size %d\n", heap->size);
	return 0;
}
