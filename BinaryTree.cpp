// BinaryTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

struct Node
{
	char data;
	struct Node *lchild, *rchild;
};

typedef struct Node TreeNode;
typedef struct Node* BiTree;

void InitBiTree(BiTree *T)
{
	*T = NULL;
}

void DestroyBiTree(BiTree *T)
{
	if (*T)
	{
		if ((*T)->lchild)
			DestroyBiTree(&((*T)->lchild));
		if ((*T)->rchild)
			DestroyBiTree(&((*T)->rchild));

		free(*T);
		*T = NULL;
	}
}

void CreatBiTree(BiTree *T)
{
	char data;
	scanf("%c", &data);

	if (data == '#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(TreeNode));
		if (!(*T))
			exit(-1);
		(*T)->data = data;
		CreatBiTree(&((*T)->lchild));
		CreatBiTree(&((*T)->lchild));
	}
}

int InsertLeftChild(BiTree p, BiTree c)
{

}

int main()
{
    return 0;
}

