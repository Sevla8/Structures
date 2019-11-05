#include "string.h"

int strlength(char* str){
	int taille = 0;
	for(int i = 0; str[i] != '\0'; i = i+1){
		taille = taille+1;
	}
	return taille;
}

int strequals(char* str1, char* str2){
	if (strlength(str1) != strlength(str2))
		return 0;
	else {
		for(int i = 0; str1[i] != '\0'; i = i+1){
			if (str1[i] != str2[i])
				return 0;
		}
		return 1;
	}
}

int startswith(char* str1, char* str2){
	if (strlength(str1) < strlength(str2))
		return 0;
	else {
		for (int i = 0; str2[i] != '\0'; i = i+1){
			if (str1[i] != str2[i])
				return 0;
		}
		return 1;
	}
}

int contains(char* str1, char* str2){
	if (strlength(str1) < strlength(str2))
		return 0;
	else if (strlength(str2) == 0)
		return 1;
	else {
		for (int i = 0; i < strlength(str1); i = i+1){
			if (startswith(str1+i, str2) == 1)
					return 1;
			}
		return 0;
	}
}

char* removeFirst(char* str, int n){
	if (n >= strlength(str)){

		char* tab = malloc(sizeof(char));
		tab[0] = '\0';

		return tab;
	}
	else {
		char* tab = (char*) malloc(sizeof(char) * (strlength(str) - n + 1));
		for (int i = 0; i < strlength(str) - n; i = i+1)
			tab[i] = str[n+i];
		tab[strlength(str) - n] = '\0';
		//printf("%s\n", tab);
		return tab;
	}
}

char* removeLast(char* str, int n){
	if (n >= strlength(str)){
		char* tab = malloc(sizeof(char));
		tab[0] = '\0';
		return tab;
	}
	else {
		char* tab = (char*) malloc(sizeof(char) * (strlength(str) - n + 1));
		for (int i = 0; i < strlength(str) - n; i = i+1)
			tab[i] = str[i];
		tab[strlength(str) - n] = '\0';
		return tab;
	}
}

int strtoint(char* str, int* error){
	if (strlength(str) != 0 && str[0] >= '0' && str[0] <= '9'){
		*error = 0;
		int x = 0;
		for (int i = 0; str[i] >= '0' && str[i] <= '9' && i < strlength(str); i = i+1){
			x = x * 10 + (str[i]-48);
		}
		return x;
	}
	else
		*error = 1;

	return 0;
}

char* inttostr(int nb){
	if (nb == 0){
		char* tab = (char*) malloc(sizeof(char) * 2);
		tab[0] = '0'; tab[1] = '\0';
		return tab;
	}
	else if (nb > 0){
		int cp = nb;
		int l = 0;
		while (cp != 0){
			cp = cp / 10;
			l = l+1;
		}
		cp = nb;
		char* tab = (char*) malloc(sizeof(char) * (l + 1));
		for (int i = 0; i < l; i = i+1){
			tab[l-1-i] = cp % 10 + 48;
			cp = cp / 10;
		}
		tab[l] = '\0';
		return tab;
	}
	else {
		int cp = -nb;
		int l = 0;
		while (cp != 0){
			cp = cp / 10;
			l = l+1;
		}
		cp = -nb;
		char* tab = (char*) malloc(sizeof(char) * (l + 2));
		for (int i = 0; i < l; i = i+1){
			tab[l-i] = cp % 10 + 48;
			cp = cp / 10;
		}
		tab[0] = '-';
		tab[l+1] = '\0';
		return tab;
	}
}

char* strcat(const char* str1, const char* str2){
	int l1 = strlength(str1);
	int l2 = strlength(str2);
	char* tab = (char*) malloc(sizeof(char) * (l1 + l2 + 1));
	for (int i = 0; i < l1; i = i+1){
		tab[i] = str1[i];
	}
	for (int i = 0; i <l2; i = i+1){
		tab[l1+i] = str2[i];
	}
	tab[l1+l2] = '\0';
	return tab;
}

int howmanydelim(char* str, char delim){
	int x = 0;
	int length = strlength(str);
	for (int i = 0; i < length; i = i+1){
		if (str[i] == delim)
			x = x+1;
	}
	return x;
}

char** split(char* str, char delim, int* nb){
	int nbdelim = howmanydelim(str, delim);
	int length = strlength(str);

	char**  pere = (char**) malloc(sizeof(char*)*(nbdelim+1));

	if (nbdelim == 0)
		*pere = str;

	else {
		int i = 0;
		int z = 0;
		int temp = 0;
		while (i < length) {
			while (str[i] != delim && i < length){
				i = i+1;
			}
			char*  fils = (char*) malloc(sizeof(char)*(i-temp+1));
			int k = temp;
			int j = 0;
			while (k < i) {
				fils[j] = str[k];
				j = j+1;
				k = k+1;
			}
			fils[j] = '\0';
			*(pere+z) = fils;
			z = z+1;
			i = i+1;
			temp = i;
		}
		return pere;
	}
}
