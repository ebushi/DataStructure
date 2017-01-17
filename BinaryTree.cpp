// BinaryTree.cpp : 定义控制台应用程序的入口点。
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
/*初始化队列*/
{
	NQ->front = NQ->rear = 0;
}

int EmptyQueue(NodeQue *NQ)
/*判定队列是否为空*/
{
	if (NQ->front == NQ->rear)
	{
		printf("EMPTY Queue\n");
		return 1;
	}
	return 0;
}

int FullQueue(NodeQue *NQ)
/*判定队列是否已满*/
{
	if (NQ->rear >= MaxSize)
	{
		printf("FULL Queue\n");
		return 1;
	}
	return 0;
}

int EnQueue(NodeQue *NQ, BiTree T)
/*入队*/
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

char DeQueue(NodeQue *NQ)
/*出队*/
{
	char e;
	if (EmptyQueue(NQ))
		return 0;
	else
	{
		e = NQ->Node[NQ->front];
		NQ->front++;
		return e;
	}
}

void InitBiTree(BiTree *T)
/*初始化二叉树*/
{
	*T = NULL;
}

void CreatBiTree(BiTree *T)
/*创建二叉树*/
{
	char ch;
	scanf_s("%c", &ch, sizeof(ch));

	if (ch == '^')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(TreeNode));
		if (!(*T))
			exit(-1);
		(*T)->data = ch;
		CreatBiTree(&((*T)->lchild));
		CreatBiTree(&((*T)->rchild));
	}
}


void DestroyBiTree(BiTree T)
/*销毁二叉树*/
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
/*先序遍历*/
{
	if (T)
	{
		printf("%c ", T->data);
		PreOrderTraversal(T->lchild);
		PreOrderTraversal(T->rchild);
	}
}

void InOrderTraversal(BiTree T)
/*中序遍历*/
{
	if (T)
	{
		InOrderTraversal(T->lchild);
		printf("%c ", T->data);
		InOrderTraversal(T->rchild);
	}
}

void PostOrderTraversal(BiTree T)
/*后序遍历*/
{
	if (T)
	{
		PostOrderTraversal(T->lchild);
		PostOrderTraversal(T->rchild);
		printf("%c ", T->data);
	}
}
/*
void LevelOrderTraversal(BiTree T)
{
	NodeQue NQ;
	BiTree T1;
	InitQueue(&NQ);

	
		EnQueue(&NQ, T);

		while (!EmptyQueue(&NQ))
		{
			T1 = Point(T, DeQueue(&NQ));
			printf("%c ",T1->data);
			if (T1->lchild)
			{
				EnQueue(&NQ, T1->lchild);
			}
				
			if (T1->rchild)
			{
				EnQueue(&NQ, T1->rchild);
			}				
		}
	
}
*/
BiTree Point(BiTree T, char e)
/*查找树中的元素e，返回其指针*/
{
	if (T)
	{
		if (T->data == 'e')
			return T;
		Point(T->lchild, 'e');
		Point(T->rchild, 'e');
	}
/*
	return NULL;
	NodeQue NQ;
	InitQueue(&NQ);
	char p;

	if (T)
	{
		EnQueue(&NQ, T);

		while (!EmptyQueue(&NQ))
		{
			p = DeQueue(&NQ);
			if (p == e)
			{
				printf("%c ", p);
				return T;
			}

			if (T->lchild)
				EnQueue(&NQ, T->lchild);
			if (T->rchild)
				EnQueue(&NQ, T->rchild);
		}
	}
	return NULL;
	*/
}

int InsertLeftChild(BiTree p, BiTree c)
/*左插入*/
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
/*右插入*/
{
	if (p)
	{
		c->rchild = p->rchild;
		p->rchild = c;
		return 1;
	}
	return 0;
}

char LeftChild(BiTree T, char e)
/*查找节点元素e的左孩子节点值*/
{
	BiTree p;
	p = Point(T, e);

	if (p && p->lchild)
		return p->lchild->data;
	return '^';		
}

char RightChild(BiTree T, char e)
/*查找节点元素e的右孩子节点值*/
{
	BiTree p;
	p = Point(T, e);

	if (p && p->rchild)
		return p->rchild->data;
	return '^';
}

int DeleteLeftTree(BiTree p)
/*删除p指向节点的左子树*/
{
	if (p)
	{
		DestroyBiTree(p->lchild);
		return 1;
	}
	return 0;
}

int DeleteRightTree(BiTree p)
/*删除p指向节点的右子树*/
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
	BiTree  T;
	InitBiTree(&T);
	CreatBiTree(&T);

	printf("\n前序遍历\n");
	PreOrderTraversal(T);

	printf("\n中序遍历\n");
	InOrderTraversal(T);

	printf("\n后序遍历\n");
	PostOrderTraversal(T);

//	printf("\n层序遍历\n");
//	LevelOrderTraversal(T);

	printf("%c\n", LeftChild(Point(T,'b'),'b'));
	
	
    return 0;
}