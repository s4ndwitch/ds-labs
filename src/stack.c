#include <stdlib.h>

#include "stack.h"

struct Stack *createStack(void) {
	struct Stack *newStack = (struct Stack *)malloc(sizeof(struct Stack) * 1);
	newStack->data = NULL;
	newStack->nextElement = NULL;
	return newStack;
}

struct Stack *top(struct Stack *stack) {
	while (stack->nextElement != NULL)
		stack = stack->nextElement;

	return stack;
}

struct Stack *pop(struct Stack *stack) {
	struct Stack *nextElement = stack->nextElement;
	while (nextElement != NULL) {
		stack = nextElement;
		nextElement = stack->nextElement;
	}

	stack->nextElement = NULL;
	return nextElement;
}

void push(struct Stack *stack, void *data) {
	if (stack->data == NULL) {
		stack->data = data;
		return;
	}

	if (stack->nextElement != NULL)
		stack = top(stack);

	struct Stack *newElement = createStack();
	newElement->data = data;
	stack->nextElement = newElement;
	return;
}

void removeElement(struct Stack *stack)	{
	if (stack == NULL)
		return;

	if (stack->data != NULL) {
		free(stack->data);
		return;
	}

    free(stack->data);
    return;
}
