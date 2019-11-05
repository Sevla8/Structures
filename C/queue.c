#include "queue.h"

Queue* add(Queue* queue, int elt) {
	Queue* new = (Queue*) malloc(sizeof(Queue));
	new->elt = elt;
	new->next = queue;
	return new;
}

Queue* remove(Queue* queue) {
	if (queue == NULL)
		return NULL;
	if (queue->next == NULL)
		return NULL;
	Queue* cur;
	for (cur = queue; cur->next->next != NULL; cur = cur->next) {}
	free(cur->next);
	cur->next = NULL;
	return queue;
}

int isEmpty(Queue* queue) {
	if (queue == NULL)
		return 1;
	return 0;
}

int last(Queue* queue) {
	if (queue != NULL) {
		for (; queue->next != NULL; queue = queue->next) {}
		return queue->elt;
	}
}

Queue* copy(Queue* queue) {
	if (queue == NULL)
		return NULL;
	Queue* new = NULL;
	while(!isEmpty(queue)) {
		new = add(new, last(queue));
		queue = remove(queue);
	}
	return new;
}

int peak(Queue* queue) {
	if (queue != NULL) {
		return queue->elt;
	}
}

Queue* depiler(Queue* queue) {
	if (queue == NULL)
		return NULL;
	Queue* temp = queue->next;
	free(queue);
	return temp;
}

Queue* inverse(Queue* queue) {
	if (queue == NULL)
		return NULL;
	Queue* new = NULL;
	while (!isEmpty(queue)) {
		new = add(new, peak(queue));
		queue = depiler(queue);
	}
	return new;
}
