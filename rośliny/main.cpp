#include "swiat.h"
#include "czlowiek.h"
#include "gatunki.h"
#include <ctime>

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    swiat s(20, 20);

    s.dodajOrganizm(new czlowiek(10, 10, &s));
    s.dodajOrganizm(new wilk(5, 5, &s));
    s.dodajOrganizm(new wilk(6, 5, &s));
    s.dodajOrganizm(new trawa(15, 15, &s));
    s.dodajOrganizm(new barszczSosnowskiego(2, 2, &s));

    s.rysujSwiat();
    while (!s.czyKoniec())
    {
        s.wykonajTure();
        s.rysujSwiat();
    }

    return 0;
}