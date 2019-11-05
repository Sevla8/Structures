#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>

// NULL <---> head <---> ... <---> tail <---> NULL

typedef struct node node;
struct node {
	int elt;
	node* next;
	node* prev;
};

node* addHead(node*, int); 				// ajoute un noeud en tete. retourne la tete
node* addTail(node*, int);				// ajoute un noeud en queue. retourne la tete
node* insert(node*, int, int);			// insere un noeud en $3. retourne la tete
void display(node*);					// affiche la liste de noeuds
void reverse_display(node*); 			// affiche la liste inverse de noeuds
node* deleteHead(node*); 				// supprime la tete. retourne la nouvelle tete
node* deleteTail(node*);				// supprime la queue. retourne la tete
node* delete(node*, int); 				// supprime le noeud $2. retourne la tete
int count(node*, int);					// retourne le nombre de noeuds
int firstOccurence(node*, int); 		// retourne la position de la premiere occurence de $2
node* deleteAll(node*, int);			// supprime les noeuds ayant la valeur $2. retourne la tete
node* sort(node*); 						// trie la liste. retourne la tete

#endif
