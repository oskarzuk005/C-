#pragma once
#include <string>
#include <iostream>

using namespace std;

class Book
{
    string author;
    string title;
    string genre;

public:
    Book();
    Book(const string &a, const string &t);
    Book(string &&a, string &&t);
    Book(const string &a, const string &t, const string &g);
    Book(string &&a, string &&t, string &&g);

    Book(const Book &other);
    Book(Book &&other);

    Book &operator=(const Book &right);
    Book &operator=(Book &&right);

    string GetAuthor() const;
    string GetTitle() const;
    string GetGenre() const;

    void SetAuthor(const string &a);
    void SetTitle(const string &t);
    void SetGenre(const string &g);

    void SetAuthor(string &&a);
    void SetTitle(string &&t);
    void SetGenre(string &&g);

    friend ostream &operator<<(ostream &ostr, const Book &b);
};