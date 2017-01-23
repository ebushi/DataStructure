#pragma once
#define Max 128

struct Queue {
	struct Tree *elem[Max];
	int front = 0;
	int tail = 0;
};

void enQue(struct Queue *que, struct Tree *tree);

void deQue(struct Queue *que, struct Tree **temp);