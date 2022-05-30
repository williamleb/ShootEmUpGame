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
	// �tape 1: On supprime la file.
	clear();

	// �tape 2:
	// pour tous les �l�ments de l'autre file...
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
		// �tape 1: On se cr�e un pointeur temporaire sur le d�but du tableau.
		T* tmp = tab;
		
		// �tape 2: On cr�e un nouveau tableau avec la nouvelle capacit�.
		tab = new T[new_cap];

		// �tape 3: On copie tous les �l�ments du premier tableau dans le deuxi�me tableau en � partir du d�but
		// des �l�ments.
		size_type i = 0;
		for (; i < sz; ++i)
		{
			tab[i] = tmp[(i + start) % cap];
		}

		// �tape 4: On ajuste les propri�t�s;
		// la capacit� change et le d�but des �l�ments est mainenant au d�but du nouveau tableau.
		cap = new_cap;
		start = 0;
		
		// �tape 6: On supprime l'ancien tableau.
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
	assert(index >= 0 && index < sz && "L'index doit �tre entre 0 (inclusivement) et le nombre d'�l�ments contenus dans le tableau (exclusivement).");
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
	assert(index >= 0 && index < sz && "L'index doit �tre entre 0 (inclusivement) et le nombre d'�l�ments contenus dans le tableau (exclusivement).");
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
	// Cas limite: Si le nombre d'�l�ment est �gal � la capacit�, on alloue un nouveau tableau
	// deux fois plus grand.
	if (sz == cap)
	{
		reserve(cap * 2 + 1);
	}

	// �tape 1: La prochaine case libre prend la valeur.
	operator[](sz) = value;

	// �tape 2: On incr�mente la taille de la file.
	sz++;
}

template <class T>
void deque<T>::push_front(const T& value)
{
	// Cas limite: Si le nombre d'�l�ment est �gal � la capacit�, on alloue un nouveau tableau
	// deux fois plus grand.
	if (sz == cap)
	{
		reserve(cap * 2 + 1);
	}

	// �tape 1: On diminue la position du d�but de la file dans le tableau.
	start--;

	// Cas limite: Si la position du d�but de la file est n�gatif, on l'envoie �
	// la fin de la file.
	if (start == -1)
	{
		start = cap - 1;
	}

	// �tape 2: Cette premi�re case libre prend la valeur donn�e en param�tre.
	tab[start] = value;

	// �tape 3: On incr�mente la taille de la file.
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