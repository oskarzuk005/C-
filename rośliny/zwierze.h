#pragma once
#include "organizm.h"

class zwierze : public organizm
{
public:
    zwierze(int poczatkowaSila, int poczatkowaInicjatywa, int x, int y, swiat *swiatGry, char znak);
    void akcja() override;
    void kolizja(organizm *napastnik) override;
    virtual void wykonajRuch(int noweX, int noweY);
};