#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct Stack Stack;
struct Stack {
	int elt;
	Stack* next;
};

Stack* add(Stack*, int);			// ajoute un element a la pile. retourne le dernier element de la pile
Stack* remove(Stack*);				// supprime le dernier element de la pile. retourne le dernier element de la pile
int isEmpty(Stack*);				// retourne 1 si la pile est vide 0 sinon
int peak(Stack*);					// retourne l element au sommet de la pile
Stack* copy(Stack*);				// retourne une copie de la pile
Stack* reverse(Stack*);				// rtourne une copie inverse de la pile

#endif
