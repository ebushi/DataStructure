#pragma once

struct WeightTree {
	struct Tree *tree;
	int weight;
};

struct Node {
	struct WeightTree weightTree;
	struct Node *last;
	struct Node *next;
};

// init the linked list, with empty head
void initPriQue(struct Node **list);

//find node at position 
struct Node * positon(struct Node *list, int pos);

struct Node *creatNode(struct Tree *tree);

int compare(struct Node* p1, struct Node* p2);

int insertAtOrder(struct Node* list, struct Node* n);

void dePriQue(struct Node *list, struct Tree **temp);
