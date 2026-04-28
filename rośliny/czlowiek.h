#pragma once
#include "zwierze.h"

class czlowiek : public zwierze
{
private:
    int czasOczekiwaniaUmiejetnosci;
    int pozostalyCzasUmiejetnosci;

public:
    czlowiek(int x, int y, swiat *swiatGry);
    void zabij() override;
    std::string pobierzNazwe() const override;
    void akcja() override;
    organizm *klonuj(int noweX, int noweY) override;
};