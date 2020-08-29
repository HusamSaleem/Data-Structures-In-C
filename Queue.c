#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int size, maxSize, rear, front;
	int *arr;
} Queue;

void printQueue(Queue *qPtr) {
	int i = qPtr->front;
	int j = 0;	
	while (j < qPtr->size) {
		printf("%d ", qPtr->arr[i]); 
		i++;
		j++;

		if (i == qPtr->size) {
			i = 0;
		}
	}

	printf("\n");
}


Queue *createQueue(int capacity) {
	Queue *queue = (Queue *) malloc(sizeof(Queue));
	
	queue->size = 0;
	queue->front = queue->rear -1;
	queue->arr = (int *) malloc(queue->maxSize * sizeof(int));
	queue->maxSize = capacity;

	return queue;
}


void enQueue(int data, Queue *qPtr) {
	if (qPtr->size == 0) {
		qPtr->rear = 0;
		qPtr->front = 0;
	}

	if (qPtr->size == qPtr->maxSize) {
		printf("Queue is full!\n");
		return;
	}

	if (qPtr->rear == qPtr->size-1) {
		qPtr->rear = 0;
	}

	qPtr->arr[qPtr->rear] = data;
	qPtr->size++;
	qPtr->rear++;
}

int deQueue(Queue *qPtr) {
	if (qPtr->size == 0) {
		printf("Queue is empty\n");
		return -1;
	}
	
	int item = qPtr->arr[qPtr->front];
	qPtr->arr[qPtr->front] = -1;
	qPtr->front++;
	qPtr->size--;

	return item;
}

int main() {
	Queue *queue = createQueue(4);

	enQueue(5, queue);
	printQueue(queue);
	enQueue(2, queue);
	printQueue(queue);
	enQueue(-5, queue);
      	printQueue(queue);	
	enQueue(-10, queue); 
	printQueue(queue);
	enQueue(2, queue);  	
	enQueue(2, queue);  
	
	printf("Item dequeued: %d\n", deQueue(queue));
	printf("Item dequeued: %d\n", deQueue(queue));
	printQueue(queue);  
	return 0;
}
