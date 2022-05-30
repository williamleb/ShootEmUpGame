#pragma once

namespace TP3_structures
{
	template <class T>
	class deque
	{
	public:
		using size_type = unsigned long;

		// Fonctions membres
		deque(size_type reserve = 0);
		deque(const deque<T>& other);
		~deque();
		deque<T>& operator=(const deque<T>&);

		// Capacité
		bool empty() const;
		size_type size() const;
		void reserve(size_type new_cap);
		void resize(size_type new_size);
		size_type capacity() const;

		// Accesseurs
		T& operator[] (size_type index);
		T& at(size_type index);
		T& front();
		T& back();

		const T& operator[] (size_type index) const;
		const T& at(size_type index) const;
		const T& front() const;
		const T& back() const;

		// Modificateurs
		void clear();
		void push_back(const T& value);
		void push_front(const T& value);
		void pop_back();
		void pop_front();
		void swap(deque& other);

	private:
		T* tab;
		size_type start;
		size_type sz;
		size_type cap;
	};
}

#include "deque.hpp"