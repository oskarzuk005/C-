#include "Kolo.h"
#include "FiguraPlaska.h"
#include <cmath>

#include <iostream>
using namespace std;

Kolo::Kolo(double r) : r(r)
{
    cout << "\nKonstruktor Kola(" << r << ")" << endl;
    ilosckol++;
    cout << "Ilosc kol: " << ilosckol << endl;
}
double Kolo::GetR() const
{
    return r;
}

void Kolo::SetR(double r)
{
    this->r = r;
}

double Kolo::Obwod()
{
    return 2 * M_PI * r;
}
double Kolo::Pole()
{
    return M_PI * pow(r, 2);
}
void Kolo::Wypisz(std::ostream &out) const
{
    out << "Figura to Kolo o promieniu: " << r << endl;
}
Kolo::~Kolo()
{
    cout << "\nDestruktor i Parametry: " << r << endl;
    ilosckol--;
}
int Kolo::ilosckol = 0;