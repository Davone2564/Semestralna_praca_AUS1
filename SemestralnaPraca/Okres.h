#pragma once
#include "UzemnaJednotka.h"

class Okres : public UzemnaJednotka
{
public:
	Okres(int triediacieCislo, std::string kod, std::string oficialnyNazov, std::string strednyNazov, std::string kratkyNazov, std::string poznamka);
};

Okres::Okres(int triediacieCislo, std::string kod, std::string oficialnyNazov, std::string strednyNazov, std::string kratkyNazov, std::string poznamka) :
	UzemnaJednotka(triediacieCislo, kod, oficialnyNazov, strednyNazov, kratkyNazov, poznamka)
{
	setTyp("okres");
}