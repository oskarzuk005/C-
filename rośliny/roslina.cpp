#include "roslina.h"
#include "swiat.h"
#include <cstdlib>

roslina::roslina(int poczatkowaSila, int x, int y, swiat *swiatGry, char znak)
    : organizm(poczatkowaSila, 0, x, y, swiatGry, znak) {}

void roslina::akcja()
{
    if (rand() % 100 < 5)
    {
        int nowePoleX, nowePoleY;
        if (wskaznikNaSwiat->znajdzWolnePole(this->polozenieX, this->polozenieY, nowePoleX, nowePoleY))
        {
            wskaznikNaSwiat->dodajOrganizm(this->klonuj(nowePoleX, nowePoleY));
            wskaznikNaSwiat->dodajKomunikat(pobierzNazwe() + " rozsiewa sie.");
        }
    }
}

void roslina::kolizja(organizm *napastnik)
{
    wskaznikNaSwiat->dodajKomunikat(napastnik->pobierzNazwe() + " zjada " + this->pobierzNazwe());
    this->zabij();
    napastnik->zmienPolozenie(this->pobierzX(), this->pobierzY());
}