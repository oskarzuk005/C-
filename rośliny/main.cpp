#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <conio.h>
#else
// Prosta alternatywa dla getch() pod Linuksem
#include <termios.h>
#include <unistd.h>
int _getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

using namespace std;

class Organizm;

class Swiat
{
private:
    int szerokosc, wysokosc;
    vector<Organizm *> organizmy;
    vector<string> komunikaty;
    int tura;
    bool koniecGry;

public:
    Swiat(int szer, int wys) : szerokosc(szer), wysokosc(wys), tura(0), koniecGry(false) {}
    ~Swiat();

    int getSzerokosc() const { return szerokosc; }
    int getWysokosc() const { return wysokosc; }
    void dodajKomunikat(string kom) { komunikaty.push_back(kom); }
    void dodajOrganizm(Organizm *org);
    Organizm *getOrganizmNaPolu(int x, int y);
    void usunMartwe();
    void wykonajTure();
    void rysujSwiat();
    bool czyKoniec() const { return koniecGry; }
    void setKoniecGry() { koniecGry = true; }
};

class Organizm
{
protected:
    int sila;
    int inicjatywa;
    int wiek;
    int x, y;
    Swiat *swiat;
    char znak;
    bool martwy;

public:
    Organizm(int sila, int inicjatywa, int x, int y, Swiat *swiat, char znak)
        : sila(sila), inicjatywa(inicjatywa), wiek(0), x(x), y(y), swiat(swiat), znak(znak), martwy(false) {}

    virtual ~Organizm() = default;

    virtual void akcja() = 0;
    virtual void kolizja(Organizm *other) = 0;

    virtual void rysowanie()
    {
        cout << znak;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getSila() const { return sila; }
    int getInicjatywa() const { return inicjatywa; }
    int getWiek() const { return wiek; }
    char getZnak() const { return znak; }
    bool czyMartwy() const { return martwy; }

    void setSila(int s) { sila = s; }
    void zabij() { martwy = true; }
    void postarz() { wiek++; }
    void zmienPolozenie(int nx, int ny)
    {
        x = nx;
        y = ny;
    }
    virtual string getNazwa() const = 0;
};

class Zwierze : public Organizm
{
public:
    Zwierze(int sila, int inicjatywa, int x, int y, Swiat *swiat, char znak)
        : Organizm(sila, inicjatywa, x, y, swiat, znak) {}

    void akcja() override
    {
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;
        if (dx == 0 && dy == 0)
            return;

        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < swiat->getSzerokosc() && ny >= 0 && ny < swiat->getWysokosc())
        {
            Organizm *cel = swiat->getOrganizmNaPolu(nx, ny);
            if (cel != nullptr)
            {
                if (cel->getNazwa() == this->getNazwa())
                {
                    // Rozmnażanie
                    // Implementacja szukania wolnego pola wokół (pominięto dla zwięzłości)
                    swiat->dodajKomunikat(getNazwa() + " rozmnaza sie.");
                }
                else
                {
                    cel->kolizja(this);
                }
            }
            else
            {
                zmienPolozenie(nx, ny);
            }
        }
    }

    void kolizja(Organizm *napastnik) override
    {
        if (this->getSila() > napastnik->getSila())
        {
            swiat->dodajKomunikat(this->getNazwa() + " zabija " + napastnik->getNazwa());
            napastnik->zabij();
        }
        else
        {
            swiat->dodajKomunikat(napastnik->getNazwa() + " zabija " + this->getNazwa());
            this->zabij();
            napastnik->zmienPolozenie(this->getX(), this->getY());
        }
    }
};

class Roslina : public Organizm
{
public:
    Roslina(int sila, int x, int y, Swiat *swiat, char znak)
        : Organizm(sila, 0, x, y, swiat, znak) {}

    void akcja() override
    {
        if (rand() % 100 < 5)
        { // 5% szans na rozsianie
            swiat->dodajKomunikat(getNazwa() + " rozsiewa sie.");
            // Logika dodawania nowej rośliny na wolne pole (pominięto dla zwięzłości)
        }
    }

    void kolizja(Organizm *napastnik) override
    {
        swiat->dodajKomunikat(napastnik->getNazwa() + " zjada " + this->getNazwa());
        this->zabij();
        napastnik->zmienPolozenie(this->getX(), this->getY());
    }
};

// --- KONKRETNE GATUNKI ---

class Wilk : public Zwierze
{
public:
    Wilk(int x, int y, Swiat *swiat) : Zwierze(9, 5, x, y, swiat, 'W') {}
    string getNazwa() const override { return "Wilk"; }
};

class Trawa : public Roslina
{
public:
    Trawa(int x, int y, Swiat *swiat) : Roslina(0, x, y, swiat, 'T') {}
    string getNazwa() const override { return "Trawa"; }
};

class BarszczSosnowskiego : public Roslina
{
public:
    BarszczSosnowskiego(int x, int y, Swiat *swiat) : Roslina(10, x, y, swiat, 'B') {}
    string getNazwa() const override { return "Barszcz Sosnowskiego"; }

    void akcja() override
    {
        Roslina::akcja();
        // Zabija zwierzęta dookoła
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (dx == 0 && dy == 0)
                    continue;
                Organizm *org = swiat->getOrganizmNaPolu(x + dx, y + dy);
                if (org != nullptr && dynamic_cast<Zwierze *>(org))
                {
                    // Wyjątek dla cyber owcy (pominięto w tym wariancie)
                    swiat->dodajKomunikat(getNazwa() + " zabija " + org->getNazwa());
                    org->zabij();
                }
            }
        }
    }

    void kolizja(Organizm *napastnik) override
    {
        swiat->dodajKomunikat(napastnik->getNazwa() + " zjada " + getNazwa() + " i ginie.");
        napastnik->zabij();
        this->zabij();
    }
};

class Czlowiek : public Zwierze
{
private:
    int cooldownUmiejetnosci;
    int czasTrwaniaUmiejetnosci;

public:
    Czlowiek(int x, int y, Swiat *swiat) : Zwierze(5, 4, x, y, swiat, 'C'), cooldownUmiejetnosci(0), czasTrwaniaUmiejetnosci(0) {}
    string getNazwa() const override { return "Czlowiek"; }

    void akcja() override
    {
        if (czasTrwaniaUmiejetnosci > 0)
        {
            swiat->dodajKomunikat("Całopalenie aktywne!");
            // Całopalenie: niszczy wszystkie rośliny i zwierzęta na sąsiednich polach
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0)
                        continue;
                    Organizm *org = swiat->getOrganizmNaPolu(x + dx, y + dy);
                    if (org != nullptr)
                    {
                        swiat->dodajKomunikat("Czlowiek spopiela " + org->getNazwa());
                        org->zabij();
                    }
                }
            }
            czasTrwaniaUmiejetnosci--;
        }
        else if (cooldownUmiejetnosci > 0)
        {
            cooldownUmiejetnosci--;
        }

        int dx = 0, dy = 0;
        bool ruchWykonany = false;

        while (!ruchWykonany)
        {
            int input = _getch();
            if (input == 224)
            { // Kod strzałki w Windows
                input = _getch();
                switch (input)
                {
                case 72:
                    dy = -1;
                    ruchWykonany = true;
                    break; // góra
                case 80:
                    dy = 1;
                    ruchWykonany = true;
                    break; // dół
                case 75:
                    dx = -1;
                    ruchWykonany = true;
                    break; // lewo
                case 77:
                    dx = 1;
                    ruchWykonany = true;
                    break; // prawo
                }
            }
            else if (input == 'r' || input == 'R')
            {
                if (cooldownUmiejetnosci == 0 && czasTrwaniaUmiejetnosci == 0)
                {
                    swiat->dodajKomunikat("Umiejetnosc Calopalenie aktywowana!");
                    czasTrwaniaUmiejetnosci = 5;
                    cooldownUmiejetnosci = 5; // odlicza sie po zakonczeniu trwania, albo od razu, dostosuj w miare potrzeb
                }
                else
                {
                    swiat->dodajKomunikat("Umiejetnosc jeszcze niegotowa.");
                }
            }
            else if (input == 'q')
            {
                swiat->setKoniecGry();
                return;
            }
        }

        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < swiat->getSzerokosc() && ny >= 0 && ny < swiat->getWysokosc())
        {
            Organizm *cel = swiat->getOrganizmNaPolu(nx, ny);
            if (cel != nullptr)
                cel->kolizja(this);
            else
                zmienPolozenie(nx, ny);
        }
    }
};

// --- METODY KLASY SWIAT ---

Swiat::~Swiat()
{
    for (auto org : organizmy)
        delete org;
}

void Swiat::dodajOrganizm(Organizm *org)
{
    organizmy.push_back(org);
}

Organizm *Swiat::getOrganizmNaPolu(int x, int y)
{
    for (auto org : organizmy)
    {
        if (!org->czyMartwy() && org->getX() == x && org->getY() == y)
            return org;
    }
    return nullptr;
}

void Swiat::usunMartwe()
{
    auto it = organizmy.begin();
    while (it != organizmy.end())
    {
        if ((*it)->czyMartwy())
        {
            delete *it;
            it = organizmy.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Swiat::wykonajTure()
{
    komunikaty.clear();
    tura++;

    // Sortowanie według inicjatywy (malejąco), potem wieku (malejąco)
    sort(organizmy.begin(), organizmy.end(), [](Organizm *a, Organizm *b)
         {
        if (a->getInicjatywa() != b->getInicjatywa())
            return a->getInicjatywa() > b->getInicjatywa();
        return a->getWiek() > b->getWiek(); });

    for (size_t i = 0; i < organizmy.size(); i++)
    {
        if (!organizmy[i]->czyMartwy())
        {
            organizmy[i]->akcja();
            organizmy[i]->postarz();
        }
    }
    usunMartwe();
}

void Swiat::rysujSwiat()
{
    system("cls"); // W Linuksie zamień na system("clear")
    cout << "Imie Nazwisko, Indeks: 123454\n";
    cout << "Tura: " << tura << "\n";
    cout << "Sterowanie: strzalki. Umiejetnosc (Calopalenie): r. Wyjscie: q.\n\n";

    for (int y = 0; y < wysokosc; y++)
    {
        for (int x = 0; x < szerokosc; x++)
        {
            Organizm *org = getOrganizmNaPolu(x, y);
            if (org)
                cout << org->getZnak();
            else
                cout << '.';
        }
        cout << endl;
    }

    cout << "\n--- ZDARZENIA ---\n";
    for (const auto &msg : komunikaty)
    {
        cout << msg << endl;
    }
}

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    Swiat swiat(20, 20);

    swiat.dodajOrganizm(new Czlowiek(10, 10, &swiat));
    swiat.dodajOrganizm(new Wilk(5, 5, &swiat));
    swiat.dodajOrganizm(new Wilk(6, 5, &swiat));
    swiat.dodajOrganizm(new Trawa(15, 15, &swiat));
    swiat.dodajOrganizm(new BarszczSosnowskiego(2, 2, &swiat));

    swiat.rysujSwiat();
    while (!swiat.czyKoniec())
    {
        swiat.wykonajTure();
        swiat.rysujSwiat();
    }

    return 0;
}