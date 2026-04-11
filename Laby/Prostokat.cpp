#include "Prostokat.h"
#include "FiguraPlaska.h"

#include <iostream>
using namespace std;
int Prostokat::iloscprostokatow = 0;
Prostokat::Prostokat(double a, double b) : a(a), b(b)
{
    cout << "\nKonstruktor Prostokąta(" << a << "," << b << ")" << endl;
    iloscprostokatow++;
    cout << "Ilosc prostokatow " << iloscprostokatow << endl;
}
double Prostokat::GetA() const
{
    return a;
}
double Prostokat::GetB() const
{
    return b;
}
void Prostokat::SetA(double a)
{
    this->a = a;
}
void Prostokat::SetB(double b)
{
    this->b = b;
}
double Prostokat::Obwod()
{
    return (a + b) * 2;
}
double Prostokat::Pole()
{
    return a * b;
}
void Prostokat::Wypisz(std::ostream &out) const
{
    if (a == b)
    {
        out << "\nFigura to kwadrat o bokach: " << a << " i " << b << endl;
    }
    else
    {
        out << "Figura to prostokat o bokach: " << a << " i " << b << endl;
    }
}
Prostokat::~Prostokat()
{
    cout << "\nDestruktor i Parametry: " << a << b << endl;
    iloscprostokatow--;
}