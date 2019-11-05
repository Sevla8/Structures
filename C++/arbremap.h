/*	UQAM / Département d'informatique
	INF3105 - Structures de données et algorithmes
	Squelette pour classe générique ArbreMap<K,V> pour le Lab8 et le TP2.

	AUTEUR(S):
	1) Nom + Code permanent du l'étudiant.e 1
	2) Nom + Code permanent du l'étudiant.e 2
*/

#ifndef __ARBREMAP_H__
#define __ARBREMAP_H__

#include "arbreavl.h"

template <class K, class V>
class ArbreMap {
	private:
		struct Entree {
			Entree(const K&);
			K cle;
			V valeur;
			bool operator<(const Entree&) const;
			bool operator<=(const Entree&) const;
			bool operator>(const Entree&) const;
			bool operator>=(const Entree&) const;
			bool operator==(const Entree&) const;
		};
		ArbreAVL<Entree> entrees;
	public:
		class Iterateur {
			public:
				Iterateur(const ArbreMap&);
				Iterateur(typename ArbreAVL<Entree>::Iterateur);
				operator bool() const;
				bool operator!() const;
				Iterateur& operator++();
				Iterateur operator++(int);
				const K& cle() const;
				const V& valeur() const;
			private:
				typename ArbreAVL<Entree>::Iterateur iter;
			friend class ArbreMap;
		};
		bool contient(const K&) const;
		void enlever(const K&);
		void vider();
		bool vide() const;
		const V& operator[] (const K&) const;
		V& operator[] (const K&);
		const V& operator[] (const Iterateur&) const;
		V& operator[] (const Iterateur&);
		Iterateur debut() const;
		Iterateur fin() const;
		Iterateur rechercher(const K&) const;
		Iterateur rechercherEgalOuPrecedent(const K&) const;
		Iterateur rechercherEgalOuSuivant(const K&) const;
	friend std::ostream& operator<<(std::ostream& out, const ArbreMap<K,V>& arbre) {
		for (ArbreMap<K,V>::Iterateur iter = arbre.debut(); iter; ++iter)
			out << iter.cle() << std::endl << arbre[iter] << std::endl;
		return out;
	}
};

//-----------------------------------------------------------------------------

template <class K, class V>
ArbreMap<K,V>::Entree::Entree(const K& c) : cle(c), valeur() {}

template <class K, class V>
bool ArbreMap<K,V>::Entree::operator<(const Entree& e) const {
	return this->cle < e.cle;
}

template <class K, class V>
bool ArbreMap<K,V>::Entree::operator<=(const Entree& e) const {
	return this->cle <= e.cle;
}

template <class K, class V>
bool ArbreMap<K,V>::Entree::operator>(const Entree& e) const {
	return this->cle > e.cle;
}

template <class K, class V>
bool ArbreMap<K,V>::Entree::operator>=(const Entree& e) const {
	return this->cle >= e.cle;
}

template <class K, class V>
bool ArbreMap<K,V>::Entree::operator==(const Entree& e) const {
	return this->cle == e.cle;
}

template <class K, class V>
void ArbreMap<K,V>::vider() {
	this->entrees.vider();
}

template <class K, class V>
bool ArbreMap<K,V>::vide() const {
	return this->entrees.vide();
}

template <class K, class V>
void ArbreMap<K,V>::enlever(const K& c) {
	this->entrees.enlever(Entree(c));
}

template <class K, class V>
bool ArbreMap<K,V>::contient(const K& c) const {
	return this->entrees.contient(Entree(c));
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& c)  const {
	typename ArbreAVL<Entree>::Iterateur iter = this->entrees.rechercher(Entree(c));
	assert(iter);
	return this->entrees[iter].valeur;
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const K& c)  {
	typename ArbreAVL<Entree>::Iterateur iter = this->entrees.rechercher(Entree(c));
	if (!iter) {
		this->entrees.inserer(Entree(c));
		iter = this->entrees.rechercher(Entree(c));
	}
	return this->entrees[iter].valeur;
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const Iterateur& it) const {
	return it.valeur();
}

template <class K, class V>
V& ArbreMap<K,V>::operator[] (const Iterateur& it) {
	return (V&)(*it.iter).valeur;
}

//-----------------------------------------------------------------------------

template <class K, class V>
ArbreMap<K,V>::Iterateur::Iterateur(const ArbreMap& a) : iter(a.entrees) {}

template <class K, class V>
ArbreMap<K,V>::Iterateur::Iterateur(typename ArbreAVL<Entree>::Iterateur it) : iter(it) {}

template <class K, class V>
ArbreMap<K,V>::Iterateur::operator bool() const {
	return this->iter;
}

template <class K, class V>
bool ArbreMap<K,V>::Iterateur::operator!() const {
	return !this->iter;
}

template <class K, class V>	// Pré-incrément
typename ArbreMap<K,V>::Iterateur& ArbreMap<K,V>::Iterateur::operator++() {
	++this->iter;
	return *this;
}

template <class K, class V>	// Post-incrément
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::Iterateur::operator++(int) {
	Iterateur copie(*this);
	this->operator++();
	return copie;
}

template <class K, class V>
const K& ArbreMap<K,V>::Iterateur::cle() const {
	return (*this->iter).cle;
}

template <class K, class V>
const V& ArbreMap<K,V>::Iterateur::valeur() const {
	return (*this->iter).valeur;
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::debut() const {
	return this->entrees.debut();
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::fin() const {
	return this->entrees.fin();
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercher(const K& clef) const {
	return this->entrees.rechercher(Entree(clef));
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuPrecedent(const K& clef) const {
	return this->entrees.rechercherEgalOuPrecedent(Entree(clef));
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuSuivant(const K& clef) const {
	return this->entrees.rechercherEgalOuSuivant(Entree(clef));
}

#endif
