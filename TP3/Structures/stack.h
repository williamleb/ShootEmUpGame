#pragma once

#include <vector>

namespace TP3_structures
{
	template <class T>
	class stack
	{
		std::vector<T> vect;

	public:
		using size_type = unsigned long;

		stack(void);
		stack(const stack<T>& other);
		~stack(void);

		void clear(void);

		void push(T val);

		void pop(void);

		T& top(void);
		const T& top(void) const;

		size_type size(void) const;

		bool empty(void) const;

		stack<T>& operator=(const stack<T>& other);

		void swap(stack& other);
	};
}

#include "stack.hpp"