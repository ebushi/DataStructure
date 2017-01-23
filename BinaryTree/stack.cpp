#include "stdafx.h"
#include "stack.h"


//@deprecated
/*void initStack(struct Stack *stack) {
stack->top = -1;
}*/

void pop(struct Stack *stack) {
	if (stack->top >= 0)
	{
		stack->top--;
	}
}




