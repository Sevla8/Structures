#ifndef STRING_H
#define STRING_H

#include <stdlib.h>

int strlength(char*);					// renvoie la taille de $1
int strequals(char*, char*);			// renvoie 1 si $1 et $2 sont identiques 0 sinon
int startswith(char*, char*);			// renvoie 1 si $1 commence par $2 0 sinon
int contains(char*, char*);				// renvoie 1 si $2 est contenue dans $1 0 sinon
char* removeFirst(char*, int);			// renvoie une chaine identique a $1 avec les $2 premiers characters en moins
char* removeLast(char*, int);			// renvoie une chaine identique a $1 avec les $2 derniers characters en moins
int strtoint(char*, int*);				// renvoie une chaine correspondant a $1 convertie en entier. si erreur met $2 a 1
char* inttostr(int);					// renvoie une chaine correspondant a $1 convertit en chaine de character
char* strcat(const char*, const char*);	// renvoie une chaine qui est la concatenation de $1 et $2
int howmanydelim(char*, char);
char** split(char*, char, int*);		// renvoie un tableau de chaines correspondantes a $1 decoupe par $2. met $3 au nombre de decoupages

#endif
