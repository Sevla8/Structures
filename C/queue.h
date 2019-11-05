#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct Queue Queue;
struct Queue {
	int elt;
	Queue* next;
};

Queue* add(Queue*, int);					// ajoute $2 a la file. retourne le dernier element enfile
Queue* remove(Queue*);						// supprime le plus ancien element enfile
int isEmpty(Queue*);						// retourne 1 si la file est vide 0 sinon
int last(Queue*);							// retourne le dernier element de la file
Queue* copy(Queue*);						// retourne une copie de la file
int peak(Queue*);
Queue* depiler(Queue*);
Queue* reverse(Queue*);						// retourne une copie inverse de la pile

#endif
