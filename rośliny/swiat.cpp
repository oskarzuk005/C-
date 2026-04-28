#include "swiat.h"
#include "organizm.h"
#include "czlowiek.h"
#include "zwierzeta.h"
#include "rosliny.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>

swiat::swiat(int szerokosc, int wysokosc) : szerokoscPlanszy(szerokosc), wysokoscPlanszy(wysokosc), numerTury(0), czyKoniecGry(false) {}

swiat::~swiat()
{
    for (auto obecnyOrganizm : listaOrganizmow)
        delete obecnyOrganizm;
}

int swiat::pobierzSzerokosc() const { return szerokoscPlanszy; }
int swiat::pobierzWysokosc() const { return wysokoscPlanszy; }
bool swiat::sprawdzKoniecGry() const { return czyKoniecGry; }
void swiat::ustawKoniecGry() { czyKoniecGry = true; }
void swiat::dodajKomunikat(std::string wiadomosc) { listaKomunikatow.push_back(wiadomosc); }
void swiat::dodajOrganizm(organizm *nowyOrganizm) { listaOrganizmow.push_back(nowyOrganizm); }

organizm *swiat::pobierzOrganizmNaPolu(int x, int y)
{
    for (auto obecnyOrganizm : listaOrganizmow)
    {
        if (!obecnyOrganizm->sprawdzCzyMartwy() && obecnyOrganizm->pobierzX() == x && obecnyOrganizm->pobierzY() == y)
            return obecnyOrganizm;
    }
    return nullptr;
}

bool swiat::znajdzWolnePole(int x, int y, int &znalezioneX, int &znalezioneY)
{
    std::vector<std::pair<int, int>> wolnePola;
    for (int przesuniecieX = -1; przesuniecieX <= 1; przesuniecieX++)
    {
        for (int przesuniecieY = -1; przesuniecieY <= 1; przesuniecieY++)
        {
            if (przesuniecieX == 0 && przesuniecieY == 0)
                continue;
            int testoweX = x + przesuniecieX, testoweY = y + przesuniecieY;
            if (testoweX >= 0 && testoweX < szerokoscPlanszy && testoweY >= 0 && testoweY < wysokoscPlanszy && pobierzOrganizmNaPolu(testoweX, testoweY) == nullptr)
            {
                wolnePola.push_back({testoweX, testoweY});
            }
        }
    }
    if (wolnePola.empty())
        return false;
    int wylosowanyIndeks = rand() % wolnePola.size();
    znalezioneX = wolnePola[wylosowanyIndeks].first;
    znalezioneY = wolnePola[wylosowanyIndeks].second;
    return true;
}

void swiat::usunMartweOrganizmy()
{
    auto iteratorOrganizmow = listaOrganizmow.begin();
    while (iteratorOrganizmow != listaOrganizmow.end())
    {
        if ((*iteratorOrganizmow)->sprawdzCzyMartwy())
        {
            delete *iteratorOrganizmow;
            iteratorOrganizmow = listaOrganizmow.erase(iteratorOrganizmow);
        }
        else
        {
            ++iteratorOrganizmow;
        }
    }
}

void swiat::wykonajTure()
{
    listaKomunikatow.clear();
    numerTury++;
    std::sort(listaOrganizmow.begin(), listaOrganizmow.end(), [](organizm *pierwszy, organizm *drugi)
              {
        if (pierwszy->pobierzInicjatywe() != drugi->pobierzInicjatywe())
            return pierwszy->pobierzInicjatywe() > drugi->pobierzInicjatywe();
        return pierwszy->pobierzWiek() > drugi->pobierzWiek(); });

    size_t poczatkowaLiczbaOrganizmow = listaOrganizmow.size();
    for (size_t indeks = 0; indeks < poczatkowaLiczbaOrganizmow; indeks++)
    {
        if (!listaOrganizmow[indeks]->sprawdzCzyMartwy())
        {
            listaOrganizmow[indeks]->akcja();
            listaOrganizmow[indeks]->postarz();
        }
    }
    usunMartweOrganizmy();
}

void swiat::rysujSwiat()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::cout << "Projekt PO - Imie Nazwisko\n";
    std::cout << "Tura: " << numerTury << "\n";
    std::cout << "Sterowanie: strzalki. Umiejetnosc: r. Zapis: s. Odczyt: l. Wyjscie: q.\n\n";

    for (int y = 0; y < wysokoscPlanszy; y++)
    {
        for (int x = 0; x < szerokoscPlanszy; x++)
        {
            organizm *znalezionyOrganizm = pobierzOrganizmNaPolu(x, y);
            if (znalezionyOrganizm)
                std::cout << znalezionyOrganizm->pobierzZnak();
            else
                std::cout << '.';
        }
        std::cout << '\n';
    }

    std::cout << "\n--- ZDARZENIA ---\n";
    for (const auto &wiadomosc : listaKomunikatow)
        std::cout << wiadomosc << '\n';
}

void swiat::zapiszStanGry(const std::string &nazwaPliku)
{
    std::ofstream strumienPliku(nazwaPliku);
    if (!strumienPliku.is_open())
        return;
    strumienPliku << szerokoscPlanszy << " " << wysokoscPlanszy << " " << numerTury << "\n";
    for (auto obecnyOrganizm : listaOrganizmow)
    {
        if (!obecnyOrganizm->sprawdzCzyMartwy())
        {
            strumienPliku << obecnyOrganizm->pobierzNazwe() << " " << obecnyOrganizm->pobierzX() << " "
                          << obecnyOrganizm->pobierzY() << " " << obecnyOrganizm->pobierzSile() << " "
                          << obecnyOrganizm->pobierzWiek() << "\n";
        }
    }
    dodajKomunikat("Stan gry zostal zapisany.");
}

void swiat::wczytajStanGry(const std::string &nazwaPliku)
{
    std::ifstream strumienPliku(nazwaPliku);
    if (!strumienPliku.is_open())
        return;
    for (auto obecnyOrganizm : listaOrganizmow)
        delete obecnyOrganizm;
    listaOrganizmow.clear();
    listaKomunikatow.clear();

    strumienPliku >> szerokoscPlanszy >> wysokoscPlanszy >> numerTury;
    std::string nazwaOrganizmu;
    int pozycjaX, pozycjaY, wczytanaSila, wczytanyWiek;
    while (strumienPliku >> nazwaOrganizmu >> pozycjaX >> pozycjaY >> wczytanaSila >> wczytanyWiek)
    {
        organizm *nowyOrganizm = nullptr;
        if (nazwaOrganizmu == "czlowiek")
            nowyOrganizm = new czlowiek(pozycjaX, pozycjaY, this);
        else if (nazwaOrganizmu == "wilk")
            nowyOrganizm = new wilk(pozycjaX, pozycjaY, this);
        else if (nazwaOrganizmu == "owca")
            nowyOrganizm = new owca(pozycjaX, pozycjaY, this);
        else if (nazwaOrganizmu == "lis")
            nowyOrganizm = new lis(pozycjaX, pozycjaY, this);
        else if (nazwaOrganizmu == "zolw")
            nowyOrganizm = new zolw(pozycjaX, pozycjaY, this);
        else if (nazwaOrganizmu == "antylopa")
            nowyOrganizm = new antylopa(pozycjaX, pozycjaY, this);
        else if (nazwaOrganizmu == "trawa")
            nowyOrganizm = new trawa(pozycjaX, pozycjaY, this);
        else if (nazwaOrganizmu == "mlecz")
            nowyOrganizm = new mlecz(pozycjaX, pozycjaY, this);
        else if (nazwaOrganizmu == "guarana")
            nowyOrganizm = new guarana(pozycjaX, pozycjaY, this);
        else if (nazwaOrganizmu == "wilcze_jagody")
            nowyOrganizm = new wilczeJagody(pozycjaX, pozycjaY, this);
        else if (nazwaOrganizmu == "barszcz_Sosnowskiego")
            nowyOrganizm = new barszczSosnowskiego(pozycjaX, pozycjaY, this);

        if (nowyOrganizm)
        {
            nowyOrganizm->ustawSile(wczytanaSila);
            nowyOrganizm->ustawWiek(wczytanyWiek);
            dodajOrganizm(nowyOrganizm);
        }
    }
    dodajKomunikat("Stan gry zostal wczytany.");
}