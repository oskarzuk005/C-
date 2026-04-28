#pragma once
#include <string>

class swiat;

class organizm
{
protected:
    int sila;
    int inicjatywa;
    int wiek;
    int polozenieX, polozenieY;
    swiat *wskaznikNaSwiat;
    char znakReprezentacji;
    bool czyJestMartwy;

public:
    organizm(int poczatkowaSila, int poczatkowaInicjatywa, int x, int y, swiat *swiatGry, char znak);
    virtual ~organizm() = default;

    virtual void akcja() = 0;
    virtual void kolizja(organizm *innyOrganizm) = 0;
    virtual std::string pobierzNazwe() const = 0;
    virtual organizm *klonuj(int noweX, int noweY) = 0;

    virtual bool czyOdbilAtak(organizm *napastnik);
    virtual bool czyUcieka();

    int pobierzX() const;
    int pobierzY() const;
    int pobierzSile() const;
    int pobierzInicjatywe() const;
    int pobierzWiek() const;
    char pobierzZnak() const;
    bool sprawdzCzyMartwy() const;

    void ustawSile(int nowaSila);
    void ustawWiek(int nowyWiek);
    virtual void zabij();
    void postarz();
    void zmienPolozenie(int noweX, int noweY);
};