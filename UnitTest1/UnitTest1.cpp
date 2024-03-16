#include "pch.h"
#include "CppUnitTest.h"
#include "../SemestralnaPraca/Algoritmus.h"
#include "../SemestralnaPraca/UzemnaJednotka.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(AlgoritmusTest)
	{
	public:
		TEST_METHOD(rozdelString1)
		{
			std::string str = "aa.bb.cc";
			Algoritmus* algoritmus = new Algoritmus();
			ds::amt::ImplicitSequence<std::string> rozdelenyString = algoritmus->rozdelString(str, '.');
			Assert::AreEqual(std::string("aa"), rozdelenyString.accessFirst()->data_);
			Assert::AreEqual(std::string("bb"), rozdelenyString.accessNext(*rozdelenyString.accessFirst())->data_);
			Assert::AreEqual(std::string("cc"), rozdelenyString.accessLast()->data_);
			delete algoritmus;
		}

		TEST_METHOD(rozdelString2)
		{
			std::string str = "..";
			Algoritmus* algoritmus = new Algoritmus();
			ds::amt::ImplicitSequence<std::string> rozdelenyString = algoritmus->rozdelString(str, '.');
			Assert::AreEqual(std::string(""), rozdelenyString.accessFirst()->data_);
			Assert::AreEqual(std::string(""), rozdelenyString.accessNext(*rozdelenyString.accessFirst())->data_);
			Assert::AreEqual(std::string(""), rozdelenyString.accessLast()->data_);
			delete algoritmus;
		}

		TEST_METHOD(rozdelString3)
		{
			std::string str = "..bg..pa..df";
			Algoritmus* algoritmus = new Algoritmus();
			ds::amt::ImplicitSequence<std::string> rozdelenyString = algoritmus->rozdelString(str, '.');
			int i = 0;
			Assert::AreEqual(std::string(""), rozdelenyString.access(i)->data_);
			i++;
			Assert::AreEqual(std::string(""), rozdelenyString.access(i)->data_);
			i++;
			Assert::AreEqual(std::string("bg"), rozdelenyString.access(i)->data_);
			i++;
			Assert::AreEqual(std::string(""), rozdelenyString.access(i)->data_);
			i++;
			Assert::AreEqual(std::string("pa"), rozdelenyString.access(i)->data_);
			i++;
			Assert::AreEqual(std::string(""), rozdelenyString.access(i)->data_);
			i++;
			Assert::AreEqual(std::string("df"), rozdelenyString.access(i)->data_);
			delete algoritmus;
		}
	};

	TEST_CLASS(UzemnaJednotkaTest)
	{
	public:
		TEST_METHOD(getVowelsCount1) {
			UzemnaJednotka* uzemnaJednotka = new UzemnaJednotka(1, "", "Slovensko", "", "SK", "");
			Assert::AreEqual(3, uzemnaJednotka->getVowelsCount());
			delete uzemnaJednotka;
		}

		TEST_METHOD(getVowelsCount2) {
			UzemnaJednotka* uzemnaJednotka = new UzemnaJednotka(1, "", "Krásno nad Kysucou", "", "KnK", "");
			Assert::AreEqual(7, uzemnaJednotka->getVowelsCount());
			delete uzemnaJednotka;
		}

		TEST_METHOD(getVowelsCount3) {
			UzemnaJednotka* uzemnaJednotka = new UzemnaJednotka(1, "", "krk", "", "krk", "");
			Assert::AreEqual(0, uzemnaJednotka->getVowelsCount());
			delete uzemnaJednotka;
		}
	};
}
