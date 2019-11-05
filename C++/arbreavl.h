/*	UQAM / Département d'informatique
	INF3105 - Structures de données et algorithmes
	Squelette pour classe générique ArbreAVL<T> pour le Lab6.

	AUTEUR(S):
	1) Nom + Code permanent du l'étudiant.e 1
	2) Nom + Code permanent du l'étudiant.e 2
*/

#ifndef __ARBREAVL_H__
#define __ARBREAVL_H__

#include <cassert>
#include "pile.h"

template <class T>
class ArbreAVL {
	public:
		ArbreAVL();
		ArbreAVL(const ArbreAVL&);
		~ArbreAVL();
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
		ArbreAVL& operator=(const ArbreAVL&);
		bool operator==(const ArbreAVL<T>&) const;
		bool operator!=(const ArbreAVL<T>&) const;
	private:
		struct Noeud{
			Noeud(const T&);
			T contenu;
			int equilibre;
			Noeud *gauche;
			Noeud *droite;
		};
		Noeud* racine;
		bool inserer(Noeud*&, const T&);
		void rotationGaucheDroite(Noeud*&);
		void rotationDroiteGauche(Noeud*&);
		void vider(Noeud*&);
		void copier(const Noeud*, Noeud*&) const;
		const T& max(Noeud*) const;
		bool enlever(Noeud*&, const T& e);
		int compter(const Noeud*, const T&, const T&) const;
		int taille(Noeud*) const;
	public:
		class Iterateur{
			public:
				Iterateur(const ArbreAVL& a);
				Iterateur(const Iterateur& a);
				Iterateur(const ArbreAVL& a, Noeud* c);
				operator bool() const;
				bool operator!() const;
				bool operator==(const Iterateur&) const;
				bool operator!=(const Iterateur&) const;
				const T& operator*() const;
				Iterateur& operator++();
				Iterateur operator++(int);
				Iterateur& operator=(const Iterateur&);
			private:
				const ArbreAVL& arbre_associe;
				Noeud* courant;
				Pile<Noeud*> chemin;
			friend class ArbreAVL;
		};
	friend std::ostream& operator<<(std::ostream& out, const ArbreAVL<T>& arbre) {
		for (ArbreAVL<T>::Iterateur iter = arbre.debut(); iter; ++iter)
			out << *iter << std::endl;
		return out;
	}
};


//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c) : contenu(c), equilibre(0), gauche(NULL), droite(NULL) {}

template <class T>
ArbreAVL<T>::ArbreAVL() : racine(NULL) {}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre) : racine(NULL) {
	this->copier(autre.racine, racine);
}

template <class T>
ArbreAVL<T>::~ArbreAVL() {
	this->vider(racine);
}

template <class T>
bool ArbreAVL<T>::contient(const T& element) const {
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
void ArbreAVL<T>::inserer(const T& element) {
	this->inserer(racine, element);
}

template <class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element) {
	if (noeud == nullptr) {
		noeud = new Noeud(element);
		return true;
	}
	if (element < noeud->contenu){
		if(this->inserer(noeud->gauche, element)) {
			noeud->equilibre++;
			if(noeud->equilibre == 0)
				return false;
			if(noeud->equilibre == 1)
				return true;
			if(noeud->gauche->equilibre == -1)
				this->rotationDroiteGauche(noeud->gauche);
			this->rotationGaucheDroite(noeud);
		}
		return false;
	}
	if (element > noeud->contenu){
		if (this->inserer(noeud->droite, element)) {
			noeud->equilibre--;
			if (noeud->equilibre == 0)
				return false;
			if (noeud->equilibre == -1)
				return true;
			if (noeud->droite->equilibre == 1)
				this->rotationGaucheDroite(noeud->droite);
			this->rotationDroiteGauche(noeud);
		}
		return false;
	}
	noeud->contenu = element;
	return false;
}

template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre) {
	Noeud *temp = racinesousarbre->gauche;
	int  ea = temp->equilibre;
	int  eb = racinesousarbre->equilibre;
	int  neb = -(ea>0 ? ea : 0) - 1 + eb;
	int  nea = ea + (neb < 0 ? neb : 0) - 1;

	temp->equilibre = nea;
	racinesousarbre->equilibre = neb;
	racinesousarbre->gauche = temp->droite;
	temp->droite = racinesousarbre;
	racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre) {
	Noeud *temp = racinesousarbre->droite;
	int  eb = temp->equilibre;
	int  ea = racinesousarbre->equilibre;
	int  nea = -(eb<0 ? eb : 0) + 1 + ea;
	int  neb = eb + (nea > 0 ? nea : 0) + 1;

	temp->equilibre = neb;
	racinesousarbre->equilibre = nea;
	racinesousarbre->droite = temp->gauche;
	temp->gauche = racinesousarbre;
	racinesousarbre = temp;
}

template <class T>
bool ArbreAVL<T>::vide() const {
	return this->racine == nullptr ? true : false;
}

template <class T>
void ArbreAVL<T>::vider(){
	this->vider(racine);
	this->racine = nullptr;
}

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud) {
	if (noeud != nullptr) {
		this->vider(noeud->droite);
		this->vider(noeud->gauche);
		delete noeud;
	}
}

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const {
	if (source != nullptr) {
		noeud = new Noeud(source->contenu);
		noeud->equilibre = source->equilibre;
		this->copier(source->gauche, noeud->gauche);
		this->copier(source->droite, noeud->droite);
	}
}

template <class T>
int  ArbreAVL<T>::hauteur() const {
	int h = 0;
	Noeud* noeud = this->racine;
	while (noeud) {
		h += 1;
		if (noeud->equilibre == 1)
			noeud = noeud->gauche;
		else
			noeud = noeud->droite;
	}
	return h;
}

template <class T>
const T& ArbreAVL<T>::max(Noeud* n) const {
	assert(n != nullptr);
	if (n->droite == nullptr)
		return n->contenu;
	return this->max(n->droite);
}

template <class T>
void ArbreAVL<T>::enlever(const T& element) {
	this->enlever(racine, element);
}

template <class T>
bool ArbreAVL<T>::enlever(Noeud*& noeud, const T& element) {
	if(element < noeud->contenu) {
		if(this->enlever(noeud->gauche, element)) {
			noeud->equilibre--;
			if(noeud->equilibre == 0)
				return false;
			if(noeud->equilibre == -1)
				return true;
			if (noeud->droite) {
				if (noeud->droite->equilibre == 1)
					this->rotationGaucheDroite(noeud->droite);
				this->rotationDroiteGauche(noeud);
			}
		}
	}
	else if(element > noeud->contenu) {
		if(this->enlever(noeud->droite, element)) {
			noeud->equilibre++;
			if (noeud->equilibre == 0)
				return false;
			if (noeud->equilibre == 1)
				return true;
			if (noeud->gauche) {
				if(noeud->gauche && noeud->gauche->equilibre == -1)
					this->rotationDroiteGauche(noeud->gauche);
				this->rotationGaucheDroite(noeud);
			}
		}
	}
	else {
		if (noeud->gauche == nullptr && noeud->droite == nullptr) {
			delete noeud;
			noeud = nullptr;
			return true;
		}
		else {
			if (noeud->gauche == nullptr) {
				Noeud* tmp = noeud->droite;
				delete noeud;
				noeud = tmp;
			}
			else if (noeud->droite == nullptr) {
				Noeud* tmp = noeud->gauche;
				delete noeud;
				noeud = tmp;
			}
			else {
				T tmp = this->max(noeud->gauche);
				this->enlever(tmp);
				noeud->contenu = tmp;
			}
			return true;
		}
	}
	return false;
}

template <class T>
int ArbreAVL<T>::compter(const T& min, const T& max) const {
	return this->compter(this->racine, min, max);
}

template <class T>
int ArbreAVL<T>::compter(const Noeud* noeud, const T& min, const T& max) const {
	if (!noeud)
		return 0;
	int nb = min <= noeud->contenu && noeud->contenu <= max ? 1 : 0;
	if (min < noeud->contenu)
		nb += this->compter(noeud->gauche, min, max);
	if (max > noeud->contenu)
		nb += this->compter(noeud->droite, min, max);
	return nb;
}

template <class T>
int  ArbreAVL<T>::taille() const {
	return this->taille(this->racine);
}

template <class T>
int  ArbreAVL<T>::taille(Noeud* noeud) const {
	if (!noeud)
		return 0;
	return 1 + this->taille(noeud->gauche) + this->taille(noeud->droite);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const {
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
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const {
	return Iterateur(*this);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T& e) const {
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
			iter.courant = noeud;
			return iter;
		}
	}
	return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T& e) const {
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
			return this->rechercher(e);
		}
	}
	if (dernier)
		return this->rechercher(dernier->contenu);
	return Iterateur(*this);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T& e) const {
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
			return this->rechercher(e);
		}
	}
	if (dernier)
		return this->rechercher(dernier->contenu);
	return Iterateur(*this);
}

template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const {
	assert(&iterateur.arbre_associe == this);
	assert(iterateur.courant);
	return iterateur.courant->contenu;
}

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur) {
	assert(&iterateur.arbre_associe == this);
	assert(iterateur.courant);
	return iterateur.courant->contenu;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
	if(this == &autre)
		return *this;
	this->vider();
	this->copier(autre.racine, racine);
	return *this;
}

template <class T>
bool ArbreAVL<T>::operator==(const ArbreAVL& autre) const {
	if (this == &autre)
		return true;
	ArbreAVL<T>::Iterateur iter1 = this->debut();
	ArbreAVL<T>::Iterateur iter2 = autre.debut();

	while (iter1 && iter2) {
		if (*iter1 != *iter2)
			return false;
		++iter1;
		++iter2;
	}
	return !iter1 && !iter2;
}

template <class T>
bool ArbreAVL<T>::operator!=(const ArbreAVL& autre) const {
	return !(*this == autre);
}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a) : arbre_associe(a), courant(nullptr) {}

template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a) : arbre_associe(a.arbre_associe) {
	this->courant = a.courant;
	this->chemin = a.chemin;
}

template <class T>	// Pré-incrément
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++() {
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
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int) {
	Iterateur copie(*this);
	operator++();
	return copie;
}

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const {
	return this->courant != nullptr;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const {
	return this->courant == nullptr;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const {
	assert(&this->arbre_associe == &o.arbre_associe);
	return this->courant == o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const {
	assert(&this->arbre_associe == &o.arbre_associe);
	return this->courant != o.courant;
}

template <class T>
const T& ArbreAVL<T>::Iterateur::operator*() const {
	assert(this->courant != nullptr);
	return this->courant->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator=(const Iterateur& autre) {
	assert(&this->arbre_associe == &autre.arbre_associe);
	this->courant = autre.courant;
	this->chemin = autre.chemin;
	return *this;
}

#endif
