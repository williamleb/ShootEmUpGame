#include "stack.h"

using namespace TP3_structures;

template <class T>
stack<T>::stack()
	:vect()
{
}

template <class T>
stack<T>::stack(const stack<T>& other)
{ 
	this->vect = other.vect; 
}

template <class T>
stack<T>::~stack()
{ 
	vect.~vector();
}

template <class T>
void stack<T>::clear(void)
{
	vect.clear();
}

template <class T>
void stack<T>::push(T val)
{ 
	vect.push_back(val); 
}

template <class T>
void stack<T>::pop() 
{ 
	vect.pop_back(); 
}

template <class T>
T& stack<T>::top()
{ 
	return vect.back(); 
}

template <class T>
const T& stack<T>::top() const
{
	return vect.back();
}

template <class T>
typename stack<T>::size_type stack<T>::size() const
{ 
	return vect.size(); 
}

template <class T>
bool stack<T>::empty() const
{ 
	return vect.empty(); 
}

template <class T>
stack<T>& stack<T>::operator=(const stack<T>& other) 
{ 
	this->vect = other.vect; 
	return *this;
}

template <class T>
void stack<T>::swap(stack& other) 
{ 
	vect.swap(other.vect);
}