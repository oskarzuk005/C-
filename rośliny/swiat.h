#pragma once
#include <vector>
#include <string>
#include "organizm.h"

class swiat
{
private:
    int szerokosc, wysokosc;
    std::vector<organizm *> organizmy;
    std::vector<std::string> komunikaty;
    int tura;
    bool koniecGry;

public:
    swiat(int szer, int wys);
    ~swiat();

    int getSzerokosc() const { return szerokosc; }
    int getWysokosc() const { return wysokosc; }
    bool czyKoniec() const { return koniecGry; }
    void setKoniecGry() { koniecGry = true; }

    void dodajKomunikat(std::string kom);
    void dodajOrganizm(organizm *org);
    organizm *getOrganizmNaPolu(int x, int y);
    void usunMartwe();
    void wykonajTure();
    void rysujSwiat();
};