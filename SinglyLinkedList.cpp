// SinglyLinkedList.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

struct Node
{
	int data;
	struct Node *next;
};

typedef struct Node ListNode;
typedef struct Node* ptrNode;

void InitList(ptrNode *head)
{
	if ((*head = (ptrNode)malloc(sizeof(ListNode))) == NULL)
		exit(-1);
	(*head)->next = NULL;
}

int EmptyList(ptrNode head)
/* return 1: empty list; return 0: not empty*/
{
	if (head->next == NULL)
		return 1;
	else
		return 0;
}

ptrNode GetElem(ptrNode head, int i)
{
	ptrNode p = head;
	int j = 0;

	if (EmptyList(head))
	{
		printf("\n空链表\n");
		return NULL;
	}

	if (i < 0)
	{
		printf("\n位置不合法\n");
		return NULL;
	}

	while ((p->next != NULL) && j < i)
	{
		p = p->next;
		j++;
	}
	
	if (j == i)
		return p;
	else
		return NULL;
		
}

ptrNode LocatElem(ptrNode head, int Elem)
{
	ptrNode p;
	p = head->next;
	if (EmptyList(head))
	{
		printf("\n空链表\n");
		return NULL;
	}

	while (p)
	{
		if (p->data != Elem)
			p = p->next;
		else
			break;
	}

	return p;
	
}

int LocatPos(ptrNode head, int Elem)
{
	int i = 0;
	ptrNode p;

	if (EmptyList(head))
	{
		printf("\n空链表\n");
		return -1;
	}

	p = head->next;

	while (p)
	{
		if (p->data != Elem)
		{
			p = p->next;
			i++;
		}
		else
			return i;
	}

	if (!p)
		return -1;
	
}

int InsertNode(ptrNode head, int position, int Elem)
/*return 0: insert failed; return 1: insert success*/
{
	int i = 0;
	ptrNode pre = head;
	ptrNode p;


	while (pre->next != NULL && i < position)
	{
		pre = pre->next;
		i++;
	}

	if (i != position)
	{
		printf("\n插入位置错误\n");
		return 0;
	}
	else
	{
		if ((p = (ptrNode)malloc(sizeof(ListNode))) == NULL)
			exit(-1);
		p->data = Elem;
		p->next = pre->next;
		pre->next = p;
		
		return 1;
	}

}

int DeleteNode(ptrNode head, int position)
/*return 0: delete failed; return 1: delete success*/
{
	int i = 0;
	ptrNode pre = head;
	ptrNode p;

	while (pre->next != NULL && pre->next->next != NULL && i < position-1)
	{
		pre = pre->next;
		i++;
	}

	if (i != position-1)
	{
		printf("\n删除位置错误\n");
		return 0;
	}
	
	p = pre->next;
	pre->next = p->next;
	free(p);

	return 1;
}

int ListLength(ptrNode head)
{
	int count = 0;
	ptrNode p = head;

	while (p->next)
	{
		p = p->next;
		count++;
	}

	return count;
}

void DestroyList(ptrNode head)
{
	ptrNode p = head;
	ptrNode q;

	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
}

void ShowList(ptrNode head)
{
	ptrNode p = head->next;

	while(p)
	{
		printf("%2d", p->data);
		p = p->next;
	}

	printf("\n");

}

int main()
{
	ptrNode L;
	
	InitList(&L);
	
	for (int i = 0; i < 10; i++)
		InsertNode(L,i,i);

	ShowList(L);

	printf("\n%d\n", ListLength(L));

	printf("\n%d\n",LocatPos(L,5));
		
	printf("\n%d\n", (GetElem(L,9))->data);
	
	DeleteNode(L,1); 

	ShowList(L);

	return 0;
}

