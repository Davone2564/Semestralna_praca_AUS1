#pragma once
#include "UzemnaJednotka.h"

class Obec : public UzemnaJednotka
{
public:
	Obec(int triediacieCislo, std::string kod, std::string oficialnyNazov, std::string strednyNazov, std::string kratkyNazov, std::string poznamka);
};

Obec::Obec(int triediacieCislo, std::string kod, std::string oficialnyNazov, std::string strednyNazov, std::string kratkyNazov, std::string poznamka) :
	UzemnaJednotka(triediacieCislo, kod, oficialnyNazov, strednyNazov, kratkyNazov, poznamka)
{
	setTyp("obec");
}