#pragma once
#include "zwierze.h"

class wilk : public zwierze
{
public:
    wilk(int x, int y, swiat *swiatGry);
    std::string pobierzNazwe() const override;
    organizm *klonuj(int noweX, int noweY) override;
};

class owca : public zwierze
{
public:
    owca(int x, int y, swiat *swiatGry);
    std::string pobierzNazwe() const override;
    organizm *klonuj(int noweX, int noweY) override;
};

class lis : public zwierze
{
public:
    lis(int x, int y, swiat *swiatGry);
    std::string pobierzNazwe() const override;
    organizm *klonuj(int noweX, int noweY) override;
    void akcja() override;
};

class zolw : public zwierze
{
public:
    zolw(int x, int y, swiat *swiatGry);
    std::string pobierzNazwe() const override;
    organizm *klonuj(int noweX, int noweY) override;
    void akcja() override;
    bool czyOdbilAtak(organizm *napastnik) override;
};

class antylopa : public zwierze
{
public:
    antylopa(int x, int y, swiat *swiatGry);
    std::string pobierzNazwe() const override;
    organizm *klonuj(int noweX, int noweY) override;
    void akcja() override;
    bool czyUcieka() override;
};