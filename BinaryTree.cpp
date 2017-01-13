// BinaryTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define MaxSize 20

struct Node
{
	char data;
	struct Node *lchild, *rchild;
};

typedef struct Node TreeNode;
typedef struct Node* BiTree;

struct Queue
{
	char Node[MaxSize];
	int front, rear;
};

typedef struct Queue NodeQue;

void InitQueue(NodeQue *NQ)
/*��ʼ������*/
{
	NQ->front = NQ->rear = 0;
}

int EmptyQueue(NodeQue *NQ)
/*�ж������Ƿ�Ϊ��*/
{
	if (NQ->front == NQ->rear)
	{
		printf("EMPTY Queue\n");
		return 1;
	}
	return 0;
}

int FullQueue(NodeQue *NQ)
/*�ж������Ƿ�����*/
{
	if (NQ->rear >= MaxSize)
	{
		printf("FULL Queue\n");
		return 1;
	}
	return 0;
}

int EnQueue(NodeQue *NQ, BiTree T)
/*���*/
{
	if (FullQueue(NQ))
		return 0;
	else
	{
		NQ->Node[NQ->rear] = T->data;
		NQ->rear++;
		return 1;
	}		
}

int DeQueue(NodeQue *NQ, char *p)
/*����*/
{
	if (EmptyQueue(NQ))
		return 0;
	else
	{
		*p = NQ->Node[NQ->front];
		NQ->front++;
		return 1;
	}
}

void InitBiTree(BiTree T)
/*��ʼ��������*/
{
	T->lchild = T->rchild = NULL;
}

void CreatBiTree(BiTree T)
/*����������*/
{
	char ch;
	scanf("%c", &ch);

	if (ch == '^')
		T = NULL;
	else
	{
		T = (BiTree)malloc(sizeof(TreeNode));
		if (!T)
			exit(-1);
		T->data = ch;
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
	}
}


void DestroyBiTree(BiTree T)
/*���ٶ�����*/
{
	if (T)
	{
		if (T->lchild)
			DestroyBiTree(T->lchild);
		if (T->rchild)
			DestroyBiTree(T->rchild);

		free(T);
		T = NULL;
	}
}


void PreOrderTraversal(BiTree T)
/*�������*/
{
	if (T)
	{
		printf("%c ", T->data);
		PreOrderTraversal(T->lchild);
		PreOrderTraversal(T->rchild);
	}
}

void InOrderTraversal(BiTree T)
/*�������*/
{
	if (T)
	{
		InOrderTraversal(T->lchild);
		printf("%c ", T->data);
		InOrderTraversal(T->rchild);
	}
}

void PostOrderTraversal(BiTree T)
/*�������*/
{
	if (T)
	{
		PostOrderTraversal(T->lchild);
		PostOrderTraversal(T->rchild);
		printf("%c ", T->data);
	}
}

void LevelOrderTraversal(BiTree T)
/*�������*/
{
	NodeQue NQ;
	InitQueue(&NQ);
	char *p;

	if (T)
	{
		EnQueue(&NQ, T);

		while (!EmptyQueue(&NQ))
		{
			DeQueue(&NQ, p);
			printf("%c ", *p);
			if (T->lchild)
				EnQueue(&NQ, T->lchild);
			if (T->rchild)
				EnQueue(&NQ, T->rchild);
		}
	}
}

int InsertLeftChild(BiTree p, BiTree c)
/*�����*/
{
	if (p)
	{
		c->rchild = p->lchild;
		p->lchild = c;
		return 1;
	}
	return 0;
}

int InsertRightChild(BiTree p, BiTree c)
/*�Ҳ���*/
{
	if (p)
	{
		c->rchild = p->rchild;
		p->rchild = c;
		return 1;
	}
	return 0;
}

BiTree Point(BiTree T, char e)
/*�������е�Ԫ��e��������ָ��*/
{
	NodeQue NQ;
	InitQueue(&NQ);
	char *p;

	if (T)
	{
		EnQueue(&NQ, T);

		while (!EmptyQueue(&NQ))
		{
			DeQueue(&NQ, p);
			if (*p == e)
			{
				printf("%c ", *p);
				return T;
			}

			if (T->lchild)
				EnQueue(&NQ, T->lchild);
			if (T->rchild)
				EnQueue(&NQ, T->rchild);
		}
	}
	return NULL;
}

char LeftChild(BiTree T, char e)
/*���ҽڵ�Ԫ��e�����ӽڵ�ֵ*/
{
	BiTree p;
	p = Point(T, e);

	if (p && p->lchild)
		return p->lchild->data;
	return '^';
		
}

char RightChild(BiTree T, char e)
/*���ҽڵ�Ԫ��e���Һ��ӽڵ�ֵ*/
{
	BiTree p;
	p = Point(T, e);

	if (p && p->rchild)
		return p->rchild->data;
	return '^';
}

int DeleteLeftTree(BiTree p)
/*ɾ��pָ��ڵ��������*/
{
	if (p)
	{
		DestroyBiTree(p->lchild);
		return 1;
	}
	return 0;
}

int DeleteRightTree(BiTree p)
/*ɾ��pָ��ڵ��������*/
{
	if (p)
	{
		DestroyBiTree(p->rchild);
		return 1;
	}
	return 0;
}

int main()
{
    return 0;
}