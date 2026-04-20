#pragma once
#include "organizm.h"
#include "swiat.h"
#include <cstdlib>

class roslina : public organizm
{
public:
    roslina(int sila, int x, int y, swiat *swiat_ptr, char znak)
        : organizm(sila, 0, x, y, swiat_ptr, znak) {}

    void akcja() override
    {
        if (rand() % 100 < 5)
        {
            swiat_ptr->dodajKomunikat(getNazwa() + " probuje sie rozsiac.");
        }
    }

    void kolizja(organizm *napastnik) override
    {
        swiat_ptr->dodajKomunikat(napastnik->getNazwa() + " zjada " + this->getNazwa());
        this->zabij();
        napastnik->zmienPolozenie(this->getX(), this->getY());
    }
};