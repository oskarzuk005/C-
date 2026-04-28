#include "rosliny.h"
#include "zwierze.h"
#include "swiat.h"

trawa::trawa(int x, int y, swiat *swiatGry) : roslina(0, x, y, swiatGry, 'T') {}
std::string trawa::pobierzNazwe() const { return "trawa"; }
organizm *trawa::klonuj(int noweX, int noweY) { return new trawa(noweX, noweY, wskaznikNaSwiat); }

mlecz::mlecz(int x, int y, swiat *swiatGry) : roslina(0, x, y, swiatGry, 'M') {}
std::string mlecz::pobierzNazwe() const { return "mlecz"; }
organizm *mlecz::klonuj(int noweX, int noweY) { return new mlecz(noweX, noweY, wskaznikNaSwiat); }
void mlecz::akcja()
{
    for (int i = 0; i < 3; i++)
        roslina::akcja();
}

guarana::guarana(int x, int y, swiat *swiatGry) : roslina(0, x, y, swiatGry, 'G') {}
std::string guarana::pobierzNazwe() const { return "guarana"; }
organizm *guarana::klonuj(int noweX, int noweY) { return new guarana(noweX, noweY, wskaznikNaSwiat); }
void guarana::kolizja(organizm *napastnik)
{
    napastnik->ustawSile(napastnik->pobierzSile() + 3);
    roslina::kolizja(napastnik);
}

wilczeJagody::wilczeJagody(int x, int y, swiat *swiatGry) : roslina(99, x, y, swiatGry, 'J') {}
std::string wilczeJagody::pobierzNazwe() const { return "wilcze_jagody"; }
organizm *wilczeJagody::klonuj(int noweX, int noweY) { return new wilczeJagody(noweX, noweY, wskaznikNaSwiat); }
void wilczeJagody::kolizja(organizm *napastnik)
{
    wskaznikNaSwiat->dodajKomunikat(napastnik->pobierzNazwe() + " zjada wilcze jagody i ginie.");
    napastnik->zabij();
    this->zabij();
}

barszczSosnowskiego::barszczSosnowskiego(int x, int y, swiat *swiatGry) : roslina(10, x, y, swiatGry, 'B') {}
std::string barszczSosnowskiego::pobierzNazwe() const { return "barszcz_Sosnowskiego"; }
organizm *barszczSosnowskiego::klonuj(int noweX, int noweY) { return new barszczSosnowskiego(noweX, noweY, wskaznikNaSwiat); }

void barszczSosnowskiego::akcja()
{
    roslina::akcja();
    for (int przesuniecieX = -1; przesuniecieX <= 1; przesuniecieX++)
    {
        for (int przesuniecieY = -1; przesuniecieY <= 1; przesuniecieY++)
        {
            if (przesuniecieX == 0 && przesuniecieY == 0)
                continue;
            organizm *celZniszczenia = wskaznikNaSwiat->pobierzOrganizmNaPolu(polozenieX + przesuniecieX, polozenieY + przesuniecieY);
            if (celZniszczenia != nullptr && dynamic_cast<zwierze *>(celZniszczenia) && celZniszczenia->pobierzNazwe() != "cyber-owca")
            {
                wskaznikNaSwiat->dodajKomunikat("barszcz Sosnowskiego zabija " + celZniszczenia->pobierzNazwe());
                celZniszczenia->zabij();
            }
        }
    }
}
void barszczSosnowskiego::kolizja(organizm *napastnik)
{
    if (napastnik->pobierzNazwe() != "cyber-owca")
    {
        wskaznikNaSwiat->dodajKomunikat(napastnik->pobierzNazwe() + " zjada barszcz i ginie.");
        napastnik->zabij();
    }
    this->zabij();
}