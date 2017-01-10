// DoubleLinkedCircularList.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef int ElemType;

struct Node
{
	ElemType data;
	struct Node *last, *next;
};

typedef struct Node ListNode;
typedef struct Node* pNode;

void InitList(pNode *head)
{
	if ((*head = (pNode)malloc(sizeof(ListNode)))==NULL)
		exit(-1);
	(*head)->last = *head;
	(*head)->next = *head;
}

pNode GetElem(pNode head, int pos)
{
	pNode p = head->next;
	int i = 0;

	while (p != head && i < pos)
	{
		p = p->next;
		i++;
	}

	if (i == pos)
		return p;
	return NULL;
}

int InsertNode(pNode head, int pos, ElemType elem)
{
	pNode p, s;

	p = GetElem(head, pos);
	if (!p)
		return 0;

	if ((s = (pNode)malloc(sizeof(ListNode))) == NULL)
		exit(-1);

	s->data = elem;
	p->last->next = s;
	s->last = p->last;
	s->next = p;
	p->last = s;

	return 1;
}

int DeleteNode(pNode head, int pos)
{
	pNode p;
	int i = 0;

	p = GetElem(head, pos);

	if (!p)
	{
		printf("删除位置错误\n");
		return 0;
	}

	p->last->next = p->next;
	p->next->last = p->last;
	free(p);
	
	return 1;
}

void ShowList(pNode head)
{
	pNode p;
	p = head->next;

	while (p != head)
	{
		printf("%d ",p->data);
		p = p->next;
	}

	printf("\n");
}

int main()
{
	pNode L;
	InitList(&L);

	for (int i = 0; i < 10; i++)
		InsertNode(L, i, i);

	ShowList(L);

	DeleteNode(L,0);

	ShowList(L);
	
    return 0;
}

