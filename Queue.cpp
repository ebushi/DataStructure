// Queue.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define QSize 50

typedef int ElemType;

struct Queue
{
	ElemType data[QSize];
	int front, rear;
};

typedef struct Queue Que;

void InitQueue(Que *Q)
{
	Q->front = Q->rear = 0;
}

int EmptyQueue(Que *Q)
{
	if (Q->front == Q->rear)
		return 1;
	return 0;
}

int EnQueue(Que *Q, ElemType elem)
{
	if (Q->rear >= QSize)
	{
		printf("The Queue is full\n");
		return 0;
	}
	else
	{
		Q->data[Q->rear] = elem;
		Q->rear++;

		return 1;
	}
}

int Dequeue(Que *Q, ElemType *p)
{
	if (Q->front < Q->rear)
	{
		*p = Q->data[Q->front];
		Q->front++;

		return 1;
	}
	else
		return 0;
}

void ShowQue(Que *Q)
{
	if (EmptyQueue(Q))
		printf("Empty Queue");
	else
		for (int i = Q->front; i < Q->rear; i++)
			printf("%d ", Q->data[i]);

	printf("\n");
}

int main()
{
	Que Q;

	InitQueue(&Q);

	for (int i = 0; i < 10; i++)
		EnQueue(&Q, i);  // EnQueue test
	ShowQue(&Q);
	
	ElemType t;
	Dequeue(&Q, &t);	//  DeQueue test
	ShowQue(&Q);

    return 0;
}