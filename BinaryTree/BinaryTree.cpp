// BinaryTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "priorityQue.h"
#include <time.h>



struct Tree
{
	char data;
	struct Tree *lchild, *rchild;
};


void init(struct Tree **tree) {
	*tree = NULL;
}


//init the stack
struct Stack stack;
struct Queue que;
struct Node  *priQue;



struct Tree* createNode(char n) {
	struct Tree *node;
	node = (struct Tree *)malloc(sizeof(struct Tree));
	node->data = n;
	node->lchild = NULL;
	node->rchild = NULL;
	return node;
}

int insertNode(struct Tree **treePtr, char temp) {
	// no tree pointer
	if (treePtr == NULL) {
		printf("no tree ptr\n");
		return 0;
	}
	//tree pointer, but null
	if (*treePtr == NULL) {
		*treePtr = createNode(temp);
		return 1;
	}
	//tree exists
	if ((*treePtr)->data > temp) {
		insertNode(&(*treePtr)->lchild, temp);
		return 1;
	}
	else {
		insertNode(&(*treePtr)->rchild, temp);
		return 1;
	}
}


void createTree(struct Tree **treeNode) {
	char nodeData;
	printf("input char:\n");
	scanf_s("%c",&nodeData, 1);

	if (nodeData == '^') {
		*treeNode = NULL;
	}
	else{
		*treeNode = (struct Tree *)malloc(sizeof(struct Tree));
		(*treeNode)->data = nodeData;
		createTree(&(*treeNode)->lchild);
		createTree(&(*treeNode)->rchild);
	}
}


void preTraverse(struct Tree *tree) {
	//pre order traverse
	if (tree != NULL) {
		printf("%c ", tree->data);
		preTraverse(tree->lchild);
		preTraverse(tree->rchild);
	}
}

void inTraverse(struct Tree *tree) {
	// in order traverse
	if (tree != NULL) {
		inTraverse(tree->lchild);
		printf("%c ", tree->data);
		inTraverse(tree->rchild);
	}
}

void postTraverse(struct Tree *tree) {
	//post order traverse
	if (tree != NULL) {
		postTraverse(tree->lchild);
		postTraverse(tree->rchild);
		printf("%c ", tree->data);
	}
}


void test1() {
	struct Tree *tree;
	init(&tree);
	createTree(&tree);
	printf("pre  order traverse: ");
	preTraverse(tree);
	preTraverse(NULL);
	printf("\n");
	printf("in   order traverse: ");
	inTraverse(tree);
	printf("\n");
	printf("post order traverse: ");
	postTraverse(tree);
	printf("\n");

}


//求树的高度
int height(struct Tree* treePtr) {
	int i = 0;
		if (treePtr == NULL) {
		return 0;
	}
	int a = height(treePtr->lchild);
	int b = height(treePtr->rchild);
	if (a > b)
		return a + 1;
	else
		return b + 1;
	
}

int getHeight(struct Tree* treePtr) {

	if (treePtr == NULL) {
		return 0;
	}
	int a = height(treePtr->lchild);
	int b = height(treePtr->rchild);
	if (a > b)
		return a + 1;
	else
		return b + 1;

}


int getStackTop(struct Stack *stack, struct Tree **p) {
	//return 0: lflag = 0 rflag = 0 
	//return 1: lflag = 1 rflag = 0
	//return 2: lflag = 1 rflag = 1

	*p = stack->elem[stack->top].tree;
	if (stack->elem[stack->top].lflag == 0 && stack->elem[stack->top].rflag == 0)
		return 0;
	if (stack->elem[stack->top].lflag == 1 && stack->elem[stack->top].rflag == 0)
		return 1;
	if (stack->elem[stack->top].lflag == 1 && stack->elem[stack->top].rflag == 1)
		return 2;
	return -1;//impossible
}



void pushAndPrint(struct Stack *stack, struct Tree *tree) {
	if (tree == NULL)
		return;
	if (stack->top < STACKMAX - 1) {
		stack->top++;
		stack->elem[stack->top].tree = tree;
		stack->elem[stack->top].lflag = 0;
		stack->elem[stack->top].rflag = 0;
		
	}
	printf("%c ", tree->data); // tree is null??

}

void preTraverseByStack(struct Tree *tree) {
	
	if (tree == NULL)
	{
		printf("empty tree\n");
		return;
	}
	//使用非递归方式实现先序遍历
	/*
	处理流程：
	用栈保存从root到当前节点的路径上所有节点。
	栈底为root，栈顶为当前节点。
	栈中每一个元素保存该节点被处理的进展情况
	入栈含义：处理到该节点，并且要被打印。
	出栈：该节点的所有子孙都被处理完毕。
	栈顶节点含义：本身已被打印，但其后继还未探索完毕。
	初始化栈：根节点入栈
	结束条件：栈为空
	*/
	//初始化，起点

	pushAndPrint(&stack, tree); //print函数必须分析栈顶的祖先情况，确定前边的标识

	while (stack.top >= 0/*bug?!!!!!!!!!!*/) {
		//取到栈顶元素，分析栈顶元素
		struct Tree *temp;
		//getTop();
		//判断后继的处理情况
		//如果左子节点未被处理：print and push 左子节点，修改自身标识，continue
		//如果左done，右未：print and push 右子节点，修改自身标识，continue
		//如果左done，右done：pop，continue
		if (getStackTop(&stack, &temp) == 0) {
			stack.elem[stack.top].lflag = 1;
			pushAndPrint(&stack, temp->lchild);
			continue;
		}

		if (getStackTop(&stack, &temp) == 1) {
			stack.elem[stack.top].rflag = 1;
			pushAndPrint(&stack, temp->rchild);
			continue;
		}

		if (getStackTop(&stack, &temp) == 2) {
			pop(&stack);
			continue;
		}
	}

}

//层序遍历
//如果队列不为空，出队并把出队节点的孩子节点入队
void levelTraverse(struct Tree *tree) {
	if (tree == NULL) {
		printf("empty tree\n");
		return;
	}
	struct Tree *temp = NULL;
	enQue(&que,tree);//enqueue the root node
	while (que.front <= que.tail) {
		deQue(&que, &temp);
		if (temp == NULL) {
			continue;
		}
		enQue(&que, temp->lchild);
		enQue(&que, temp->rchild);
		printf("%c ", temp->data);
	}
}

//最佳优先搜索
 void bestFirstSearch(struct Tree *tree){
	if (tree == NULL) {
		printf("empty tree\n");
		return;
	}
	struct Tree *temp = NULL;
	initPriQue(&priQue);
	insertAtOrder(priQue, creatNode(tree));
	while (priQue->next != NULL) {
		dePriQue(priQue, &temp);
		if (temp == NULL) {
			continue;
		}
		printf("%c ", temp->data);
		insertAtOrder(priQue, creatNode(temp->lchild));
		insertAtOrder(priQue, creatNode(temp->rchild));
	}
}


//测试节点插入函数
void testinsertNode() {
	
	struct Tree *ptree = NULL;
	insertNode(&ptree, 'e');
//	preTraverse(ptree);
//	printf("\n");
	insertNode(&ptree, 'a');
//	preTraverse(ptree);
//	printf("\n");
	insertNode(&ptree, 'd');
//	preTraverse(ptree);
//	printf("\n");
	insertNode(&ptree, 'b');
//	preTraverse(ptree);
//	printf("\n");
	insertNode(&ptree, 'h');
//	preTraverse(ptree);
//	printf("\n");
	insertNode(&ptree, 'g');
//	preTraverse(ptree);
//	printf("\n");
	insertNode(&ptree, 'f');
//	preTraverse(ptree);
//	printf("\n");
	inTraverse(ptree);
	printf("\n");
//	postTraverse(ptree);
//	printf("\n");

	printf("%d", height(ptree));

}

/*void fn(int* k) {
	printf("*k=%d\n", *k);
	printf("&k=%d\n", &k);
	int kk = 8;
	k = &kk;

}*/

/*void testargs() {
	int j = 9;
	int* i;
	i = &j;
	printf("*i=%d\n", *i);
	printf("&i=%d\n", &i);
	fn(i);

}
*/

//测试高度函数
void testheight() {
	struct Tree *ptree = NULL;
	insertNode(&ptree, 'b');
	insertNode(&ptree, 'a');
	insertNode(&ptree, 'c');
	inTraverse(ptree);
	int h = height(ptree);
}

/*
int computeJiecheng(int n) {
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;
	return computeJiecheng(n-1)*n;
}
*/


//镜像反转一棵树
void mirrorTree(struct Tree* tree) {
	struct Tree *temp;
	if (tree == NULL) {
		return;
	}

	mirrorTree(tree->lchild);
	mirrorTree(tree->rchild);
	temp = tree->lchild;
	tree->lchild = tree->rchild;
	tree->rchild = temp;
	return;
}
//测试镜像反转一棵树函数
void testmirrorTree() {
	struct Tree *ptree = NULL;
	insertNode(&ptree, 'b');
	insertNode(&ptree, 'a');
	insertNode(&ptree, 'c');
	insertNode(&ptree, 'd');
	insertNode(&ptree, 'e');
	insertNode(&ptree, 'f');
	insertNode(&ptree, 'g');
	insertNode(&ptree, 'h');
	insertNode(&ptree, 'i');
	inTraverse(ptree);
	printf("\n");
	mirrorTree(ptree);
	inTraverse(ptree);
	printf("\n");
}

//按照树状结构打印一棵树
void printTree(struct Tree *tree, int level) {
	
	if (tree == NULL) {
		return;
	}
	
	if (level == 0) {
		printf("%c\n", tree->data);
	}
	else {
		printf("|");
		for (int i = 0; i < level - 1;i++) {
			printf("\t");
		}
		printf("----%c\n", tree->data);

	}
	level++;
	printTree(tree->lchild,level);
	printTree(tree->rchild,level);
}

//测试树状输出一棵树函数
void testprintTree() {
	struct Tree *ptree = NULL;
	insertNode(&ptree, 'e');
	insertNode(&ptree, 'a');
	insertNode(&ptree, 'c');
	insertNode(&ptree, 'd');
	insertNode(&ptree, 'b');
	insertNode(&ptree, 'i');
	insertNode(&ptree, 'f');
	insertNode(&ptree, 'g');
	insertNode(&ptree, 'h');
	inTraverse(ptree);
	printf("\n");
	preTraverse(ptree);
	printf("\n");
	printTree(ptree,0);
}
	
//测试先序遍历的非递归实现函数	
void testpreTraverseByStack() {
	struct Tree *ptree = NULL;
	insertNode(&ptree, 'd');
	insertNode(&ptree, 'b');
	insertNode(&ptree, 'f');
	insertNode(&ptree, 'a');
	insertNode(&ptree, 'c');
	insertNode(&ptree, 'e');
	insertNode(&ptree, 'g');
	preTraverse(ptree);
	printf("\n");
	printTree(ptree, 0);
	printf("\n");
	preTraverseByStack(ptree);
}

//测试层序遍历函数
void testlevelTraverse() {
	struct Tree *ptree = NULL;
	insertNode(&ptree, 'd');
	insertNode(&ptree, 'b');
	insertNode(&ptree, 'f');
	insertNode(&ptree, 'a');
	insertNode(&ptree, 'c');
	insertNode(&ptree, 'e');
	insertNode(&ptree, 'g');
	printf("Pre Order Traverse:\n");
	preTraverse(ptree);
	printf("\n\n");
	printf("Tree Structure:\n");
	printTree(ptree, 0);
	printf("\n\n");
	printf("Level Traverse:\n");
	levelTraverse(ptree);
	printf("\n");
}


//测试层序遍历的边界条件，即当树为空时
void testlevelTraverse1() {
	struct Tree *ptree = NULL;
	printf("Level Traverse:\n");
	levelTraverse(ptree);
	printf("\n");
}

//测试最佳优先搜索
void testBestFirstSearch() {
	struct Tree *ptree = NULL;
	insertNode(&ptree, 'd');
	insertNode(&ptree, 'b');
	insertNode(&ptree, 'f');
	insertNode(&ptree, 'a');
	insertNode(&ptree, 'c');
	insertNode(&ptree, 'e');
	insertNode(&ptree, 'g');
	printf("Pre Order Traverse:\n");
	preTraverse(ptree);
	printf("\n\n");
	printf("Tree Structure:\n");
	printTree(ptree, 0);
	printf("\n\n");
	printf("bestFirstSearch:\n");
	bestFirstSearch(ptree);
	printf("\n");

}

int main()
{
	//test1();
	//testargs();
	//testinsertNode();
	//testheight();
	//printf("├└ ─");
	//int k = computeJiecheng(2);
	//testmirrorTree();
	//testprintTree();
	//testpreTraverseByStack();
	//testlevelTraverse();
	//testlevelTraverse1();
	srand(time(0));
	testBestFirstSearch();
	

	return 0;
	
}

