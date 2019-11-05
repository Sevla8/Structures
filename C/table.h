#ifndef TABLE_H
#define TABLE_H

void init(int tab[], int taille, int nb);			// initialise les cases de tab a nb
int count(int tab[], int taille);					// renvoie le nombre de cases de tab non nulles
int max1(int a, int b);
int max(int tab[], int taille);						// renvoie le max de tab
void inverse(int tab[], int taille);				// inverse les elements de tab
int egal(int a, int b);
int count(int tab[], int taille);					// renvoie le nombre d'elements distincts de tab
void move(int tab[], int taille, int a, int b);		// insere l'element a la position b a la position a en decalant les autres elements
void sortSign(int tab[], int taille);				// place les elements negatifs au debut, les elements positifs a la fin
void change(int tab[], int taille, int i, int j);	// echange de place les elements en i et j
void sort(int tab[], int taille);					// trie le tableau par ordre croissant

#endif
