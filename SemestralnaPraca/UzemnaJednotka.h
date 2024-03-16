#pragma once
#include <libds/heap_monitor.h>
#include <string>

class UzemnaJednotka
{
private:
	int aTriediacieCislo;
	std::string aKod;
	std::string aOficialnyNazov;
	std::string aStrednyNazov;
	std::string aKratkyNazov;
	std::string aPoznamka;
	std::string aTyp;
public:
	UzemnaJednotka();
	UzemnaJednotka(int triediacieCislo, std::string kod, std::string oficialnyNazov, std::string strednyNazov, std::string kratkyNazov, std::string poznamka);
	std::string getKod();
	std::string getOficialnyNazov();
	std::string getKratkyNazov();
	std::string getPoznamka();
	std::string getTyp();
	int getVowelsCount();
	void setTyp(std::string typ);
	bool startsWithStr(std::string str);
	bool containsStr(std::string str);
	bool hasType(std::string str);
	int compareAlphabetical(UzemnaJednotka& other);
	int compareVowelsCount(UzemnaJednotka& other);
	virtual std::string toString();
};

UzemnaJednotka::UzemnaJednotka() {
	aTriediacieCislo = 0;
	aKod = "";
	aOficialnyNazov = "";
	aStrednyNazov = "";
	aKratkyNazov = "";
	aPoznamka = "";
	aTyp = "krajina";
}

UzemnaJednotka::UzemnaJednotka(int triediacieCislo, std::string kod, std::string oficialnyNazov, std::string strednyNazov, std::string kratkyNazov, std::string poznamka)
{
	aTriediacieCislo = triediacieCislo;
	aKod = kod;
	aOficialnyNazov = oficialnyNazov;
	aStrednyNazov = strednyNazov;
	aKratkyNazov = kratkyNazov;
	aPoznamka = poznamka;
	aTyp = "krajina";
}

std::string UzemnaJednotka::getKod() {
	return this->aKod;
}

std::string UzemnaJednotka::getOficialnyNazov() {
	return this->aOficialnyNazov;
}

std::string UzemnaJednotka::getKratkyNazov() {
	return this->aKratkyNazov;
}

std::string UzemnaJednotka::getPoznamka() {
	return this->aPoznamka;
}

std::string UzemnaJednotka::getTyp() {
	return aTyp;
}

int UzemnaJednotka::getVowelsCount()
{
	int pocetSamohlasok = 0;
	std::string samohlasky = "aáäeéiíyýoóôuúAÁEÉIÍYÝOÓUÚ";
	for (int i = 0; i < this->aOficialnyNazov.size(); i++) {
		for (int j = 0; j < samohlasky.size(); j++) {
			if (this->aOficialnyNazov[i] == samohlasky[j]) {
				pocetSamohlasok++;
				break;
			}
		}
	}
	return pocetSamohlasok;
}

void UzemnaJednotka::setTyp(std::string typ) {
	aTyp = typ;
}

bool UzemnaJednotka::startsWithStr(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	std::transform(aOficialnyNazov.begin(), aOficialnyNazov.end(), aOficialnyNazov.begin(), ::tolower);
	if (aOficialnyNazov.find(str) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool UzemnaJednotka::containsStr(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	std::transform(aOficialnyNazov.begin(), aOficialnyNazov.end(), aOficialnyNazov.begin(), ::tolower);
	if (aOficialnyNazov.find(str) == std::string::npos) {
		return false;
	}
	else {
		return true;
	}
}

bool UzemnaJednotka::hasType(std::string str) {
	return str.compare(this->aTyp) == 0;
}

int UzemnaJednotka::compareAlphabetical(UzemnaJednotka& other)
{
	return this->aOficialnyNazov.compare(other.aOficialnyNazov);
}

int UzemnaJednotka::compareVowelsCount(UzemnaJednotka& other)
{
	if (this->getVowelsCount() < other.getVowelsCount()) {
		return -1;
	}
	else if (this->getVowelsCount() > other.getVowelsCount()) {
		return 1;
	}
	else {
		return 0;
	}
}

std::string UzemnaJednotka::toString() {
	return std::to_string(this->aTriediacieCislo) + " " + this->aKod + " " + this->aOficialnyNazov + " " + this->aStrednyNazov + " " + this->aKratkyNazov + " " + this->aPoznamka;
}