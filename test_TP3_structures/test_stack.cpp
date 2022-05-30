#include "stdafx.h"
#include "../TP3/Structures/stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TP3_structures;

namespace test_TP3_structures
{
	TEST_CLASS(test_stack)
	{
	public:
		TEST_METHOD(test_stack_constructor)
		{
			// Appel de la méthode à tester --------------
			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			// Validation des résultats ------------------
			Assert::IsTrue(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 0, stackRegular.size());

			Assert::IsTrue(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplex.size());

			Assert::IsTrue(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)0, stackPointer.size());
		}

		TEST_METHOD(test_stack_copyConstructor_emptyStack)
		{
			// Mise en place des données -----------------
			stack<int> stackRegularToCopy;
			stack<stack<int>> stackComplexToCopy;
			stack<int*> stackPointerToCopy;

			// Appel de la méthode à tester --------------
			stack<int> stackRegular(stackRegularToCopy);
			stack<stack<int>> stackComplex(stackComplexToCopy);
			stack<int*> stackPointer(stackPointerToCopy);

			// Validation des résultats ------------------
			Assert::IsTrue(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 0, stackRegular.size());

			Assert::IsTrue(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplex.size());

			Assert::IsTrue(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)0, stackPointer.size());
		}

		TEST_METHOD(test_stack_copyConstructor_filledStack)
		{
			// Mise en place des données -----------------
			stack<int> stackRegularToCopy;
			stackRegularToCopy.push(2);
			stackRegularToCopy.push(3);
			stackRegularToCopy.push(1);

			stack<stack<int>> stackComplexToCopy;
			stackComplexToCopy.push(stackRegularToCopy);

			stack<int*> stackPointerToCopy;
			int i = 10;
			int j = 9;
			stackPointerToCopy.push(&i);
			stackPointerToCopy.push(&j);

			// Appel de la méthode à tester --------------
			stack<int> stackRegular(stackRegularToCopy);
			stack<stack<int>> stackComplex(stackComplexToCopy);
			stack<int*> stackPointer(stackPointerToCopy);

			// Validation des résultats ------------------
			// On vérifie que les piles copiées sont égales aux originales.

			// La pile régulière.
			Assert::IsFalse(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 3, stackRegular.size());
			Assert::AreEqual(1, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(3, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(2, stackRegular.top());

			// La pile complexe.
			Assert::IsFalse(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)1, stackComplex.size());

			stack<int> result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.top());
			result.pop();
			Assert::AreEqual(3, result.top());
			result.pop();
			Assert::AreEqual(2, result.top());

			// La pile de pointeurs.
			Assert::IsFalse(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)2, stackPointer.size());
			Assert::AreEqual(9, *stackPointer.top());
			stackPointer.pop();
			Assert::AreEqual(10, *stackPointer.top());
		}

		TEST_METHOD(test_stack_destructor)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stackRegular.push(2);
			stackRegular.push(3);
			stackRegular.push(1);

			stack<stack<int>> stackComplex;
			stackComplex.push(stackRegular);

			stack<int*> stackPointer;
			int i = 10;
			int j = 9;
			stackPointer.push(&i);
			stackPointer.push(&j);

			// Appel de la méthode à tester --------------
			stackRegular.~stack();
			stackComplex.~stack();
			stackPointer.~stack();

			// Validation des résultats ------------------
			Assert::IsTrue(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 0, stackRegular.size());

			Assert::IsTrue(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplex.size());

			Assert::IsTrue(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)0, stackPointer.size());
		}

		TEST_METHOD(test_stack_clear)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stackRegular.push(2);
			stackRegular.push(3);
			stackRegular.push(1);

			stack<stack<int>> stackComplex;
			stackComplex.push(stackRegular);

			stack<int*> stackPointer;
			int i = 10;
			int j = 9;
			stackPointer.push(&i);
			stackPointer.push(&j);

			// Appel de la méthode à tester --------------
			stackRegular.clear();
			stackComplex.clear();
			stackPointer.clear();

			// Validation des résultats ------------------
			Assert::IsTrue(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 0, stackRegular.size());

			Assert::IsTrue(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplex.size());

			Assert::IsTrue(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)0, stackPointer.size());
		}

		TEST_METHOD(test_stack_push_firstValue)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			// Appel de la méthode à tester --------------
			stackRegular.push(2);
			stackComplex.push(stackRegular);
			int i = 10;
			stackPointer.push(&i);

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été ajouté.

			// La pile régulière.
			Assert::IsFalse(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 1, stackRegular.size());
			Assert::AreEqual(2, stackRegular.top());

			// La pile complexe.
			Assert::IsFalse(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)1, stackComplex.size());

			stack<int> result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 1, result.size());
			Assert::AreEqual(2, result.top());

			// La pile de pointeurs.
			Assert::IsFalse(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)1, stackPointer.size());
			Assert::AreEqual(10, *stackPointer.top());
		}

		TEST_METHOD(test_stack_push_manyValues)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			// Appel de la méthode à tester --------------
			stackRegular.push(2);
			stackRegular.push(3);
			stackRegular.push(1);

			stackComplex.push(stackRegular);
			stack<int> other;
			other.push(99);
			other.push(98);
			stackComplex.push(other);

			int i = 10;
			int j = 9;
			stackPointer.push(&i);
			stackPointer.push(&j);

			// Validation des résultats ------------------
			// On vérifie que les éléments ont bien été ajoutés.

			// La pile régulière.
			Assert::IsFalse(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 3, stackRegular.size());
			Assert::AreEqual(1, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(3, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(2, stackRegular.top());

			// La pile complexe.
			Assert::IsFalse(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)2, stackComplex.size());

			stack<int> result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 2, result.size());
			Assert::AreEqual(98, result.top());
			result.pop();
			Assert::AreEqual(99, result.top());

			stackComplex.pop();
			result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.top());
			result.pop();
			Assert::AreEqual(3, result.top());
			result.pop();
			Assert::AreEqual(2, result.top());

			// La pile de pointeurs.
			Assert::IsFalse(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)2, stackPointer.size());
			Assert::AreEqual(9, *stackPointer.top());
			stackPointer.pop();
			Assert::AreEqual(10, *stackPointer.top());
		}

		TEST_METHOD(test_stack_pop_manyValues)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			stackRegular.push(2);
			stackRegular.push(3);
			stackRegular.push(1);

			stackComplex.push(stackRegular);
			stack<int> other;
			other.push(99);
			other.push(98);
			stackComplex.push(other);

			int i = 10;
			int j = 9;
			stackPointer.push(&i);
			stackPointer.push(&j);

			// Appel de la méthode à tester --------------
			stackRegular.pop();
			stackComplex.pop();
			stackPointer.pop();

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été enlevé.

			// La pile régulière.
			Assert::IsFalse(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 2, stackRegular.size());
			Assert::AreEqual(3, stackRegular.top());

			// La pile complexe.
			Assert::IsFalse(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)1, stackComplex.size());

			stack<int> result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.top());

			// La pile de pointeurs.
			Assert::IsFalse(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)1, stackPointer.size());
			Assert::AreEqual(10, *stackPointer.top());
		}

		TEST_METHOD(test_stack_pop_oneValue)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			stackRegular.push(2);

			stackComplex.push(stackRegular);

			int i = 10;
			stackPointer.push(&i);

			// Appel de la méthode à tester --------------
			stackRegular.pop();
			stackComplex.pop();
			stackPointer.pop();

			// Validation des résultats ------------------
			Assert::IsTrue(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 0, stackRegular.size());

			Assert::IsTrue(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplex.size());

			Assert::IsTrue(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)0, stackPointer.size());
		}

		TEST_METHOD(test_stack_top_access)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			// Appel de la méthpde et validation ---------

			// La pile régulière.
			stackRegular.push(2);
			Assert::AreEqual(2, stackRegular.top());
			stackRegular.push(3);
			Assert::AreEqual(3, stackRegular.top());
			stackRegular.push(1);
			Assert::AreEqual(1, stackRegular.top());

			// La pile complexe.
			stackComplex.push(stackRegular);
			stack<int> result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.top());
			result.pop();
			Assert::AreEqual(3, result.top());
			result.pop();
			Assert::AreEqual(2, result.top());

			// La pile de pointeurs.
			int i = 10;
			int j = 9;
			stackPointer.push(&i);
			Assert::AreEqual(10, *stackPointer.top());
			stackPointer.push(&j);
			Assert::AreEqual(9, *stackPointer.top());
		}

		TEST_METHOD(test_stack_top_modify)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			// La pile régulière.
			stackRegular.push(2);
			stackRegular.push(3);
			stackRegular.push(1);

			// La pile complexe.
			stackComplex.push(stackRegular);

			// La pile de pointeurs.
			int i = 10;
			int j = 9;
			stackPointer.push(&i);
			stackPointer.push(&j);

			// Appel de la méthode à tester -----------------
			stackRegular.top() = 999;

			stack<int> other;
			other.push(1);
			stackComplex.top() = other;

			int k = 299;
			stackPointer.top() = &k;

			// Validation des résultats ---------------------
			Assert::AreEqual(999, stackRegular.top());

			stack<int> result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 1, result.size());
			Assert::AreEqual(1, result.top());

			Assert::AreEqual(299, *stackPointer.top());
		}

		void validate_test_stack_const_top_access(const stack<int>& stackRegular, const stack<stack<int>>& stackComplex, const stack<int*>& stackPointer)
		{
			// Appel de la méthode et validation ---------
			Assert::AreEqual(1, stackRegular.top());

			stack<int> result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.top());

			Assert::AreEqual(9, *stackPointer.top());
		}
		TEST_METHOD(test_stack_const_top_access)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			stackRegular.push(2);
			stackRegular.push(3);
			stackRegular.push(1);

			stackComplex.push(stackRegular);

			// La pile de pointeurs.
			int i = 10;
			int j = 9;
			stackPointer.push(&i);
			stackPointer.push(&j);

			validate_test_stack_const_top_access(stackRegular, stackComplex, stackPointer);
		}

		TEST_METHOD(test_stack_size)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			// Appel de la méthode et validation ---------

			// La pile régulière.
			Assert::AreEqual((stack<int>::size_type) 0, stackRegular.size());
			stackRegular.push(2);
			Assert::AreEqual((stack<int>::size_type) 1, stackRegular.size());
			stackRegular.push(3);
			Assert::AreEqual((stack<int>::size_type) 2, stackRegular.size());
			stackRegular.push(1);
			Assert::AreEqual((stack<int>::size_type) 3, stackRegular.size());

			// La pile complexe.
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplex.size());
			stackComplex.push(stackRegular);
			Assert::AreEqual((stack<stack<int>>::size_type)1, stackComplex.size());

			// La pile de pointeurs.
			Assert::AreEqual((stack<int*>::size_type)0, stackPointer.size());
			int i = 10;
			int j = 9;
			stackPointer.push(&i);
			Assert::AreEqual((stack<int*>::size_type)1, stackPointer.size());
			stackPointer.push(&j);
			Assert::AreEqual((stack<int*>::size_type)2, stackPointer.size());
		}

		TEST_METHOD(test_stack_empty)
		{
			// Mise en place des données -----------------
			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			// Appel de la méthode et validation ---------

			// La pile régulière.
			Assert::IsTrue(stackRegular.empty());
			stackRegular.push(2);
			Assert::IsFalse(stackRegular.empty());
			stackRegular.push(3);
			Assert::IsFalse(stackRegular.empty());
			stackRegular.push(1);
			Assert::IsFalse(stackRegular.empty());

			// La pile complexe.
			Assert::IsTrue(stackComplex.empty());
			stackComplex.push(stackRegular);
			Assert::IsFalse(stackComplex.empty());

			// La pile de pointeurs.
			Assert::IsTrue(stackPointer.empty());
			int i = 10;
			int j = 9;
			stackPointer.push(&i);
			Assert::IsFalse(stackPointer.empty());
			stackPointer.push(&j);
			Assert::IsFalse(stackPointer.empty());
		}

		TEST_METHOD(test_stack_operatorEqual_emptyStacks)
		{
			// Mise en place des données -----------------
			stack<int> stackRegularToCopy;
			stack<stack<int>> stackComplexToCopy;
			stack<int*> stackPointerToCopy;

			// Appel de la méthode à tester --------------
			stack<int> stackRegular = stackRegularToCopy;
			stack<stack<int>> stackComplex = stackComplexToCopy;
			stack<int*> stackPointer = stackPointerToCopy;

			// Validation des résultats ------------------
			Assert::IsTrue(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 0, stackRegular.size());

			Assert::IsTrue(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplex.size());

			Assert::IsTrue(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)0, stackPointer.size());
		}

		TEST_METHOD(test_stack_operatorEqual_emptyStackToCopy)
		{
			// Mise en place des données -----------------
			stack<int> stackRegularToCopy;
			stack<stack<int>> stackComplexToCopy;
			stack<int*> stackPointerToCopy;

			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			stackRegular.push(2);
			stackRegular.push(3);
			stackRegular.push(1);

			stackComplex.push(stackRegular);
			stack<int> other;
			other.push(99);
			other.push(98);
			stackComplex.push(other);

			int i = 10;
			int j = 9;
			stackPointer.push(&i);
			stackPointer.push(&j);

			// Appel de la méthode à tester --------------
			stackRegular = stackRegularToCopy;
			stackComplex = stackComplexToCopy;
			stackPointer = stackPointerToCopy;

			// Validation des résultats ------------------
			Assert::IsTrue(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 0, stackRegular.size());

			Assert::IsTrue(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplex.size());

			Assert::IsTrue(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)0, stackPointer.size());
		}

		TEST_METHOD(test_stack_operatorEqual_filledStackToCopy)
		{
			// Mise en place des données -----------------
			stack<int> stackRegularToCopy;
			stackRegularToCopy.push(2);
			stackRegularToCopy.push(3);
			stackRegularToCopy.push(1);

			stack<stack<int>> stackComplexToCopy;
			stackComplexToCopy.push(stackRegularToCopy);

			stack<int*> stackPointerToCopy;
			int i = 10;
			int j = 9;
			stackPointerToCopy.push(&i);
			stackPointerToCopy.push(&j);

			// Appel de la méthode à tester --------------
			stack<int> stackRegular = stackRegularToCopy;
			stack<stack<int>> stackComplex = stackComplexToCopy;
			stack<int*> stackPointer = stackPointerToCopy;

			// Validation des résultats ------------------
			// On vérifie que les piles copiées sont égales aux originales.

			// La pile régulière.
			Assert::IsFalse(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 3, stackRegular.size());
			Assert::AreEqual(1, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(3, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(2, stackRegular.top());

			// La pile complexe.
			Assert::IsFalse(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)1, stackComplex.size());

			stack<int> result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.top());
			result.pop();
			Assert::AreEqual(3, result.top());
			result.pop();
			Assert::AreEqual(2, result.top());

			// La pile de pointeurs.
			Assert::IsFalse(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)2, stackPointer.size());
			Assert::AreEqual(9, *stackPointer.top());
			stackPointer.pop();
			Assert::AreEqual(10, *stackPointer.top());
		}

		TEST_METHOD(test_stack_operatorEqual_filledStacks)
		{
			// Mise en place des données -----------------
			stack<int> stackRegularToCopy;
			stackRegularToCopy.push(2);
			stackRegularToCopy.push(3);
			stackRegularToCopy.push(1);

			stack<stack<int>> stackComplexToCopy;
			stackComplexToCopy.push(stackRegularToCopy);

			stack<int*> stackPointerToCopy;
			int i = 10;
			int j = 9;
			stackPointerToCopy.push(&i);
			stackPointerToCopy.push(&j);

			stack<int> stackRegular;
			stackRegular.push(7);
			stackRegular.push(6);
			stackRegular.push(2);
			stackRegular.push(22);
			stackRegular.push(44);
			stackRegular.push(66);

			stack<stack<int>> stackComplex;
			stackComplex.push(stackRegular);
			stack<int> other;
			other.push(3453);
			other.push(462);
			stackComplex.push(other);

			stack<int*> stackPointer;
			int k = 23;
			int l = 14;
			stackPointer.push(&i);
			stackPointer.push(&j);

			// Appel de la méthode à tester --------------
			stackRegular = stackRegularToCopy;
			stackComplex = stackComplexToCopy;
			stackPointer = stackPointerToCopy;

			// Validation des résultats ------------------
			// On vérifie que les piles copiées sont égales aux originales.

			// La pile régulière.
			Assert::IsFalse(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 3, stackRegular.size());
			Assert::AreEqual(1, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(3, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(2, stackRegular.top());

			// La pile complexe.
			Assert::IsFalse(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)1, stackComplex.size());

			stack<int> result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.top());
			result.pop();
			Assert::AreEqual(3, result.top());
			result.pop();
			Assert::AreEqual(2, result.top());

			// La pile de pointeurs.
			Assert::IsFalse(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)2, stackPointer.size());
			Assert::AreEqual(9, *stackPointer.top());
			stackPointer.pop();
			Assert::AreEqual(10, *stackPointer.top());
		}

		TEST_METHOD(test_stack_swap_emptyStacks)
		{
			// Mise en place des données -----------------
			stack<int> stackRegularToCopy;
			stack<stack<int>> stackComplexToCopy;
			stack<int*> stackPointerToCopy;

			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			// Appel de la méthode à tester --------------
			stackRegular.swap(stackRegularToCopy);
			stackComplex.swap(stackComplexToCopy);
			stackPointer.swap(stackPointerToCopy);

			// Validation des résultats ------------------
			// Les premières piles doivent avoir les valeurs des deuxièmes.
			Assert::IsTrue(stackRegularToCopy.empty());
			Assert::AreEqual((stack<int>::size_type) 0, stackRegularToCopy.size());

			Assert::IsTrue(stackComplexToCopy.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplexToCopy.size());

			Assert::IsTrue(stackPointerToCopy.empty());
			Assert::AreEqual((stack<int*>::size_type)0, stackPointerToCopy.size());

			// Les deuxièmes piles doivent avoir les valeurs des premières.
			Assert::IsTrue(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 0, stackRegular.size());

			Assert::IsTrue(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplex.size());

			Assert::IsTrue(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)0, stackPointer.size());
		}

		TEST_METHOD(test_stack_swap_oneFilledStack)
		{
			// Mise en place des données -----------------
			stack<int> stackRegularToCopy;
			stackRegularToCopy.push(2);
			stackRegularToCopy.push(3);
			stackRegularToCopy.push(1);

			stack<stack<int>> stackComplexToCopy;
			stackComplexToCopy.push(stackRegularToCopy);

			stack<int*> stackPointerToCopy;
			int i = 10;
			int j = 9;
			stackPointerToCopy.push(&i);
			stackPointerToCopy.push(&j);

			stack<int> stackRegular;
			stack<stack<int>> stackComplex;
			stack<int*> stackPointer;

			// Appel de la méthode à tester --------------
			stackRegular.swap(stackRegularToCopy);
			stackComplex.swap(stackComplexToCopy);
			stackPointer.swap(stackPointerToCopy);

			// Validation des résultats ------------------
			// Les premières piles doivent avoir les valeurs des deuxièmes.
			Assert::IsTrue(stackRegularToCopy.empty());
			Assert::AreEqual((stack<int>::size_type) 0, stackRegularToCopy.size());

			Assert::IsTrue(stackComplexToCopy.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)0, stackComplexToCopy.size());

			Assert::IsTrue(stackPointerToCopy.empty());
			Assert::AreEqual((stack<int*>::size_type)0, stackPointerToCopy.size());

			// Les deuxièmes piles doivent avoir les valeurs des premières.
			// La pile régulière.
			Assert::IsFalse(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 3, stackRegular.size());
			Assert::AreEqual(1, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(3, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(2, stackRegular.top());

			// La pile complexe.
			Assert::IsFalse(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)1, stackComplex.size());

			stack<int> result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.top());
			result.pop();
			Assert::AreEqual(3, result.top());
			result.pop();
			Assert::AreEqual(2, result.top());

			// La pile de pointeurs.
			Assert::IsFalse(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)2, stackPointer.size());
			Assert::AreEqual(9, *stackPointer.top());
			stackPointer.pop();
			Assert::AreEqual(10, *stackPointer.top());
		}

		TEST_METHOD(test_stack_swap_twoFilledStacks)
		{
			// Mise en place des données -----------------
			stack<int> stackRegularToCopy;
			stackRegularToCopy.push(2);
			stackRegularToCopy.push(3);
			stackRegularToCopy.push(1);

			stack<stack<int>> stackComplexToCopy;
			stackComplexToCopy.push(stackRegularToCopy);

			stack<int*> stackPointerToCopy;
			int i = 10;
			int j = 9;
			stackPointerToCopy.push(&i);
			stackPointerToCopy.push(&j);

			stack<int> stackRegular;
			stackRegular.push(7);
			stackRegular.push(6);
			stackRegular.push(2);
			stackRegular.push(22);
			stackRegular.push(44);
			stackRegular.push(66);

			stack<stack<int>> stackComplex;
			stackComplex.push(stackRegular);
			stack<int> other;
			other.push(3453);
			other.push(462);
			stackComplex.push(other);

			stack<int*> stackPointer;
			int k = 23;
			int l = 14;
			stackPointer.push(&k);
			stackPointer.push(&l);

			// Appel de la méthode à tester --------------
			stackRegular.swap(stackRegularToCopy);
			stackComplex.swap(stackComplexToCopy);
			stackPointer.swap(stackPointerToCopy);

			// Validation des résultats ------------------
			// Les premières piles doivent avoir les valeurs des deuxièmes.
			// La pile régulière.
			Assert::IsFalse(stackRegularToCopy.empty());
			Assert::AreEqual((stack<int>::size_type) 6, stackRegularToCopy.size());
			Assert::AreEqual(66, stackRegularToCopy.top());
			stackRegularToCopy.pop();
			Assert::AreEqual(44, stackRegularToCopy.top());
			stackRegularToCopy.pop();
			Assert::AreEqual(22, stackRegularToCopy.top());
			stackRegularToCopy.pop();
			Assert::AreEqual(2, stackRegularToCopy.top());
			stackRegularToCopy.pop();
			Assert::AreEqual(6, stackRegularToCopy.top());
			stackRegularToCopy.pop();
			Assert::AreEqual(7, stackRegularToCopy.top());

			// La pile complexe.
			Assert::IsFalse(stackComplexToCopy.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)2, stackComplexToCopy.size());

			stack<int> result = stackComplexToCopy.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 2, result.size());
			Assert::AreEqual(462, result.top());
			result.pop();
			Assert::AreEqual(3453, result.top());

			stackComplexToCopy.pop();
			result = stackComplexToCopy.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 6, result.size());
			Assert::AreEqual(66, result.top());
			result.pop();
			Assert::AreEqual(44, result.top());
			result.pop();
			Assert::AreEqual(22, result.top());
			result.pop();
			Assert::AreEqual(2, result.top());
			result.pop();
			Assert::AreEqual(6, result.top());
			result.pop();
			Assert::AreEqual(7, result.top());

			// La pile de pointeurs.
			Assert::IsFalse(stackPointerToCopy.empty());
			Assert::AreEqual((stack<int*>::size_type)2, stackPointerToCopy.size());
			Assert::AreEqual(14, *stackPointerToCopy.top());
			stackPointerToCopy.pop();
			Assert::AreEqual(23, *stackPointerToCopy.top());

			// Les deuxièmes piles doivent avoir les valeurs des premières.
			// La pile régulière.
			Assert::IsFalse(stackRegular.empty());
			Assert::AreEqual((stack<int>::size_type) 3, stackRegular.size());
			Assert::AreEqual(1, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(3, stackRegular.top());
			stackRegular.pop();
			Assert::AreEqual(2, stackRegular.top());

			// La pile complexe.
			Assert::IsFalse(stackComplex.empty());
			Assert::AreEqual((stack<stack<int>>::size_type)1, stackComplex.size());

			result = stackComplex.top();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((stack<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.top());
			result.pop();
			Assert::AreEqual(3, result.top());
			result.pop();
			Assert::AreEqual(2, result.top());

			// La pile de pointeurs.
			Assert::IsFalse(stackPointer.empty());
			Assert::AreEqual((stack<int*>::size_type)2, stackPointer.size());
			Assert::AreEqual(9, *stackPointer.top());
			stackPointer.pop();
			Assert::AreEqual(10, *stackPointer.top());
		}

	};
}