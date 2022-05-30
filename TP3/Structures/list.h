#pragma once

namespace TP3_structures
{
	template <class T>
	class list
	{
	public:
		using size_type = unsigned long;

	private:
		struct Box;

		Box before, after;
		size_type sz;

		Box* insert(Box* position, const T& value);
		Box* erase(Box* position);

	public:
		class iterator;
		class reverse_iterator;
		class const_iterator;
		class const_reverse_iterator;

		// Fonctions membres
		list();
		~list();
		list(const list& other);
		list(std::initializer_list<T>);
		list& operator=(const list& other);
		void swap(list& other);

		// Fonctions modificatrices
		iterator insert(iterator pos, const T& value);
		iterator erase(iterator pos);
		reverse_iterator insert(reverse_iterator iterator, const T& value);
		reverse_iterator erase(reverse_iterator iterator);

		void push_back(const T& value);
		void pop_back();
		void push_front(const T& value);
		void pop_front();

		// Accesseurs
		T& back();
		T& front();
		const T& back()const;
		const T& front()const;

		void clear();
		size_type size() const;
		bool empty() const;

		// Itérateurs
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;

		// Opérations
		void reverse();
		void splice(iterator position, list& other);
		void resize(size_t new_size, const T& value = T());
		void remove(const T& value);
	};

	template <class T>
	struct list<T>::Box
	{
		T value;
		Box* next;
		Box* previous;

		Box(const T& value, Box* next = nullptr, Box* previous = nullptr);
		~Box();
	};

	template <class T>
	class list<T>::iterator
	{
		friend class list<T>;

		Box* pos;

	public:
		iterator(Box* pos = nullptr);
		iterator(const iterator& other);
		T& operator*() const;
		T* operator->() const;
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		bool operator==(const iterator& left);
		bool operator!=(const iterator& left);
	};

	template <class T>
	class list<T>::reverse_iterator
	{
		friend class list<T>;

		Box* pos;

	public:
		reverse_iterator(Box* pos = nullptr);
		reverse_iterator(const reverse_iterator& other);
		T& operator*() const;
		T* operator->() const;
		reverse_iterator& operator++();
		reverse_iterator operator++(int);
		reverse_iterator& operator--();
		reverse_iterator operator--(int);
		bool operator==(const reverse_iterator& left);
		bool operator!=(const reverse_iterator& left);
	};

	template <class T>
	class list<T>::const_iterator
	{
		friend class list<T>;

		const Box* pos;

	public:
		const_iterator(const Box* pos = nullptr);
		const_iterator(const const_iterator& other);
		const_iterator(const iterator& other);
		const T& operator*() const;
		const T* operator->() const;
		const_iterator& operator++();
		const_iterator operator++(int);
		const_iterator& operator--();
		const_iterator operator--(int);
		bool operator==(const const_iterator& left);
		bool operator!=(const const_iterator& left);
	};

	template <class T>
	class list<T>::const_reverse_iterator
	{
		friend class list<T>;

		const Box* pos;

	public:
		const_reverse_iterator(const Box* pos = nullptr);
		const_reverse_iterator(const const_reverse_iterator& other);
		const_reverse_iterator(const reverse_iterator& other);
		const T& operator*() const;
		const T* operator->() const;
		const_reverse_iterator& operator++();
		const_reverse_iterator operator++(int);
		const_reverse_iterator& operator--();
		const_reverse_iterator operator--(int);
		bool operator==(const const_reverse_iterator& left);
		bool operator!=(const const_reverse_iterator& left);
	};
}

#include "list.hpp"