#include <iostream>
#include <unistd.h>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

void slow(string tekst, int ms)
{
    for (char c : tekst)
    {
        cout << c << flush;
        usleep(ms * 1000);
    }
}

struct entity
{
    string name;
    int hp;
    int atack;
    int defence;
    int gold;
    int level;
};

struct ceny
{
    int atak;
    int hp;
    int defence;
};

struct potwor
{
    string name;
    int hp;
    int atack;
};

int main()
{
    srand(time(0));
    int round = 1;
    string imie;

    slow("\nWitaj, nazwij postać: \n", 20);
    cin >> imie;

    entity gracz = {imie, 30, 7, 5, 0, 1};
    ceny koszt = {10, 10, 10};

    slow("\nWitaj w grze ", 20);
    slow(gracz.name, 20);
    cout << "\nHP: " << gracz.hp << " | ATK: " << gracz.atack << endl;

    while (gracz.hp > 0)
    {
        usleep(500000);
        cout << "\n--- RUNDA " << round << " ---" << endl;
        int event = rand() % 3 + 1;
        usleep(500000);

        switch (event)
        {
        case 1:
        {
            int zloto = 10 + rand() % 20 + round;
            slow("\nZnajdujesz skrzynke! Zyskujesz: " + to_string(zloto) + " zlota.\n", 20);
            gracz.gold += zloto;
            break;
        }
        case 2:
        {
            slow("\nWALKA!!\n", 20);
            potwor p;
            int szansa = rand() % 3 + 1;

            if (szansa == 1)
                p = {"Dziobak", 15, 2};
            else if (szansa == 2)
                p = {"Niedzwiedz", 25, 4};
            else
                p = {"Barbarzynca", 40, 8};

            slow("Atakuje " + p.name + "!\n", 20);

            while (gracz.hp > 0 && p.hp > 0)
            {
                cout << "\nTwoje HP: " << gracz.hp << " | " << p.name << " HP: " << p.hp << endl;
                cout << "Atak (a) / Ucieczka (u): ";
                char decyzja;
                cin >> decyzja;

                if (decyzja == 'a')
                {
                    p.hp -= gracz.atack;
                    if (p.hp > 0)
                    {
                        int redukcja = (p.atack * gracz.defence) / 100;
                        int obrazenia = p.atack - redukcja;
                        gracz.hp -= obrazenia;
                    }
                }
                else if (decyzja == 'u')
                {
                    slow("Uciekasz!\n", 20);
                    break;
                }
            }

            if (p.hp <= 0)
            {
                slow("Zabiles przeciwnika!\n", 20);
                int nagrodaExp = 0;
                switch (szansa)
                {
                case 1:
                    nagrodaExp = 20 + round;
                    break;
                case 2:
                    nagrodaExp = 50 + round;
                    break;
                case 3:
                    nagrodaExp = 100 + round;
                    break;
                }
                slow("Zdobywasz " + to_string(nagrodaExp) + " doswiadczenia!\n", 20);
            }
            break;
        }
        case 3:
        {
            slow("\nSpotykasz karczme\nChcialbyś coś ulepszyć? t/n", 20);
            char decycja;
            cin >> decycja;
            if (decycja == 't')
            {
                while (true)
                {
                    slow("Co chcialbys ulepszyc? (z)broje , (h)p , (m)iecz, (n)ie", 20);
                    char ulepszenie;
                    cin >> ulepszenie;
                    if (ulepszenie == 'z' && gracz.gold >= koszt.defence)
                    {
                        slow("Ulepszono zbroje", 20);
                        gracz.defence += 1;
                        gracz.gold -= koszt.defence;
                        koszt.defence += 10;
                    }
                    else if (ulepszenie == 'h' && gracz.gold >= koszt.hp)
                    {
                        slow("Ulepszono hp", 20);
                        gracz.hp += 10;
                        gracz.gold -= koszt.hp;
                        koszt.hp += 10;
                    }
                    else if (ulepszenie == 'm' && gracz.gold >= koszt.atak)
                    {
                        slow("Ulepszono atak", 20);
                        gracz.atack += 5;
                        gracz.gold -= koszt.atak;
                        koszt.atak += 10;
                    }
                    else if (ulepszenie == 'n')
                    {
                        break;
                    }
                    else
                    {
                        slow("Albo cie nie stać albo gadasz glupoty", 20);
                    }
                }
            }
            else
            {
                slow("NO OK", 20);
            }

            break;
        }
        }

        round++;
        if (gracz.hp <= 0)
        {
            slow("\nZGINALES. Koniec gry.\n", 50);
        }
        usleep(500000);
    }
    return 0;
}