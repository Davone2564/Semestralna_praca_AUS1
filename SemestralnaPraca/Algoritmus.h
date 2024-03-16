#pragma once
#include <libds/heap_monitor.h>
#include <libds/amt/implicit_sequence.h>
#include <libds/amt/explicit_hierarchy.h>
#include <libds/adt/table.h>
#include "UzemnaJednotka.h"
#include "Kraj.h"
#include "Okres.h"
#include "Obec.h"
#include <fstream>
#include <iterator>
#include <limits>

class Algoritmus
{
private:
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* aHierarchia;
	ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>* aKrajeTabulka;
	ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>* aOkresyTabulka;
	ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>* aObceTabulka;
public:
	Algoritmus();
	~Algoritmus();
	ds::amt::ImplicitSequence<UzemnaJednotka*>* NacitajDataUroven1(std::string nazovSuboru);
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* NacitajDataUroven2a3();
	template<typename Iterator> 
	ds::amt::ImplicitSequence<UzemnaJednotka*> filtrujData(Iterator zaciatok, Iterator koniec, std::function<bool(UzemnaJednotka)> predikat);
	ds::amt::ImplicitSequence<std::string> rozdelString(std::string str, char dl);
	void vypisHodnotuZTabulky(std::string kluc, std::string typ);
	void vypisUzemneJednotkyZTabulky(std::string typ);
};

Algoritmus::Algoritmus()
{
	this->aHierarchia = nullptr;
	this->aKrajeTabulka = nullptr;
	this->aOkresyTabulka = nullptr;
	this->aObceTabulka = nullptr;
}

Algoritmus::~Algoritmus() {
	// vymazavame objekty UzemnychJednotiek vytvorene v hierarchii
	if (this->aHierarchia) {
		std::function<void(ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*)> mazanieFunkcia = [](ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* blok) { delete blok->data_; };
		this->aHierarchia->processPostOrder(this->aHierarchia->accessRoot(), mazanieFunkcia);
		delete this->aHierarchia;
	}

	// vymazavame postupne vsetky IS, ktore sa nachadzaju v tabulkach ako objekty
	if (this->aKrajeTabulka) {
		ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>::IteratorType itk = this->aKrajeTabulka->begin();
		while (itk != this->aKrajeTabulka->end()) {
			delete itk.operator*().data_;
			itk++;
		}
		delete this->aKrajeTabulka;
	}

	if (this->aOkresyTabulka) {
		ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>::IteratorType itok = this->aOkresyTabulka->begin();
		while (itok != this->aOkresyTabulka->end()) {
			delete itok.operator*().data_;
			itok++;
		}
		delete this->aOkresyTabulka;
	}

	if (this->aObceTabulka) {
		ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>::IteratorType itob = this->aObceTabulka->begin();
		while (itob != this->aObceTabulka->end()) {
			delete itob.operator*().data_;
			itob++;
		}
		delete this->aObceTabulka;
	}
}

ds::amt::ImplicitSequence<UzemnaJednotka*>* Algoritmus::NacitajDataUroven1(std::string nazovSuboru)
{
	ds::amt::ImplicitSequence<UzemnaJednotka*>* uzemneJednotky = new ds::amt::ImplicitSequence<UzemnaJednotka*>();
	std::ifstream input;
	std::string riadok;
	int triediacieCislo;
	std::string kod;
	std::string oficialnyNazov;
	std::string strednyNazov;
	std::string kratkyNazov;
	std::string poznamka;
	ds::amt::ImplicitSequence<std::string> rozdelenyString;
	input.open(nazovSuboru);
	input.ignore(LLONG_MAX, '\n');
	while (!input.eof()) {
		getline(input, riadok);
		rozdelenyString.assign(rozdelString(riadok, ';'));

		triediacieCislo = stoi(rozdelenyString.accessFirst()->data_);
		kod = rozdelenyString.access(1)->data_;
		oficialnyNazov = rozdelenyString.access(2)->data_;
		strednyNazov = rozdelenyString.access(3)->data_;
		kratkyNazov = rozdelenyString.access(4)->data_;
		poznamka = rozdelenyString.access(5)->data_;

		uzemneJednotky->insertLast().data_ = new UzemnaJednotka(triediacieCislo, kod, oficialnyNazov, strednyNazov, kratkyNazov, poznamka);

	}
	input.close();
	return uzemneJednotky;
}

ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* Algoritmus::NacitajDataUroven2a3() {
	this->aHierarchia = new ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>();
	this->aKrajeTabulka = new ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>();
	this->aOkresyTabulka = new ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>();
	this->aObceTabulka = new ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>();
	this->aHierarchia->emplaceRoot().data_ = new UzemnaJednotka(0, "SK", "Slovenská republika", "", "Slovensko", "");
	std::ifstream input;
	input.open("kraje.csv");
	std::string riadok;
	input.ignore(LLONG_MAX, '\n');
	int triediacieCislo;
	std::string kod;
	std::string oficialnyNazov;
	std::string strednyNazov;
	std::string kratkyNazov;
	std::string poznamka;
	ds::amt::ImplicitSequence<std::string> rozdelenyString;
	Kraj* novyKraj = nullptr;
	Okres* novyOkres = nullptr;
	Obec* novaObec = nullptr;
	int i = 0;
	//nacitame si najprv kraje a ulozime si ich ako synov korena
	while (!input.eof()) {
		getline(input, riadok);
		rozdelenyString.assign(rozdelString(riadok, ';'));

		triediacieCislo = stoi(rozdelenyString.accessFirst()->data_);
		kod = rozdelenyString.access(1)->data_;
		oficialnyNazov = rozdelenyString.access(2)->data_;
		strednyNazov = rozdelenyString.access(3)->data_;
		kratkyNazov = rozdelenyString.access(4)->data_;
		poznamka = rozdelenyString.access(5)->data_;

		novyKraj = new Kraj(triediacieCislo, kod, oficialnyNazov, strednyNazov, kratkyNazov, poznamka);
		this->aHierarchia->emplaceSon(*this->aHierarchia->accessRoot(), i).data_ = novyKraj;
		this->aKrajeTabulka->insert(novyKraj->getOficialnyNazov(), new ds::amt::ImplicitSequence<UzemnaJednotka*>());
		this->aKrajeTabulka->find(novyKraj->getOficialnyNazov())->insertLast().data_ = novyKraj;
		i++;
	}
	
	input.close();
	input.open("okresy.csv");
	input.ignore(LLONG_MAX, '\n');
	i = 0;
	ds::amt::ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*> kraje = *this->aHierarchia->accessRoot()->sons_;
	ds::amt::ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>::ImplicitSequenceIterator it = kraje.begin();
	//nacitavame okresy ako synov jednotlivych krajov
	while (it != kraje.end()) {
		getline(input, riadok);
		rozdelenyString.assign(rozdelString(riadok, ';'));

		triediacieCislo = stoi(rozdelenyString.accessFirst()->data_);
		kod = rozdelenyString.access(1)->data_;
		oficialnyNazov = rozdelenyString.access(2)->data_;
		strednyNazov = rozdelenyString.access(3)->data_;
		kratkyNazov = rozdelenyString.access(4)->data_;
		poznamka = rozdelenyString.access(5)->data_;

		novyOkres = new Okres(triediacieCislo, kod, oficialnyNazov, strednyNazov, kratkyNazov, poznamka);
		// posledny okres Zahranicie
		if (triediacieCislo == 81) {
			this->aHierarchia->emplaceSon(*it.operator*(), i).data_ = novyOkres;
			// ak zistime ze tabulka uz obsahuje uzemny celok s rovnakym nazvom tak uz len pridame hodnotu do IS daneho kluca
			if (!this->aOkresyTabulka->contains(novyOkres->getOficialnyNazov())) {
				this->aOkresyTabulka->insert(novyOkres->getOficialnyNazov(), new ds::amt::ImplicitSequence<UzemnaJednotka*>());
			}
			this->aOkresyTabulka->find(novyOkres->getOficialnyNazov())->insertLast().data_ = novyOkres;
			it++;
		}
		else if (it.operator*()->data_->getPoznamka().substr(5).compare(kod.substr(0, 5)) == 0) {
			this->aHierarchia->emplaceSon(*it.operator*(), i).data_ = novyOkres;
			if (!this->aOkresyTabulka->contains(novyOkres->getOficialnyNazov())) {
				this->aOkresyTabulka->insert(novyOkres->getOficialnyNazov(), new ds::amt::ImplicitSequence<UzemnaJednotka*>());
			}
			this->aOkresyTabulka->find(novyOkres->getOficialnyNazov())->insertLast().data_ = novyOkres;
			i++;
		}
		else {
			it++;
			i = 0;
			
			this->aHierarchia->emplaceSon(*it.operator*(), i).data_ = novyOkres;
			if (!this->aOkresyTabulka->contains(novyOkres->getOficialnyNazov())) {
				this->aOkresyTabulka->insert(novyOkres->getOficialnyNazov(), new ds::amt::ImplicitSequence<UzemnaJednotka*>());
			}
			this->aOkresyTabulka->find(novyOkres->getOficialnyNazov())->insertLast().data_ = novyOkres;
			i++;
		}
	}

	//nacitavame obce ako synov jednotlivych okresov
	input.close();
	input.open("obce.csv");
	input.ignore(LLONG_MAX, '\n');
	i = 0;
	ds::amt::ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*> okresy;
	ds::amt::ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>::ImplicitSequenceIterator itk = kraje.begin();
	while (itk != kraje.end()) {
		if (itk.operator*()->data_->getKod().compare("9") == 0) {
			break;
		}
		okresy.assign(*itk.operator*()->sons_);
		ds::amt::ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>::ImplicitSequenceIterator ito = okresy.begin();
		while (ito != okresy.end()) {
			getline(input, riadok);
			rozdelenyString.assign(rozdelString(riadok, ';'));

			triediacieCislo = stoi(rozdelenyString.accessFirst()->data_);
			kod = rozdelenyString.access(1)->data_;
			oficialnyNazov = rozdelenyString.access(2)->data_;
			strednyNazov = rozdelenyString.access(3)->data_;
			kratkyNazov = rozdelenyString.access(4)->data_;
			poznamka = rozdelenyString.access(5)->data_;

			novaObec = new Obec(triediacieCislo, kod, oficialnyNazov, strednyNazov, kratkyNazov, poznamka);
			if (ito.operator*()->data_->getKod().compare(kod.substr(0, 6)) == 0) {
				this->aHierarchia->emplaceSon(*ito.operator*(), i).data_ = novaObec;
				if (!this->aObceTabulka->contains(novaObec->getOficialnyNazov())) {
					this->aObceTabulka->insert(novaObec->getOficialnyNazov(), new ds::amt::ImplicitSequence<UzemnaJednotka*>());
				}
				this->aObceTabulka->find(novaObec->getOficialnyNazov())->insertLast().data_ = novaObec;
				i++;
			}
			else {
				i = 0;
				ito++;
				if (ito != okresy.end()) {
					this->aHierarchia->emplaceSon(*ito.operator*(), i).data_ = novaObec;
					if (!this->aObceTabulka->contains(novaObec->getOficialnyNazov())) {
						this->aObceTabulka->insert(novaObec->getOficialnyNazov(), new ds::amt::ImplicitSequence<UzemnaJednotka*>());
					}
					this->aObceTabulka->find(novaObec->getOficialnyNazov())->insertLast().data_ = novaObec;
					i++;
				}
				else {
					delete novaObec;
				}
			}
		}
		i = 0;
		itk++;
	}
	//pridame si dve obce, ktore patria okresom zahranicie
	okresy.assign(*kraje.accessLast()->data_->sons_);
	for (int i = 0; i < 2; i++) {
		getline(input, riadok);
		rozdelenyString.assign(rozdelString(riadok, ';'));

		triediacieCislo = stoi(rozdelenyString.accessFirst()->data_);
		kod = rozdelenyString.access(1)->data_;
		oficialnyNazov = rozdelenyString.access(2)->data_;
		strednyNazov = rozdelenyString.access(3)->data_;
		kratkyNazov = rozdelenyString.access(4)->data_;
		poznamka = rozdelenyString.access(5)->data_;

		novaObec = new Obec(triediacieCislo, kod, oficialnyNazov, strednyNazov, kratkyNazov, poznamka);
		this->aHierarchia->emplaceSon(*okresy.access(i)->data_, 0).data_ = novaObec;
		if (!this->aObceTabulka->contains(novaObec->getOficialnyNazov())) {
			this->aObceTabulka->insert(novaObec->getOficialnyNazov(), new ds::amt::ImplicitSequence<UzemnaJednotka*>());
		}
		this->aObceTabulka->find(novaObec->getOficialnyNazov())->insertLast().data_ = novaObec;
	}
	return this->aHierarchia;
}

template<typename Iterator>
ds::amt::ImplicitSequence<UzemnaJednotka*> Algoritmus::filtrujData(Iterator zaciatok, Iterator koniec, std::function<bool(UzemnaJednotka)> predikat)
{
	ds::amt::ImplicitSequence<UzemnaJednotka*> filtrovaneData;
	while (zaciatok != koniec) {
		UzemnaJednotka* uzemnaJednotka = zaciatok.operator*();
		if (predikat(*uzemnaJednotka)) {
			filtrovaneData.insertLast().data_ = uzemnaJednotka;
		}
		++zaciatok;
	}
	return filtrovaneData;
}

ds::amt::ImplicitSequence<std::string> Algoritmus::rozdelString(std::string str, char dl)
{
	std::string slovo = "";
	str = str;
	int dlzkaStringu = str.size();

	ds::amt::ImplicitSequence<std::string> substr_zoznam;
	for (int i = 0; i <= dlzkaStringu; i++) {
		// ak sa dostaneme k delimiteru, tak ulozime slovo do vektoru a vynulujeme ho
		if (str[i] == dl || i == dlzkaStringu) {
			substr_zoznam.insertLast().data_ = slovo;
			slovo = "";
		}
		else {
			slovo += str[i];
		}
	}

	return substr_zoznam;
}

void Algoritmus::vypisHodnotuZTabulky(std::string kluc, std::string typ) {
	ds::amt::ImplicitSequence<UzemnaJednotka*>** hodnota = nullptr;
	if (typ.compare("kraj") == 0) {
		this->aKrajeTabulka->tryFind(kluc, hodnota);
	}
	else if (typ.compare("okres") == 0) {
		this->aOkresyTabulka->tryFind(kluc, hodnota);
	}
	else if (typ.compare("obec") == 0) {
		this->aObceTabulka->tryFind(kluc, hodnota);
	}
	else {
		std::cout << "Zadali ste nesprávny typ územnej jednotky!";
	}

	if (!hodnota) {
		std::cout << "V danej tabu¾ke sa nenachádza územná jednotka so zadaným názvom\n";
	}
	else {
		for (int i = 0; i < (*hodnota)->size(); i++) {
			std::cout << (*hodnota)->access(i)->data_->toString() << "\n";
		}
	}
	std::cout << "\n";
}

void Algoritmus::vypisUzemneJednotkyZTabulky(std::string typ) {
	if (typ.compare("kraj") == 0) {
		ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>::IteratorType it = this->aKrajeTabulka->begin();
		while (it != this->aKrajeTabulka->end()) {
			for (int i = 0; i < it.operator*().data_->size(); i++) {
				std::cout << it.operator*().data_->access(i)->data_->toString() << "\n";
			}
			++it;
		}
	}
	else if (typ.compare("okres") == 0) {
		ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>::IteratorType it = this->aOkresyTabulka->begin();
		while (it != this->aOkresyTabulka->end()) {
			for (int i = 0; i < it.operator*().data_->size(); i++) {
				std::cout << it.operator*().data_->access(i)->data_->toString() << "\n";
			}
			++it;
		}
	}
	else if (typ.compare("obec") == 0) {
		ds::adt::SortedSequenceTable<std::string, ds::amt::ImplicitSequence<UzemnaJednotka*>*>::IteratorType it = this->aObceTabulka->begin();
		while (it != this->aObceTabulka->end()) {
			for (int i = 0; i < it.operator*().data_->size(); i++) {
				std::cout << it.operator*().data_->access(i)->data_->toString() << "\n";
			}
			++it;
		}
	}
	else {
		std::cout << "Bol zadaný nesprávny typ územnej jednotky\n";
	}
}