#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void przesiejWDol(int dane[], int i, int n)
{
    int l = 2 * i;
    int r = 2 * i + 1;
    int max_idx = i;

    if (l <= n && dane[l] > dane[i])
    {
        max_idx = l;
    }

    if (r <= n && dane[r] > dane[max_idx])
    {
        max_idx = r;
    }

    if (max_idx != i)
    {
        swap(dane[i], dane[max_idx]);
        przesiejWDol(dane, max_idx, n);
    }
}

void przygotuj(int dane[], int n)
{
    for (int i = n / 2; i >= 1; i--)
    {
        przesiejWDol(dane, i, n);
    }
}

void sortowanie(int dane[], int n)
{
    przygotuj(dane, n);
    for (int i = n; i >= 2; i--)
    {
        swap(dane[1], dane[i]);
        przesiejWDol(dane, 1, i - 1);
    }
}

int main()
{
    string linia;
    while (getline(cin, linia))
    {
        if (linia.empty())
            continue;

        int tab[15];
        int ile = 0;
        stringstream ss(linia);
        int x;

        while (ss >> x)
        {
            ile++;
            tab[ile] = x;
        }

        if (ile > 0)
        {
            sortowanie(tab, ile);
            for (int i = 1; i <= ile; i++)
            {
                cout << tab[i] << (i == ile ? "" : " ");
            }
            cout << endl;
        }
    }
    return 0;
}