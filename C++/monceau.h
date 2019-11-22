#ifndef __MONCEAU_H__
#define __MONCEAU_H__

template<class T>
class Monceau {
	public:
		void inserer(const T&);
		const T& minimum const;
		void enleverMinimum();
		bool estVide() const;
	private:
		Tableau<T> valeurs;
		inline int parent(int indice) const {return (indice-1)/2;}
		inline int enfant1(int indice) const {return 2*indice+1;}
		inline int enfant2(int indice) const {return 2*indice+2;}
}

template<class T>
bool Monceau<T>::estVide() {
	return this->valeurs.vide();
}

template<class T>
const T& Monceau<T>::minimum() const {
	return this->valeurs[0];
}

template<class T>
void Monceau<T>::inserer(const T& element) {
	int indice = this->valeurs.taille();
	this->valeurs.ajouter(element);
	int parent = parent(indice);
	while (indice > 0 && this->valeurs[indice] < this->valeurs[parent]) {
		T temp = this->valeurs[indice];
		this->valeurs[indice] = this->valeurs[parent];
		this->valeurs[parent] = temp;
		indice = parent;
		parent = parent(indice);
	}
}

template<class T>
void Monceau<T>::enleverMinimum() {
	this->valeurs[0] = this->valeurs[this->valeurs.taille()-1];
	this->valeurs.enlever_dernier();
	int indice = 0;
	int enfant = enfant1(indice);
	while (enfant1 < this->valeurs.taille()-1 && this->valeurs[enfant] < this->valeurs[indice]) {
		if (enfant+1 < this->valeurs.taille() && this->valeurs[enfant+1] < this->valeurs[enfant])
			enfant = enfant+1;
		T temp = this->valeurs[indice];
		this->valeurs[indice] = this->valeurs[enfant];
		this->valeurs[enfant] = temp;
		indice = enfant;
		enfant = enfant1(indice);
	}
}

#endif
