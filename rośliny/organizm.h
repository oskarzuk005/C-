#pragma once
#include <string>

class swiat;

class organizm
{
protected:
    int sila;
    int inicjatywa;
    int wiek;
    int x, y;
    swiat *swiat_ptr;
    char znak;
    bool martwy;

public:
    organizm(int sila, int inicjatywa, int x, int y, swiat *swiat_ptr, char znak)
        : sila(sila), inicjatywa(inicjatywa), wiek(0), x(x), y(y), swiat_ptr(swiat_ptr), znak(znak), martwy(false) {}

    virtual ~organizm() = default;

    virtual void akcja() = 0;
    virtual void kolizja(organizm *other) = 0;
    virtual std::string getNazwa() const = 0;

    int getX() const { return x; }
    int getY() const { return y; }
    int getSila() const { return sila; }
    int getInicjatywa() const { return inicjatywa; }
    int getWiek() const { return wiek; }
    char getZnak() const { return znak; }
    bool czyMartwy() const { return martwy; }

    void setSila(int s) { sila = s; }
    virtual void zabij() { martwy = true; }
    void postarz() { wiek++; }
    void zmienPolozenie(int nx, int ny)
    {
        x = nx;
        y = ny;
    }
};