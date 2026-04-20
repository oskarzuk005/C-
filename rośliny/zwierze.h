#pragma once
#include "organizm.h"
#include "swiat.h"
#include <cstdlib>

class zwierze : public organizm
{
public:
    zwierze(int sila, int inicjatywa, int x, int y, swiat *swiat_ptr, char znak)
        : organizm(sila, inicjatywa, x, y, swiat_ptr, znak) {}

    void akcja() override
    {
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;
        if (dx == 0 && dy == 0)
            return;

        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < swiat_ptr->getSzerokosc() && ny >= 0 && ny < swiat_ptr->getWysokosc())
        {
            organizm *cel = swiat_ptr->getOrganizmNaPolu(nx, ny);
            if (cel != nullptr)
            {
                if (cel->getNazwa() == this->getNazwa())
                {
                    swiat_ptr->dodajKomunikat(getNazwa() + " probuje sie rozmnazac.");
                }
                else
                {
                    cel->kolizja(this);
                }
            }
            else
            {
                zmienPolozenie(nx, ny);
            }
        }
    }

    void kolizja(organizm *napastnik) override
    {
        if (this->getSila() > napastnik->getSila())
        {
            swiat_ptr->dodajKomunikat(this->getNazwa() + " zabija " + napastnik->getNazwa());
            napastnik->zabij();
        }
        else
        {
            swiat_ptr->dodajKomunikat(napastnik->getNazwa() + " zabija " + this->getNazwa());
            this->zabij();
            napastnik->zmienPolozenie(this->getX(), this->getY());
        }
    }
};