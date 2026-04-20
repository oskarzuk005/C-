#pragma once
#include "zwierze.h"
#include "roslina.h"

class wilk : public zwierze
{
public:
    wilk(int x, int y, swiat *swiat_ptr) : zwierze(9, 5, x, y, swiat_ptr, 'W') {}
    std::string getNazwa() const override { return "wilk"; }
};

class trawa : public roslina
{
public:
    trawa(int x, int y, swiat *swiat_ptr) : roslina(0, x, y, swiat_ptr, 'T') {}
    std::string getNazwa() const override { return "trawa"; }
};

class barszczSosnowskiego : public roslina
{
public:
    barszczSosnowskiego(int x, int y, swiat *swiat_ptr) : roslina(10, x, y, swiat_ptr, 'B') {}
    std::string getNazwa() const override { return "barszcz Sosnowskiego"; }

    void akcja() override
    {
        roslina::akcja();
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (dx == 0 && dy == 0)
                    continue;
                organizm *org = swiat_ptr->getOrganizmNaPolu(x + dx, y + dy);
                if (org != nullptr && dynamic_cast<zwierze *>(org))
                {
                    swiat_ptr->dodajKomunikat(getNazwa() + " zabija " + org->getNazwa());
                    org->zabij();
                }
            }
        }
    }

    void kolizja(organizm *napastnik) override
    {
        swiat_ptr->dodajKomunikat(napastnik->getNazwa() + " zjada " + getNazwa() + " i ginie.");
        napastnik->zabij();
        this->zabij();
    }
};