#include "stack.h"

Stack* add(Stack* stack, int elt) {
	Stack* new = (Stack*) malloc(sizeof(Stack));
	new->elt = elt;
	new->next = stack;
	return new;
}

Stack* remove(Stack* stack) {
	if (stack == NULL)
		return NULL;
	Stack* temp = stack->next;
	free(stack);
	return temp;
}

int isEmpty(Stack* stack) {
	if (stack == NULL)
		return 1;
	return 0;
}

int peak(Stack* stack) {
	if (stack != NULL) {
		return stack->elt;
	}
}

Stack* copy(Stack* stack) {
	if (stack == NULL)
		return NULL;
	Stack* temp = NULL;
	while(!isEmpty(stack)) {
		temp = add(temp, peak(stack));
		stack = remove(stack);
	}
	Stack* new = NULL;
	while(!isEmpty(temp)) {
		new = add(new, peak(temp));
		temp = remove(temp);

	}
	return new;
}

Stack* reverse(Stack* stack) {
	if (stack == NULL)
		return NULL;
	Stack* new = NULL;
	while(!isEmpty(stack)) {
		new = add(new, peak(stack));
		stack = remove(stack);
	}
	return new;
}
