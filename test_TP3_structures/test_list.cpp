#include "stdafx.h"
#include "../TP3/Structures/list.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TP3_structures;

namespace test_TP3_structures
{
	TEST_CLASS(test_list)
	{
	public:
		TEST_METHOD(test_list_constructor)
		{
			// Appel de la méthode à tester --------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Validation des résultats ------------------
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_destructor)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(3);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			listRegular.~list();
			listComplex.~list();
			listPointer.~list();

			// Validation des résultats ------------------
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_copyConstructor_emptyLists)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			list<list<int>> listComplexToCopy;
			list<int*> listPointerToCopy;

			// Appel de la méthode à tester --------------
			list<int> listRegular(listRegularToCopy);
			list<list<int>> listComplex(listComplexToCopy);
			list<int*> listPointer(listPointerToCopy);

			// Validation des résultats ------------------
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_copyConstructor_filledLists)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			listRegularToCopy.push_back(2);
			listRegularToCopy.push_back(3);
			listRegularToCopy.push_back(1);

			list<list<int>> listComplexToCopy;
			listComplexToCopy.push_back(listRegularToCopy);

			list<int*> listPointerToCopy;
			int i = 10;
			int j = 9;
			listPointerToCopy.push_back(&i);
			listPointerToCopy.push_back(&j);

			// Appel de la méthode à tester --------------
			list<int> listRegular(listRegularToCopy);
			list<list<int>> listComplex(listComplexToCopy);
			list<int*> listPointer(listPointerToCopy);

			// Validation des résultats ------------------
			// On vérifie que les listes copiées sont égales aux originales.

			// La liste régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());
			auto iterRegular = listRegular.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La liste complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La liste de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(10, **iterPointer);
			++iterPointer;
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_constructor_initializer_list_emptyLists)
		{

			// Appel de la méthode à tester --------------
			list<int> listRegular{};
			list<list<int>> listComplex{};
			list<int*> listPointer{};

			// Validation des résultats ------------------
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_constructor_initializer_list_filledLists)
		{

			// Appel de la méthode à tester --------------
			list<int> listRegular{2, 3, 1};
			list<list<int>> listComplex{listRegular};
			int i = 10;
			int j = 9;
			list<int*> listPointer{&i, &j};

			// Validation des résultats ------------------
			// On vérifie que les listes copiées sont égales aux originales.

			// La liste régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());
			auto iterRegular = listRegular.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La liste complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La liste de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(10, **iterPointer);
			++iterPointer;
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_operatorEqual_emptyLists)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			list<list<int>> listComplexToCopy;
			list<int*> listPointerToCopy;

			// Appel de la méthode à tester --------------
			list<int> listRegular = listRegularToCopy;
			list<list<int>> listComplex = listComplexToCopy;
			list<int*> listPointer = listPointerToCopy;

			// Validation des résultats ------------------
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_operatorEqual_emptyListToCopy)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			list<list<int>> listComplexToCopy;
			list<int*> listPointerToCopy;

			list<int> listRegular;
			listRegular.push_back(999);
			listRegular.push_back(1024);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);
			list<int> other;
			other.push_back(606);
			other.push_back(24);
			other.push_back(49);
			other.push_back(63);
			listComplex.push_back(other);

			list<int*> listPointer;
			int k = 99;
			listPointer.push_back(&k);

			// Appel de la méthode à tester --------------
			listRegular = listRegularToCopy;
			listComplex = listComplexToCopy;
			listPointer = listPointerToCopy;

			// Validation des résultats ------------------
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_operatorEqual_filledListToCopy)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			listRegularToCopy.push_back(2);
			listRegularToCopy.push_back(3);
			listRegularToCopy.push_back(1);

			list<list<int>> listComplexToCopy;
			listComplexToCopy.push_back(listRegularToCopy);

			list<int*> listPointerToCopy;
			int i = 10;
			int j = 9;
			listPointerToCopy.push_back(&i);
			listPointerToCopy.push_back(&j);

			// Appel de la méthode à tester --------------
			list<int> listRegular = listRegularToCopy;
			list<list<int>> listComplex = listComplexToCopy;
			list<int*> listPointer = listPointerToCopy;

			// Validation des résultats ------------------
			// On vérifie que les listes copiées sont égales aux originales.

			// La liste régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());
			auto iterRegular = listRegular.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La liste complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La liste de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(10, **iterPointer);
			++iterPointer;
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_operatorEqual_filledLists)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			listRegularToCopy.push_back(2);
			listRegularToCopy.push_back(3);
			listRegularToCopy.push_back(1);

			list<list<int>> listComplexToCopy;
			listComplexToCopy.push_back(listRegularToCopy);

			list<int*> listPointerToCopy;
			int i = 10;
			int j = 9;
			listPointerToCopy.push_back(&i);
			listPointerToCopy.push_back(&j);

			list<int> listRegular;
			listRegular.push_back(999);
			listRegular.push_back(1024);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);
			list<int> other;
			other.push_back(606);
			other.push_back(24);
			other.push_back(49);
			other.push_back(63);
			listComplex.push_back(other);

			list<int*> listPointer;
			int k = 99;
			listPointer.push_back(&k);

			// Appel de la méthode à tester --------------
			listRegular = listRegularToCopy;
			listComplex = listComplexToCopy;
			listPointer = listPointerToCopy;

			// Validation des résultats ------------------
			// On vérifie que les listes copiées sont égales aux originales.

			// La liste régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());
			auto iterRegular = listRegular.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La liste complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La liste de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(10, **iterPointer);
			++iterPointer;
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_swap_emptyLists)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			list<list<int>> listComplexToCopy;
			list<int*> listPointerToCopy;

			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthode à tester --------------
			listRegular.swap(listRegularToCopy);
			listComplex.swap(listComplexToCopy);
			listPointer.swap(listPointerToCopy);

			// Validation des résultats ------------------
			// Les premières listes doivent avoir les valeurs des deuxièmes.
			Assert::IsTrue(listRegularToCopy.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegularToCopy.size());

			Assert::IsTrue(listComplexToCopy.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplexToCopy.size());

			Assert::IsTrue(listPointerToCopy.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointerToCopy.size());

			// Les deuxièmes listes doivent avoir les valeurs des premières.
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_swap_oneFilledList)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			listRegularToCopy.push_front(2);
			listRegularToCopy.push_front(3);
			listRegularToCopy.push_front(1);

			list<list<int>> listComplexToCopy;
			listComplexToCopy.push_back(listRegularToCopy);

			list<int*> listPointerToCopy;
			int i = 10;
			int j = 9;
			listPointerToCopy.push_back(&i);
			listPointerToCopy.push_back(&j);

			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthode à tester --------------
			listRegular.swap(listRegularToCopy);
			listComplex.swap(listComplexToCopy);
			listPointer.swap(listPointerToCopy);

			// Validation des résultats ------------------
			// Les premières listes doivent avoir les valeurs des deuxièmes.
			Assert::IsTrue(listRegularToCopy.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegularToCopy.size());

			Assert::IsTrue(listComplexToCopy.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplexToCopy.size());

			Assert::IsTrue(listPointerToCopy.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointerToCopy.size());

			// Les deuxièmes listes doivent avoir les valeurs des premières.
			// La liste régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());
			auto iterRegular = listRegular.begin();
			int isalut = *iterRegular;
			Assert::AreEqual(1, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);

			// La liste complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(1, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);

			// La liste de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(10, **iterPointer);
			++iterPointer;
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_swap_twoFilledLists)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			listRegularToCopy.push_front(2);
			listRegularToCopy.push_front(3);
			listRegularToCopy.push_front(1);

			list<list<int>> listComplexToCopy;
			listComplexToCopy.push_back(listRegularToCopy);

			list<int*> listPointerToCopy;
			int i = 10;
			int j = 9;
			listPointerToCopy.push_back(&j);
			listPointerToCopy.push_back(&i);

			list<int> listRegular;
			listRegular.push_front(7);
			listRegular.push_front(6);
			listRegular.push_front(2);
			listRegular.push_front(22);
			listRegular.push_front(44);
			listRegular.push_front(66);

			list<list<int>> listComplex;
			listComplex.push_front(listRegular);
			list<int> other;
			other.push_back(462);
			other.push_back(3453);
			listComplex.push_front(other);

			list<int*> listPointer;
			int k = 23;
			int l = 14;
			listPointer.push_back(&l);
			listPointer.push_back(&k);

			// Appel de la méthode à tester --------------
			listRegular.swap(listRegularToCopy);
			listComplex.swap(listComplexToCopy);
			listPointer.swap(listPointerToCopy);

			// Validation des résultats ------------------
			// Les premières listes doivent avoir les valeurs des deuxièmes.
			// La liste régulière.
			Assert::IsFalse(listRegularToCopy.empty());
			Assert::AreEqual((list<int>::size_type) 6, listRegularToCopy.size());
			auto iterRegular = listRegularToCopy.begin();
			Assert::AreEqual(66, *iterRegular);
			++iterRegular;
			Assert::AreEqual(44, *iterRegular);
			++iterRegular;
			Assert::AreEqual(22, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(6, *iterRegular);
			++iterRegular;
			Assert::AreEqual(7, *iterRegular);

			// La liste complexe.
			Assert::IsFalse(listComplexToCopy.empty());
			Assert::AreEqual((list<list<int>>::size_type)2, listComplexToCopy.size());

			auto iterComplex = listComplexToCopy.begin();
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 2, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(462, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3453, *iterRegular);

			++iterComplex;
			result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 6, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(66, *iterRegular);
			++iterRegular;
			Assert::AreEqual(44, *iterRegular);
			++iterRegular;
			Assert::AreEqual(22, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(6, *iterRegular);
			++iterRegular;
			Assert::AreEqual(7, *iterRegular);

			// La liste de pointeurs.
			Assert::IsFalse(listPointerToCopy.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointerToCopy.size());
			auto iterPointer = listPointerToCopy.begin();
			Assert::AreEqual(14, **iterPointer);
			++iterPointer;
			Assert::AreEqual(23, **iterPointer);

			// Les deuxièmes listes doivent avoir les valeurs des premières.
			// La liste régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());
			iterRegular = listRegular.begin();
			Assert::AreEqual(1, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);

			// La liste complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(1, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);

			// La liste de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			iterPointer = listPointer.begin();
			Assert::AreEqual(9, **iterPointer);
			++iterPointer;
			Assert::AreEqual(10, **iterPointer);
		}

		TEST_METHOD(test_list_insert_iterator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 2;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.begin();
			++iterRegular;
			++iterRegular;
			++iterRegular;
			iterRegular = listRegular.insert(iterRegular, 99);

			list<int> other;
			other.push_back(9000);
			auto iterComplex = listComplex.begin();
			iterComplex = listComplex.insert(iterComplex, other);

			int k = 20;
			auto iterPointer = listPointer.begin();
			iterPointer++;
			iterPointer++;
			iterPointer = listPointer.insert(iterPointer, &k);
			
			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été ajouté.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 4, listRegular.size());
			auto iterRegularToVerify = listRegular.begin();
			iterRegularToVerify++;
			iterRegularToVerify++;
			iterRegularToVerify++;
			Assert::IsTrue(iterRegularToVerify == iterRegular);
			Assert::AreEqual(99, *iterRegularToVerify);

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)2, listComplex.size());
			auto iterComplexToVerify = listComplex.begin();
			Assert::IsTrue(iterComplexToVerify == iterComplex);

			list<int> result = *iterComplexToVerify;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(9000, result.front());

			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)3, listPointer.size());
			auto iterPointerToVerify = listPointer.begin();
			iterPointerToVerify++;
			iterPointerToVerify++;
			Assert::IsTrue(iterPointerToVerify == iterPointer);
			Assert::AreEqual(20, **iterPointerToVerify);
		}

		TEST_METHOD(test_list_erase_iterator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);
			list<int> other;
			other.push_back(9000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 2;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.begin();
			++iterRegular;
			iterRegular = listRegular.erase(iterRegular);

			auto iterComplex = listComplex.begin();
			iterComplex = listComplex.erase(iterComplex);

			auto iterPointer = listPointer.begin();
			iterPointer++;
			iterPointer = listPointer.erase(iterPointer);

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été ajouté.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 2, listRegular.size());
			auto iterRegularToVerify = listRegular.begin();
			iterRegularToVerify++;
			Assert::IsTrue(iterRegularToVerify == iterRegular);
			Assert::AreEqual(19, *iterRegularToVerify);

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());
			auto iterComplexToVerify = listComplex.begin();
			Assert::IsTrue(iterComplexToVerify == iterComplex);

			list<int> result = *iterComplexToVerify;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(9000, result.front());

			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)1, listPointer.size());
			auto iterPointerToVerify = listPointer.begin();
			iterPointerToVerify++;
			Assert::IsTrue(iterPointerToVerify == iterPointer);
			Assert::IsTrue(listPointer.end() == iterPointer);
		}

		TEST_METHOD(test_list_insert_reverse_iterator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 2;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.rbegin();
			++iterRegular;
			++iterRegular;
			++iterRegular;
			iterRegular = listRegular.insert(iterRegular, 99);

			list<int> other;
			other.push_back(9000);
			auto iterComplex = listComplex.rbegin();
			iterComplex = listComplex.insert(iterComplex, other);

			int k = 20;
			auto iterPointer = listPointer.rbegin();
			iterPointer++;
			iterPointer++;
			iterPointer = listPointer.insert(iterPointer, &k);

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été ajouté.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 4, listRegular.size());
			auto iterRegularToVerify = listRegular.rbegin();
			iterRegularToVerify++;
			iterRegularToVerify++;
			iterRegularToVerify++;
			Assert::IsTrue(iterRegularToVerify == iterRegular);
			Assert::AreEqual(99, *iterRegularToVerify);

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)2, listComplex.size());
			auto iterComplexToVerify = listComplex.rbegin();
			Assert::IsTrue(iterComplexToVerify == iterComplex);

			list<int> result = *iterComplexToVerify;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(9000, result.front());

			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)3, listPointer.size());
			auto iterPointerToVerify = listPointer.rbegin();
			iterPointerToVerify++;
			iterPointerToVerify++;
			Assert::IsTrue(iterPointerToVerify == iterPointer);
			Assert::AreEqual(20, **iterPointerToVerify);
		}

		TEST_METHOD(test_list_erase_reverse_iterator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);
			list<int> other;
			other.push_back(9000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 2;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.rbegin();
			++iterRegular;
			iterRegular = listRegular.erase(iterRegular);

			auto iterComplex = listComplex.rbegin();
			++iterComplex;
			iterComplex = listComplex.erase(iterComplex);

			auto iterPointer = listPointer.rbegin();
			iterPointer = listPointer.erase(iterPointer);

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été ajouté.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 2, listRegular.size());
			auto iterRegularToVerify = listRegular.rbegin();
			iterRegularToVerify++;
			Assert::IsTrue(iterRegularToVerify == iterRegular);
			Assert::AreEqual(2, *iterRegularToVerify);

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());
			auto iterComplexToVerify = listComplex.rbegin();
			iterComplexToVerify++;
			Assert::IsTrue(iterComplexToVerify == iterComplex);
			Assert::IsTrue(listComplex.rend() == iterComplex);

			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)1, listPointer.size());
			auto iterPointerToVerify = listPointer.rbegin();
			Assert::IsTrue(iterPointerToVerify == iterPointer);
			Assert::IsTrue(10 == **iterPointer);
		}

		TEST_METHOD(test_list_push_back_firstValue)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthode à tester --------------
			listRegular.push_back(2);
			listComplex.push_back(listRegular);
			int i = 10;
			listPointer.push_back(&i);

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été ajouté.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 1, listRegular.size());
			Assert::AreEqual(2, listRegular.front());

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.back();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(2, result.back());

			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)1, listPointer.size());
			Assert::AreEqual(10, *listPointer.back());
		}

		TEST_METHOD(test_list_push_back_manyValues)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthode à tester --------------
			listRegular.push_back(2);
			listRegular.push_back(3);
			listRegular.push_back(1);

			listComplex.push_back(listRegular);
			list<int> other;
			other.push_back(99);
			other.push_back(98);
			listComplex.push_back(other);

			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Validation des résultats ------------------
			// On vérifie que les éléments ont bien été ajoutés.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());
			auto iterRegular = listRegular.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)2, listComplex.size());

			auto iterComplex = listComplex.begin();
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			++iterComplex;
			result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 2, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(99, *iterRegular);
			++iterRegular;
			Assert::AreEqual(98, *iterRegular);


			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(10, **iterPointer);
			++iterPointer;
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_push_front_firstValue)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthode à tester --------------
			listRegular.push_front(2);
			listComplex.push_front(listRegular);
			int i = 10;
			listPointer.push_front(&i);

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été ajouté.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 1, listRegular.size());
			Assert::AreEqual(2, listRegular.front());

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.back();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(2, result.back());

			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)1, listPointer.size());
			Assert::AreEqual(10, *listPointer.back());
		}

		TEST_METHOD(test_list_push_front_manyValues)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthode à tester --------------
			listRegular.push_front(1);
			listRegular.push_front(3);
			listRegular.push_front(2);

			list<int> other;
			other.push_front(98);
			other.push_front(99);
			listComplex.push_front(other);
			listComplex.push_front(listRegular);

			int i = 10;
			int j = 9;

			listPointer.push_front(&j);
			listPointer.push_front(&i);

			// Validation des résultats ------------------
			// On vérifie que les éléments ont bien été ajoutés.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());
			auto iterRegular = listRegular.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)2, listComplex.size());

			auto iterComplex = listComplex.begin();
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			++iterComplex;
			result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 2, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(99, *iterRegular);
			++iterRegular;
			Assert::AreEqual(98, *iterRegular);


			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(10, **iterPointer);
			++iterPointer;
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_pop_back_manyValues)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			listRegular.push_front(2);
			listRegular.push_front(3);
			listRegular.push_back(1);

			listComplex.push_back(listRegular);
			list<int> other;
			other.push_back(99);
			other.push_back(98);
			listComplex.push_front(other);

			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			listRegular.pop_back();
			listComplex.pop_back();
			listPointer.pop_back();

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été enlevé.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 2, listRegular.size());
			Assert::AreEqual(2, listRegular.back());

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.back();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 2, result.size());
			Assert::AreEqual(99, result.front());
			Assert::AreEqual(98, result.back());

			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)1, listPointer.size());
			Assert::AreEqual(10, *listPointer.back());
		}

		TEST_METHOD(test_list_pop_back_oneValue)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			listRegular.push_front(2);

			listComplex.push_back(listRegular);

			int i = 10;
			listPointer.push_back(&i);

			// Appel de la méthode à tester --------------
			listRegular.pop_back();
			listComplex.pop_back();
			listPointer.pop_back();

			// Validation des résultats ------------------
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_pop_front_manyValues)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			listRegular.push_front(2);
			listRegular.push_front(3);
			listRegular.push_back(1);

			listComplex.push_back(listRegular);
			list<int> other;
			other.push_back(99);
			other.push_back(98);
			listComplex.push_front(other);

			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			listRegular.pop_front();
			listComplex.pop_front();
			listPointer.pop_front();

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été enlevé.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 2, listRegular.size());
			Assert::AreEqual(2, listRegular.front());

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			auto iterRegular = result.begin();
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);

			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)1, listPointer.size());
			Assert::AreEqual(9, *listPointer.front());
		}

		TEST_METHOD(test_list_pop_front_oneValue)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			listRegular.push_front(2);

			listComplex.push_back(listRegular);

			int i = 10;
			listPointer.push_back(&i);

			// Appel de la méthode à tester --------------
			listRegular.pop_front();
			listComplex.pop_front();
			listPointer.pop_front();

			// Validation des résultats ------------------
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_front_access)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode et validation ---------

			// La file régulière.
			Assert::AreEqual(2, listRegular.front());

			// La file complexe.
			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result.front());

			// La file de pointeurs.
			Assert::AreEqual(10, *listPointer.front());
		}

		void validate_test_list_const_front_access(const list<int>& listRegular, const list<list<int>>& listComplex, const list<int*>& listPointer)
		{
			// La file régulière.
			Assert::AreEqual(2, listRegular.front());

			// La file complexe.
			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			Assert::AreEqual(2, result.front());

			// La file de pointeurs.
			Assert::AreEqual(10, *listPointer.front());
		}
		TEST_METHOD(test_list_const_front_access)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode et validation ---------
			validate_test_list_const_front_access(listRegular, listComplex, listPointer);
		}

		TEST_METHOD(test_list_front_modify)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			listRegular.front() = 99;

			list<int> other;
			other.push_back(10'000);
			listComplex.front() = other;

			int k = 88;
			listPointer.front() = &k;

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(99, listRegular.front());

			// La file complexe.
			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.front());

			// La file de pointeurs.
			Assert::AreEqual(88, *listPointer.front());
		}

		TEST_METHOD(test_list_back_access)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode et validation ---------

			// La file régulière.
			Assert::AreEqual(1, listRegular.back());

			// La file complexe.
			list<int> result = listComplex.back();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.back());

			// La file de pointeurs.
			Assert::AreEqual(9, *listPointer.back());
		}

		void validate_test_list_const_back_access(const list<int>& listRegular, const list<list<int>>& listComplex, const list<int*>& listPointer)
		{
			// La file régulière.
			Assert::AreEqual(1, listRegular.back());

			// La file complexe.
			list<int> result = listComplex.back();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			Assert::AreEqual(1, result.back());

			// La file de pointeurs.
			Assert::AreEqual(9, *listPointer.back());
		}
		TEST_METHOD(test_list_const_back_access)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode et validation ---------
			validate_test_list_const_back_access(listRegular, listComplex, listPointer);
		}

		TEST_METHOD(test_list_back_modify)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			listRegular.back() = 90;

			list<int> other;
			other.push_back(10'000);
			listComplex.back() = other;

			int l = 0;
			listPointer.back() = &l;

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(90, listRegular.back());

			// La file complexe.
			list<int> result = listComplex.back();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			Assert::AreEqual(0, *listPointer.back());
		}

		TEST_METHOD(test_list_clear)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(3);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			listRegular.clear();
			listComplex.clear();
			listPointer.clear();

			// Validation des résultats ------------------
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_size)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthode et validation ---------

			// La file régulière.
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());
			listRegular.push_back(2);
			Assert::AreEqual((list<int>::size_type) 1, listRegular.size());
			listRegular.push_back(3);
			Assert::AreEqual((list<int>::size_type) 2, listRegular.size());
			listRegular.push_back(1);
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());

			// La file complexe.
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());
			listComplex.push_back(listRegular);
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			// La file de pointeurs.
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			Assert::AreEqual((list<int*>::size_type)1, listPointer.size());
			listPointer.push_back(&j);
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
		}

		TEST_METHOD(test_list_empty)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthpde et validation ---------

			// La file régulière.
			Assert::IsTrue(listRegular.empty());
			listRegular.push_back(2);
			Assert::IsFalse(listRegular.empty());
			listRegular.push_back(3);
			Assert::IsFalse(listRegular.empty());
			listRegular.push_back(1);
			Assert::IsFalse(listRegular.empty());

			// La file complexe.
			Assert::IsTrue(listComplex.empty());
			listComplex.push_back(listRegular);
			Assert::IsFalse(listComplex.empty());

			// La file de pointeurs.
			Assert::IsTrue(listPointer.empty());
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			Assert::IsFalse(listPointer.empty());
			listPointer.push_back(&j);
			Assert::IsFalse(listPointer.empty());
		}

		TEST_METHOD(test_list_begin)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.begin();
			auto iterComplex = listComplex.begin();
			auto iterPointer = listPointer.begin();

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(2, *iterRegular);

			// La file complexe.
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			Assert::AreEqual(10, **iterPointer);
		}

		TEST_METHOD(test_list_end)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.end();
			auto iterComplex = listComplex.end();
			auto iterPointer = listPointer.end();

			// Validation des résultats ------------------

			// La file régulière.
			iterRegular--;
			Assert::AreEqual(1, *iterRegular);

			// La file complexe.
			iterComplex--;
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			iterPointer--;
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_rbegin)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.rbegin();
			auto iterComplex = listComplex.rbegin();
			auto iterPointer = listPointer.rbegin();

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(1, *iterRegular);

			// La file complexe.
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_rend)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.rend();
			auto iterComplex = listComplex.rend();
			auto iterPointer = listPointer.rend();

			// Validation des résultats ------------------

			// La file régulière.
			iterRegular--;
			Assert::AreEqual(2, *iterRegular);

			// La file complexe.
			iterComplex--;
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			iterPointer--;
			Assert::AreEqual(10, **iterPointer);
		}

		void validate_test_list_const_begin(const list<int>& listRegular, const list<list<int>>& listComplex, const list<int*>& listPointer)
		{
			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.begin();
			auto iterComplex = listComplex.begin();
			auto iterPointer = listPointer.begin();

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(2, *iterRegular);

			// La file complexe.
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			Assert::AreEqual(10, **iterPointer);
		}
		TEST_METHOD(test_list_const_begin)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			validate_test_list_const_begin(listRegular, listComplex, listPointer);
		}

		void validate_test_list_const_end(const list<int>& listRegular, const list<list<int>>& listComplex, const list<int*>& listPointer)
		{
			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.end();
			auto iterComplex = listComplex.end();
			auto iterPointer = listPointer.end();

			// Validation des résultats ------------------

			// La file régulière.
			iterRegular--;
			Assert::AreEqual(1, *iterRegular);

			// La file complexe.
			iterComplex--;
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			iterPointer--;
			Assert::AreEqual(9, **iterPointer);
		}
		TEST_METHOD(test_list_const_end)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			validate_test_list_const_end(listRegular, listComplex, listPointer);
		}

		void validate_test_list_const_rbegin(const list<int>& listRegular, const list<list<int>>& listComplex, const list<int*>& listPointer)
		{
			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.rbegin();
			auto iterComplex = listComplex.rbegin();
			auto iterPointer = listPointer.rbegin();

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(1, *iterRegular);

			// La file complexe.
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			Assert::AreEqual(9, **iterPointer);
		}
		TEST_METHOD(test_list_const_rbegin)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			validate_test_list_const_rbegin(listRegular, listComplex, listPointer);
		}

		void validate_test_list_const_rend(const list<int>& listRegular, const list<list<int>>& listComplex, const list<int*>& listPointer)
		{
			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.rend();
			auto iterComplex = listComplex.rend();
			auto iterPointer = listPointer.rend();

			// Validation des résultats ------------------

			// La file régulière.
			iterRegular--;
			Assert::AreEqual(2, *iterRegular);

			// La file complexe.
			iterComplex--;
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			iterPointer--;
			Assert::AreEqual(10, **iterPointer);
		}
		TEST_METHOD(test_list_const_rend)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			validate_test_list_const_rend(listRegular, listComplex, listPointer);
		}

		TEST_METHOD(test_list_cbegin)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.cbegin();
			auto iterComplex = listComplex.cbegin();
			auto iterPointer = listPointer.cbegin();

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(2, *iterRegular);

			// La file complexe.
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			Assert::AreEqual(10, **iterPointer);
		}

		TEST_METHOD(test_list_cend)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.cend();
			auto iterComplex = listComplex.cend();
			auto iterPointer = listPointer.cend();

			// Validation des résultats ------------------

			// La file régulière.
			iterRegular--;
			Assert::AreEqual(1, *iterRegular);

			// La file complexe.
			iterComplex--;
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			iterPointer--;
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_crbegin)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.crbegin();
			auto iterComplex = listComplex.crbegin();
			auto iterPointer = listPointer.crbegin();

			// Validation des résultats ------------------

			// La file régulière.
			Assert::AreEqual(1, *iterRegular);

			// La file complexe.
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_crend)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_front(3);
			listRegular.push_front(2);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			list<int> other;
			other.push_back(10'000);
			listComplex.push_back(other);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.crend();
			auto iterComplex = listComplex.crend();
			auto iterPointer = listPointer.crend();

			// Validation des résultats ------------------

			// La file régulière.
			iterRegular--;
			Assert::AreEqual(2, *iterRegular);

			// La file complexe.
			iterComplex--;
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 1, result.size());
			Assert::AreEqual(10'000, result.back());

			// La file de pointeurs.
			iterPointer--;
			Assert::AreEqual(10, **iterPointer);
		}

		TEST_METHOD(test_reverse_emptyLists)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthode à tester --------------
			listRegular.reverse();
			listComplex.reverse();
			listPointer.reverse();

			// Validation des résultats ------------------
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_reverse_filledLists)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(3);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			int j = 9;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			listRegular.reverse();
			listComplex.reverse();
			listPointer.reverse();

			// Validation des résultats ------------------
			// On vérifie que les éléments ont bien été ajoutés.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());
			auto iterRegular = listRegular.begin();
			Assert::AreEqual(1, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);

			// La file complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			auto iterComplex = listComplex.begin();
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);


			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(9, **iterPointer);
			++iterPointer;
			Assert::AreEqual(10, **iterPointer);
		}

		TEST_METHOD(test_list_splice_emptyLists)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			list<list<int>> listComplexToCopy;
			list<int*> listPointerToCopy;

			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthode à tester --------------
			listRegular.splice(listRegular.end(), listRegularToCopy);
			listComplex.splice(listComplex.end(), listComplexToCopy);
			listPointer.splice(listPointer.end(), listPointerToCopy);

			// Validation des résultats ------------------
			// Les premières listes doivent avoir été vidés.
			Assert::IsTrue(listRegularToCopy.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegularToCopy.size());

			Assert::IsTrue(listComplexToCopy.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplexToCopy.size());

			Assert::IsTrue(listPointerToCopy.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointerToCopy.size());

			// Les deuxièmes listes doivent avoir les valeurs des premières à la position demandée.
			Assert::IsTrue(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegular.size());

			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_splice_emptyListToCopy)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			list<list<int>> listComplexToCopy;
			list<int*> listPointerToCopy;

			list<int> listRegular;
			listRegular.push_front(7);
			listRegular.push_front(6);
			listRegular.push_front(2);
			listRegular.push_front(22);
			listRegular.push_front(44);
			listRegular.push_front(66);

			list<list<int>> listComplex;
			listComplex.push_front(listRegular);
			list<int> other;
			other.push_back(462);
			other.push_back(3453);
			listComplex.push_front(other);

			list<int*> listPointer;
			int k = 23;
			int l = 14;
			listPointer.push_back(&l);
			listPointer.push_back(&k);
			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.begin();
			iterRegular++;
			iterRegular++;
			iterRegular++;
			listRegular.splice(iterRegular, listRegularToCopy);
			listComplex.splice(listComplex.end(), listComplexToCopy);
			listPointer.splice(listPointer.begin(), listPointerToCopy);

			// Validation des résultats ------------------
			// Les premières listes doivent avoir été vidés.
			Assert::IsTrue(listRegularToCopy.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegularToCopy.size());

			Assert::IsTrue(listComplexToCopy.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplexToCopy.size());

			Assert::IsTrue(listPointerToCopy.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointerToCopy.size());

			// Les deuxièmes listes doivent avoir les valeurs des premières à la position demandée.
			// La liste régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 6, listRegular.size());
			iterRegular = listRegular.begin();
			Assert::AreEqual(66, *iterRegular);
			++iterRegular;
			Assert::AreEqual(44, *iterRegular);
			++iterRegular;
			Assert::AreEqual(22, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(6, *iterRegular);
			++iterRegular;
			Assert::AreEqual(7, *iterRegular);

			// La liste complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)2, listComplex.size());

			auto iterComplex = listComplex.begin();
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 2, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(462, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3453, *iterRegular);

			++iterComplex;
			result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 6, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(66, *iterRegular);
			++iterRegular;
			Assert::AreEqual(44, *iterRegular);
			++iterRegular;
			Assert::AreEqual(22, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(6, *iterRegular);
			++iterRegular;
			Assert::AreEqual(7, *iterRegular);

			// La liste de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(14, **iterPointer);
			++iterPointer;
			Assert::AreEqual(23, **iterPointer);
		}

		TEST_METHOD(test_list_splice_filledListToCopy)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			listRegularToCopy.push_front(2);
			listRegularToCopy.push_front(3);
			listRegularToCopy.push_front(1);

			list<list<int>> listComplexToCopy;
			listComplexToCopy.push_back(listRegularToCopy);

			list<int*> listPointerToCopy;
			int i = 10;
			int j = 9;
			listPointerToCopy.push_back(&i);
			listPointerToCopy.push_back(&j);

			list<int> listRegular;
			list<list<int>> listComplex;
			list<int*> listPointer;

			// Appel de la méthode à tester --------------
			listRegular.splice(listRegular.end(), listRegularToCopy);
			listComplex.splice(listComplex.end(), listComplexToCopy);
			listPointer.splice(listPointer.end(), listPointerToCopy);

			// Validation des résultats ------------------
			// Les premières listes doivent avoir été vidés.
			Assert::IsTrue(listRegularToCopy.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegularToCopy.size());

			Assert::IsTrue(listComplexToCopy.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplexToCopy.size());

			Assert::IsTrue(listPointerToCopy.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointerToCopy.size());

			// Les deuxièmes listes doivent avoir les valeurs des premières à la position demandée.
			// La liste régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());
			auto iterRegular = listRegular.begin();
			Assert::AreEqual(1, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);

			// La liste complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(1, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);

			// La liste de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)2, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(10, **iterPointer);
			++iterPointer;
			Assert::AreEqual(9, **iterPointer);
		}

		TEST_METHOD(test_list_splice_twoFilledLists)
		{
			// Mise en place des données -----------------
			list<int> listRegularToCopy;
			listRegularToCopy.push_front(2);
			listRegularToCopy.push_front(3);
			listRegularToCopy.push_front(1);

			list<list<int>> listComplexToCopy;
			listComplexToCopy.push_back(listRegularToCopy);

			list<int*> listPointerToCopy;
			int i = 10;
			int j = 9;
			listPointerToCopy.push_back(&j);
			listPointerToCopy.push_back(&i);

			list<int> listRegular;
			listRegular.push_front(7);
			listRegular.push_front(6);
			listRegular.push_front(2);
			listRegular.push_front(22);
			listRegular.push_front(44);
			listRegular.push_front(66);

			list<list<int>> listComplex;
			listComplex.push_front(listRegular);
			list<int> other;
			other.push_back(462);
			other.push_back(3453);
			listComplex.push_front(other);

			list<int*> listPointer;
			int k = 23;
			int l = 14;
			listPointer.push_back(&l);
			listPointer.push_back(&k);

			// Appel de la méthode à tester --------------
			auto iterRegular = listRegular.begin();
			iterRegular++;
			iterRegular++;
			iterRegular++;
			listRegular.splice(iterRegular, listRegularToCopy);
			listComplex.splice(listComplex.end(), listComplexToCopy);
			listPointer.splice(listPointer.begin(), listPointerToCopy);

			// Validation des résultats ------------------
			// Les premières listes doivent avoir été vidés.
			Assert::IsTrue(listRegularToCopy.empty());
			Assert::AreEqual((list<int>::size_type) 0, listRegularToCopy.size());

			Assert::IsTrue(listComplexToCopy.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplexToCopy.size());

			Assert::IsTrue(listPointerToCopy.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointerToCopy.size());

			// Les deuxièmes listes doivent avoir les valeurs des premières à la position demandée.
			// La liste régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 9, listRegular.size());
			iterRegular = listRegular.begin();
			Assert::AreEqual(66, *iterRegular);
			++iterRegular;
			Assert::AreEqual(44, *iterRegular);
			++iterRegular;
			Assert::AreEqual(22, *iterRegular);
			++iterRegular;
			Assert::AreEqual(1, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(6, *iterRegular);
			++iterRegular;
			Assert::AreEqual(7, *iterRegular);

			// La liste complexe.
			Assert::IsFalse(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)3, listComplex.size());

			auto iterComplex = listComplex.begin();
			list<int> result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 2, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(462, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3453, *iterRegular);

			++iterComplex;
			result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 6, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(66, *iterRegular);
			++iterRegular;
			Assert::AreEqual(44, *iterRegular);
			++iterRegular;
			Assert::AreEqual(22, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);
			++iterRegular;
			Assert::AreEqual(6, *iterRegular);
			++iterRegular;
			Assert::AreEqual(7, *iterRegular);

			++iterComplex;
			result = *iterComplex;
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type) 3, result.size());
			iterRegular = result.begin();
			Assert::AreEqual(1, *iterRegular);
			++iterRegular;
			Assert::AreEqual(3, *iterRegular);
			++iterRegular;
			Assert::AreEqual(2, *iterRegular);

			// La liste de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)4, listPointer.size());
			auto iterPointer = listPointer.begin();
			Assert::AreEqual(9, **iterPointer);
			++iterPointer;
			Assert::AreEqual(10, **iterPointer);
			++iterPointer;
			Assert::AreEqual(14, **iterPointer);
			++iterPointer;
			Assert::AreEqual(23, **iterPointer);
		}

		TEST_METHOD(test_list_resize_noResize)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(3);
			listRegular.push_back(1);

			list<list<int>> listComplex;

			list<int*> listPointer;
			int i = 10;
			listPointer.push_back(&i);

			// Appel de la méthode  à tester -------------

			// Validation des résultats ------------------
			listRegular.resize(3);
			listComplex.resize(0);
			listPointer.resize(1);

			// La file régulière.
			Assert::AreEqual((list<int>::size_type) 3, listRegular.size());

			// La file complexe.
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			// La file de pointeurs.
			Assert::AreEqual((list<int*>::size_type)1, listPointer.size());
		}

		TEST_METHOD(test_list_resize_greaterResize)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(3);
			listRegular.push_back(1);

			list<list<int>> listComplex;

			list<int*> listPointer;
			int i = 10;
			listPointer.push_back(&i);

			// Appel de la méthode à tester --------------
			// On teste lorsqu'on réserve un nombre supérieur à la taille.
			// Dans ce cas, la taille devrait avoir changé en conséquant et les valeurs
			// devraient être des valeurs par défauts.
			listRegular.resize(6, 999);
			list<int> other;
			other.push_back(10'000);
			listComplex.resize(1, other);
			listPointer.resize(55);

			// Validation des résultats ------------------
			// La file régulière.
			Assert::AreEqual((list<int>::size_type) 6, listRegular.size());
			auto iterRegular = listRegular.begin();
			iterRegular++;
			iterRegular++;
			iterRegular++;
			for (iterRegular; iterRegular != listRegular.end(); ++iterRegular)
			{
				Assert::AreEqual(999, *iterRegular);
			}

			// La file complexe.
			Assert::AreEqual((list<list<int>>::size_type)1, listComplex.size());

			list<int> result = listComplex.front();
			Assert::IsFalse(result.empty());
			Assert::AreEqual((list<int>::size_type)1, result.size());
			Assert::AreEqual(10'000, result.front());

			// La file de pointeurs.
			Assert::AreEqual((list<int*>::size_type)55, listPointer.size());
			auto iterPointer = listPointer.begin();
			iterPointer++;
			for (iterPointer; iterPointer != listPointer.end(); ++iterPointer)
			{
				Assert::AreEqual((int*)nullptr, *iterPointer);
			}
		}

		TEST_METHOD(test_list_resize_lesserResize)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(3);
			listRegular.push_back(1);

			list<list<int>> listComplex;
			listComplex.push_back(listRegular);

			list<int*> listPointer;
			int i = 10;
			listPointer.push_back(&i);

			// Appel de la méthode à tester --------------
			listRegular.resize(2);
			listComplex.resize(0);
			listPointer.resize(0);

			// Validation des résultats ------------------
			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 2, listRegular.size());
			auto iterRegular = listRegular.begin();
			Assert::AreEqual(2, *iterRegular);
			iterRegular++;
			Assert::AreEqual(3, *iterRegular);
			iterRegular++;
			Assert::IsTrue(listRegular.end() == iterRegular);

			// La file complexe.
			Assert::IsTrue(listComplex.empty());
			Assert::AreEqual((list<list<int>>::size_type)0, listComplex.size());

			// La file de pointeurs.
			Assert::IsTrue(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)0, listPointer.size());
		}

		TEST_METHOD(test_list_remove)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			list<int*> listPointer;
			int i = 10;
			int j = 2;
			listPointer.push_back(&i);
			listPointer.push_back(&j);

			// Appel de la méthode à tester --------------
			listRegular.remove(5);
			listPointer.remove(&j);

			// Validation des résultats ------------------
			// On vérifie que l'élément a bien été ajouté.

			// La file régulière.
			Assert::IsFalse(listRegular.empty());
			Assert::AreEqual((list<int>::size_type) 2, listRegular.size());
			auto iterRegularToVerify = listRegular.begin();
			iterRegularToVerify++;
			Assert::AreEqual(19, *iterRegularToVerify);

			// La file de pointeurs.
			Assert::IsFalse(listPointer.empty());
			Assert::AreEqual((list<int*>::size_type)1, listPointer.size());
			auto iterPointerToVerify = listPointer.begin();
			Assert::AreEqual(10, **iterPointerToVerify);
			iterPointerToVerify++;
			Assert::IsTrue(listPointer.end() == iterPointerToVerify);
		}

		TEST_METHOD(test_list_iterator_operatorAsterisk)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			// En accès.
			auto iterBegin = listRegular.begin();
			// En modification.
			auto iterEnd = listRegular.end();
			iterEnd--;
			*iterEnd = 4;

			// Appel de la méthode et validation ---------
			Assert::AreEqual(2, *iterBegin);
			Assert::AreEqual(4, *iterEnd);
		}

		struct Test
		{
			int val = 0;
		};
		TEST_METHOD(test_list_iterator_operatorArrow)
		{
			// Mise en place des données -----------------
			list<Test> listRegular;
			Test other;
			listRegular.push_back(other);

			auto iter = listRegular.begin();

			// Appel de la méthode à teste ---------------
			iter->val = 3;

			// Validation des résultats  -----------------
			Assert::AreEqual(3, (*iter).val);
		}

		TEST_METHOD(test_list_iterator_operatorPlusPlus)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.begin();

			// Appel de la méthode et validation ---------
			iter++;
			Assert::AreEqual(5, *iter);
			iter++;
			Assert::AreEqual(19, *iter);
		}

		TEST_METHOD(test_list_iterator_plusPlusOperator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.begin();

			// Appel de la méthode et validation ---------
			++iter;
			Assert::AreEqual(5, *iter);
			++iter;
			Assert::AreEqual(19, *iter);
		}

		TEST_METHOD(test_list_iterator_operatorMinusMinus)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.end();

			// Appel de la méthode et validation ---------
			iter--;
			Assert::AreEqual(19, *iter);
			iter--;
			Assert::AreEqual(5, *iter);
			iter--;
			Assert::AreEqual(2, *iter);
		}

		TEST_METHOD(test_list_iterator_minusMinusOperator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.end();

			// Appel de la méthode et validation ---------
			iter--;
			Assert::AreEqual(19, *iter);
			iter--;
			Assert::AreEqual(5, *iter);
			iter--;
			Assert::AreEqual(2, *iter);
		}

		TEST_METHOD(test_list_iterator_operatorEqualEqual)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iterBegin = listRegular.begin();
			auto iterMiddle = listRegular.begin();
			iterMiddle++;
			auto iterEnd = listRegular.end();

			// Appel de la méthode et validation ---------
			Assert::IsTrue(iterBegin == listRegular.begin());
			Assert::IsFalse(iterBegin == iterMiddle);
			Assert::IsTrue(iterEnd == listRegular.end());
		}

		TEST_METHOD(test_list_iterator_operatorExclamationEqual)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iterBegin = listRegular.begin();
			auto iterMiddle = listRegular.begin();
			iterMiddle++;
			auto iterEnd = listRegular.end();

			// Appel de la méthode et validation ---------
			Assert::IsFalse(iterBegin != listRegular.begin());
			Assert::IsTrue(iterBegin != iterMiddle);
			Assert::IsFalse(iterEnd != listRegular.end());
		}

		TEST_METHOD(test_list_reverse_iterator_operatorAsterisk)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			// En accès.
			auto iterBegin = listRegular.rbegin();
			// En modification.
			auto iterEnd = listRegular.rend();
			iterEnd--;
			*iterEnd = 4;

			// Appel de la méthode et validation ---------
			Assert::AreEqual(19, *iterBegin);
			Assert::AreEqual(4, *iterEnd);
		}

		TEST_METHOD(test_list_reverse_iterator_operatorArrow)
		{
			// Mise en place des données -----------------
			list<Test> listRegular;
			Test other;
			listRegular.push_back(other);

			auto iter = listRegular.rbegin();

			// Appel de la méthode à teste ---------------
			iter->val = 3;

			// Validation des résultats  -----------------
			Assert::AreEqual(3, (*iter).val);
		}

		TEST_METHOD(test_list_reverse_iterator_operatorPlusPlus)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.rbegin();

			// Appel de la méthode et validation ---------
			iter++;
			Assert::AreEqual(5, *iter);
			iter++;
			Assert::AreEqual(2, *iter);
		}

		TEST_METHOD(test_list_reverse_iterator_plusPlusOperator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.rbegin();

			// Appel de la méthode et validation ---------
			++iter;
			Assert::AreEqual(5, *iter);
			++iter;
			Assert::AreEqual(2, *iter);
		}

		TEST_METHOD(test_list_reverse_iterator_operatorMinusMinus)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.rend();

			// Appel de la méthode et validation ---------
			iter--;
			Assert::AreEqual(2, *iter);
			iter--;
			Assert::AreEqual(5, *iter);
			iter--;
			Assert::AreEqual(19, *iter);
		}

		TEST_METHOD(test_list_reverse_iterator_minusMinusOperator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.rend();

			// Appel de la méthode et validation ---------
			iter--;
			Assert::AreEqual(2, *iter);
			iter--;
			Assert::AreEqual(5, *iter);
			iter--;
			Assert::AreEqual(19, *iter);
		}

		TEST_METHOD(test_list_reverse_iterator_operatorEqualEqual)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iterBegin = listRegular.rbegin();
			auto iterMiddle = listRegular.rbegin();
			iterMiddle++;
			auto iterEnd = listRegular.rend();

			// Appel de la méthode et validation ---------
			Assert::IsTrue(iterBegin == listRegular.rbegin());
			Assert::IsFalse(iterBegin == iterMiddle);
			Assert::IsTrue(iterEnd == listRegular.rend());
		}

		TEST_METHOD(test_list_reverse_iterator_operatorExclamationEqual)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iterBegin = listRegular.rbegin();
			auto iterMiddle = listRegular.rbegin();
			iterMiddle++;
			auto iterEnd = listRegular.rend();

			// Appel de la méthode et validation ---------
			Assert::IsFalse(iterBegin != listRegular.rbegin());
			Assert::IsTrue(iterBegin != iterMiddle);
			Assert::IsFalse(iterEnd != listRegular.rend());
		}

		TEST_METHOD(test_list_const_iterator_iterator_constructor)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.begin();
			iter++;

			// Appel de la méthode à tester --------------
			list<int>::const_iterator constIter(iter);

			// Validation des résultats ------------------
			Assert::AreEqual(5, *constIter);
		}

		TEST_METHOD(test_list_const_iterator_operatorAsterisk)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			// En accès.
			auto iterBegin = listRegular.cbegin();
			auto iterEnd = listRegular.cend();
			iterEnd--;

			// Appel de la méthode et validation ---------
			Assert::AreEqual(2, *iterBegin);
			Assert::AreEqual(19, *iterEnd);
		}

		struct const_Test
		{
			int val = 14;
		};
		TEST_METHOD(test_list_const_iterator_operatorArrow)
		{
			// Mise en place des données -----------------
			list<const_Test> listRegular;
			const_Test other;
			listRegular.push_back(other);

			auto iter = listRegular.cbegin();

			// Appel de la méthode et validation ---------
			Assert::AreEqual(14, iter->val);
		}

		TEST_METHOD(test_list_const_iterator_operatorPlusPlus)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.cbegin();

			// Appel de la méthode et validation ---------
			iter++;
			Assert::AreEqual(5, *iter);
			iter++;
			Assert::AreEqual(19, *iter);
		}

		TEST_METHOD(test_list_const_iterator_plusPlusOperator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.cbegin();

			// Appel de la méthode et validation ---------
			++iter;
			Assert::AreEqual(5, *iter);
			++iter;
			Assert::AreEqual(19, *iter);
		}

		TEST_METHOD(test_list_const_iterator_operatorMinusMinus)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.cend();

			// Appel de la méthode et validation ---------
			iter--;
			Assert::AreEqual(19, *iter);
			iter--;
			Assert::AreEqual(5, *iter);
			iter--;
			Assert::AreEqual(2, *iter);
		}

		TEST_METHOD(test_list_const_iterator_minusMinusOperator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.cend();

			// Appel de la méthode et validation ---------
			iter--;
			Assert::AreEqual(19, *iter);
			iter--;
			Assert::AreEqual(5, *iter);
			iter--;
			Assert::AreEqual(2, *iter);
		}

		TEST_METHOD(test_list_const_iterator_operatorEqualEqual)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iterBegin = listRegular.cbegin();
			auto iterMiddle = listRegular.cbegin();
			iterMiddle++;
			auto iterEnd = listRegular.cend();

			// Appel de la méthode et validation ---------
			Assert::IsTrue(iterBegin == listRegular.cbegin());
			Assert::IsFalse(iterBegin == iterMiddle);
			Assert::IsTrue(iterEnd == listRegular.cend());
		}

		TEST_METHOD(test_list_const_iterator_operatorExclamationEqual)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iterBegin = listRegular.cbegin();
			auto iterMiddle = listRegular.cbegin();
			iterMiddle++;
			auto iterEnd = listRegular.cend();

			// Appel de la méthode et validation ---------
			Assert::IsFalse(iterBegin != listRegular.cbegin());
			Assert::IsTrue(iterBegin != iterMiddle);
			Assert::IsFalse(iterEnd != listRegular.cend());
		}

		TEST_METHOD(test_list_const_reverse_iterator_iterator_constructor)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.rbegin();
			iter++;

			// Appel de la méthode à tester --------------
			list<int>::const_reverse_iterator constIter(iter);

			// Validation des résultats ------------------
			Assert::AreEqual(5, *constIter);
		}

		TEST_METHOD(test_list_const_reverse_iterator_operatorAsterisk)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			// En accès.
			auto iterBegin = listRegular.crbegin();
			auto iterEnd = listRegular.crend();
			iterEnd--;

			// Appel de la méthode et validation ---------
			Assert::AreEqual(19, *iterBegin);
			Assert::AreEqual(2, *iterEnd);
		}

		TEST_METHOD(test_list_const_reverse_iterator_operatorArrow)
		{
			// Mise en place des données -----------------
			list<const_Test> listRegular;
			const_Test other;
			listRegular.push_back(other);

			auto iter = listRegular.crbegin();

			// Validation des résultats  -----------------
			Assert::AreEqual(14, iter->val);
		}

		TEST_METHOD(test_list_const_reverse_iterator_operatorPlusPlus)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.crbegin();

			// Appel de la méthode et validation ---------
			iter++;
			Assert::AreEqual(5, *iter);
			iter++;
			Assert::AreEqual(2, *iter);
		}

		TEST_METHOD(test_list_const_reverse_iterator_plusPlusOperator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.crbegin();

			// Appel de la méthode et validation ---------
			++iter;
			Assert::AreEqual(5, *iter);
			++iter;
			Assert::AreEqual(2, *iter);
		}

		TEST_METHOD(test_list_const_reverse_iterator_operatorMinusMinus)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.crend();

			// Appel de la méthode et validation ---------
			iter--;
			Assert::AreEqual(2, *iter);
			iter--;
			Assert::AreEqual(5, *iter);
			iter--;
			Assert::AreEqual(19, *iter);
		}

		TEST_METHOD(test_list_const_reverse_iterator_minusMinusOperator)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iter = listRegular.crend();

			// Appel de la méthode et validation ---------
			iter--;
			Assert::AreEqual(2, *iter);
			iter--;
			Assert::AreEqual(5, *iter);
			iter--;
			Assert::AreEqual(19, *iter);
		}

		TEST_METHOD(test_list_const_reverse_iterator_operatorEqualEqual)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iterBegin = listRegular.crbegin();
			auto iterMiddle = listRegular.crbegin();
			iterMiddle++;
			auto iterEnd = listRegular.crend();

			// Appel de la méthode et validation ---------
			Assert::IsTrue(iterBegin == listRegular.crbegin());
			Assert::IsFalse(iterBegin == iterMiddle);
			Assert::IsTrue(iterEnd == listRegular.crend());
		}

		TEST_METHOD(test_list_const_reverse_iterator_operatorExclamationEqual)
		{
			// Mise en place des données -----------------
			list<int> listRegular;
			listRegular.push_back(2);
			listRegular.push_back(5);
			listRegular.push_back(19);

			auto iterBegin = listRegular.crbegin();
			auto iterMiddle = listRegular.crbegin();
			iterMiddle++;
			auto iterEnd = listRegular.crend();

			// Appel de la méthode et validation ---------
			Assert::IsFalse(iterBegin != listRegular.crbegin());
			Assert::IsTrue(iterBegin != iterMiddle);
			Assert::IsFalse(iterEnd != listRegular.crend());
		}
	};
}