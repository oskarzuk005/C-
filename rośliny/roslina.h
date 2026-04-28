#pragma once
#include "organizm.h"

class roslina : public organizm
{
public:
    roslina(int poczatkowaSila, int x, int y, swiat *swiatGry, char znak);
    void akcja() override;
    void kolizja(organizm *napastnik) override;
};