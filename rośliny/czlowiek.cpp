#include "czlowiek.h"
#include "swiat.h"
#include "narzedzia.h"

czlowiek::czlowiek(int x, int y, swiat *swiatGry)
    : zwierze(5, 4, x, y, swiatGry, 'C'), czasOczekiwaniaUmiejetnosci(0), pozostalyCzasUmiejetnosci(0) {}

void czlowiek::zabij()
{
    organizm::zabij();
    wskaznikNaSwiat->dodajKomunikat("Zginales! Koniec gry.");
    wskaznikNaSwiat->ustawKoniecGry();
}

std::string czlowiek::pobierzNazwe() const { return "czlowiek"; }
organizm *czlowiek::klonuj(int noweX, int noweY) { return nullptr; }

void czlowiek::akcja()
{
    if (pozostalyCzasUmiejetnosci > 0)
    {
        wskaznikNaSwiat->dodajKomunikat("Calopalenie aktywne!");
        for (int przesuniecieX = -1; przesuniecieX <= 1; przesuniecieX++)
        {
            for (int przesuniecieY = -1; przesuniecieY <= 1; przesuniecieY++)
            {
                if (przesuniecieX == 0 && przesuniecieY == 0)
                    continue;
                organizm *celUmiejetnosci = wskaznikNaSwiat->pobierzOrganizmNaPolu(polozenieX + przesuniecieX, polozenieY + przesuniecieY);
                if (celUmiejetnosci != nullptr)
                {
                    wskaznikNaSwiat->dodajKomunikat("Czlowiek spopiela " + celUmiejetnosci->pobierzNazwe());
                    celUmiejetnosci->zabij();
                }
            }
        }
        pozostalyCzasUmiejetnosci--;
        if (pozostalyCzasUmiejetnosci == 0)
            czasOczekiwaniaUmiejetnosci = 5;
    }
    else if (czasOczekiwaniaUmiejetnosci > 0)
    {
        czasOczekiwaniaUmiejetnosci--;
    }

    int kierunekX = 0, kierunekY = 0;
    bool czyRuchZostalWykonany = false;

#ifdef _WIN32
    int wejscieOczekiwane1 = 224, wejscieOczekiwane2 = -1;
#else
    int wejscieOczekiwane1 = 27, wejscieOczekiwane2 = 91;
#endif

    while (!czyRuchZostalWykonany)
    {
        int wcisnietyKlawisz = pobierzKlawisz();
        if (wcisnietyKlawisz == wejscieOczekiwane1)
        {
            wcisnietyKlawisz = pobierzKlawisz();
            if (wejscieOczekiwane2 != -1 && wcisnietyKlawisz == wejscieOczekiwane2)
                wcisnietyKlawisz = pobierzKlawisz();
            switch (wcisnietyKlawisz)
            {
            case 72:
            case 65:
                kierunekY = -1;
                czyRuchZostalWykonany = true;
                break;
            case 80:
            case 66:
                kierunekY = 1;
                czyRuchZostalWykonany = true;
                break;
            case 77:
            case 67:
                kierunekX = 1;
                czyRuchZostalWykonany = true;
                break;
            case 75:
            case 68:
                kierunekX = -1;
                czyRuchZostalWykonany = true;
                break;
            }
        }
        else if (wcisnietyKlawisz == 'r' || wcisnietyKlawisz == 'R')
        {
            if (czasOczekiwaniaUmiejetnosci == 0 && pozostalyCzasUmiejetnosci == 0)
            {
                wskaznikNaSwiat->dodajKomunikat("Umiejetnosc Calopalenie aktywowana!");
                pozostalyCzasUmiejetnosci = 5;
            }
            else
            {
                wskaznikNaSwiat->dodajKomunikat("Umiejetnosc jeszcze niegotowa.");
            }
        }
        else if (wcisnietyKlawisz == 's' || wcisnietyKlawisz == 'S')
        {
            wskaznikNaSwiat->zapiszStanGry("zapis.txt");
            czyRuchZostalWykonany = true;
        }
        else if (wcisnietyKlawisz == 'l' || wcisnietyKlawisz == 'L')
        {
            wskaznikNaSwiat->wczytajStanGry("zapis.txt");
            czyRuchZostalWykonany = true;
        }
        else if (wcisnietyKlawisz == 'q')
        {
            wskaznikNaSwiat->ustawKoniecGry();
            return;
        }
    }

    if (kierunekX != 0 || kierunekY != 0)
        wykonajRuch(polozenieX + kierunekX, polozenieY + kierunekY);
}