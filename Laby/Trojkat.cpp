#include "Trojkat.h"
#include "FiguraPlaska.h"
#include <cmath>

#include <iostream>
using namespace std;

int Trojkat::ilosctrojkatow = 0;
Trojkat::Trojkat(double a, double b, double c) : a(a), b(b), c(c)
{
    cout << "\nKonstruktor Trojkata(" << a << "," << b << "," << c << ")" << endl;
    ilosctrojkatow++;
    cout << "Ilosc trojkatow: " << ilosctrojkatow << endl;
}
double Trojkat::GetA() const
{
    return a;
}
double Trojkat::GetB() const
{
    return b;
}
double Trojkat::GetC() const
{
    return c;
}
void Trojkat::SetA(double a)
{
    this->a = a;
}
void Trojkat::SetB(double b)
{
    this->b = b;
}
void Trojkat::SetC(double c)
{
    this->c = c;
}
double Trojkat::Obwod()
{
    return a + b + c;
}
double Trojkat::Pole()
{
    double p = (a + b + c) / 2.0;
    double pole = sqrt(p * (p - a) * (p - b) * (p - c));
    return pole;
}
void Trojkat::Wypisz(std::ostream &out) const
{
    out << "Figura to trojkat o bokach: " << a << " i " << b << " i " << c << endl;
}
Trojkat::~Trojkat()
{
    cout << "\nDestruktor i Parametry: " << a << b << c;
    ilosctrojkatow--;
}