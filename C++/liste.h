/*
	INF3105 - Structures de données et algorithmes
	UQAM / Département d'informatique

	Liste simplement chaînée.
*/

#if !defined(__LISTE_H__)
#define __LISTE_H__

#include <assert.h>

template <class T>
class Liste {
	public:
		class Iterateur;
		Liste();
		~Liste();
		bool estVide() const;
		void vider();
		bool operator==(const Liste&) const;
		const Liste& operator = (const Liste&);
		T& operator[] (const Iterateur&);
		const T& operator[] (const Iterateur&) const;	
		Iterateur inserer(const T&, const Iterateur&); // Les fonctions insérer retournent un Itérateur sur la position de l'objet inséré.
		Iterateur inserer_debut(const T&);
		Iterateur inserer_fin(const T&);
		Iterateur enlever(const Iterateur&); // La fonction enlever retourne un Iterateur sur la position suivante de l'objet enlevé.
		void enlever_debut();
		void enlever_fin();
		Iterateur debut() const; // Iterateur sur le début.
		Iterateur fin() const; // Iterateur sur la fin. La fin est la position suivante du dernier élément.
		Iterateur trouver(const T&) const; // Retourne un itérateur sur le premier élément cherchée. S'il n'existe pas, retourne fin().
	private:
		struct Cellule {
			Cellule(const T&, Cellule* s = nullptr);
			T contenu;
			Cellule* suivante;
		};
	public:
		struct Iterateur{
			public:
				Iterateur(const Iterateur&);
				Iterateur(const Liste&);
				operator bool() const; // retourne vrai si l'itérateur n'est pas rendu à la fin. Permet de faire while(iter)
				bool operator!() const; // retourne faux si l'itérateur n'est pas rendu à la fin
				bool operator==(const Iterateur&) const; // compare deux itérateur (deux "positions")
				bool operator!=(const Iterateur&) const; // !compare deux itérateur (deux "positions")
				Iterateur operator++(int);  // post-incrément (passe au suivant)
				Iterateur& operator++(); // pré-incrément (passe au suivant)
				//T& operator*(); // Pourquoi est-ce une mauvaise idée? Qu'arrive-t-il si la liste est constante?
				const T& operator*() const; // déférencement
				Iterateur& operator = (const Iterateur&); // affecte l'itérateur à la valeur d'un autre
			private:
				Cellule* precedente; // pointeur sur la Cellule précédente de la position courante
				const Liste& liste;  // référence sur la Liste associée à l'itérateur courant (pour des fins de robustesse).
	 		friend class Liste;
		};
	private:
		Liste(const Liste&);
		Cellule* derniere;
};

template <class T>
Liste<T>::Liste() {
	this->derniere = nullptr;
}

template <class T>
Liste<T>::~Liste() {
	vider();
}

template <class T>
bool Liste<T>::estVide() const {
	return this->derniere == nullptr;
}

template <class T>
void Liste<T>::vider() {
	while (!estVide()) {
		this->enlever_debut();
	}
}

template <class T>
const Liste<T>& Liste<T>::operator=(const Liste<T>& autre) {
	this->vider();
	Iterateur iter(autre.debut());
	while (iter) {
		this->inserer_fin(*iter);
		iter++;
	}
	return *this;
}

template <class T>
T& Liste<T>::operator[](const Iterateur& i) {
	assert(&i.liste == this);
	assert(i.precedente != nullptr);
	return i.precedente->suivante->contenu;
}

template <class T>
const T& Liste<T>::operator[](const Iterateur& i) const {
	assert(&i.liste == this);
	assert(i.precedente != nullptr);
	return i.precedente->suivante->contenu;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::inserer(const T& e, const Iterateur& i) {
	assert(this == &i.liste);
	Iterateur iter(i);
	if (this->derniere == nullptr) {
		this->derniere = new Cellule(e, nullptr);
		this->derniere->suivante = this->derniere;
		iter.precedente = this->derniere;
	}
	else if (iter.precedente == nullptr) {
		this->inserer_fin(e);
	}
	else {
		iter.precedente->suivante = new Cellule(e, iter.precedente->suivante);
		iter.precedente = iter.precedente->suivante;
	}
	return iter;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::inserer_debut(const T& e) {
	Iterateur iter(*this);
	if (this->derniere == nullptr) {
		this->derniere = new Cellule(e, nullptr);
		this->derniere->suivante = this->derniere;
		iter.precedente = this->derniere;
	}
	else
		iter.precedente->suivante = new Cellule(e, iter.precedente->suivante);
	return iter;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::inserer_fin(const T& e) {
	Iterateur iter(*this);
	if (this->derniere == nullptr) {
		this->derniere = new Cellule(e, nullptr);
		this->derniere->suivante = this->derniere;
		iter.precedente = this->derniere;
	}
	else {
		iter.precedente->suivante = new Cellule(e, iter.precedente->suivante);
		this->derniere = iter.precedente->suivante;
		iter.precedente = iter.precedente->suivante;
	}
	return iter;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::enlever(const Iterateur& i) {
	assert(this->derniere != nullptr);
	assert(&i.liste == this);
	Iterateur iter(i);
	if (this->derniere == this->derniere->suivante) {
		assert(iter.precedente = nullptr);
		delete this->derniere;
		this->derniere = nullptr;
		iter = nullptr;
	}
	else {
		Cellule tmp = iter.precedente->suivante;
		iter.precedente->suivante = iter.precedente->suivante->suivante;
		delete tmp;
		if (iter.precedente->suivante == this->derniere)
			iter.precedente = nullptr;
		else 
			iter.precedente = iter.precedente->suivante;
	}
	return iter;
}

template <class T>
void Liste<T>::enlever_debut(){
	if (this->derniere != nullptr) {
		if (this->derniere == this->derniere->suivante) {
			delete this->derniere;
			this->derniere = nullptr;
		}
		else {
			Cellule* tmp = this->derniere->suivante;
			this->derniere->suivante = this->derniere->suivante->suivante;
			delete tmp;
		}
	}
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::debut() const {
	return Iterateur(*this);
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::fin() const {
	Iterateur iter(*this);
	iter.precedente = nullptr;
	return iter;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::trouver(const T& e) const {
	Iterateur iter = this->debut();
	while (iter) {
		if (*iter == e)
			return iter;
		iter++;
	}
	return fin();
}

template <class T>
bool Liste<T>::operator==(const Liste& autre) const {
	if(this == &autre) 
		return true;
	Iterateur iter1 = this->debut();
	Iterateur iter2 = autre.debut();
	while (iter1 && iter2) {
		if (*iter1 != *iter2)
			return false;
		iter1++;
		iter2++;
	}
	if (iter1 || iter2)
		return false;
	return true;
}

//----------------------------------------------------//
template <class T>
Liste<T>::Iterateur::Iterateur(const Iterateur& i) : liste(i.liste) {
	this->precedente = i.precedente;
}

template <class T>
Liste<T>::Iterateur::Iterateur(const Liste<T>& l) : liste(l) {
	this->precedente = l.derniere;
}

template <class T>
bool Liste<T>::Iterateur::operator!() const {
	return this->precedente == nullptr;
}

template <class T>
Liste<T>::Iterateur::operator bool() const {
	return this->precedente != nullptr;
}

template <class T>
bool Liste<T>::Iterateur::operator==(const Iterateur& autre) const {
	return this->precedente == autre.precedente && &this->liste == &autre.liste;
}

template <class T>
bool Liste<T>::Iterateur::operator!=(const Iterateur& autre) const {
	return this->precedente != autre.precedente || &this->liste != &autre.liste;
}

template <class T>
typename Liste<T>::Iterateur& Liste<T>::Iterateur::operator++() {
	this->precedente = this->precedente->suivante;
	if (this->precedente == this->liste.derniere) 
		this->precedente = nullptr;
	return *this;
}

template <class T>
typename Liste<T>::Iterateur Liste<T>::Iterateur::operator++(int) {
	Iterateur temp(*this);
	this->precedente = this->precedente->suivante;
	if (this->precedente == this->liste.derniere) 
		this->precedente = nullptr;
	return temp;
}

template <class T>
const T& Liste<T>::Iterateur::operator*() const {
	return liste[*this];
}

template <class T>
typename Liste<T>::Iterateur& Liste<T>::Iterateur::operator=(const Iterateur& autre) {
	assert(&this->liste == &autre.liste);
	this->precedente = autre.precedente;
	return *this;
}

template <class T>
Liste<T>::Cellule::Cellule(const T& e, Cellule* c) : suivante(c) {
	this->contenu = e;
}

#endif
