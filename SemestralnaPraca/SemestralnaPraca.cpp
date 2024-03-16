#define UROVEN1
//#define UROVEN2
//#define UROVEN3
//#define UROVEN4
#include <libds/heap_monitor.h>
#include <libds/amt/hierarchy.h>
#include <iostream>
#include "Algoritmus.h"
#include "TriediaciAlgoritmus.h"
#include <Windows.h>

#ifdef UROVEN1
int main() {
    initHeapMonitor();
    std::setlocale(LC_ALL, "slovak");
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    std::function<bool(UzemnaJednotka)> predikat;
    ds::amt::ImplicitSequence<UzemnaJednotka*>* data = nullptr;
    Algoritmus algoritmus;
    std::string vstup;

    std::cout << "Semestrálna práca, úroveň 1\n";
    std::cout << "-------------------------------------------------------------------------------------------------\n";
    while (true) {
        while (true) {
            std::cout << "Zadajte, ktorý typ územných jednotiek chcete prehľadávať(kraje(kr)/obce(ob)/okresy(ok)/koniec(k)):";
            std::cin >> vstup;
            if (vstup.compare("kraje") == 0 || vstup.compare("KRAJE") == 0 || vstup.compare("kr") == 0 || vstup.compare("KR") == 0) {
                data = algoritmus.NacitajDataUroven1("kraje.csv");
                break;
            }
            else if (vstup.compare("okresy") == 0 || vstup.compare("OKRESY") == 0 || vstup.compare("ok") == 0 || vstup.compare("OK") == 0) {
                data = algoritmus.NacitajDataUroven1("okresy.csv");
                break;
            }
            else if (vstup.compare("obce") == 0 || vstup.compare("OBCE") == 0 || vstup.compare("ob") == 0 || vstup.compare("OB") == 0) {
                data = algoritmus.NacitajDataUroven1("obce.csv");
                break;
            }
            else if (vstup.compare("koniec") == 0 || vstup.compare("KONIEC") == 0 || vstup.compare("k") == 0 || vstup.compare("K") == 0) {
                std::cout << "Dovidenia\n";
                return 0;
            }
            else {
                std::cout << "Zadali ste zlý vstup.\n";
                continue;
            }
        }
        bool koniec = false;
        while (!koniec) {
            std::cout << "Zadajte, ktorý typ prehľadávania chcete použiť(startsWithStr(s)/containsStr(c)/printAll(p)/koniec prehľadávania(k)):";
            std::cin >> vstup;
            if (vstup.compare("startsWithStr") == 0 || vstup.compare("s") == 0 || vstup.compare("S") == 0) {
                std::cout << "Zadajte reťazec, ktorým začínajú názvy územných jednotiek:";
                std::cin.ignore();
                std::getline(std::cin, vstup);
                predikat = [vstup](UzemnaJednotka uzemnaJednotka) { return uzemnaJednotka.startsWithStr(vstup); };
            }
            else if (vstup.compare("containsStr") == 0 || vstup.compare("c") == 0 || vstup.compare("C") == 0) {
                std::cout << "Zadajte reťazec, ktorý obsahujú názvy územných jednotiek:";
                std::cin.ignore();
                std::getline(std::cin, vstup);
                predikat = [vstup](UzemnaJednotka uzemnaJednotka) { return uzemnaJednotka.containsStr(vstup); };
            }
            else if (vstup.compare("printAll") == 0 || vstup.compare("p") == 0 || vstup.compare("P") == 0) {
                predikat = [](UzemnaJednotka uzemnaJednotka) { return true; };
            }
            else if (vstup.compare("koniec") == 0 || vstup.compare("k") == 0 || vstup.compare("K") == 0) {
                for (int i = 0; i < data->size(); i++) {
                    delete data->access(i)->data_;
                }
                delete data;
                std::cout << "\n";
                break;
            }
            else {
                std::cout << "Zadal si zlý vstup.\n";
                continue;
            }

            ds::amt::ImplicitSequence<UzemnaJednotka*> filtrovaneData(algoritmus.filtrujData(data->begin(), data->end(), predikat));
            for (int i = 0; i < filtrovaneData.size(); i++) {
                std::cout << filtrovaneData.access(i)->data_->getOficialnyNazov() << '\n';
            }
            std::cout << '\n';
        }
    }
}
#endif

#ifdef UROVEN2
int main()
{
    initHeapMonitor();
    std::setlocale(LC_ALL, "slovak");
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    ds::amt::ImplicitSequence<UzemnaJednotka>* data = nullptr;
    Algoritmus* algoritmus = new Algoritmus();
    ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia = algoritmus->NacitajDataUroven2a3();
    ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* aktualnyVrchol = hierarchia->accessRoot();
    ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator* aktPozicia = new ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator(hierarchia, aktualnyVrchol);

    std::string vstup;
    std::cout << "Semestrálna práca, úroveň 2\n";
    std::cout << "-----------------------------------------------------------------------------------------------------------\n";
    while (true) {
        std::function<bool(UzemnaJednotka)> predikat;
        std::cout << "Aktuálna pozícia: " << aktualnyVrchol->data_->getOficialnyNazov() << "\n";
        std::cout << "Zvoľte možnosť(printAll(p)/startsWithStr(s)/containsStr(c)/hasType(h)/zvolSyna(zs)/zvolOtca(zo)/koniec(k)):";
        std::cin >> vstup;
        if (vstup.compare("p") == 0) {
            // predikat bude vzdy vracat hodnotu true, dostaneme vsetky uzemne jednotky podhierarchie
            predikat = [](UzemnaJednotka uzemnaJednotka) { return true; };
        }
        else if (vstup.compare("s") == 0) {
            std::cout << "Zadajte reťazec, ktorým začínajú názvy územných jednotiek:";
            std::cin.ignore();
            std::getline(std::cin, vstup);
            predikat = [vstup](UzemnaJednotka uzemnaJednotka) { return uzemnaJednotka.startsWithStr(vstup); };
        }
        else if (vstup.compare("c") == 0) {
            std::cout << "Zadajte reťazec, ktorý obsahujú názvy územných jednotiek:";
            std::cin.ignore();
            std::getline(std::cin, vstup);
            predikat = [vstup](UzemnaJednotka uzemnaJednotka) { return uzemnaJednotka.containsStr(vstup); };
        }
        else if (vstup.compare("h") == 0) {
            std::cout << "Zadajte typ územnej jednotky(kraj/obec/okres):";
            std::cin.ignore();
            std::getline(std::cin, vstup);
            predikat = [vstup](UzemnaJednotka uzemnaJednotka) { return uzemnaJednotka.hasType(vstup); };
        }
        else if (vstup.compare("zs") == 0) {
            for (int i = 0; i < aktualnyVrchol->sons_->size(); i++) {
                std::cout << i << ". " << aktualnyVrchol->sons_->access(i)->data_->data_->getOficialnyNazov() << '\n';
            }
            int number;
            std::cout << "Zadaj cislo, ktoreho syna chces zvolit:";
            std::cin >> number;
            aktualnyVrchol = aktualnyVrchol->sons_->access(number)->data_;
            delete aktPozicia;
            aktPozicia = new ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator(hierarchia, aktualnyVrchol);

        }
        else if (vstup.compare("zo") == 0) {
            aktualnyVrchol = hierarchia->accessParent(*aktualnyVrchol);
            delete aktPozicia;
            aktPozicia = new ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator(hierarchia, aktualnyVrchol);
        }
        else if (vstup.compare("k") == 0) {
            // zmazeme si objekty uzemnych celkov celej hierarchie
            delete algoritmus;
            delete aktPozicia;
            std::cout << "Dovidenia\n";
            return 0;
        }
        else {
            std::cout << "Zadal si zly vstup.\n";
        }
        // ak si pouzivatel zvolil nejaky z predikatov, tak ideme filtrovat data na zaklade tohto predikatu(posleme ho ako funkciu)
        if (predikat) {
            ds::amt::ImplicitSequence<UzemnaJednotka*> filtrovaneData(algoritmus->filtrujData(*aktPozicia, hierarchia->end(), predikat));
            for (int i = 0; i < filtrovaneData.size(); i++) {
                std::cout << filtrovaneData.access(i)->data_->getOficialnyNazov() << '\n';
            }
        }
        std::cout << '\n';
    }
}
#endif

#ifdef UROVEN3
int main() {
    initHeapMonitor();
    std::setlocale(LC_ALL, "slovak");
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    Algoritmus* algoritmus = new Algoritmus();
    algoritmus->NacitajDataUroven2a3();
    std::string nazov;
    std::string typ;
    std::string vstup;

    std::cout << "Semestrálna práca, úroveň 3\n";
    std::cout << "-----------------------------------------------------------------------------------------------------------\n";
    while (true) {
        std::cout << "Zvoľte si možnosť\n1.vyhľadávanie danej územnej jednotky(search)\n2.výpis územných jednotiek daného typu(print)\n3.koniec aplikácie(exit))\nZadaj číslo/písmeno:";
        std::getline(std::cin, vstup);
        if (vstup.compare("1") == 0 || vstup.compare("s") == 0 || vstup.compare("search") == 0) {
            bool koniec = false;
            while (!koniec) {
                while (true) {
                    std::cout << "Zadajte typ územného celku, ktorý chcete vyhľadať(pre koniec vyhľadávania zadajte jednotku):";
                    std::getline(std::cin, typ);
                    if (typ.compare("kraj") == 0 || typ.compare("okres") == 0 || typ.compare("obec") == 0) {
                        break;
                    }
                    else if (typ.compare("1") == 0 || typ.compare("koniec") == 0 || typ.compare("k") == 0) {
                        koniec = true;
                        std::cout << "\n";
                        break;
                    }
                    else {
                        std::cout << "Zadali ste nesprávny typ územnej jednotky\n";
                        continue;
                    }
                }
                if (koniec) {
                    break;
                }
                while (true) {
                    std::cout << "Zadajte názov územného celku ktorého informácie chcete vyhľadať(pre ukončenie stlačte 1):";
                    std::getline(std::cin, nazov);
                    if (nazov.compare("1") == 0 || nazov.compare("k") == 0) {
                        break;
                        std::cout << "\n";
                    }
                    algoritmus->vypisHodnotuZTabulky(nazov, typ);
                }
            }
        }
        else if (vstup.compare("2") == 0 || vstup.compare("print") == 0 || vstup.compare("p") == 0) {
            while (true) {
                std::cout << "Zadajte typ územných jednotiek ktoré chcete vypísať(pre koniec vypisovania zadajte jednotku):";
                std::getline(std::cin, typ);
                if (typ.compare("kraj") == 0 || typ.compare("okres") == 0 || typ.compare("obec") == 0) {
                    algoritmus->vypisUzemneJednotkyZTabulky(typ);
                }
                else if (typ.compare("1") == 0 || typ.compare("koniec") == 0 || typ.compare("k") == 0) {
                    std::cout << "\n";
                    break;
                }
                else {
                    std::cout << "Zadali ste nesprávny typ územnej jednotky\n";
                    continue;
                }
            }
        }
        else if (vstup.compare("3") == 0 || vstup.compare("e") == 0 || vstup.compare("exit") == 0) {
            break;
        }
        else {
            std::cout << "Zadali ste zlý vstup!\n";
        }
    }
    delete algoritmus;
}
#endif

#ifdef UROVEN4
int main() {
    initHeapMonitor();
    std::setlocale(LC_ALL, "slovak");
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    std::function<int(UzemnaJednotka*, UzemnaJednotka*)> komparator;
    ds::amt::ImplicitSequence<UzemnaJednotka>* data = nullptr;
    Algoritmus* algoritmus = new Algoritmus();
    ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia = algoritmus->NacitajDataUroven2a3();
    ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* aktualnyVrchol = hierarchia->accessRoot();
    ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator* aktPozicia = new ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator(hierarchia, aktualnyVrchol);

    std::string vstup;
    std::cout << "Semestrálna práca, úroveň 4\n";
    std::cout << "-----------------------------------------------------------------------------------------------------------\n";
    while (true) {
        bool vypisatPocetSamohlasok = false;
        std::function<bool(UzemnaJednotka)> predikat;
        std::cout << "Aktuálna pozícia: " << aktualnyVrchol->data_->getOficialnyNazov() << "\n";
        std::cout << "Zvoľ si predikat(printAll(p)/startsWithStr(s)/containsStr(c)/hasType(h)/zvolSyna(zs)/zvolOtca(zo)/koniec(k)):";
        std::cin >> vstup;
        if (vstup.compare("p") == 0) {
            // predikat bude vzdy vracat hodnotu true, dostaneme vsetky uzemne jednotky podhierarchie
            predikat = [](UzemnaJednotka uzemnaJednotka) { return true; };
        }
        else if (vstup.compare("s") == 0) {
            std::cout << "Zadajte reťazec, ktorým začínajú názvy územných jednotiek:";
            std::cin.ignore();
            std::getline(std::cin, vstup);
            predikat = [vstup](UzemnaJednotka uzemnaJednotka) { return uzemnaJednotka.startsWithStr(vstup); };
        }
        else if (vstup.compare("c") == 0) {
            std::cout << "Zadajte reťazec, ktorý obsahujú názvy územných jednotiek:";
            std::cin.ignore();
            std::getline(std::cin, vstup);
            predikat = [vstup](UzemnaJednotka uzemnaJednotka) { return uzemnaJednotka.containsStr(vstup); };
        }
        else if (vstup.compare("h") == 0) {
            std::cout << "Zadajte typ územnej jednotky(kraj/obec/okres):";
            std::cin.ignore();
            std::getline(std::cin, vstup);
            predikat = [vstup](UzemnaJednotka uzemnaJednotka) { return uzemnaJednotka.hasType(vstup); };
        }
        else if (vstup.compare("zs") == 0) {
            for (int i = 0; i < aktualnyVrchol->sons_->size(); i++) {
                std::cout << i << ". " << aktualnyVrchol->sons_->access(i)->data_->data_->getOficialnyNazov() << '\n';
            }
            int number;
            std::cout << "Zadaj cislo, ktoreho syna chces zvolit:";
            std::cin >> number;
            aktualnyVrchol = aktualnyVrchol->sons_->access(number)->data_;
            delete aktPozicia;
            aktPozicia = new ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator(hierarchia, aktualnyVrchol);

        }
        else if (vstup.compare("zo") == 0) {
            aktualnyVrchol = hierarchia->accessParent(*aktualnyVrchol);
            delete aktPozicia;
            aktPozicia = new ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator(hierarchia, aktualnyVrchol);
        }
        else if (vstup.compare("k") == 0) {
            // zmazeme si objekty uzemnych celkov celej hierarchie
            delete algoritmus;
            delete aktPozicia;
            std::cout << "Dovidenia\n";
            return 0;
        }
        else {
            std::cout << "Zadal si zly vstup.\n";
        }

        // ak sme si nezvolili ziadny predikat tak neurobime nic(nefiltrujeme a ani nesortujeme)
        if (!predikat) {
            continue;
        }

        // ak si pouzivatel zvolil predikat tak data vyfiltrujeme podla zadaneho predikatu a ulozime do premennej
        ds::amt::ImplicitSequence<UzemnaJednotka*> filtrovaneData(algoritmus->filtrujData(*aktPozicia, hierarchia->end(), predikat));
        
        // teraz ideme triedit vyfiltrované dáta
        while (true) {
            std::cout << "Zvoľ možnosť, ktorou chceš utriediť dáta(compareAlphabetical(ca)/compareVowelsCount(cvc)):";
            std::cin >> vstup;
            if (vstup.compare("ca") == 0) {
                komparator = [](UzemnaJednotka* uzemnaJednotka1, UzemnaJednotka* uzemnaJednotka2) { return uzemnaJednotka1->compareAlphabetical(*uzemnaJednotka2); };
                break;
            }
            else if (vstup.compare("cvc") == 0) {
                komparator = [](UzemnaJednotka* uzemnaJednotka1, UzemnaJednotka* uzemnaJednotka2) { return uzemnaJednotka1->compareVowelsCount(*uzemnaJednotka2); };
                vypisatPocetSamohlasok = true;
                break;
            }
            else {
                std::cout << "Zadal si zlý vstup.\n";
                continue;
            }
        }
        TriediaciAlgoritmus::triedData(filtrovaneData, komparator, 0, filtrovaneData.size() - 1);
        // ak budeme triedit podla pocu samohlasok, ku kazdej uzemnej jednotke vypiseme aj pocet samohlasok v oficialnom nazve
        if (vypisatPocetSamohlasok) {
            for (int i = 0; i < filtrovaneData.size(); i++) {
                std::cout << filtrovaneData.access(i)->data_->getOficialnyNazov() << " " << filtrovaneData.access(i)->data_->getVowelsCount() << '\n';
            }
        }
        else {
            for (int i = 0; i < filtrovaneData.size(); i++) {
                std::cout << filtrovaneData.access(i)->data_->getOficialnyNazov() << '\n';
            }
        }
        std::cout << '\n';
    }
}
#endif