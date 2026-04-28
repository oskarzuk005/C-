#pragma once
#include "zwierze.h"
#include "roslina.h"

// --- ZWIERZETA ---
class wilk : public zwierze
{
public:
    wilk(int x, int y, swiat *swiat_ptr) : zwierze(9, 5, x, y, swiat_ptr, 'W') {}
    std::string getNazwa() const override { return "wilk"; }
    organizm *klonuj(int nx, int ny) override { return new wilk(nx, ny, swiat_ptr); }
};

class owca : public zwierze
{
public:
    owca(int x, int y, swiat *swiat_ptr) : zwierze(4, 4, x, y, swiat_ptr, 'O') {}
    std::string getNazwa() const override { return "owca"; }
    organizm *klonuj(int nx, int ny) override { return new owca(nx, ny, swiat_ptr); }
};

class lis : public zwierze
{
public:
    lis(int x, int y, swiat *swiat_ptr) : zwierze(3, 7, x, y, swiat_ptr, 'L') {}
    std::string getNazwa() const override { return "lis"; }
    organizm *klonuj(int nx, int ny) override { return new lis(nx, ny, swiat_ptr); }
    void akcja() override
    {
        int dx = rand() % 3 - 1, dy = rand() % 3 - 1;
        if (dx == 0 && dy == 0)
            return;
        int nx = x + dx, ny = y + dy;
        organizm *cel = swiat_ptr->getOrganizmNaPolu(nx, ny);
        if (cel == nullptr || cel->getSila() <= this->getSila())
        {
            wykonajRuch(nx, ny);
        }
    }
};

class zolw : public zwierze
{
public:
    zolw(int x, int y, swiat *swiat_ptr) : zwierze(2, 1, x, y, swiat_ptr, 'Z') {}
    std::string getNazwa() const override { return "zolw"; }
    organizm *klonuj(int nx, int ny) override { return new zolw(nx, ny, swiat_ptr); }
    void akcja() override
    {
        if (rand() % 100 >= 75)
            zwierze::akcja();
    }
    bool czyOdbilAtak(organizm *napastnik) override
    {
        return napastnik->getSila() < 5;
    }
};

class antylopa : public zwierze
{
public:
    antylopa(int x, int y, swiat *swiat_ptr) : zwierze(4, 4, x, y, swiat_ptr, 'A') {}
    std::string getNazwa() const override { return "antylopa"; }
    organizm *klonuj(int nx, int ny) override { return new antylopa(nx, ny, swiat_ptr); }
    void akcja() override
    {
        int dx = (rand() % 5 - 2), dy = (rand() % 5 - 2);
        if (dx == 0 && dy == 0)
            return;
        wykonajRuch(x + dx, y + dy);
    }
    bool ucieczka() override { return (rand() % 100 < 50); }
};

// --- ROSLINY ---
class trawa : public roslina
{
public:
    trawa(int x, int y, swiat *swiat_ptr) : roslina(0, x, y, swiat_ptr, 'T') {}
    std::string getNazwa() const override { return "trawa"; }
    organizm *klonuj(int nx, int ny) override { return new trawa(nx, ny, swiat_ptr); }
};

class mlecz : public roslina
{
public:
    mlecz(int x, int y, swiat *swiat_ptr) : roslina(0, x, y, swiat_ptr, 'M') {}
    std::string getNazwa() const override { return "mlecz"; }
    organizm *klonuj(int nx, int ny) override { return new mlecz(nx, ny, swiat_ptr); }
    void akcja() override
    {
        for (int i = 0; i < 3; i++)
            roslina::akcja();
    }
};

class guarana : public roslina
{
public:
    guarana(int x, int y, swiat *swiat_ptr) : roslina(0, x, y, swiat_ptr, 'G') {}
    std::string getNazwa() const override { return "guarana"; }
    organizm *klonuj(int nx, int ny) override { return new guarana(nx, ny, swiat_ptr); }
    void kolizja(organizm *napastnik) override
    {
        napastnik->setSila(napastnik->getSila() + 3);
        roslina::kolizja(napastnik);
    }
};

class wilczeJagody : public roslina
{
public:
    wilczeJagody(int x, int y, swiat *swiat_ptr) : roslina(99, x, y, swiat_ptr, 'J') {}
    std::string getNazwa() const override { return "wilcze_jagody"; }
    organizm *klonuj(int nx, int ny) override { return new wilczeJagody(nx, ny, swiat_ptr); }
    void kolizja(organizm *napastnik) override
    {
        swiat_ptr->dodajKomunikat(napastnik->getNazwa() + " zjada wilcze jagody i ginie.");
        napastnik->zabij();
        this->zabij();
    }
};

class barszczSosnowskiego : public roslina
{
public:
    barszczSosnowskiego(int x, int y, swiat *swiat_ptr) : roslina(10, x, y, swiat_ptr, 'B') {}
    std::string getNazwa() const override { return "barszcz_Sosnowskiego"; }
    organizm *klonuj(int nx, int ny) override { return new barszczSosnowskiego(nx, ny, swiat_ptr); }

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
                if (org != nullptr && dynamic_cast<zwierze *>(org) && org->getNazwa() != "cyber-owca")
                {
                    swiat_ptr->dodajKomunikat("barszcz Sosnowskiego zabija " + org->getNazwa());
                    org->zabij();
                }
            }
        }
    }
    void kolizja(organizm *napastnik) override
    {
        if (napastnik->getNazwa() != "cyber-owca")
        {
            swiat_ptr->dodajKomunikat(napastnik->getNazwa() + " zjada barszcz i ginie.");
            napastnik->zabij();
        }
        this->zabij();
    }
};