#include "node.h"

node* addHead(node* head, int elt) {
	node* new = (node*) malloc(sizeof(node));
	new->elt = elt;
	new->next = head;
	new->prev = NULL;
	if (head != NULL) {
		head->prev = new;
	}
	return new;
}

node* addTail(node* head, int elt) {
	if (head == NULL) {
		return addHead(head, elt);
	}
	node* cur;
	for (cur = head; cur->next != NULL; cur = cur->next) {
	}
	node* new = (node*) malloc(sizeof(node));
	new->elt = elt;
	new->next = NULL;
	new->prev = cur;
	cur->next = new;
	if (cur == head) {
		return cur;
	}
	return head;
}

node* insert(node* head, int elt, int p) {
	if (head == NULL) {
		return addHead(head, elt);
	}
	if (p <= 0) {
		return addHead(head, elt);
	}
	node* cur; int i = 0;
	for (cur = head; cur->next != NULL && i < p-1; cur = cur->next) {
		i += 1;
	}
	if (cur->next == NULL) {
		return addTail(head, elt);
	}
	node* new = (node*) malloc(sizeof(node));
	node* tmp = cur->next;
	new->elt = elt;
	new->next = cur->next;
	new->prev = cur;
	cur->next = new;
	tmp->prev = new;
	return head;
}

void display(node* head) {
	if (head == NULL) {
		printf("[]\n");
	}
	else {
		printf("[");
		for (node* cur = head; cur != NULL; cur = cur->next) {
			printf("%d", cur->elt);
			if (cur->next != NULL) {
				printf(",");
			}
		}
		printf("]\n");
	}
}

void reverse_display(node* head) {
	if (head == NULL) {
		printf("[]\n");
	}
	else {
		node* cur0;
		for (cur0 = head; cur0->next != NULL; cur0 = cur0->next) {}
		printf("[");
		for (node* cur = cur0; cur != NULL; cur = cur->prev) {
			printf("%d", cur->elt);
			if (cur->prev != NULL) {
				printf(",");
			}
		}
		printf("]\n");
	}
}

node* deleteHead(node* head) {
	if (head != NULL) {
		node* tmp = head->next;
		if (tmp != NULL) {
			tmp->prev = NULL;
			free(head);
			return tmp;
		}
	}
	return NULL;
}

node* deleteTail(node* head) {
	if (head != NULL) {
		node* cur;
		for (cur = head; cur->next != NULL; cur = cur->next) {}
		node* tmp = cur->prev;
		if (tmp != NULL) {
			tmp->next = NULL;
			free(cur);
			return head;
		}
	}
	return NULL;
}

node* delete(node* head, int p) {
	if (head != NULL) {
		node* cur; int i = 0;
		for (cur = head; cur->next != NULL && i < p; cur = cur->next) {
			i += 1;
		}
		if (i == p) {
			if (cur->next == NULL) {
				return deleteTail(head);
			}
			if (cur->prev == NULL) {
				return deleteHead(head);
			}
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(cur);
		}
	}
	return head;
}

int count(node* head, int elt) {
	if (head == NULL) {
		return 0;
	}
	node* cur; int i = 0;
	for (cur = head; cur != NULL; cur = cur->next) {
		if (cur->elt == elt) {
			i += 1;
		}
	}
	return i;
}

int firstOccurence(node* head, int elt) {
	node* cur; int i = 0;
	for (cur = head; cur != NULL; cur = cur->next) {
		if (cur->elt == elt) {
			return i;
		}
		i += 1;
	}
	return -1;
}

node* deleteAll(node* head, int elt) {
	if (head != NULL) {
		int nb = count(head, elt);
		for (int i = 0; i < nb; i += 1){
			int x = firstOccurence(head, elt);
			head = delete(head, x);
		}
	}
	return head;
}

node* sort(node* head) {
	if (head == NULL) {
		return NULL;
	}
	for (node* cur1 = head; cur1 != NULL; cur1 = cur1->next) {
		for (node* cur2 = cur1; cur2 != NULL; cur2 = cur2->next) {
			if (cur1->elt > cur2->elt) {
				int tmp = cur1->elt;
				cur1->elt = cur2->elt;
				cur2->elt = tmp;
			}
		}
	}
	return head;
}
