#pragma once
#define STACKMAX 128

struct StackElem {
	struct Tree *tree;
	int lflag;
	int rflag;
};

//store the ancestors of the current node
//store the path from the root to the current node
struct Stack {
	struct StackElem elem[STACKMAX];
	int top = -1;
};

void pop(struct Stack *stack);

