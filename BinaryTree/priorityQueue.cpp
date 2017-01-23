// DualLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include "priorityQue.h"


// generate one random weight
int genWeight() {
	return rand() % 10;
}


// init the linked list, with empty head
void initPriQue(struct Node **list) {
	*list = (struct Node *)malloc(sizeof(struct Node));
	((*list)->weightTree).tree = NULL;
	((*list)->weightTree).weight = 0;
	(*list)->last = NULL;
	(*list)->next = NULL;

}

//find node at position 
struct Node * positon(struct Node *list, int pos) {
	struct Node *p;
	p = list;
	int i = 0;

	while (p && i < pos) {
		p = p->next;
		i++;
	}

	if (i == pos) {
		return p;
	}
	return NULL;
}


//creat one node
struct Node *creatNode(struct Tree *tree) {
	struct Node *q;
	q = (struct Node *)malloc(sizeof(struct Node));
	(q->weightTree).weight = genWeight();
	(q->weightTree).tree = tree;
	return q;
}

/*
@return:
1  when p1 > p2
0  when p1 == p2
-1 when p1 < p2
-2 when p1 == null || p2 == null
*/
int compare(struct Node* p1, struct Node* p2) {
	if (!p1 || !p2) {
		return -2;
	}

	if ((p1->weightTree).weight < (p2->weightTree).weight) {
		return 1;
	}

	if ((p1->weightTree).weight > (p2->weightTree).weight) {
		return -1;
	}

	if ((p1->weightTree).weight == (p2->weightTree).weight) {
		return 0;
	}

	return -2;
}


int insertAtOrder(struct Node* list, struct Node* n) {
	int res = -3; // the result of compare(p,n)
	if (n == NULL) {
		printf("invalid node\n");
		return 0;
	}
	struct Node* p = list;
	struct Node* q = list;
	// the list is empty,insert the first node
	if (p->next == NULL) {
		//insertNode at tail
		p->next = n;
		n->last = p;
		n->next = NULL;
		return 1;
	}
	p = p->next;
	//找到插入位置的指针
	while (p != NULL) {
		//insert after p

		res = compare(p, n);
		if (res == -1) {	//p<n
			q = p;
			p = p->next;
			continue;// 当前节点大于待插入节点，并且当前节点不是最后一个
		}
		//
		else if (res == 0 || res == 1) {
			break;//已找到待插入位置的后一个位置
		}
	}

	if (res == 0 || res == 1) {
		//insert in middle
		p->last->next = n;
		n->last = p->last;
		n->next = p;
		p->last = n;
		return 1;
	}

	if (res == -1) {
		//待插入节点最小，应插入在tail
		q->next = n;
		n->last = q;
		n->next = NULL;
		return 1;
	}
	return 0;
}



void dePriQue(struct Node *list, struct Tree **temp) {
	
	if (list == NULL) {
		printf("priority Queue is empty now\n");
		return;
	}
	struct Node *p = list->next;
	*temp = (p->weightTree).tree;
	if (p->next != NULL) {
		p->next->last = list;
		list->next = p->next;
		free(p);
	}
	else {
		list->next = NULL;
		free(p);
	}
}


