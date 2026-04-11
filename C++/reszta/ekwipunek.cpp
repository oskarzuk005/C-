#include <iostream>
#include <string>
using namespace std;
int main()
{
    string tablica[5] = {"pusta", "pusta", "pusta", "pusta", "pusta"};
    for (int i = 0; i < 5; i++)
    {
        cout << tablica[i] << endl;
    }
    char wybor;
    int slot;
    string item;

    while (true)
    {
        cout << "dodać coś? t/n" << endl;
        cin >> wybor;
        switch (wybor)
        {
        case 't':
            cout << "Ktory slot" << endl;
            cin >> slot;
            cout << "Jaki item" << endl;
            cin >> item;

            switch (slot)
            {
            case 1:
                tablica[0] = item;
                break;
            case 2:
                tablica[1] = item;
                break;
            case 3:
                tablica[2] = item;
                break;
            case 4:
                tablica[3] = item;
                break;
            case 5:
                tablica[4] = item;
                break;
            }
            break;
        case 'n':

            break;
        }
        cout << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << tablica[i] << endl;
        }
    }
}