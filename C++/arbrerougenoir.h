/*	UQAM / Département d'informatique
	INF3105 - Structures de données et algorithmes
	Squelette pour classe générique ArbreRougeNoir<T> pour le Lab9.
*/

#ifndef __ARBREROUGENOIR_H__
#define __ARBREROUGENOIR_H__

#include <cassert>
#include "pile.h"

template <class T>
class ArbreRougeNoir {
	public:
		ArbreRougeNoir();
		ArbreRougeNoir(const ArbreRougeNoir&);
		~ArbreRougeNoir();
		void inserer(const T&);
		void enlever(const T&);
		bool vide() const;
		int  hauteur() const;
		int taille() const;
		bool contient(const T&) const;
		int compter(const T& min, const T& max) const;
		void vider();
		class Iterateur;
		Iterateur debut() const;
		Iterateur fin() const;
		Iterateur rechercher(const T&) const;
		Iterateur rechercherEgalOuSuivant(const T&) const;
		Iterateur rechercherEgalOuPrecedent(const T&) const;
		const T& operator[](const Iterateur&) const;
		T& operator[](const Iterateur&);
		ArbreRougeNoir& operator=(const ArbreRougeNoir&);
		bool operator==(const ArbreRougeNoir<T>&) const;
		bool operator!=(const ArbreRougeNoir<T>&) const;
	private:
		struct Noeud{
			Noeud(const T&);
			T contenu;
			bool rouge;
			Noeud *gauche;
			Noeud *droite;
		};
		Noeud* racine;
		bool inserer(Noeud*&, const T&, Pile<Noeud*>*);
		void rotationGaucheDroite(Noeud*&);
		void rotationDroiteGauche(Noeud*&);
		void vider(Noeud*&);
		void copier(const Noeud*, Noeud*&) const;
		const T& max(Noeud*) const;
		bool enlever(Noeud*&, const T& e);
		int compter(const Noeud*, const T&, const T&) const;
		int taille(Noeud*) const;
		int hauteur(Noeud*) const;
	public:
		class Iterateur{
			public:
				Iterateur(const ArbreRougeNoir& a);
				Iterateur(const Iterateur& a);
				Iterateur(const ArbreRougeNoir& a, Noeud* c);
				operator bool() const;
				bool operator!() const;
				bool operator==(const Iterateur&) const;
				bool operator!=(const Iterateur&) const;
				const T& operator*() const;
				Iterateur& operator++();
				Iterateur operator++(int);
				Iterateur& operator=(const Iterateur&);
			private:
				const ArbreRougeNoir& arbre_associe;
				Noeud* courant;
				Pile<Noeud*> chemin;
			friend class ArbreRougeNoir;
		};
	friend std::ostream& operator<<(std::ostream& out, ArbreRougeNoir<T>& arbre) {
		for (ArbreRougeNoir<T>::Iterateur iter = arbre.debut(); iter; ++iter)
			out << *iter << std::endl;
		return out;
	}
};


//-----------------------------------------------------------------------------

template <class T>
ArbreRougeNoir<T>::Noeud::Noeud(const T& c) : contenu(c), rouge(true), gauche(NULL), droite(NULL) {}

template <class T>
ArbreRougeNoir<T>::ArbreRougeNoir() : racine(NULL) {}

template <class T>
ArbreRougeNoir<T>::ArbreRougeNoir(const ArbreRougeNoir<T>& autre) : racine(NULL) {
	this->copier(autre.racine, this->racine);
}

template <class T>
ArbreRougeNoir<T>::~ArbreRougeNoir() {
	this->vider(this->racine);
}

template <class T>
bool ArbreRougeNoir<T>::contient(const T& element) const {
	Noeud* noeud = this->racine;
	while (noeud) {
		if (element < noeud->contenu)
			noeud = noeud->gauche;
		else if (element > noeud->contenu)
			noeud = noeud->droite;
		else
			return true;
	}
	return false;
}

template <class T>
void ArbreRougeNoir<T>::inserer(const T& element) {
	Pile<Noeud*> freres;
	this->inserer(this->racine, element, &freres);
}

template <class T>
bool ArbreRougeNoir<T>::inserer(Noeud*& noeud, const T& element, Pile<Noeud*>* freres) {
	freres->empiler(noeud);
	if (noeud == nullptr) {
		noeud = new Noeud(element);
		if (noeud == this->racine)
			noeud->rouge = false;
		return true;
	}
	if (element < noeud->contenu) {
		if(inserer(noeud->gauche, element, freres)) {
			if(!noeud->rouge)
				return false;
			freres->depiler();
			Noeud* grandPere = freres->depiler();
			if (grandPere->droite != nullptr && grandPere->droite->rouge) {
				noeud->rouge = false;
				grandPere->droite->rouge = false;
				grandPere->rouge = true;
				if (grandPere == this->racine)
					grandPere->rouge = false;
				freres->empiler(grandPere);
				return true;
			}
			if (noeud->droite)
				this->rotationDroiteGauche(noeud->gauche);
			this->rotationGaucheDroite(noeud);
			freres->empiler(grandPere);
			return true;
		}
		return false;
	}
	if (element > noeud->contenu) {
		if (inserer(noeud->droite, element, freres)) {
			if(!noeud->rouge)
				return false;
			freres->depiler();
			Noeud* grandPere = freres->depiler();
			if (grandPere->gauche != nullptr && grandPere->gauche->rouge) {
				noeud->rouge = false;
				grandPere->gauche->rouge = false;
				grandPere->rouge = true;
				if (grandPere == this->racine)
					grandPere->rouge = false;
				freres->empiler(grandPere);
				return true;
			}
			if (noeud->gauche != nullptr)
				this->rotationGaucheDroite(noeud->droite);
			this->rotationDroiteGauche(noeud);
			freres->empiler(grandPere);
			return true;
		}
		return false;
	}
	noeud->contenu = element;
	return false;
}

template <class T>
void ArbreRougeNoir<T>::rotationGaucheDroite(Noeud*& racinesousarbre) {
	Noeud *temp = racinesousarbre->gauche;

	racinesousarbre->gauche = temp->droite;
	temp->droite = racinesousarbre;
	racinesousarbre = temp;

	racinesousarbre->rouge = false;
	racinesousarbre->droite->rouge = true;
}

template <class T>
void ArbreRougeNoir<T>::rotationDroiteGauche(Noeud*& racinesousarbre) {
	Noeud *temp = racinesousarbre->droite;

	racinesousarbre->droite = temp->gauche;
	temp->gauche = racinesousarbre;
	racinesousarbre = temp;

	racinesousarbre->rouge = false;
	racinesousarbre->gauche->rouge = true;
}

template <class T>
bool ArbreRougeNoir<T>::vide() const {
	return this->racine == nullptr ? true : false;
}

template <class T>
void ArbreRougeNoir<T>::vider(){
	this->vider(racine);
	this->racine = nullptr;
}

template <class T>
void ArbreRougeNoir<T>::vider(Noeud*& noeud) {
	if (noeud != nullptr) {
		vider(noeud->droite);
		vider(noeud->gauche);
		delete noeud;
	}
}

template <class T>
void ArbreRougeNoir<T>::copier(const Noeud* source, Noeud*& noeud) const {
	if (source != nullptr) {
		noeud = new Noeud(source->contenu);
		noeud->rouge = source->rouge;
		copier(source->gauche, noeud->gauche);
		copier(source->droite, noeud->droite);
	}
}

template <class T>
int  ArbreRougeNoir<T>::hauteur() const {
	return this->hauteur(this->racine);
}

template <class T>
int  ArbreRougeNoir<T>::hauteur(Noeud* noeud) const {
	if (!noeud)
		return 0;
	return this->hauteur(noeud->gauche) < this->hauteur(noeud->droite) ? this->hauteur(noeud->droite) + 1 : this->hauteur(noeud->gauche) + 1; 
}

template <class T>
const T& ArbreRougeNoir<T>::max(Noeud* n) const {
	assert(n != nullptr);
	if (n->droite == nullptr)
		return n->contenu;
	return max(n->droite);
}

template <class T>
void ArbreRougeNoir<T>::enlever(const T& element) {
	this->enlever(racine, element);
}

template <class T>
bool ArbreRougeNoir<T>::enlever(Noeud*& noeud, const T& element) {
	return false;
}

template <class T>
int ArbreRougeNoir<T>::compter(const T& min, const T& max) const {
	return this->compter(this->racine, min, max);
}

template <class T>
int ArbreRougeNoir<T>::compter(const Noeud* noeud, const T& min, const T& max) const {
	if (!noeud)
		return 0;
	int nb = min <= noeud->contenu && noeud->contenu <= max ? 1 : 0;
	if (min < noeud->contenu)
		nb += compter(noeud->gauche, min, max);
	if (max > noeud->contenu)
		nb += compter(noeud->droite, min, max);
	return nb;
}

template <class T>
int  ArbreRougeNoir<T>::taille() const {
	return this->taille(this->racine);
}

template <class T>
int  ArbreRougeNoir<T>::taille(Noeud* noeud) const {
	if (!noeud)
		return 0;
	return 1 + taille(noeud->gauche) + taille(noeud->droite);
}

template <class T>
typename ArbreRougeNoir<T>::Iterateur ArbreRougeNoir<T>::debut() const {
	Iterateur iter(*this);
	iter.courant = this->racine;
	if (iter.courant != nullptr) {
		while (iter.courant->gauche != nullptr) {
			iter.chemin.empiler(iter.courant);
			iter.courant = iter.courant->gauche;
		}
	}
	return iter;
}

template <class T>
typename ArbreRougeNoir<T>::Iterateur ArbreRougeNoir<T>::fin() const {
	return Iterateur(*this);
}

template <class T>
typename ArbreRougeNoir<T>::Iterateur ArbreRougeNoir<T>::rechercher(const T& e) const {
	Iterateur iter(*this);
	Noeud* noeud(this->racine);
	while (noeud) {
		if (e < noeud->contenu) {
			iter.chemin.empiler(noeud);
			noeud = noeud->gauche;
		}
		else if (e > noeud->contenu) {
			noeud = noeud->droite;
		}
		else {
			assert(e == noeud->contenu);
			iter.courant = noeud;
			return iter;
		}
	}
	return iter;
}

template <class T>
typename ArbreRougeNoir<T>::Iterateur ArbreRougeNoir<T>::rechercherEgalOuPrecedent(const T& e) const {
	Noeud* noeud(this->racine);
	Noeud* dernier(nullptr);
	while (noeud) {
		if (e < noeud->contenu)
			noeud = noeud->gauche;
		else if (e > noeud->contenu) {
			dernier = noeud;
			noeud = noeud->droite;
		}
		else {
			assert(e == noeud->contenu);
			return rechercher(e);
		}
	}
	if (dernier)
		return rechercher(dernier->contenu);
	return Iterateur(*this);
}

template <class T>
typename ArbreRougeNoir<T>::Iterateur ArbreRougeNoir<T>::rechercherEgalOuSuivant(const T& e) const {
	Noeud* noeud(this->racine);
	Noeud* dernier(nullptr);
	while (noeud) {
		if (e < noeud->contenu) {
			dernier = noeud;
			noeud = noeud->gauche;
		}
		else if (e > noeud->contenu) {
			noeud = noeud->droite;
		}
		else {
			assert(e == noeud->contenu);
			return rechercher(e);
		}
	}
	if (dernier)
		return rechercher(dernier->contenu);
	return Iterateur(*this);
}

template <class T>
const T& ArbreRougeNoir<T>::operator[](const Iterateur& iterateur) const {
	assert(&iterateur.arbre_associe == this);
	assert(iterateur.courant);
	return iterateur.courant->contenu;
}

template <class T>
T& ArbreRougeNoir<T>::operator[](const Iterateur& iterateur) {
	assert(&iterateur.arbre_associe == this);
	assert(iterateur.courant);
	return iterateur.courant->contenu;
}

template <class T>
ArbreRougeNoir<T>& ArbreRougeNoir<T>::operator=(const ArbreRougeNoir& autre) {
	if(this == &autre) 
		return *this;
	vider();
	copier(autre.racine, racine);
	return *this;
}

template <class T>
bool ArbreRougeNoir<T>::operator==(const ArbreRougeNoir& autre) const {
	if (this == &autre)
		return true;
	ArbreRougeNoir<T>::Iterateur iter1 = this->debut();
	ArbreRougeNoir<T>::Iterateur iter2 = autre.debut();

	while (iter1 && iter2) {
		if (*iter1 != *iter2)
			return false;
		++iter1;
		++iter2;
	}
	return !iter1 && !iter2;
}

template <class T>
bool ArbreRougeNoir<T>::operator!=(const ArbreRougeNoir& autre) const {
	return !(*this == autre);
}

template <class T>
ArbreRougeNoir<T>::Iterateur::Iterateur(const ArbreRougeNoir& a) : arbre_associe(a), courant(nullptr) {}

template <class T>
ArbreRougeNoir<T>::Iterateur::Iterateur(const ArbreRougeNoir<T>::Iterateur& a) : arbre_associe(a.arbre_associe) {
	this->courant = a.courant;
	this->chemin = a.chemin;
}

template <class T>	// Pré-incrément
typename ArbreRougeNoir<T>::Iterateur& ArbreRougeNoir<T>::Iterateur::operator++() {
	if (!this->courant)
		return *this;
	Noeud* noeud = this->courant->droite;
	while (noeud) {
		this->chemin.empiler(noeud);
		noeud = noeud->gauche;
	}
	if (!this->chemin.vide())
		this->courant = this->chemin.depiler();
	else 
		this->courant = nullptr;
	return *this;
}

template <class T>	// Post-incrément
typename ArbreRougeNoir<T>::Iterateur ArbreRougeNoir<T>::Iterateur::operator++(int) {
	Iterateur copie(*this);
	operator++();
	return copie;
}

template <class T>
ArbreRougeNoir<T>::Iterateur::operator bool() const {
	return this->courant != nullptr;
}

template <class T>
bool ArbreRougeNoir<T>::Iterateur::operator!() const {
	return this->courant == nullptr;
}

template <class T>
bool ArbreRougeNoir<T>::Iterateur::operator==(const Iterateur& o) const {
	assert(&this->arbre_associe == &o.arbre_associe);
	return this->courant == o.courant;
}

template <class T>
bool ArbreRougeNoir<T>::Iterateur::operator!=(const Iterateur& o) const {
	assert(&this->arbre_associe == &o.arbre_associe);
	return this->courant != o.courant;
}

template <class T>
const T& ArbreRougeNoir<T>::Iterateur::operator*() const {
	assert(this->courant != nullptr);
	return this->courant->contenu;
}

template <class T>
typename ArbreRougeNoir<T>::Iterateur& ArbreRougeNoir<T>::Iterateur::operator=(const Iterateur& autre) {
	assert(&this->arbre_associe == &autre.arbre_associe);
	this->courant = autre.courant;
	this->chemin = autre.chemin;
	return *this;
}

#endif
