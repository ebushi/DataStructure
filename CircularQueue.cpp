// CircularQueue.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define	CQSize 8

struct CirQueue
{
	int data[CQSize];
	int front, rear;
	int tag;
};

typedef struct CirQueue CQ;

void InitCQ(CQ *Q)
{
	Q->front = Q->rear = 0;
	Q->tag = 0;
}

int EmptyCQ(CQ *Q)
{
	if (Q->front == Q->rear && Q->tag == 0)
	{
		printf("Empty Circular Queue\n");
		return 1;
	}

	return 0;
}

int FullCQ(CQ *Q)
{
	if (Q->front == Q->rear && Q->tag == 1)
	{
		printf("Full Circular Queue\n");
		return 1;
	}
	return 0;
}


int EnCQ(CQ *Q, int data)
{
	if (FullCQ(Q))
		return 0;

	Q->data[Q->rear] = data;
	Q->rear = (Q->rear+1)%CQSize;
	Q->tag = 1;

	return 1;
}

int DeCQ(CQ *Q, int *p)
{
	if (EmptyCQ(Q))
		return 0;

	*p = Q->data[Q->front];
	Q->front = (Q->front + 1) % CQSize;
	Q->tag = 0;
	return 1;
}

void ShowCQ(CQ *Q)
{
	if (EmptyCQ(Q))
		return;
	if (Q->front < Q->rear)
	{
		for (int i = Q->front; i < Q->rear; i++)
			printf("%d ",Q->data[i]);
	}
	else
	{
		for (int j = Q->front; j < Q->rear + CQSize; j++)
			printf("%d ", Q->data[j%CQSize]);
	}
	printf("\n");
}

int main()
{
	CQ Q;

	InitCQ(&Q);

	for (int i = 0; i < 10; i++)
		EnCQ(&Q,i);		// Enter Circular Queue test
	ShowCQ(&Q);

	int p;
	DeCQ(&Q, &p);		// Out of CQ test
	printf("%d\n", p);

	DeCQ(&Q, &p);
	printf("%d\n", p);

	DeCQ(&Q, &p);
	printf("%d\n", p);


	EnCQ(&Q, 8);
	EnCQ(&Q, 9);
	EnCQ(&Q, 10);		// Circular test

	ShowCQ(&Q);
	return 0;
}