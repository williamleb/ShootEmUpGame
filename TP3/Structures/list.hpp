#include "list.h"

using namespace TP3_structures;

template <class T>
typename list<T>::Box* list<T>::insert(Box* position, const T& value)
{
	// �tape 1: Cr�er une bo�te qui pointe sur la bo�te � la position et
	// sur la bo�te avant la position.
	Box* newBox = new Box(value, position, position->previous);

	// �tape 2: Faire pointer la bo�te avant la position sur la nouvelle bo�te.
	position->previous->next = newBox;

	// �tape 3: Faire pointer la bo�te � la position sur la nouvelle bo�te.
	position->previous = newBox;

	// �tape 4: Incr�menter la taille de la liste.
	++sz;

	// �tape 5: Renvoyer un pointeur sur la nouvelle bo�te.
	return newBox;
}

template <class T>
typename list<T>::Box* list<T>::erase(Box* position)
{
	// �tape 1: Faire pointer la bo�te avant sur la bo�te apr�s.
	position->previous->next = position->next;

	// �tape 2: Faire pointer la bo�te apr�s sur la bo�te avant.
	Box* next = position->next;
	next->previous = position->previous;

	// �tape 3: Effacer la bo�te.
	delete position;

	// �tape 4: D�cr�menter la taille de la liste.
	--sz;

	// �tape 5: Revoyer un poiteur sur la bo�te suivante.
	return next;
}

template <class T>
list<T>::list()
	:before(T()), after(T()), sz(0)
{
	// Le next de la premi�re bo�te pointe sur la derni�re;
	// le previous de la derni�re pointe sur la premi�re.
	before.next = &after;
	after.previous = &before;
}

template <class T>
list<T>::~list()
{
	clear();
}

template <class T>
list<T>::list(const list& other)
	: list()
{
	*this = other;
}

template <class T>
list<T>::list(std::initializer_list<T> initalizer)
	: list()
{
	// Pour toutes les valeurs dans la liste d'initialisation...
	for (T value : initalizer)
	{
		// On les pousse dans la liste.
		push_back(value);
	}
}

template <class T>
list<T>& list<T>::operator=(const list& other)
{
	// On commence par supprimer le vecteur.
	clear();

	// Pour tous les �l�ments de l'autre liste...
	Box* position = other.before.next;
	while (position != &other.after)
	{
		// On les pousse dans la liste actuelle.
		push_back(position->value);

		position = position->next;
	}

	return *this;
}

template <class T>
void list<T>::swap(list& other)
{
	Box* lastBox = after.previous;
	Box* otherLastBox = other.after.previous;
	std::swap(before.next->previous, other.before.next->previous);
	std::swap(lastBox->next, otherLastBox->next);
	std::swap(after.previous, other.after.previous);
	std::swap(before.next, other.before.next);
	std::swap(sz, other.sz);
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos, const T& value)
{
	return iterator(insert(pos.pos, value));
}

template <class T>
typename list<T>::iterator list<T>::erase(iterator pos)
{
	return iterator(erase(pos.pos));
}

template <class T>
typename list<T>::reverse_iterator list<T>::insert(reverse_iterator iterator, const T& value)
{
	--iterator;
	return reverse_iterator(insert(iterator.pos, value));
}

template <class T>
typename list<T>::reverse_iterator list<T>::erase(reverse_iterator iterator)
{
	Box* next = erase(iterator.pos);
	return reverse_iterator(next->previous);
}

template <class T>
void list<T>::push_back(const T& value)
{
	insert(&after, value);
}

template <class T>
void list<T>::pop_back()
{
	erase(after.previous);
}

template <class T>
void list<T>::push_front(const T& value)
{
	insert(before.next, value);
}

template <class T>
void list<T>::pop_front()
{
	erase(before.next);
}

template <class T>
T& list<T>::back()
{
	return after.previous->value;
}

template <class T>
T& list<T>::front()
{
	return before.next->value;
}

template <class T>
const T& list<T>::back() const
{
	return after.previous->value;
}

template <class T>
const T& list<T>::front() const
{
	return before.next->value;
}

template <class T>
void list<T>::clear()
{
	// Tant qu'on a des �l�ments...
	while (sz != 0)
	{
		// On les retire.
		pop_front();
	}
}

template <class T>
typename list<T>::size_type list<T>::size() const
{
	return sz;
}

template <class T>
bool list<T>::empty() const
{
	return sz == 0;
}

template <class T>
typename list<T>::iterator list<T>::begin()
{
	return iterator(before.next);
}

template <class T>
typename list<T>::const_iterator list<T>::begin() const
{
	return const_iterator(before.next);
}

template <class T>
typename list<T>::iterator list<T>::end()
{
	return iterator(&after);
}

template <class T>
typename list<T>::const_iterator list<T>::end() const
{
	return const_iterator(&after);
}

template <class T>
typename list<T>::reverse_iterator list<T>::rbegin()
{
	return reverse_iterator(after.previous);
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::rbegin() const
{
	return const_reverse_iterator(after.previous);
}

template <class T>
typename list<T>::reverse_iterator list<T>::rend()
{
	return reverse_iterator(&before);
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::rend() const
{
	return const_reverse_iterator(&before);
}

template <class T>
typename list<T>::const_iterator list<T>::cbegin() const
{
	return const_iterator(before.next);
}

template <class T>
typename list<T>::const_iterator list<T>::cend() const
{
	return const_iterator(&after);
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::crbegin() const
{
	return const_reverse_iterator(after.previous);
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::crend() const
{
	return const_reverse_iterator(&before);
}

template <class T>
void list<T>::reverse()
{
	// Pout toutes les bo�tes...
	Box* position = &before;
	while (position != nullptr)
	{
		// On inverse leur next et previous.
		std::swap(position->next, position->previous);

		position = position->previous;
	}

	// La premi�re bo�te doit pointer sur la bo�te after.
	// La derni�re bo�te doit pointer sur la bo�te before.
	std::swap(after.next->previous, before.previous->next);

	// On inverse la bo�te d'avant et celle d'apr�s.
	std::swap(before, after);
}

template <class T>
void list<T>::splice(iterator pos, list& other)
{
	Box* position = pos.pos;

	// �tape 1 : On encha�ne le d�but de l'autre liste.
	position->previous->next = other.before.next;
	other.before.next->previous = position->previous;

	// �tape 2 : On encha�ne la fin de l'autre liste.
	position->previous = other.after.previous;
	other.after.previous->next = position;

	// �tape 3 : On ajoute la taille.
	sz += other.sz;

	// �tape 4 : On enl�ve les �l�ments de l'autre liste.
	other.before.next = &after;
	other.after.previous = &before;
	other.sz = 0;
}

template <class T>
void list<T>::resize(size_t new_size, const T& value)
{
	// Si la nouvelle taille est plus petite que la taille actuelle...
	while (new_size < sz)
	{
		// On enl�ve des �l�ments.
		pop_back();
	}

	// Si le nouvelle taille est plus grande que la taille actuelle...
	while (new_size > sz)
	{
		// On ajoute des �l�ments.
		push_back(value);
	}
}

template <class T>
void list<T>::remove(const T& value)
{
	// On parcourt tous les �l�ments jusqu'� ce qu'on trouve celui cherch�.
	Box* position = before.next;
	while (position != &after)
	{
		// Si on trouve la valeur...
		if (value == position->value)
		{
			// On l'efface.
			erase(position);
			break;
		}

		position = position->next;
	}
}

// Struct list<T>::Box ----------------------------------------------------------------------------
template <class T>
list<T>::Box::Box(const T& value, Box* next, Box* previous)
	:value(value), next(next), previous(previous)
{
}

template <class T>
list<T>::Box::~Box()
{
	previous = next = nullptr;
}

// Class list<T>::iterator ------------------------------------------------------------------------
template <class T>
list<T>::iterator::iterator(Box* pos = nullptr)
	: pos(pos)
{
}

template <class T>
list<T>::iterator::iterator(const iterator& other)
	: pos(other.pos)
{
}

template <class T>
T& list<T>::iterator::operator*() const
{
	return pos->value;
}

template <class T>
T* list<T>::iterator::operator->() const
{
	return &(pos->value);
}

template <class T>
typename list<T>::iterator& list<T>::iterator::operator++()
{
	pos = pos->next;
	return *this;
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator++(int)
{
	pos = pos->next;
	return *this;
}

template <class T>
typename list<T>::iterator& list<T>::iterator::operator--()
{
	pos = pos->previous;
	return *this;
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator--(int cpt)
{
	pos = pos->previous;
	return *this;
}

template <class T>
bool list<T>::iterator::operator==(const iterator& left)
{
	return pos == left.pos;
}

template <class T>
bool list<T>::iterator::operator!=(const iterator& left)
{
	return pos != left.pos;
}

// Class list<T>::reverse_iterator ----------------------------------------------------------------
template <class T>
list<T>::reverse_iterator::reverse_iterator(Box* pos = nullptr)
	: pos(pos)
{
}

template <class T>
list<T>::reverse_iterator::reverse_iterator(const reverse_iterator& other)
	: pos(other.pos)
{
}

template <class T>
T& list<T>::reverse_iterator::operator*() const
{
	return pos->value;
}


template <class T>
T* list<T>::reverse_iterator::operator->() const
{
	return &(pos->value);
}

template <class T>
typename list<T>::reverse_iterator& list<T>::reverse_iterator::operator++()
{
	pos = pos->previous;
	return *this;
}

template <class T>
typename list<T>::reverse_iterator list<T>::reverse_iterator::operator++(int)
{
	pos = pos->previous;
	return *this;
}

template <class T>
typename list<T>::reverse_iterator& list<T>::reverse_iterator::operator--()
{
	pos = pos->next;
	return *this;
}

template <class T>
typename list<T>::reverse_iterator list<T>::reverse_iterator::operator--(int)
{
	pos = pos->next;
	return *this;
}

template <class T>
bool list<T>::reverse_iterator::operator==(const reverse_iterator& left)
{
	return pos == left.pos;
}

template <class T>
bool list<T>::reverse_iterator::operator!=(const reverse_iterator& left)
{
	return pos != left.pos;
}

// Class list<T>::const_iterator ------------------------------------------------------------------
template <class T>
list<T>::const_iterator::const_iterator(const Box* pos = nullptr)
	: pos(pos)
{
}

template <class T>
list<T>::const_iterator::const_iterator(const const_iterator& other)
	: pos(other.pos)
{
}

template <class T>
list<T>::const_iterator::const_iterator(const iterator& other)
	: pos(other.pos)
{
}

template <class T>
const T& list<T>::const_iterator::operator*() const
{
	return pos->value;
}

template <class T>
const T* list<T>::const_iterator::operator->() const
{
	return &(pos->value);
}

template <class T>
typename list<T>::const_iterator& list<T>::const_iterator::operator++()
{
	pos = pos->next;
	return *this;
}

template <class T>
typename list<T>::const_iterator list<T>::const_iterator::operator++(int)
{
	pos = pos->next;
	return *this;
}

template <class T>
typename list<T>::const_iterator& list<T>::const_iterator::operator--()
{
	pos = pos->previous;
	return *this;
}

template <class T>
typename list<T>::const_iterator list<T>::const_iterator::operator--(int cpt)
{
	pos = pos->previous;
	return *this;
}

template <class T>
bool list<T>::const_iterator::operator==(const const_iterator& left)
{
	return pos == left.pos;
}

template <class T>
bool list<T>::const_iterator::operator!=(const const_iterator& left)
{
	return pos != left.pos;
}

// Class list<T>::const_reverse_iterator ----------------------------------------------------------
template <class T>
list<T>::const_reverse_iterator::const_reverse_iterator(const Box* pos = nullptr)
	: pos(pos)
{
}

template <class T>
list<T>::const_reverse_iterator::const_reverse_iterator(const const_reverse_iterator& other)
	: pos(other.pos)
{
}

template <class T>
list<T>::const_reverse_iterator::const_reverse_iterator(const reverse_iterator& other)
	: pos(other.pos)
{
}

template <class T>
const T& list<T>::const_reverse_iterator::operator*() const
{
	return pos->value;
}


template <class T>
const T* list<T>::const_reverse_iterator::operator->() const
{
	return &(pos->value);
}

template <class T>
typename list<T>::const_reverse_iterator& list<T>::const_reverse_iterator::operator++()
{
	pos = pos->previous;
	return *this;
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::const_reverse_iterator::operator++(int)
{
	pos = pos->previous;
	return *this;
}

template <class T>
typename list<T>::const_reverse_iterator& list<T>::const_reverse_iterator::operator--()
{
	pos = pos->next;
	return *this;
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::const_reverse_iterator::operator--(int)
{
	pos = pos->next;
	return *this;
}

template <class T>
bool list<T>::const_reverse_iterator::operator==(const const_reverse_iterator& left)
{
	return pos == left.pos;
}

template <class T>
bool list<T>::const_reverse_iterator::operator!=(const const_reverse_iterator& left)
{
	return pos != left.pos;
}