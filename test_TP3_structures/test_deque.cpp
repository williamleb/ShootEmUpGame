#include "stdafx.h"
#include "../TP3/Structures/deque.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TP3_structures;

namespace test_TP3_structures
{
	TEST_CLASS(test_deque)
	{
	public:
		TEST_METHOD(test_deque_constructor)
		{
			// Appel de la méthode à tester --------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			// Validation des résultats ------------------
			Assert::IsTrue(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.size());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.capacity());

			Assert::IsTrue(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.capacity());

			Assert::IsTrue(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_copyConstructor_emptyDeques)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegularToCopy;
			deque<deque<int>> dequeComplexToCopy;
			deque<int*> dequePointerToCopy;

			// Appel de la méthode à tester --------------
			deque<int> dequeRegular(dequeRegularToCopy);
			deque<deque<int>> dequeComplex(dequeComplexToCopy);
			deque<int*> dequePointer(dequePointerToCopy);

			// Validation des résultats ------------------
			Assert::IsTrue(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.size());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.capacity());

			Assert::IsTrue(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.capacity());

			Assert::IsTrue(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_copyConstructor_filledDeques)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegularToCopy;
			dequeRegularToCopy.push_back(2);
			dequeRegularToCopy.push_back(3);
			dequeRegularToCopy.push_back(1);

			deque<deque<int>> dequeComplexToCopy;
			dequeComplexToCopy.push_back(dequeRegularToCopy);

			deque<int*> dequePointerToCopy;
			int i = 10;
			int j = 9;
			dequePointerToCopy.push_back(&i);
			dequePointerToCopy.push_back(&j);

			// Appel de la méthode à tester --------------
			deque<int> dequeRegular(dequeRegularToCopy);
			deque<deque<int>> dequeComplex(dequeComplexToCopy);
			deque<int*> dequePointer(dequePointerToCopy);

			// Validation des résultats ------------------
			// On vérifie que les files copiées sont égales aux originales.

			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 3, dequeRegular.size());
			Assert::AreEqual(2, dequeRegular[0]);
			Assert::AreEqual(3, dequeRegular[1]);
			Assert::AreEqual(1, dequeRegular[2]);

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result[0]);
			Assert::AreEqual(3, result[1]);
			Assert::AreEqual(1, result[2]);

			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)2, dequePointer.size());
			Assert::AreEqual(10, *dequePointer[0]);
			Assert::AreEqual(9, *dequePointer[1]);
		}

		TEST_METHOD(test_deque_destructor)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_back(2);
			dequeRegular.push_back(3);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode à tester --------------
			dequeRegular.~deque();
			dequeComplex.~deque();
			dequePointer.~deque();

			// Validation des résultats ------------------
			Assert::IsTrue(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.size());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.capacity());

			Assert::IsTrue(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.capacity());

			Assert::IsTrue(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_operatorEqual_emptyDeques)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegularToCopy;
			deque<deque<int>> dequeComplexToCopy;
			deque<int*> dequePointerToCopy;

			// Appel de la méthode à tester --------------
			deque<int> dequeRegular = dequeRegularToCopy;
			deque<deque<int>> dequeComplex = dequeComplexToCopy;
			deque<int*> dequePointer = dequePointerToCopy;

			// Validation des résultats ------------------
			Assert::IsTrue(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.size());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.capacity());

			Assert::IsTrue(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.capacity());

			Assert::IsTrue(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_operatorEqual_emptyDequeToCopy)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegularToCopy;
			deque<deque<int>> dequeComplexToCopy;
			deque<int*> dequePointerToCopy;

			deque<int> dequeRegular;
			dequeRegular.push_back(999);
			dequeRegular.push_back(1024);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);
			deque<int> other;
			other.push_back(606);
			other.push_back(24);
			other.push_back(49);
			other.push_back(63);
			dequeComplex.push_back(other);

			deque<int*> dequePointer;
			int k = 99;
			dequePointer.push_back(&k);

			// Appel de la méthode à tester --------------
			dequeRegular = dequeRegularToCopy;
			dequeComplex = dequeComplexToCopy;
			dequePointer = dequePointerToCopy;

			// Validation des résultats ------------------
			Assert::IsTrue(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.size());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.capacity());

			Assert::IsTrue(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.capacity());

			Assert::IsTrue(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_operatorEqual_filledDequeToCopy)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegularToCopy;
			dequeRegularToCopy.push_back(2);
			dequeRegularToCopy.push_back(3);
			dequeRegularToCopy.push_back(1);

			deque<deque<int>> dequeComplexToCopy;
			dequeComplexToCopy.push_back(dequeRegularToCopy);

			deque<int*> dequePointerToCopy;
			int i = 10;
			int j = 9;
			dequePointerToCopy.push_back(&i);
			dequePointerToCopy.push_back(&j);

			// Appel de la méthode à tester --------------
			deque<int> dequeRegular = dequeRegularToCopy;
			deque<deque<int>> dequeComplex = dequeComplexToCopy;
			deque<int*> dequePointer = dequePointerToCopy;

			// Validation des résultats ------------------
			// On vérifie que les files copiées sont égales aux originales.

			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 3, dequeRegular.size());
			Assert::AreEqual(2, dequeRegular[0]);
			Assert::AreEqual(3, dequeRegular[1]);
			Assert::AreEqual(1, dequeRegular[2]);

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result[0]);
			Assert::AreEqual(3, result[1]);
			Assert::AreEqual(1, result[2]);

			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)2, dequePointer.size());
			Assert::AreEqual(10, *dequePointer[0]);
			Assert::AreEqual(9, *dequePointer[1]);
		}

		TEST_METHOD(test_deque_operatorEqual_filledDeques)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegularToCopy;
			dequeRegularToCopy.push_back(2);
			dequeRegularToCopy.push_back(3);
			dequeRegularToCopy.push_back(1);

			deque<deque<int>> dequeComplexToCopy;
			dequeComplexToCopy.push_back(dequeRegularToCopy);

			deque<int*> dequePointerToCopy;
			int i = 10;
			int j = 9;
			dequePointerToCopy.push_back(&i);
			dequePointerToCopy.push_back(&j);

			deque<int> dequeRegular;
			dequeRegular.push_back(999);
			dequeRegular.push_back(1024);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);
			deque<int> other;
			other.push_back(606);
			other.push_back(24);
			other.push_back(49);
			other.push_back(63);
			dequeComplex.push_back(other);

			deque<int*> dequePointer;
			int k = 99;
			dequePointer.push_back(&k);

			// Appel de la méthode à tester --------------
			dequeRegular = dequeRegularToCopy;
			dequeComplex = dequeComplexToCopy;
			dequePointer = dequePointerToCopy;

			// Validation des résultats ------------------
			// On vérifie que les files copiées sont égales aux originales.

			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 3, dequeRegular.size());
			Assert::AreEqual(2, dequeRegular[0]);
			Assert::AreEqual(3, dequeRegular[1]);
			Assert::AreEqual(1, dequeRegular[2]);

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result[0]);
			Assert::AreEqual(3, result[1]);
			Assert::AreEqual(1, result[2]);

			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)2, dequePointer.size());
			Assert::AreEqual(10, *dequePointer[0]);
			Assert::AreEqual(9, *dequePointer[1]);
		}

		TEST_METHOD(test_deque_empty)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			// Appel de la méthpde et validation ---------

			// La file régulière.
			Assert::IsTrue(dequeRegular.empty());
			dequeRegular.push_back(2);
			Assert::IsFalse(dequeRegular.empty());
			dequeRegular.push_back(3);
			Assert::IsFalse(dequeRegular.empty());
			dequeRegular.push_back(1);
			Assert::IsFalse(dequeRegular.empty());

			// La file complexe.
			Assert::IsTrue(dequeComplex.empty());
			dequeComplex.push_back(dequeRegular);
			Assert::IsFalse(dequeComplex.empty());

			// La file de pointeurs.
			Assert::IsTrue(dequePointer.empty());
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			Assert::IsFalse(dequePointer.empty());
			dequePointer.push_back(&j);
			Assert::IsFalse(dequePointer.empty());
		}

		TEST_METHOD(test_deque_size)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			// Appel de la méthode et validation ---------

			// La file régulière.
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.size());
			dequeRegular.push_back(2);
			Assert::AreEqual((deque<int>::size_type) 1, dequeRegular.size());
			dequeRegular.push_back(3);
			Assert::AreEqual((deque<int>::size_type) 2, dequeRegular.size());
			dequeRegular.push_back(1);
			Assert::AreEqual((deque<int>::size_type) 3, dequeRegular.size());

			// La file complexe.
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());
			dequeComplex.push_back(dequeRegular);
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			// La file de pointeurs.
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			Assert::AreEqual((deque<int*>::size_type)1, dequePointer.size());
			dequePointer.push_back(&j);
			Assert::AreEqual((deque<int*>::size_type)2, dequePointer.size());
		}

		TEST_METHOD(test_deque_reserve_noReserve)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_back(2);
			dequeRegular.push_back(3);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;

			deque<int*> dequePointer;
			int i = 10;
			dequePointer.push_back(&i);

			// Appel de la méthode et validation ---------
			// On teste lorsqu'on réserve un nombre égale et un nombre inférieur à la capacité.
			// Dans ces cas la capacité ne devrait pas changer.

			// La file régulière.
			deque<int>::size_type oldCapacity = dequeRegular.capacity();
			dequeRegular.reserve(oldCapacity);
			Assert::AreEqual((deque<int>::size_type) oldCapacity, dequeRegular.capacity());
			dequeRegular.reserve(oldCapacity - 1);
			Assert::AreEqual((deque<int>::size_type) oldCapacity, dequeRegular.capacity());
			dequeRegular.reserve(0);
			Assert::AreEqual((deque<int>::size_type) oldCapacity, dequeRegular.capacity());

			// La file complexe.
			dequeComplex.reserve(0);
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.capacity());

			// La file de pointeurs.
			oldCapacity = dequePointer.capacity();
			dequePointer.reserve(oldCapacity);
			Assert::AreEqual((deque<int*>::size_type)oldCapacity, dequePointer.capacity());
			dequePointer.reserve(oldCapacity - 1);
			Assert::AreEqual((deque<int*>::size_type)oldCapacity, dequePointer.capacity());
			dequePointer.reserve(0);
			Assert::AreEqual((deque<int*>::size_type)oldCapacity, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_reserve_trueReserve)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_back(2);
			dequeRegular.push_back(3);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;

			deque<int*> dequePointer;
			int i = 10;
			dequePointer.push_back(&i);

			// Appel de la méthode et validation ---------

			// La file régulière.
			deque<int>::size_type oldCapacity = dequeRegular.capacity();
			dequeRegular.reserve(oldCapacity + 1);
			Assert::AreEqual((deque<int>::size_type) oldCapacity + 1, dequeRegular.capacity());
			dequeRegular.reserve(200);
			Assert::AreEqual((deque<int>::size_type) 200, dequeRegular.capacity());

			// La file complexe.
			dequeComplex.reserve(1);
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.capacity());
			dequeComplex.reserve(13);
			Assert::AreEqual((deque<deque<int>>::size_type)13, dequeComplex.capacity());

			// La file de pointeurs.
			oldCapacity = dequePointer.capacity();
			dequePointer.reserve(oldCapacity + 1);
			Assert::AreEqual((deque<int*>::size_type)oldCapacity + 1, dequePointer.capacity());
			dequePointer.reserve(40);
			Assert::AreEqual((deque<int*>::size_type)40, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_resize_noResize)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_back(2);
			dequeRegular.push_back(3);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;

			deque<int*> dequePointer;
			int i = 10;
			dequePointer.push_back(&i);

			// Appel de la méthode et validation ---------
			// On teste lorsqu'on réserve un nombre égale à la taille.
			// Dans ces cas la taille et la capacité ne devraient pas changer.

			// La file régulière.
			deque<int>::size_type oldCapacity = dequeRegular.capacity();
			dequeRegular.resize(3);
			Assert::AreEqual((deque<int>::size_type) 3, dequeRegular.size());
			Assert::AreEqual((deque<int>::size_type) oldCapacity, dequeRegular.capacity());

			// La file complexe.
			dequeComplex.resize(0);
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.capacity());

			// La file de pointeurs.
			oldCapacity = dequePointer.capacity();
			dequePointer.resize(1);
			Assert::AreEqual((deque<int*>::size_type)1, dequePointer.size());
			Assert::AreEqual((deque<int*>::size_type)oldCapacity, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_resize_greaterResize)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_back(2);
			dequeRegular.push_back(3);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;

			deque<int*> dequePointer;
			int i = 10;
			dequePointer.push_back(&i);

			// Appel de la méthode à tester --------------
			// On teste lorsqu'on réserve un nombre supérieur à la taille.
			// Dans ce cas, la taille devrait avoir changé en conséquant et les valeurs
			// devraient être des valeurs par défauts.
			dequeRegular.resize(6);
			dequeComplex.resize(1);
			dequePointer.resize(55);

			// Validation des résultats ------------------
			// La file régulière.
			Assert::AreEqual((deque<int>::size_type) 6, dequeRegular.size());
			for (int i = 3; i < 6; ++i)
			{
				Assert::AreEqual(int(), dequeRegular[i]);
			}

			// La file complexe.
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			deque<int> result = dequeComplex[0];
			Assert::IsTrue(result.empty());
			Assert::AreEqual((deque<int>::size_type)0, result.size());

			// La file de pointeurs.
			Assert::AreEqual((deque<int*>::size_type)55, dequePointer.size());
			for (int i = 1; i < 55; ++i)
			{
				Assert::AreEqual((int*)nullptr, dequePointer[i]);
			}
		}

		TEST_METHOD(test_deque_resize_lesserResize)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_back(2);
			dequeRegular.push_back(3);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			dequePointer.push_back(&i);

			// Appel de la méthode et validation ---------
			// On teste lorsqu'on réserve un nombre plus petit que la taille.
			// Dans ce cas la taille devrait changer, mais pas la capacité.

			// La file régulière.
			deque<int>::size_type oldCapacity = dequeRegular.capacity();
			dequeRegular.resize(2);
			Assert::AreEqual((deque<int>::size_type) 2, dequeRegular.size());
			Assert::AreEqual((deque<int>::size_type) oldCapacity, dequeRegular.capacity());

			// La file complexe.
			oldCapacity = dequeComplex.capacity();
			dequeComplex.resize(0);
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());
			Assert::AreEqual((deque<deque<int>>::size_type)oldCapacity, dequeComplex.capacity());

			// La file de pointeurs.
			oldCapacity = dequePointer.capacity();
			dequePointer.resize(0);
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
			Assert::AreEqual((deque<int*>::size_type)oldCapacity, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_capacity)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			// Appel de la méthode et validation ---------

			// La file régulière.
			Assert::AreEqual((deque<int>::size_type)0, dequeRegular.capacity());
			dequeRegular.reserve(20);
			Assert::AreEqual((deque<int>::size_type)20, dequeRegular.capacity());

			// La file complexe.
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.capacity());
			dequeComplex.reserve(90);
			Assert::AreEqual((deque<deque<int>>::size_type)90, dequeComplex.capacity());

			// La file de pointeurs.
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.capacity());
			dequePointer.resize(2);
			Assert::AreEqual((deque<int*>::size_type)2, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_operatorBracket_access)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode et validation ---------

			// La file régulière.
			Assert::AreEqual(2, dequeRegular[0]);
			Assert::AreEqual(3, dequeRegular[1]);
			Assert::AreEqual(1, dequeRegular[2]);

			// La file complexe.
			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result[0]);
			Assert::AreEqual(3, result[1]);
			Assert::AreEqual(1, result[2]);

			// La file de pointeurs.
			Assert::AreEqual(10, *dequePointer[0]);
			Assert::AreEqual(9, *dequePointer[1]);
		}

		void validate_test_deque_const_operatorBracket_access(const deque<int>& dequeRegular, const deque<deque<int>>& dequeComplex, const deque<int*>& dequePointer)
		{
			// La file régulière.
			Assert::AreEqual(2, dequeRegular[0]);
			Assert::AreEqual(3, dequeRegular[1]);
			Assert::AreEqual(1, dequeRegular[2]);

			// La file complexe.
			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result[0]);
			Assert::AreEqual(3, result[1]);
			Assert::AreEqual(1, result[2]);

			// La file de pointeurs.
			Assert::AreEqual(10, *dequePointer[0]);
			Assert::AreEqual(9, *dequePointer[1]);
		}
		TEST_METHOD(test_deque_const_operatorBracket_access)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode et validation ---------
			validate_test_deque_const_operatorBracket_access(dequeRegular, dequeComplex, dequePointer);
		}

		TEST_METHOD(test_deque_operatorBracket_modify)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode à tester --------------
			dequeRegular[0] = 99;
			dequeRegular[1] = 139;
			dequeRegular[2] = 90;

			deque<int> other;
			other.push_back(10'000);
			dequeComplex[0] = other;

			int k = 88;
			int l = 0;
			dequePointer[0] = &k;
			dequePointer[1] = &l;

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(99, dequeRegular[0]);
			Assert::AreEqual(139, dequeRegular[1]);
			Assert::AreEqual(90, dequeRegular[2]);

			// La file complexe.
			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result[0]);

			// La file de pointeurs.
			Assert::AreEqual(88, *dequePointer[0]);
			Assert::AreEqual(0, *dequePointer[1]);
		}

		TEST_METHOD(test_deque_at_access)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode et validation ---------

			// La file régulière.
			Assert::AreEqual(2, dequeRegular.at(0));
			Assert::AreEqual(3, dequeRegular.at(1));
			Assert::AreEqual(1, dequeRegular.at(2));

			// La file complexe.
			deque<int> result = dequeComplex.at(0);
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result.at(0));
			Assert::AreEqual(3, result.at(1));
			Assert::AreEqual(1, result.at(2));

			// La file de pointeurs.
			Assert::AreEqual(10, *dequePointer.at(0));
			Assert::AreEqual(9, *dequePointer.at(1));
		}

		void validate_test_deque_const_at_access(const deque<int>& dequeRegular, const deque<deque<int>>& dequeComplex, const deque<int*>& dequePointer)
		{
			// La file régulière.
			Assert::AreEqual(2, dequeRegular.at(0));
			Assert::AreEqual(3, dequeRegular.at(1));
			Assert::AreEqual(1, dequeRegular.at(2));

			// La file complexe.
			deque<int> result = dequeComplex.at(0);
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result.at(0));
			Assert::AreEqual(3, result.at(1));
			Assert::AreEqual(1, result.at(2));

			// La file de pointeurs.
			Assert::AreEqual(10, *dequePointer.at(0));
			Assert::AreEqual(9, *dequePointer.at(1));
		}
		TEST_METHOD(test_deque_const_at_access)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode et validation ---------
			validate_test_deque_const_at_access(dequeRegular, dequeComplex, dequePointer);
		}

		TEST_METHOD(test_deque_at_modify)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode à tester --------------
			dequeRegular.at(0) = 99;
			dequeRegular.at(1) = 139;
			dequeRegular.at(2) = 90;

			deque<int> other;
			other.push_back(10'000);
			dequeComplex.at(0) = other;

			int k = 88;
			int l = 0;
			dequePointer.at(0) = &k;
			dequePointer.at(1) = &l;

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(99, dequeRegular.at(0));
			Assert::AreEqual(139, dequeRegular.at(1));
			Assert::AreEqual(90, dequeRegular.at(2));

			// La file complexe.
			deque<int> result = dequeComplex.at(0);
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.at(0));

			// La file de pointeurs.
			Assert::AreEqual(88, *dequePointer.at(0));
			Assert::AreEqual(0, *dequePointer.at(1));
		}

		TEST_METHOD(test_deque_front_access)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode et validation ---------

			// La file régulière.
			Assert::AreEqual(2, dequeRegular.front());

			// La file complexe.
			deque<int> result = dequeComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result.front());
			Assert::AreEqual(3, result.at(1));
			Assert::AreEqual(1, result.at(2));

			// La file de pointeurs.
			Assert::AreEqual(10, *dequePointer.front());
		}

		void validate_test_deque_const_front_access(const deque<int>& dequeRegular, const deque<deque<int>>& dequeComplex, const deque<int*>& dequePointer)
		{
			// La file régulière.
			Assert::AreEqual(2, dequeRegular.front());

			// La file complexe.
			deque<int> result = dequeComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result.front());
			Assert::AreEqual(3, result.at(1));
			Assert::AreEqual(1, result.at(2));

			// La file de pointeurs.
			Assert::AreEqual(10, *dequePointer.front());
		}
		TEST_METHOD(test_deque_const_front_access)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode et validation ---------
			validate_test_deque_const_front_access(dequeRegular, dequeComplex, dequePointer);
		}

		TEST_METHOD(test_deque_front_modify)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode à tester --------------
			dequeRegular.front() = 99;

			deque<int> other;
			other.push_back(10'000);
			dequeComplex.front() = other;

			int k = 88;
			dequePointer.front() = &k;

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(99, dequeRegular.front());

			// La file complexe.
			deque<int> result = dequeComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.front());

			// La file de pointeurs.
			Assert::AreEqual(88, *dequePointer.front());
		}

		TEST_METHOD(test_deque_back_access)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode et validation ---------

			// La file régulière.
			Assert::AreEqual(1, dequeRegular.back());

			// La file complexe.
			deque<int> result = dequeComplex.back();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result.at(0));
			Assert::AreEqual(3, result.at(1));
			Assert::AreEqual(1, result.back());

			// La file de pointeurs.
			Assert::AreEqual(9, *dequePointer.back());
		}

		void validate_test_deque_const_back_access(const deque<int>& dequeRegular, const deque<deque<int>>& dequeComplex, const deque<int*>& dequePointer)
		{
			// La file régulière.
			Assert::AreEqual(1, dequeRegular.back());

			// La file complexe.
			deque<int> result = dequeComplex.back();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result.at(0));
			Assert::AreEqual(3, result.at(1));
			Assert::AreEqual(1, result.back());

			// La file de pointeurs.
			Assert::AreEqual(9, *dequePointer.back());
		}
		TEST_METHOD(test_deque_const_back_access)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode et validation ---------
			validate_test_deque_const_back_access(dequeRegular, dequeComplex, dequePointer);
		}

		TEST_METHOD(test_deque_back_modify)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode à tester --------------
			dequeRegular.back() = 90;

			deque<int> other;
			other.push_back(10'000);
			dequeComplex.back() = other;

			int l = 0;
			dequePointer.back() = &l;

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(90, dequeRegular.back());

			// La file complexe.
			deque<int> result = dequeComplex.back();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			Assert::AreEqual(0, *dequePointer.back());
		}

		TEST_METHOD(test_deque_clear)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			dequeRegular.push_back(2);
			dequeRegular.push_back(3);
			dequeRegular.push_back(1);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_back(dequeRegular);

			deque<int*> dequePointer;
			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode à tester --------------
			dequeRegular.clear();
			dequeComplex.clear();
			dequePointer.clear();

			// Validation des résultats ------------------
			Assert::IsTrue(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.size());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.capacity());

			Assert::IsTrue(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.capacity());

			Assert::IsTrue(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.capacity());
		}

		TEST_METHOD(test_deque_push_back_firstValue)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			// Appel de la méthode à tester --------------
			dequeRegular.push_back(2);
			dequeComplex.push_back(dequeRegular);
			int i = 10;
			dequePointer.push_back(&i);

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été ajouté.

			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 1, dequeRegular.size());
			Assert::AreEqual(2, dequeRegular[0]);

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 1, result.size());
			Assert::AreEqual(2, result[0]);

			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)1, dequePointer.size());
			Assert::AreEqual(10, *dequePointer[0]);
		}

		TEST_METHOD(test_deque_push_back_manyValues)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			// Appel de la méthode à tester --------------
			dequeRegular.push_back(2);
			dequeRegular.push_back(3);
			dequeRegular.push_back(1);

			dequeComplex.push_back(dequeRegular);
			deque<int> other;
			other.push_back(99);
			other.push_back(98);
			dequeComplex.push_back(other);

			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Validation des résultats ------------------
			// On vérifie que les éléments ont bien été ajoutés.

			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 3, dequeRegular.size());
			Assert::AreEqual(2, dequeRegular[0]);
			Assert::AreEqual(3, dequeRegular[1]);
			Assert::AreEqual(1, dequeRegular[2]);

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)2, dequeComplex.size());

			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result[0]);
			Assert::AreEqual(3, result[1]);
			Assert::AreEqual(1, result[2]);

			result = dequeComplex[1];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 2, result.size());
			Assert::AreEqual(99, result[0]);
			Assert::AreEqual(98, result[1]);
			

			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)2, dequePointer.size());
			Assert::AreEqual(10, *dequePointer[0]);
			Assert::AreEqual(9, *dequePointer[1]);
		}

		TEST_METHOD(test_deque_push_front_firstValue)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			// Appel de la méthode à tester --------------
			dequeRegular.push_front(2);
			dequeComplex.push_front(dequeRegular);
			int i = 10;
			dequePointer.push_front(&i);

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été ajouté.

			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 1, dequeRegular.size());
			Assert::AreEqual(2, dequeRegular[0]);

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 1, result.size());
			Assert::AreEqual(2, result[0]);

			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)1, dequePointer.size());
			Assert::AreEqual(10, *dequePointer[0]);
		}

		TEST_METHOD(test_deque_push_front_manyValues)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			// Appel de la méthode à tester --------------
			dequeRegular.push_front(1);
			dequeRegular.push_front(3);
			dequeRegular.push_front(2);

			deque<int> other;
			other.push_front(98);
			other.push_front(99);
			dequeComplex.push_front(other);
			dequeComplex.push_front(dequeRegular);

			int i = 10;
			int j = 9;

			dequePointer.push_front(&j);
			dequePointer.push_front(&i);

			// Validation des résultats ------------------
			// On vérifie que les éléments ont bien été ajoutés.

			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 3, dequeRegular.size());
			Assert::AreEqual(2, dequeRegular[0]);
			Assert::AreEqual(3, dequeRegular[1]);
			Assert::AreEqual(1, dequeRegular[2]);

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)2, dequeComplex.size());

			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result[0]);
			Assert::AreEqual(3, result[1]);
			Assert::AreEqual(1, result[2]);

			result = dequeComplex[1];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 2, result.size());
			Assert::AreEqual(99, result[0]);
			Assert::AreEqual(98, result[1]);


			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)2, dequePointer.size());
			Assert::AreEqual(10, *dequePointer[0]);
			Assert::AreEqual(9, *dequePointer[1]);
		}

		TEST_METHOD(test_deque_pop_back_manyValues)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			dequeRegular.push_front(2);
			dequeRegular.push_front(3);
			dequeRegular.push_back(1);

			dequeComplex.push_back(dequeRegular);
			deque<int> other;
			other.push_back(99);
			other.push_back(98);
			dequeComplex.push_front(other);

			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode à tester --------------
			dequeRegular.pop_back();
			dequeComplex.pop_back();
			dequePointer.pop_back();

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été enlevé.

			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 2, dequeRegular.size());
			Assert::AreEqual(2, dequeRegular.back());

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			deque<int> result = dequeComplex.back();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 2, result.size());
			Assert::AreEqual(99, result[0]);
			Assert::AreEqual(98, result[1]);

			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)1, dequePointer.size());
			Assert::AreEqual(10, *dequePointer.back());
		}

		TEST_METHOD(test_deque_pop_back_oneValue)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			dequeRegular.push_front(2);

			dequeComplex.push_back(dequeRegular);

			int i = 10;
			dequePointer.push_back(&i);

			// Appel de la méthode à tester --------------
			dequeRegular.pop_back();
			dequeComplex.pop_back();
			dequePointer.pop_back();

			// Validation des résultats ------------------
			Assert::IsTrue(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.size());

			Assert::IsTrue(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());

			Assert::IsTrue(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
		}

		TEST_METHOD(test_deque_pop_front_manyValues)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			dequeRegular.push_front(2);
			dequeRegular.push_front(3);
			dequeRegular.push_back(1);

			dequeComplex.push_back(dequeRegular);
			deque<int> other;
			other.push_back(99);
			other.push_back(98);
			dequeComplex.push_front(other);

			int i = 10;
			int j = 9;
			dequePointer.push_back(&i);
			dequePointer.push_back(&j);

			// Appel de la méthode à tester --------------
			dequeRegular.pop_front();
			dequeComplex.pop_front();
			dequePointer.pop_front();

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été enlevé.

			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 2, dequeRegular.size());
			Assert::AreEqual(2, dequeRegular.front());

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			deque<int> result = dequeComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(3, result[0]);
			Assert::AreEqual(2, result[1]);
			Assert::AreEqual(1, result[2]);

			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)1, dequePointer.size());
			Assert::AreEqual(9, *dequePointer.front());
		}

		TEST_METHOD(test_deque_pop_front_oneValue)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			dequeRegular.push_front(2);

			dequeComplex.push_back(dequeRegular);

			int i = 10;
			dequePointer.push_back(&i);

			// Appel de la méthode à tester --------------
			dequeRegular.pop_front();
			dequeComplex.pop_front();
			dequePointer.pop_front();

			// Validation des résultats ------------------
			Assert::IsTrue(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.size());

			Assert::IsTrue(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());

			Assert::IsTrue(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
		}

		TEST_METHOD(test_deque_swap_emptyDeques)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegularToCopy;
			deque<deque<int>> dequeComplexToCopy;
			deque<int*> dequePointerToCopy;

			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			// Appel de la méthode à tester --------------
			dequeRegular.swap(dequeRegularToCopy);
			dequeComplex.swap(dequeComplexToCopy);
			dequePointer.swap(dequePointerToCopy);

			// Validation des résultats ------------------
			// Les premières files doivent avoir les valeurs des deuxièmes.
			Assert::IsTrue(dequeRegularToCopy.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegularToCopy.size());

			Assert::IsTrue(dequeComplexToCopy.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplexToCopy.size());

			Assert::IsTrue(dequePointerToCopy.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointerToCopy.size());

			// Les deuxièmes files doivent avoir les valeurs des premières.
			Assert::IsTrue(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegular.size());

			Assert::IsTrue(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplex.size());

			Assert::IsTrue(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointer.size());
		}

		TEST_METHOD(test_deque_swap_oneFilledDeque)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegularToCopy;
			dequeRegularToCopy.push_front(2);
			dequeRegularToCopy.push_front(3);
			dequeRegularToCopy.push_front(1);

			deque<deque<int>> dequeComplexToCopy;
			dequeComplexToCopy.push_back(dequeRegularToCopy);

			deque<int*> dequePointerToCopy;
			int i = 10;
			int j = 9;
			dequePointerToCopy.push_back(&i);
			dequePointerToCopy.push_back(&j);

			deque<int> dequeRegular;
			deque<deque<int>> dequeComplex;
			deque<int*> dequePointer;

			// Appel de la méthode à tester --------------
			dequeRegular.swap(dequeRegularToCopy);
			dequeComplex.swap(dequeComplexToCopy);
			dequePointer.swap(dequePointerToCopy);

			// Validation des résultats ------------------
			// Les premières files doivent avoir les valeurs des deuxièmes.
			Assert::IsTrue(dequeRegularToCopy.empty());
			Assert::AreEqual((deque<int>::size_type) 0, dequeRegularToCopy.size());

			Assert::IsTrue(dequeComplexToCopy.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)0, dequeComplexToCopy.size());

			Assert::IsTrue(dequePointerToCopy.empty());
			Assert::AreEqual((deque<int*>::size_type)0, dequePointerToCopy.size());

			// Les deuxièmes files doivent avoir les valeurs des premières.
			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 3, dequeRegular.size());
			Assert::AreEqual(1, dequeRegular[0]);
			Assert::AreEqual(3, dequeRegular[1]);
			Assert::AreEqual(2, dequeRegular[2]);

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			deque<int> result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result[0]);
			Assert::AreEqual(3, result[1]);
			Assert::AreEqual(2, result[2]);

			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)2, dequePointer.size());
			Assert::AreEqual(10, *dequePointer[0]);
			Assert::AreEqual(9, *dequePointer[1]);
		}

		TEST_METHOD(test_deque_swap_twoFilleddeques)
		{
			// Mise en place des données -----------------
			deque<int> dequeRegularToCopy;
			dequeRegularToCopy.push_front(2);
			dequeRegularToCopy.push_front(3);
			dequeRegularToCopy.push_front(1);

			deque<deque<int>> dequeComplexToCopy;
			dequeComplexToCopy.push_back(dequeRegularToCopy);

			deque<int*> dequePointerToCopy;
			int i = 10;
			int j = 9;
			dequePointerToCopy.push_back(&j);
			dequePointerToCopy.push_back(&i);

			deque<int> dequeRegular;
			dequeRegular.push_front(7);
			dequeRegular.push_front(6);
			dequeRegular.push_front(2);
			dequeRegular.push_front(22);
			dequeRegular.push_front(44);
			dequeRegular.push_front(66);

			deque<deque<int>> dequeComplex;
			dequeComplex.push_front(dequeRegular);
			deque<int> other;
			other.push_back(462);
			other.push_back(3453);
			dequeComplex.push_front(other);

			deque<int*> dequePointer;
			int k = 23;
			int l = 14;
			dequePointer.push_back(&l);
			dequePointer.push_back(&k);

			// Appel de la méthode à tester --------------
			dequeRegular.swap(dequeRegularToCopy);
			dequeComplex.swap(dequeComplexToCopy);
			dequePointer.swap(dequePointerToCopy);

			// Validation des résultats ------------------
			// Les premières files doivent avoir les valeurs des deuxièmes.
			// La file régulière.
			Assert::IsFalse(dequeRegularToCopy.empty());
			Assert::AreEqual((deque<int>::size_type) 6, dequeRegularToCopy.size());
			Assert::AreEqual(66, dequeRegularToCopy[0]);
			Assert::AreEqual(44, dequeRegularToCopy[1]);
			Assert::AreEqual(22, dequeRegularToCopy[2]);
			Assert::AreEqual(2, dequeRegularToCopy[3]);
			Assert::AreEqual(6, dequeRegularToCopy[4]);
			Assert::AreEqual(7, dequeRegularToCopy[5]);

			// La file complexe.
			Assert::IsFalse(dequeComplexToCopy.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)2, dequeComplexToCopy.size());

			deque<int> result = dequeComplexToCopy[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 2, result.size());
			Assert::AreEqual(462, result[0]);
			Assert::AreEqual(3453, result[1]);

			result = dequeComplexToCopy[1];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 6, result.size());
			Assert::AreEqual(66, result[0]);
			Assert::AreEqual(44, result[1]);
			Assert::AreEqual(22, result[2]);
			Assert::AreEqual(2, result[3]);
			Assert::AreEqual(6, result[4]);
			Assert::AreEqual(7, result[5]);

			// La file de pointeurs.
			Assert::IsFalse(dequePointerToCopy.empty());
			Assert::AreEqual((deque<int*>::size_type)2, dequePointerToCopy.size());
			Assert::AreEqual(14, *dequePointerToCopy[0]);
			Assert::AreEqual(23, *dequePointerToCopy[1]);

			// Les deuxièmes files doivent avoir les valeurs des premières.
			// La file régulière.
			Assert::IsFalse(dequeRegular.empty());
			Assert::AreEqual((deque<int>::size_type) 3, dequeRegular.size());
			Assert::AreEqual(1, dequeRegular[0]);
			Assert::AreEqual(3, dequeRegular[1]);
			Assert::AreEqual(2, dequeRegular[2]);

			// La file complexe.
			Assert::IsFalse(dequeComplex.empty());
			Assert::AreEqual((deque<deque<int>>::size_type)1, dequeComplex.size());

			result = dequeComplex[0];
			Assert::IsFalse(result.empty());
			Assert::AreEqual((deque<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result[0]);
			Assert::AreEqual(3, result[1]);
			Assert::AreEqual(2, result[2]);

			// La file de pointeurs.
			Assert::IsFalse(dequePointer.empty());
			Assert::AreEqual((deque<int*>::size_type)2, dequePointer.size());
			Assert::AreEqual(9, *dequePointer[0]);
			Assert::AreEqual(10, *dequePointer[1]);
		}

	};
}