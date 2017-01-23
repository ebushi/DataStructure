#include "stdafx.h"
#include "queue.h"

//入队
void enQue(struct Queue *que, struct Tree *tree) {
	if (tree == NULL) {
		return;
	}
	if (que->tail >= Max - 1) {
		printf("queue is full\n");
		return;
	}
	que->elem[que->tail] = tree;
	que->tail++;
}

//出队
void deQue(struct Queue *que, struct Tree **temp) {
	if (que->front > que->tail) {
		printf("empty Queue\n");
		return;
	}
	*temp = que->elem[que->front];
	que->front++;
}



