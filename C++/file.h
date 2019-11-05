/*
	INF3105 - Structures de données et algorithmes
	UQAM / Département d'informatique
*/

#ifndef __FILE_H__
#define __FILE_H__

template <class T> 
class File {
	public:
		File();
		File(const File<T>&);
		~File();
		const T& tete() const;
		void enfiler(const T&);
		void defiler(T&);
		T defiler();
		bool vide() const;
		void vider();
		File<T>& operator=(const File<T>&);
	private:
		class Cellule {
			public:
				Cellule(const T&, Cellule* c = nullptr);
				T element;
				Cellule* suivante;
		};
		Cellule *queue;
	friend bool operator==(const File<T>& file1, const File<T>& file2) {
		if (&file1 == &file2)
			return true;
		if (file1.queue == nullptr && file2.queue == nullptr)
			return true;
		else if (file1.queue == nullptr || file2.queue == nullptr)
			return false;
		Cellule* cell1 = file1.queue;
		Cellule* cell2 = file2.queue;
		if (cell1->element == cell2->element) {
			cell1 = cell1->suivante;
			cell2 = cell2->suivante;
		}
		else
			return false;
		while (cell1 != file1.queue && cell2 != file2.queue) {
			if (cell1->element == cell2->element) {
				cell1 = cell1->suivante;
				cell2 = cell2->suivante;
			}
			else
				return false;
		}
		if (cell1 == file1.queue && cell2 == file2.queue)
			return true;
		return false;
	}
};

#include <assert.h>

template <class T>
File<T>::File() : queue(nullptr) {}

template <class T>
File<T>::File(const File<T>& autre) {
	if (autre.queue != nullptr) {
		this->queue = new Cellule(autre.queue->element, nullptr);
		this->queue->suivante = this->queue;
		Cellule** queue_ptr = &this->queue;
		Cellule* cell = autre.queue->suivante;
		while (cell != autre.queue) {
			(*queue_ptr)->suivante = new Cellule(cell->element, this->queue);
			queue_ptr = &((*queue_ptr)->suivante);
			cell = cell->suivante;
		}
	}
}

template <class T>
File<T>::~File() {
	vider();
}

template <class T>
const T& File<T>::tete() const {
	assert(this->queue != nullptr);
	return this->queue->suivante->element;
}

template <class T>
void File<T>::enfiler(const T& e) {
	if (this->queue == nullptr) {
		this->queue = new Cellule(e, nullptr);
		this->queue->suivante = this->queue;
	} 
	else {
		Cellule *cell = this->queue;
		this->queue = new Cellule(e, this->queue->suivante);
		cell->suivante = this->queue;
	}
	assert(queue);
}

template <class T>
void File<T>::defiler(T& r) {
	assert(!this->vide());
	Cellule *cell = this->queue->suivante;
	if (this->queue == this->queue->suivante)
		this->queue = nullptr;
	else
		this->queue->suivante = this->queue->suivante->suivante;
	delete cell;
}

template <class T>
T File<T>::defiler() {
	assert(!this->vide());
	T result(this->queue->suivante->element);
	Cellule *cell = this->queue->suivante;
	if (this->queue == this->queue->suivante)
		this->queue = nullptr;
	else
		this->queue->suivante = this->queue->suivante->suivante;
	delete cell;
	return result;
}

template <class T>
bool File<T>::vide() const {
	return queue == nullptr;
}

template <class T>
void File<T>::vider() {
	while (!this->vide())
		this->defiler();
}

template <class T>
File<T>& File<T>::operator=(const File<T>& autre) {
	if (this == &autre)
		return *this;
	this->vider();
	if (autre.queue != nullptr) {
		this->queue = new Cellule(autre.queue->element, nullptr);
		this->queue->suivante = this->queue;
		Cellule** queue_ptr = &this->queue;
		Cellule* cell = autre.queue->suivante;
		while (cell != autre.queue) {
			(*queue_ptr)->suivante = new Cellule(cell->element, this->queue);
			queue_ptr = &((*queue_ptr)->suivante);
			cell = cell->suivante;
		}
	}
	return *this;
}

template <class T>
File<T>::Cellule::Cellule(const T& e, Cellule* c) : element(e), suivante(c) {}

#endif
