#include "deque.h"
#include <cassert>

using namespace TP3_structures;

template <class T>
deque<T>::deque(size_type reserve)
	:tab(nullptr), start(0), sz(0), cap(0)
{
	this->reserve(0);
}

template <class T>
deque<T>::deque(const deque<T>& other)
	:deque()
{
	*this = other;
}

template <class T>
deque<T>::~deque()
{
	clear();
}

template <class T>
deque<T>& deque<T>::operator=(const deque<T>& other)
{
	// Étape 1: On supprime la file.
	clear();

	// Étape 2:
	// pour tous les éléments de l'autre file...
	reserve(other.sz);
	for (size_type i = 0; i < other.sz; ++i)
	{
		// On les pousse dans la file actuelle.
		push_back(other[i]);
	}

	return *this;
}

template <class T>
bool deque<T>::empty() const
{
	return sz == 0;
}

template <class T>
typename deque<T>::size_type deque<T>::size() const
{
	return sz;
}

template <class T>
void deque<T>::reserve(size_type new_cap)
{
	if (cap < new_cap)
	{
		// Étape 1: On se crée un pointeur temporaire sur le début du tableau.
		T* tmp = tab;
		
		// Étape 2: On crée un nouveau tableau avec la nouvelle capacité.
		tab = new T[new_cap];

		// Étape 3: On copie tous les éléments du premier tableau dans le deuxième tableau en à partir du début
		// des éléments.
		size_type i = 0;
		for (; i < sz; ++i)
		{
			tab[i] = tmp[(i + start) % cap];
		}

		// Étape 4: On ajuste les propriétés;
		// la capacité change et le début des éléments est mainenant au début du nouveau tableau.
		cap = new_cap;
		start = 0;
		
		// Étape 6: On supprime l'ancien tableau.
		delete[] tmp;
	}
}

template <class T>
void deque<T>::resize(size_type new_size)
{
	if (new_size > sz)
	{
		if (new_size > cap)
		{
			reserve(new_size);
		}

		for (size_type i = sz; i < new_size; i++)
		{
			tab[i] = T();
		}
	}
	sz = new_size;
}

template <class T>
typename deque<T>::size_type deque<T>::capacity() const
{
	return cap;
}

template <class T>
T& deque<T>::operator[] (size_type index)
{
	return *(tab + ((start + index) % cap));
}

template <class T>
T& deque<T>::at(size_type index)
{
	assert(index >= 0 && index < sz && "L'index doit être entre 0 (inclusivement) et le nombre d'éléments contenus dans le tableau (exclusivement).");
	return *(tab + ((start + index) % cap));
}

template <class T>
T& deque<T>::front()
{
	return *(tab + start);
}

template <class T>
T& deque<T>::back()
{
	return *(tab + ((start + sz - 1) % cap));
}

template <class T>
const T& deque<T>::operator[] (size_type index) const
{
	return *(tab + ((start + index) % cap));
}

template <class T>
const T& deque<T>::at(size_type index) const
{
	assert(index >= 0 && index < sz && "L'index doit être entre 0 (inclusivement) et le nombre d'éléments contenus dans le tableau (exclusivement).");
	return *(tab + ((start + index) % cap));
}

template <class T>
const T& deque<T>::front() const
{
	return *(tab + start);
}

template <class T>
const T& deque<T>::back() const
{
	return *(tab + ((start + sz - 1) % cap));
}

template <class T>
void deque<T>::clear()
{
	sz = 0;
	cap = 0;
	start = 0;
	delete[] tab;
	tab = nullptr;
}

template <class T>
void deque<T>::push_back(const T& value)
{
	// Cas limite: Si le nombre d'élément est égal à la capacité, on alloue un nouveau tableau
	// deux fois plus grand.
	if (sz == cap)
	{
		reserve(cap * 2 + 1);
	}

	// Étape 1: La prochaine case libre prend la valeur.
	operator[](sz) = value;

	// Étape 2: On incrémente la taille de la file.
	sz++;
}

template <class T>
void deque<T>::push_front(const T& value)
{
	// Cas limite: Si le nombre d'élément est égal à la capacité, on alloue un nouveau tableau
	// deux fois plus grand.
	if (sz == cap)
	{
		reserve(cap * 2 + 1);
	}

	// Étape 1: On diminue la position du début de la file dans le tableau.
	start--;

	// Cas limite: Si la position du début de la file est négatif, on l'envoie à
	// la fin de la file.
	if (start == -1)
	{
		start = cap - 1;
	}

	// Étape 2: Cette première case libre prend la valeur donnée en paramètre.
	tab[start] = value;

	// Étape 3: On incrémente la taille de la file.
	sz++;
}

template <class T>
void deque<T>::pop_back()
{
	sz--;
}

template <class T>
void deque<T>::pop_front()
{
	start = (start + 1) % cap;
	sz--;
}

template <class T>
void deque<T>::swap(deque& other)
{
	std::swap(tab, other.tab);
	std::swap(start, other.start);
	std::swap(cap, other.cap);
	std::swap(sz, other.sz);
}