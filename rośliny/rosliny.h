#pragma once
#include "roslina.h"

class trawa : public roslina
{
public:
    trawa(int x, int y, swiat *swiatGry);
    std::string pobierzNazwe() const override;
    organizm *klonuj(int noweX, int noweY) override;
};

class mlecz : public roslina
{
public:
    mlecz(int x, int y, swiat *swiatGry);
    std::string pobierzNazwe() const override;
    organizm *klonuj(int noweX, int noweY) override;
    void akcja() override;
};

class guarana : public roslina
{
public:
    guarana(int x, int y, swiat *swiatGry);
    std::string pobierzNazwe() const override;
    organizm *klonuj(int noweX, int noweY) override;
    void kolizja(organizm *napastnik) override;
};

class wilczeJagody : public roslina
{
public:
    wilczeJagody(int x, int y, swiat *swiatGry);
    std::string pobierzNazwe() const override;
    organizm *klonuj(int noweX, int noweY) override;
    void kolizja(organizm *napastnik) override;
};

class barszczSosnowskiego : public roslina
{
public:
    barszczSosnowskiego(int x, int y, swiat *swiatGry);
    std::string pobierzNazwe() const override;
    organizm *klonuj(int noweX, int noweY) override;
    void akcja() override;
    void kolizja(organizm *napastnik) override;
};