#include <iostream>
#include "book.h"
#include "section.h"
#include "library.h"

using namespace std;

int main()
{

    Book b1{"Stanislaw Lem", "Solaris", "Sci-Fi"};
    Book b2{"Frank Herbert", "Diuna", "Sci-Fi"};
    Book b3{"Katsuhiro Ōtomo", "Akira", "Sci-Fi"};
    Book b4{"J.R.R. Tolkien", "Hobbit", "Fantasy"};
    Book b5{"Andrzej Sapkowski", "Wiedzmin", "Fantasy"};

    Section s1("Sci-Fi\n", {b1, b2, b3});
    Section s2("Fantasy\n", {b4, b5});

    Library lib1 = {s2, s1};

    Book b6{"Stephen King", "Lsnienie", "Horror"};
    Book b7{"H.P. Lovecraft", "Zew Cthulhu", "Horror"};
    Book b8{"George Orwell", "Rok 1984", "Dramat"};
    Book b9{"Agatha Christie", "Morderstwo", "Kryminal"};

    Section s3("Horror\n", {b6, b7});
    Section s4("Inne\n", {b8, b9});

    Library lib2 = {s4, s3};

    cout << "library 1" << endl;
    cout << lib1 << endl;

    cout << "library 2" << endl;
    cout << lib2 << endl;

    return 0;
}