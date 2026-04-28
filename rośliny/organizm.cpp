#include "organizm.h"

organizm::organizm(int poczatkowaSila, int poczatkowaInicjatywa, int x, int y, swiat *swiatGry, char znak)
    : sila(poczatkowaSila), inicjatywa(poczatkowaInicjatywa), wiek(0), polozenieX(x), polozenieY(y),
      wskaznikNaSwiat(swiatGry), znakReprezentacji(znak), czyJestMartwy(false) {}

bool organizm::czyOdbilAtak(organizm *napastnik) { return false; }
bool organizm::czyUcieka() { return false; }

int organizm::pobierzX() const { return polozenieX; }
int organizm::pobierzY() const { return polozenieY; }
int organizm::pobierzSile() const { return sila; }
int organizm::pobierzInicjatywe() const { return inicjatywa; }
int organizm::pobierzWiek() const { return wiek; }
char organizm::pobierzZnak() const { return znakReprezentacji; }
bool organizm::sprawdzCzyMartwy() const { return czyJestMartwy; }

void organizm::ustawSile(int nowaSila) { sila = nowaSila; }
void organizm::ustawWiek(int nowyWiek) { wiek = nowyWiek; }
void organizm::zabij() { czyJestMartwy = true; }
void organizm::postarz() { wiek++; }
void organizm::zmienPolozenie(int noweX, int noweY)
{
    polozenieX = noweX;
    polozenieY = noweY;
}