#pragma once
#include <vector>
#include <string>

class organizm;

class swiat
{
private:
    int szerokoscPlanszy, wysokoscPlanszy;
    std::vector<organizm *> listaOrganizmow;
    std::vector<std::string> listaKomunikatow;
    int numerTury;
    bool czyKoniecGry;

public:
    swiat(int szerokosc, int wysokosc);
    ~swiat();

    int pobierzSzerokosc() const;
    int pobierzWysokosc() const;
    bool sprawdzKoniecGry() const;
    void ustawKoniecGry();

    void dodajKomunikat(std::string wiadomosc);
    void dodajOrganizm(organizm *nowyOrganizm);
    organizm *pobierzOrganizmNaPolu(int x, int y);
    bool znajdzWolnePole(int x, int y, int &znalezioneX, int &znalezioneY);
    void usunMartweOrganizmy();
    void wykonajTure();
    void rysujSwiat();

    void zapiszStanGry(const std::string &nazwaPliku);
    void wczytajStanGry(const std::string &nazwaPliku);
};