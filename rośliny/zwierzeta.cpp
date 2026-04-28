#include "zwierzeta.h"
#include "swiat.h"
#include <cstdlib>

wilk::wilk(int x, int y, swiat *swiatGry) : zwierze(9, 5, x, y, swiatGry, 'W') {}
std::string wilk::pobierzNazwe() const { return "wilk"; }
organizm *wilk::klonuj(int noweX, int noweY) { return new wilk(noweX, noweY, wskaznikNaSwiat); }

owca::owca(int x, int y, swiat *swiatGry) : zwierze(4, 4, x, y, swiatGry, 'O') {}
std::string owca::pobierzNazwe() const { return "owca"; }
organizm *owca::klonuj(int noweX, int noweY) { return new owca(noweX, noweY, wskaznikNaSwiat); }

lis::lis(int x, int y, swiat *swiatGry) : zwierze(3, 7, x, y, swiatGry, 'L') {}
std::string lis::pobierzNazwe() const { return "lis"; }
organizm *lis::klonuj(int noweX, int noweY) { return new lis(noweX, noweY, wskaznikNaSwiat); }
void lis::akcja()
{
    int przesuniecieX = rand() % 3 - 1, przesuniecieY = rand() % 3 - 1;
    if (przesuniecieX == 0 && przesuniecieY == 0)
        return;
    int noweX = polozenieX + przesuniecieX, noweY = polozenieY + przesuniecieY;
    organizm *celRuchu = wskaznikNaSwiat->pobierzOrganizmNaPolu(noweX, noweY);
    if (celRuchu == nullptr || celRuchu->pobierzSile() <= this->pobierzSile())
        wykonajRuch(noweX, noweY);
}

zolw::zolw(int x, int y, swiat *swiatGry) : zwierze(2, 1, x, y, swiatGry, 'Z') {}
std::string zolw::pobierzNazwe() const { return "zolw"; }
organizm *zolw::klonuj(int noweX, int noweY) { return new zolw(noweX, noweY, wskaznikNaSwiat); }
void zolw::akcja()
{
    if (rand() % 100 >= 75)
        zwierze::akcja();
}
bool zolw::czyOdbilAtak(organizm *napastnik) { return napastnik->pobierzSile() < 5; }

antylopa::antylopa(int x, int y, swiat *swiatGry) : zwierze(4, 4, x, y, swiatGry, 'A') {}
std::string antylopa::pobierzNazwe() const { return "antylopa"; }
organizm *antylopa::klonuj(int noweX, int noweY) { return new antylopa(noweX, noweY, wskaznikNaSwiat); }
void antylopa::akcja()
{
    int przesuniecieX = (rand() % 5 - 2), przesuniecieY = (rand() % 5 - 2);
    if (przesuniecieX == 0 && przesuniecieY == 0)
        return;
    wykonajRuch(polozenieX + przesuniecieX, polozenieY + przesuniecieY);
}
bool antylopa::czyUcieka() { return (rand() % 100 < 50); }