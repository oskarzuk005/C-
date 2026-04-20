#pragma once
#include "zwierze.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
inline int _getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

class czlowiek : public zwierze
{
private:
    int cooldownUmiejetnosci;
    int czasTrwaniaUmiejetnosci;

public:
    czlowiek(int x, int y, swiat *swiat_ptr) : zwierze(5, 4, x, y, swiat_ptr, 'C'), cooldownUmiejetnosci(0), czasTrwaniaUmiejetnosci(0) {}
    void zabij() override
    {
        organizm::zabij();
        swiat_ptr->dodajKomunikat("Zginales! Koniec gry.");
        swiat_ptr->setKoniecGry();
    }

    std::string getNazwa() const override { return "czlowiek"; }

    void akcja() override
    {
        if (czasTrwaniaUmiejetnosci > 0)
        {
            swiat_ptr->dodajKomunikat("Calopalenie aktywne!");
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0)
                        continue;
                    organizm *org = swiat_ptr->getOrganizmNaPolu(x + dx, y + dy);
                    if (org != nullptr)
                    {
                        swiat_ptr->dodajKomunikat("czlowiek spopiela " + org->getNazwa());
                        org->zabij();
                    }
                }
            }
            czasTrwaniaUmiejetnosci--;
            if (czasTrwaniaUmiejetnosci == 0)
                cooldownUmiejetnosci = 5;
        }
        else if (cooldownUmiejetnosci > 0)
        {
            cooldownUmiejetnosci--;
        }

        int dx = 0, dy = 0;
        bool ruchWykonany = false;
        while (!ruchWykonany)
        {
            int input = _getch();
            if (input == 224 || input == 27)
            {
                input = _getch();
                if (input == 91)
                    input = _getch();
                switch (input)
                {
                case 72:
                case 65:
                    dy = -1;
                    ruchWykonany = true;
                    break;
                case 80:
                case 66:
                    dy = 1;
                    ruchWykonany = true;
                    break;
                case 77:
                case 67:
                    dx = 1;
                    ruchWykonany = true;
                    break;
                case 75:
                case 68:
                    dx = -1;
                    ruchWykonany = true;
                    break;
                }
            }
            else if (input == 'r' || input == 'R')
            {
                if (cooldownUmiejetnosci == 0 && czasTrwaniaUmiejetnosci == 0)
                {
                    swiat_ptr->dodajKomunikat("Umiejetnosc Calopalenie aktywowana!");
                    czasTrwaniaUmiejetnosci = 5;
                }
                else
                {
                    swiat_ptr->dodajKomunikat("Umiejetnosc jeszcze niegotowa.");
                }
            }
            else if (input == 'q')
            {
                swiat_ptr->setKoniecGry();
                return;
            }
        }

        int nx = x + dx;
        int ny = y + dy;
        if (nx >= 0 && nx < swiat_ptr->getSzerokosc() && ny >= 0 && ny < swiat_ptr->getWysokosc())
        {
            organizm *cel = swiat_ptr->getOrganizmNaPolu(nx, ny);
            if (cel != nullptr)
                cel->kolizja(this);
            else
                zmienPolozenie(nx, ny);
        }
    }
};