#include <iostream>
#include "FabrykaObiektow.h"
#include "FiguraPlaska.h"

using namespace std;

int main()
{
    FabrykaObiektow::stworz('p', 2, 3);
    FabrykaObiektow::stworz('p', 2, 3);
    FiguraPlaska *tablica[3];

    tablica[0] = FabrykaObiektow::stworz('p', 2, 3);
    tablica[1] = FabrykaObiektow::stworz('k', 4);
    tablica[2] = FabrykaObiektow::stworz('t', 3, 4, 5);

    for (int i = 0; i < 3; i++)
    {
        if (tablica[i] != nullptr)
        {
            cout << i << ": " << *tablica[i] << endl;
            cout << "Pole: " << tablica[i]->Pole() << endl;
            cout << "Obwod: " << tablica[i]->Obwod() << endl;
            cout << "-----------------" << endl;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        delete tablica[i];
    }

    return 0;
}