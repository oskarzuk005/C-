#include "swiat.h"
#include "czlowiek.h"
#include "zwierzeta.h"
#include "rosliny.h"
#include <ctime>
#include <cstdlib>

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    swiat obecnySwiat(20, 20);

    obecnySwiat.dodajOrganizm(new czlowiek(10, 10, &obecnySwiat));

    obecnySwiat.dodajOrganizm(new wilk(5, 5, &obecnySwiat));
    obecnySwiat.dodajOrganizm(new wilk(6, 5, &obecnySwiat));
    obecnySwiat.dodajOrganizm(new owca(1, 1, &obecnySwiat));
    obecnySwiat.dodajOrganizm(new owca(2, 1, &obecnySwiat));
    obecnySwiat.dodajOrganizm(new lis(18, 18, &obecnySwiat));
    obecnySwiat.dodajOrganizm(new zolw(8, 8, &obecnySwiat));
    obecnySwiat.dodajOrganizm(new antylopa(12, 12, &obecnySwiat));

    obecnySwiat.dodajOrganizm(new trawa(15, 15, &obecnySwiat));
    obecnySwiat.dodajOrganizm(new mlecz(3, 15, &obecnySwiat));
    obecnySwiat.dodajOrganizm(new guarana(10, 2, &obecnySwiat));
    obecnySwiat.dodajOrganizm(new wilczeJagody(4, 4, &obecnySwiat));
    obecnySwiat.dodajOrganizm(new barszczSosnowskiego(2, 2, &obecnySwiat));

    obecnySwiat.rysujSwiat();
    while (!obecnySwiat.sprawdzKoniecGry())
    {
        obecnySwiat.wykonajTure();
        obecnySwiat.rysujSwiat();
    }

    return 0;
}