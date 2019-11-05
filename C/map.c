#include "map.h"

int hash(char* str) {
	int hash = 0;
	for (int i = 0; str[i] != '\0'; i += 1)
		hash += str[i];
	return hash % 100;
}

void* get(void* tab, char* str) {
	return tab + hash(str);
}
