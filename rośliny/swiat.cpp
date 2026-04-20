#include "swiat.h"
#include <iostream>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#else
#include <stdlib.h>
#endif

swiat::swiat(int szer, int wys) : szerokosc(szer), wysokosc(wys), tura(0), koniecGry(false) {}

swiat::~swiat()
{
    for (auto org : organizmy)
        delete org;
}

void swiat::dodajKomunikat(std::string kom) { komunikaty.push_back(kom); }

void swiat::dodajOrganizm(organizm *org) { organizmy.push_back(org); }

organizm *swiat::getOrganizmNaPolu(int x, int y)
{
    for (auto org : organizmy)
    {
        if (!org->czyMartwy() && org->getX() == x && org->getY() == y)
            return org;
    }
    return nullptr;
}

void swiat::usunMartwe()
{
    auto it = organizmy.begin();
    while (it != organizmy.end())
    {
        if ((*it)->czyMartwy())
        {
            delete *it;
            it = organizmy.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void swiat::wykonajTure()
{
    komunikaty.clear();
    tura++;

    std::sort(organizmy.begin(), organizmy.end(), [](organizm *a, organizm *b)
              {
        if (a->getInicjatywa() != b->getInicjatywa())
            return a->getInicjatywa() > b->getInicjatywa();
        return a->getWiek() > b->getWiek(); });

    for (size_t i = 0; i < organizmy.size(); i++)
    {
        if (!organizmy[i]->czyMartwy())
        {
            organizmy[i]->akcja();
            organizmy[i]->postarz();
        }
    }
    usunMartwe();
}

void swiat::rysujSwiat()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::cout << "Imie Nazwisko, Indeks: 123454\n";
    std::cout << "Tura: " << tura << "\n";
    std::cout << "Sterowanie: strzalki. Umiejetnosc (Calopalenie): r. Wyjscie: q.\n\n";

    for (int y = 0; y < wysokosc; y++)
    {
        for (int x = 0; x < szerokosc; x++)
        {
            organizm *org = getOrganizmNaPolu(x, y);
            if (org)
                std::cout << org->getZnak();
            else
                std::cout << '.';
        }
        std::cout << '\n';
    }

    std::cout << "\n--- ZDARZENIA ---\n";
    for (const auto &msg : komunikaty)
        std::cout << msg << '\n';
}