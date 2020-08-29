#include <stdio.h>
#include <stdlib.h>

size_t size = 0;
size_t maxSize = 4;

int *stack;

void createNewMemory() {
	stack = (int *) realloc(stack, size * 2 * sizeof(int));
	maxSize *= 2;
}

void printStack() {
	if (size == 0)	{
		return;
	}

	printf("[ ");
	for (int i = 0; i < size - 1; i++) {
		printf("%d,", *(stack + i));
	}

	printf("%d", *(stack + size - 1));
	printf(" ]\n");
}

void insert(int data) {
	if (size == maxSize) {
		createNewMemory();
	}

	*(stack + size) = data;
	size++;
}

int pop() {
	if (size == 0) {
		printf("Nothing to remove\n");
		return -1;
	}

	int item = *(stack + size  - 1);
	*(stack + size - 1) = -1;
	size--;

	return item;
}

int *createStack(size_t initialSize) {
	int *stack = malloc(initialSize * sizeof(int));
	return stack;
}

int main() {
	stack = createStack(maxSize);
	insert(5);
	printStack();
	insert(-2);
	printStack();
	printf("Popped item: %d\n", pop());
	printStack();

	return 0;

}
