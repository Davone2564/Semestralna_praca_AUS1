#  Návrh aplikácie

Moju aplikáciu som si rozdelil do viacerých úrovní. Algoritmy týkajúce
sa prvej, druhej a tretej úrovni sú poväčšine implementované v triede
Algoritmus. Nachádzajú sa tu metódy na načítavanie údajov z csv súborov
a rôzne algoritmy potrebné pre prvé tri úrovne SP. Načítavanie dát v
druhej a tretej úrovni SP sa realizuje v jednej spoločnej metóde. V
mojom projekte sa nachádza jedna main trieda s názvom
SemestralnaPraca.cpp. V tejto triede sú implementované štyri main
funkcie, medzi ktorými sa môžeme prepínať pomocou preprocesora.
Implementácia štvrtej úrovne SP, samotný triediaci algoritmus je
definovaný v samostatnej triede s názvom TriediaciAlgoritmus. Jednotlivé
územné jednotky sú definované pomocou spoločného predka s názvom
UzemnaJednotka, ktorej potomkovia sú triedy Kraj, Okres a Obec.
Potomkovia sa líšia od tohto predka tým že majú definovaný konkrétny typ
a majú inak implementované metódy toString.
