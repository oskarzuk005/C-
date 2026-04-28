#include "zwierze.h"
#include "swiat.h"
#include <cstdlib>

zwierze::zwierze(int poczatkowaSila, int poczatkowaInicjatywa, int x, int y, swiat *swiatGry, char znak)
    : organizm(poczatkowaSila, poczatkowaInicjatywa, x, y, swiatGry, znak) {}

void zwierze::akcja()
{
    int przesuniecieX = rand() % 3 - 1;
    int przesuniecieY = rand() % 3 - 1;
    if (przesuniecieX == 0 && przesuniecieY == 0)
        return;
    wykonajRuch(polozenieX + przesuniecieX, polozenieY + przesuniecieY);
}

void zwierze::wykonajRuch(int noweX, int noweY)
{
    if (noweX >= 0 && noweX < wskaznikNaSwiat->pobierzSzerokosc() && noweY >= 0 && noweY < wskaznikNaSwiat->pobierzWysokosc())
    {
        organizm *celRuchu = wskaznikNaSwiat->pobierzOrganizmNaPolu(noweX, noweY);
        if (celRuchu != nullptr)
        {
            if (celRuchu->pobierzNazwe() == this->pobierzNazwe())
            {
                int wolnePoleX, wolnePoleY;
                if (wskaznikNaSwiat->znajdzWolnePole(this->polozenieX, this->polozenieY, wolnePoleX, wolnePoleY))
                {
                    wskaznikNaSwiat->dodajOrganizm(this->klonuj(wolnePoleX, wolnePoleY));
                    wskaznikNaSwiat->dodajKomunikat("Rozmnazanie: powstaje nowe " + pobierzNazwe());
                }
            }
            else
            {
                celRuchu->kolizja(this);
            }
        }
        else
        {
            zmienPolozenie(noweX, noweY);
        }
    }
}

void zwierze::kolizja(organizm *napastnik)
{
    if (this->czyOdbilAtak(napastnik))
    {
        wskaznikNaSwiat->dodajKomunikat(this->pobierzNazwe() + " odbija atak od " + napastnik->pobierzNazwe());
        return;
    }
    if (this->czyUcieka())
    {
        int bezpieczneX, bezpieczneY;
        if (wskaznikNaSwiat->znajdzWolnePole(this->polozenieX, this->polozenieY, bezpieczneX, bezpieczneY))
        {
            this->zmienPolozenie(bezpieczneX, bezpieczneY);
            wskaznikNaSwiat->dodajKomunikat(this->pobierzNazwe() + " ucieka przed walka.");
            napastnik->zmienPolozenie(polozenieX, polozenieY);
            return;
        }
    }

    if (this->pobierzSile() > napastnik->pobierzSile())
    {
        wskaznikNaSwiat->dodajKomunikat(this->pobierzNazwe() + " zabija " + napastnik->pobierzNazwe());
        napastnik->zabij();
    }
    else
    {
        wskaznikNaSwiat->dodajKomunikat(napastnik->pobierzNazwe() + " zabija " + this->pobierzNazwe());
        this->zabij();
        napastnik->zmienPolozenie(this->pobierzX(), this->pobierzY());
    }
}