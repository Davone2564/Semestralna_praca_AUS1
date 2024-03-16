#pragma once
#include "UzemnaJednotka.h"

class Kraj : public UzemnaJednotka
{
public:
	Kraj(int triediacieCislo, std::string kod, std::string oficialnyNazov, std::string strednyNazov, std::string kratkyNazov, std::string poznamka);
	std::string toString() override;
};

Kraj::Kraj(int triediacieCislo, std::string kod, std::string oficialnyNazov, std::string strednyNazov, std::string kratkyNazov, std::string poznamka) :
	UzemnaJednotka(triediacieCislo, kod, oficialnyNazov, strednyNazov, kratkyNazov, poznamka)
{
	setTyp("kraj");
}

std::string Kraj::toString() {
	return this->getKod() + " " + this->getOficialnyNazov() + " " + this->getKratkyNazov() + " " + this->getPoznamka();
}