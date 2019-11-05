#include <iostream>
#include "tableau.h"

const int RUN = 32;

template <typename T>
void insertionSort(Tableau<T>& tab, int bottom, int top) {
	for (int i = bottom+1; i <= top; i += 1) {
		int tmp = tab[i];
		int j = i;
		while (j > bottom && tab[j-1] > tmp) {
			tab[j] = tab[j-1];
			j -= 1;
		}
		tab[j] = tmp;
	}
}

template <typename T>
void mergeSort(Tableau<T>& tab, int bottom, int top) {
	if (bottom < top) {
		int middle = bottom+(top-bottom)/2;
		mergeSort(tab, bottom, middle);
		mergeSort(tab, middle+1, top);
		merge(tab, bottom, top, middle);
	}
}

template <typename T>
void merge(Tableau<T>& tab, int bottom, int top, int middle) {
	int n1 = middle-bottom+1;
	int n2 = top-middle;
	int left[n1];
	int right[n2];
	for (int i = 0; i < n1; i += 1)
		left[i] = tab[bottom+i];
	for (int j = 0; j < n2; j += 1)
		right[j] = tab[middle+1+j];

	int i = 0, j = 0, k = bottom;
	while (i < n1 && j < n2) {
		if (left[i] <= right[j]) {
			tab[k] = left[i];
			i += 1;
		}
		else {
			tab[k] = right[j];
			j += 1;
		}
		k += 1;
	}
	while (i < n1) {
		tab[k] = left[i];
		i += 1;
		k += 1;
	}
	while (j < n2) {
		tab[k] = right[j];
		j += 1;
		k += 1;
	}
}

template <typename T>
void timSort(Tableau<T>& tab, int bottom, int top) {
	for (int i = bottom; i <= top; i += RUN)
		insertionSort(tab, i, i + RUN-1 < top ? i + RUN-1 : top);

	for (int size = RUN; size <= top; size *= 2) {
		for (int left = bottom; left <= top; left += 2*size) {
			int middle = left + size - 1; 
			int right = left+2*size < top ? left+2*size : top;
			merge(tab, left, right, middle); 
		} 
	} 
}

int main(int argc, const char *argv[]) {
	Tableau<int> tableau;
	tableau.ajouter(9);
	tableau.ajouter(789);
	tableau.ajouter(4);
	tableau.ajouter(8);
	tableau.ajouter(1);
	tableau.ajouter(47);
	tableau.ajouter(436);
	tableau.ajouter(94);
	tableau.ajouter(81);
	tableau.ajouter(23);
	tableau.ajouter(0);
	tableau.ajouter(14);
	tableau.ajouter(1453);
	tableau.ajouter(845);
	tableau.ajouter(79);
	tableau.ajouter(1534);
	tableau.ajouter(145);
	tableau.ajouter(32);
	tableau.ajouter(9);
	tableau.ajouter(845);

	timSort(tableau, 0, tableau.taille()-1);

	for (int i = 0; i < tableau.taille(); i += 1)
		std::cout << tableau[i] << "\t";
	std::cout << std::endl;

	return 0;
}
