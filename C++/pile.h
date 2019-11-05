/*
	INF3105 - Structures de données et algorithmes
	UQAM / Département d'informatique
*/

#ifndef __PILE_H__
#define __PILE_H__

template <typename T>
class Pile {
	public:
		Pile();
		Pile(const Pile<T>&);
		~Pile();
		const T& sommetPile() const;
		void empiler(const T&);
		void depiler(T&);
		T depiler();
		bool vide() const;
		void vider();
		Pile<T>& operator=(const Pile<T>&);
	private:
		struct Cellule {
			Cellule(const T&, Cellule* c = nullptr);
			T contenu;
			Cellule* suivante;
		};
		Cellule* sommet;

	friend bool operator==(const Pile<T>& pile1, const Pile<T>& pile2) {
	Cellule* cell1 = pile1.sommet;
	Cellule* cell2 = pile2.sommet;
	while (cell1 != nullptr && cell2 != nullptr) {
		if (cell1->contenu == cell2->contenu) {
			cell1 = cell1->suivante;
			cell2 = cell2->suivante;
		}
		else
			return false;
	}
	if (cell1 == nullptr && cell2 == nullptr)
		return true;
	return false;
}
};

#include "assert.h"

template <class T>
Pile<T>::Pile() : sommet(nullptr) {}

template <class T>
Pile<T>::Pile(const Pile<T>& autre) {
	Cellule** sommet_ptr = &this->sommet;
	Cellule* cell = autre.sommet;
	while (cell != nullptr) {
		*sommet_ptr = new Cellule(cell->contenu, nullptr);
		sommet_ptr = &((*sommet_ptr)->suivante);
		cell = cell->suivante;
	}
}

template <class T>
Pile<T>::~Pile() {
	vider();
}

template <class T>
const T& Pile<T>::sommetPile() const {
	assert(this->sommet != nullptr);
	return this->sommet->contenu;
}

template <class T>
void Pile<T>::empiler(const T& element) {
	this->sommet = new Cellule(element, this->sommet);
	assert(this->sommet != nullptr);
}

template <class T>
void Pile<T>::depiler(T& element) {
	assert(this->sommet != nullptr);
	element = this->sommet->contenu;
	Cellule* cell = this->sommet;
	this->sommet = this->sommet->suivante;
	delete cell;
}

template <class T>
T Pile<T>::depiler() {
	assert(this->sommet != nullptr);
	T element = this->sommet->contenu;
	Cellule* cell = this->sommet;
	this->sommet = this->sommet->suivante;
	delete cell;
	return element;
}

template <class T>
bool Pile<T>::vide() const {
	return sommet == nullptr;
}

template <class T>
void Pile<T>::vider() {
	while(!vide())
		depiler();  
}

template <class T>
Pile<T>& Pile<T>::operator=(const Pile<T>& autre) {
	if (this == &autre)
		return *this;

	Cellule** sommet_ptr = &this->sommet;
	Cellule* cell = autre.sommet;
	while (cell != nullptr || *sommet_ptr != nullptr) {
		if (*sommet_ptr == nullptr) {
			*sommet_ptr = new Cellule(cell->contenu, nullptr);
			sommet_ptr = &((*sommet_ptr)->suivante);
			cell = cell->suivante;
		}
		else if (cell == nullptr) {
			Cellule* tmp = *sommet_ptr;
			*sommet_ptr = (*sommet_ptr)->suivante;
			delete tmp;
		}
		else {
			(*sommet_ptr)->contenu = cell->contenu;
			sommet_ptr = &((*sommet_ptr)->suivante);
			cell = cell->suivante;
		}
	}
	return *this;
}

template <class T>
Pile<T>::Cellule::Cellule(const T& e, Cellule* c) : contenu(e), suivante(c) {}

#endif
