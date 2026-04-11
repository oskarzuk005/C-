#include "FabrykaObiektow.h"
#include "Prostokat.h"
#include "Kolo.h"
#include "Trojkat.h"

FiguraPlaska *FabrykaObiektow::stworz(char typ, double a, double b, double c)
{
    switch (typ)
    {
    case 'p':
        return new Prostokat(a, b);
    case 'k':
        return new Kolo(a);
    case 't':
        return new Trojkat(a, b, c);
    default:
        return nullptr;
    }
}