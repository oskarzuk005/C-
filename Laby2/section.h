#pragma once
#include "book.h"
#include <initializer_list>
#include <iostream>
#include <string>

using namespace std;

class Section
{
    string genreName;
    Book *books;
    size_t size;

public:
    Section();
    Section(const string &name, initializer_list<Book> list);
    Section(const Section &orig);
    Section(Section &&orig);

    Section &operator=(const Section &right);
    Section &operator=(Section &&right);

    Book &operator[](size_t index);
    const Book &operator[](size_t index) const;

    size_t GetSize() const;
    string GetGenreName() const;

    ~Section();

    friend ostream &operator<<(ostream &ostr, const Section &s);
};