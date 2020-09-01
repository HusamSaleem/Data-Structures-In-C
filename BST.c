#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *left;
	struct Node *right;
} Node;

typedef struct {
	int size;
	struct Node *root;
} BstTree;

BstTree* createTree() {
	BstTree *tree = malloc(sizeof(BstTree));
	tree->size = 0;
	tree->root = NULL;

	return tree;
}

// Found == 1, not found = 0
int search(BstTree *tree, int key) {
	if (tree->size == 0) {
		return 0;
	}
	
	struct Node* curNode = tree->root;

	while (curNode != NULL && curNode->data != key) {
		if (curNode->data <= key) {
			curNode = curNode->right;
		} else {
			curNode = curNode->left;
		}	
	}

	if (curNode != NULL && curNode->data == key) {
		return 1;
	} else {
		return 0;
	}
}

void printInOrder(struct Node *root) {
	if (root != NULL) {
		printInOrder((struct Node*) root->left);
		printf("%d ", root->data);
		printInOrder((struct Node*) root->right);
	}
}

struct Node *findInOrderSuccessor(struct Node* root) {
	struct Node* current = root; 
	  
	    /* loop down to find the leftmost leaf */
	    while (current->left != NULL) { 
		    current = current->left; 
	    }
	   return current; 
}

void delete(BstTree *tree, struct Node *node) {
	struct Node *curNode = tree->root;
	struct Node *prev = NULL;
	
	// Find the node
	while (curNode != NULL && curNode != node) {
		prev = curNode;

		if (curNode->data > node->data) {
			curNode = curNode->left;
		} else {
			curNode = curNode->right;
		}
	}

	// 3 Cases
	
	// Case 1: 0 child
	// Case 2: 1 child
	// Case 3: 2 child
	
	// Case 1: 0 Children
	if (curNode->left == NULL && curNode->right == NULL) {
		// Just remove it
		
		// If the node is root
		if (curNode == tree->root) {
			free(tree->root);
			tree->root = NULL;
		} else if (prev->right == curNode) {
			free(prev->right);
			prev->right = NULL;
		} else {
			free(prev->left);
			prev->left = NULL;
		}
	} 
	// Case 3: 2 Child
	else if (curNode->left != NULL && curNode->right != NULL) {
		// Find in order successor
		struct Node *successor = findInOrderSuccessor(curNode->right);
		struct Node *temp = curNode;
		// Handle root case
		if (curNode == tree->root) {
			tree->root->data = successor->data;
		} else {
			if (prev->data > curNode->data) {
				prev->left->data = successor->data;
			} else {
				prev->right->data = successor->data;
			}
		}

		// Delete the successor
		delete(tree, successor);
	} 
	// Case 2: 1 Child
	else if (curNode->left == NULL || curNode->right == NULL) {
		// If the node is root
		if (curNode == tree->root) {
			if (tree->root->left != NULL) {
			 	struct Node *temp = tree->root;
				tree->root = tree->root->left;
				free(temp);
			} else {
				struct Node *temp = tree->root;
				tree->root = tree->root->right;
				free(temp);
			}
		} else {
			if (curNode->right != NULL) {
				if (prev->data > curNode->data) {
					struct Node *temp = curNode;
					prev->left = curNode->right;
					free(temp);
				} else {
					struct Node *temp = curNode;
					prev->right = curNode->right;
					free(temp);
				}
			} else if (curNode->left != NULL) {
				if (prev->data > curNode->data) {
					struct Node *temp = curNode;
					prev->left = curNode->left;
					free(temp);
				} else {
					struct Node *temp = curNode;
					prev->right = curNode->left;
					free(temp);
				}
			}	
		}
	}
	tree->size--;
}

struct Node* findPtr(BstTree *tree, int data) {
	struct Node *curNode = tree->root;

	while (curNode != NULL && curNode->data != data) {
		if (curNode->data > data) {
			curNode = curNode->left;
		} else {
			curNode = curNode->right;
		}
	}

	return curNode;
}

void tryDelete(BstTree *tree, int data) {
	if (tree->size == 0) {
		printf("Tree is empty!\n");
		return;
	}
	if (search(tree, data) == 0) {
		printf("Element not in tree\n");
		return;
	}

	struct Node *ptr = findPtr(tree, data);
	delete(tree, ptr);
}

void insert(BstTree *tree, int data) {

	if (search(tree, data) == 1) {
		printf("Element already exists\n");
		return;
	}

	struct Node *curNode = tree->root;
	struct Node *prev = NULL;

	while (curNode != NULL) {
		prev = curNode;

		if (data >= curNode->data) {
			curNode = curNode->right;
		} else {
			curNode = curNode->left;
		}
	}

	// Make root
	if (prev == NULL) {
		tree->root = (struct Node*) malloc(sizeof(Node));
		tree->root->data = data;
		tree->root->left = NULL;
		tree->root->right = NULL;
	} else {
		// Insert into tree
		if (prev->data >= data) {
			prev->left = (struct Node*) malloc(sizeof(Node));

			prev->left->data = data;
			prev->left->left = NULL;
			prev->left->right = NULL;
		} else {
			prev->right = (struct Node*) malloc(sizeof(Node));

			prev->right->data = data;
			prev->right->right = NULL;
			prev->right->left = NULL;
		}
	}

	tree->size++;
}

int main() {
	BstTree *tree = createTree();

	// Insertions
	insert(tree, 5);
	insert(tree, 3);
	insert(tree, 8);
	insert(tree, 6);
	insert(tree, 10);

	// Searching
	printf("Found: %d\n", search(tree, 5));
	printf("Found: %d\n", search(tree, 10));
	printf("Found: %d\n", search(tree, 3));
       	printf("Found: %d\n", search(tree, 8));
	printf("Found: %d\n", search(tree, 11));    	
	

	// Deletion
	tryDelete(tree, 5);
	tryDelete(tree, 3);
	tryDelete(tree, 10);

	// Re-insertion again
	insert(tree, 9);
	insert(tree, 9);
	insert(tree, 7);

	if (tree->root != NULL) {
		printf("Root : %d\n", tree->root->data);
	}
	
	printInOrder((struct Node*) tree->root);
	return 0;
}
