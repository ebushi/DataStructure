// Stack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define StackSize 100

typedef int ElemType;

struct Stack
{
	ElemType stack[StackSize];
	int top;
};
 
typedef struct Stack seqStack;

void InitStack(seqStack *s)
{
	s->top = 0;
}

int PopStack(seqStack *s, ElemType *p)
{
	if (s->top == 0)
	{
		printf("Empty Stack\n");
		return 0;
	}
	else
	{
		*p = s->stack[s->top];
		s->top--;
		return 1;		
	}

}

int PushStack(seqStack *s, ElemType elem)
{
	if (s->top >= StackSize)
	{
		printf("Full Stack\n");
		return 0;
	}
	else
	{
		s->stack[s->top] = elem;
		s->top++;
		return 1;
	}

}

void ShowStack(seqStack *s)
{
	for (int i = 0; i < s->top; i++)
		printf("%d ", s->stack[i]);
	printf("\n");
}

int main()
{
	seqStack S;
	
	InitStack(&S);
	for (int i = 0; i < 10; i++)
		PushStack(&S,i);
	ShowStack(&S);
/*	
	ElemType *t;
	PopStack(&S, t);
	printf("%d ", *t);
*/
	
    return 0;
}

