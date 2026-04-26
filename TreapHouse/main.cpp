#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Produkt
{
    int id;
    int cena;
    int priorytet;
    int rozmiar_poddrzewa;
    long long suma_cen;
    Produkt *lewe, *prawe;

    Produkt(int _id, int _cena) : id(_id), cena(_cena), priorytet(rand()), rozmiar_poddrzewa(1),
                                  suma_cen(_cena), lewe(nullptr), prawe(nullptr) {}
};

int daj_rozmiar(Produkt *p) { return p ? p->rozmiar_poddrzewa : 0; }
long long daj_sume(Produkt *p) { return p ? p->suma_cen : 0; }

void aktualizuj_statystyki(Produkt *p)
{
    if (p)
    {
        p->rozmiar_poddrzewa = 1 + daj_rozmiar(p->lewe) + daj_rozmiar(p->prawe);
        p->suma_cen = p->cena + daj_sume(p->lewe) + daj_sume(p->prawe);
    }
}

void rozdziel(Produkt *korzen, int granica_id, Produkt *&mniejsze, Produkt *&wieksze)
{
    if (!korzen)
    {
        mniejsze = wieksze = nullptr;
        return;
    }
    if (korzen->id <= granica_id)
    {
        rozdziel(korzen->prawe, granica_id, korzen->prawe, wieksze);
        mniejsze = korzen;
    }
    else
    {
        rozdziel(korzen->lewe, granica_id, mniejsze, korzen->lewe);
        wieksze = korzen;
    }
    aktualizuj_statystyki(korzen);
}

Produkt *polacz(Produkt *lewe, Produkt *prawe)
{
    if (!lewe || !prawe)
        return lewe ? lewe : prawe;
    if (lewe->priorytet > prawe->priorytet)
    {
        lewe->prawe = polacz(lewe->prawe, prawe);
        aktualizuj_statystyki(lewe);
        return lewe;
    }
    else
    {
        prawe->lewe = polacz(lewe, prawe->lewe);
        aktualizuj_statystyki(prawe);
        return prawe;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0));

    int liczba_operacji;
    cin >> liczba_operacji;
    Produkt *drzewo = nullptr;

    while (liczba_operacji--)
    {
        char komenda;
        cin >> komenda;

        if (komenda == 'A')
        {
            int id, cena;
            cin >> id >> cena;
            Produkt *czescl, *srodek, *czescp;
            rozdziel(drzewo, id - 1, czescl, czescp);
            rozdziel(czescp, id, srodek, czescp);

            if (srodek)
                srodek->cena = cena;
            else
                srodek = new Produkt(id, cena);

            aktualizuj_statystyki(srodek);
            drzewo = polacz(czescl, polacz(srodek, czescp));
        }
        else if (komenda == 'D')
        {
            int id;
            cin >> id;
            Produkt *czescl, *srodek, *czescp;
            rozdziel(drzewo, id - 1, czescl, czescp);
            rozdziel(czescp, id, srodek, czescp);
            delete srodek;
            drzewo = polacz(czescl, czescp);
        }
        else if (komenda == 'S')
        {
            int id_od, id_do;
            cin >> id_od >> id_do;
            if (id_od > id_do)
            {
                cout << "0\n";
                continue;
            }
            Produkt *czescl, *srodek, *czescp;
            rozdziel(drzewo, id_od - 1, czescl, czescp);
            rozdziel(czescp, id_do, srodek, czescp);
            cout << daj_sume(srodek) << "\n";
            drzewo = polacz(czescl, polacz(srodek, czescp));
        }
        else if (komenda == 'C')
        {
            cout << daj_rozmiar(drzewo) << "\n";
        }
    }
    return 0;
}