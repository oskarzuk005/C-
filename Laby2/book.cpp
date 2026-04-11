#include "book.h"
#include <iostream>
#include <utility>

using namespace std;

Book::Book() : author(" "), title(" "), genre(" ") {}

Book::Book(const string &a, const string &t)
    : author(a), title(t), genre(" ") {}

Book::Book(string &&a, string &&t)
    : author(std::move(a)), title(std::move(t)), genre(" ") {}

Book::Book(const string &a, const string &t, const string &g)
    : author(a), title(t), genre(g) {}

Book::Book(string &&a, string &&t, string &&g)
    : author(std::move(a)), title(std::move(t)), genre(std::move(g)) {}

Book::Book(const Book &other)
    : author(other.author), title(other.title), genre(other.genre) {}

Book::Book(Book &&other)
    : author(std::move(other.author)), title(std::move(other.title)), genre(std::move(other.genre)) {}

Book &Book::operator=(const Book &right)
{
    if (this != &right)
    {
        Book tmp(right);
        swap(author, tmp.author);
        swap(title, tmp.title);
        swap(genre, tmp.genre);
    }
    return *this;
}

Book &Book::operator=(Book &&right)
{
    if (this != &right)
    {
        author = std::move(right.author);
        title = std::move(right.title);
        genre = std::move(right.genre);
    }
    return *this;
}

string Book::GetAuthor() const { return author; }
string Book::GetTitle() const { return title; }
string Book::GetGenre() const { return genre; }

void Book::SetAuthor(const string &a) { author = a; }
void Book::SetTitle(const string &t) { title = t; }
void Book::SetGenre(const string &g) { genre = g; }

void Book::SetAuthor(string &&a) { author = std::move(a); }
void Book::SetTitle(string &&t) { title = std::move(t); }
void Book::SetGenre(string &&g) { genre = std::move(g); }

ostream &operator<<(ostream &ostr, const Book &b)
{
    ostr << "\"" << b.author << "\", \"" << b.title << "\", \"" << b.genre << "\"";
    return ostr;
}