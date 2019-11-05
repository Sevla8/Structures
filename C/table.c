#include "table.h"

void init(int tab[], int taille, int nb){
  int i;
  for (i=0; i<taille; i=i+1){
    tab[i] = nb;
  }
}

int count(int tab[], int taille){
  int i;
  int j = 0;
  for (i=0; i<taille; i=i+1){
    if (tab[i] != 0)
      j = j+1;
  }
  return j;
}

int max1(int a, int b){
  if (a >= b)
    return a;
  else
    return b;
}

int max(int tab[], int taille){
  int i;
  int j = 0;
  for (i=0; i<taille; i=i+1){
    j = max1(j, tab[i]);
  }
  return j;
}

void inverse(int tab[], int taille){
  int i;
  int x;
  for (i=0; i<taille/2; i=i+1){
    x = tab[i];
    tab[i] = tab[taille-i-1];
    tab[taille-i-1] = x;
  }
}

int egal(int a, int b){
  if (a == b)
    return 1;
  else
    return 0;
}

int count(int tab[], int taille){
  int i; int j;
  int x = 0;
  int y = taille;
  int temp;
  for (i=0; i<taille; i=i+1){
    for (j=i+1; j<taille; j=j+1){
      if (egal(tab[i], tab[j]))
	  x = x+1;
    }
    if (x != 0)
      y = y-1;
    x = 0;
  }
  return y;
}

void move(int tab[], int taille, int a, int b){
  int x = tab[b];
  if (a <= b && b < taille){
    int i;
    for (i=0; i<b-a ; i=i+1){
      tab[b-i] = tab[b-i-1];
    }

    tab[a] = x;
  }
}

void sortSign(int tab[], int taille){
  int i; int x = 0;
  for (i=0; i<taille; i=i+1){
    if (tab[i] < 0){
      move(tab, taille, 0+x, i);
      x = x+1;
    }
  }
}

void change(int tab[], int taille, int i, int j){
  int x = tab[i];
  tab[i] = tab[j];
  tab[j] = x;
}

void sort(int tab[], int taille){
  int i; int x = 0; int j;
  for (i=0; i<taille; i=i+1){
    for (j=i; j<taille; j=j+1){
      if (tab[i] > tab[j])
	       change(tab, taille, i, j);
    }
  }
}
