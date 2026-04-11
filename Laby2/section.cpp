#include "section.h"
#include <utility>

using namespace std;

Section::Section() : genreName(" "), books(nullptr), size(0) {}

Section::Section(const string &name, initializer_list<Book> list)
    : genreName(name), size(list.size()), books(new Book[list.size()])
{
    size_t i = 0;
    for (const auto &b : list)
    {
        books[i++] = b;
    }
}

Section::Section(const Section &orig)
    : genreName(orig.genreName), size(orig.size), books(new Book[orig.size])
{
    for (size_t i = 0; i < size; ++i)
    {
        books[i] = orig.books[i];
    }
}

Section::Section(Section &&orig)
    : genreName(std::move(orig.genreName)), books(orig.books), size(orig.size)
{
    orig.books = nullptr;
    orig.size = 0;
}

Section &Section::operator=(const Section &right)
{
    if (this != &right)
    {
        Section tmp(right);
        swap(genreName, tmp.genreName);
        swap(books, tmp.books);
        swap(size, tmp.size);
    }
    return *this;
}

Section &Section::operator=(Section &&right)
{
    if (this != &right)
    {
        genreName = std::move(right.genreName);
        swap(books, right.books);
        swap(size, right.size);
    }
    return *this;
}

Book &Section::operator[](size_t index) { return books[index]; }
const Book &Section::operator[](size_t index) const { return books[index]; }

size_t Section::GetSize() const { return size; }
string Section::GetGenreName() const { return genreName; }

Section::~Section()
{
    if (books != nullptr)
        delete[] books;
}

ostream &operator<<(ostream &ostr, const Section &s)
{
    ostr << "\nSekcja: " << s.genreName << "\n";
    for (size_t i = 0; i < s.size; ++i)
    {
        ostr << s.books[i] << "\n";
    }
    return ostr;
}