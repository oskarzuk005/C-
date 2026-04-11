#pragma once
#include "section.h"
#include <initializer_list>
#include <iostream>

using namespace std;

class Library
{
    Section *sections;
    size_t size;

public:
    Library();
    Library(initializer_list<Section> list);
    Library(const Library &orig);
    Library(Library &&orig);

    Library &operator=(const Library &right);
    Library &operator=(Library &&right);

    Section &operator[](size_t index);
    const Section &operator[](size_t index) const;

    size_t GetSize() const;

    ~Library();

    friend ostream &operator<<(ostream &ostr, const Library &l);
};