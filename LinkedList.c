#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	struct Node *next;
} Node;


Node *head;
int size = 0;
int maxSize = 4;

void addMoreMemory(Node *listPtr) {
	listPtr = (Node *) realloc(listPtr, size * 2 * sizeof(Node));
	head = listPtr;
	maxSize = size * 2;
}

void clearList() {
	Node* tmp;

       	while (head != NULL) {
       		tmp = head;
		head = (Node *) head->next;
		free(tmp);
	}

	head = NULL;
	maxSize = 4;
	size = 0;

	printf("List has been cleared!\n");
}

void printList() {
	if (size == 0) {
		printf("List is empty\n");
		return;
	}

	Node *curNode = head;

	while (curNode != NULL) {
		printf("%d -> ", curNode->data);
		curNode = (Node *) curNode->next;
	}

	printf("\n");
}

void delete(int data) {
	if (size == 0){
		printf("List is empty. Nothing Deleted\n");
		return;
	}

	Node *curNode = head;
	Node *prev = NULL;

	while (curNode != NULL) {
		if (curNode->data == data) {
			break;
		}

		prev = curNode;
		curNode = (Node *) curNode->next;
	}
	
	if (curNode == NULL) {
		printf("Element not found\n");
		return;
	}
	
	// Remove the head
	if (prev == NULL) {
		if (curNode->next != NULL) {
			Node *temp = (Node *) head->next;
			head = (Node *) curNode->next;

			free(temp);
			temp = NULL;
		} else {
			free(head);
			head = NULL;
		}
	} else {
		Node *temp = (Node *) prev->next;
		prev->next = (struct Node *) curNode->next;
		free(temp);
		temp = NULL;
	}

	printf("%d has been deleted\n", data);
	size--;
}

void insertAtHead(int data) {
	if (size == 0) {
		head->data = data;
		size++;
		return;
	}

	Node *newNode = malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = (struct Node *) head;
	head = newNode;
	size++;
}
void initList(int initialSize) {
       	head = (Node *) malloc(initialSize * sizeof(Node));
	
	if (head != NULL) {
		printf("Linked List has been created successfully\n");
       	}
}


void insert(int data, int pos) {
	if (size == 0 && head == NULL) {
		initList(maxSize);
	}
	if (size == maxSize) {
		addMoreMemory(head);
	}

	if (pos == 0 || size == 0) {
		insertAtHead(data);
		return;
	}

	if (pos < 0) {
		printf("Not a valid position\n");
		return;
	}

	Node *curNode = head;
	Node *prev = NULL;

	int i = 0;
	while (curNode != NULL && i < pos) {
		prev = curNode;
		curNode = (Node *) curNode->next;
		i++;
	}

	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode->data = data;

	if (prev != NULL) {	
		prev->next = (struct Node *)newNode;
		newNode->next = (struct Node *) curNode;
	} else {
		curNode->next = (struct Node *) newNode;
	}

	size++;

	printf("Element %d has been inserted at position %d\n", data, i);
}

void showMenu() {
	printf("\n-----Linked List-----\n");
	printf("0. Exit\n");
	printf("1. Add an element\n");
	printf("2. Print the list\n");
	printf("3. Delete an element\n");
	printf("4. Clear the list\n");
	printf("5. Display List Size\n");
	printf("-----------------------\n");

	int userInput;
	scanf("%d", &userInput);

	switch(userInput) {

		case 0:
			printf("Exiting...\n");
			exit(0);
			break;
		case 1:
			printf("Enter the element you want to add\n");
			int num;
			scanf("%d", &num);
			
			printf("Enter the position you want to add it at\n");
		       	int pos;
			scanf("%d", &pos);	

			insert(num, pos);
			showMenu();
			break;
		case 2:
			printList();
			showMenu();
			break;
		case 3:
			printf("Enter the number you want to delete\n");
			int num1;
			scanf("%d", &num1);

			delete(num1);
			
			showMenu();
			break;
		case 4:
			clearList();
			showMenu();
			break;
		case 5:
			printf("The size of this list is %d\n", size);
			showMenu();
			break;
		default:
			printf("Not a valid command\n");
			showMenu();
			break;

	}

}

int main() {
	initList(maxSize);
	showMenu();
	return 0;
}
