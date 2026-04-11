#include "library.h"
#include <utility>

using namespace std;

Library::Library() : sections(nullptr), size(0) {}

Library::Library(initializer_list<Section> list)
    : size(list.size()), sections(new Section[list.size()])
{
    size_t i = 0;
    for (const auto &s : list)
    {
        sections[i++] = s;
    }
}

Library::Library(const Library &orig) : size(orig.size), sections(new Section[orig.size])
{
    for (size_t i = 0; i < size; ++i)
    {
        sections[i] = orig.sections[i];
    }
}

Library::Library(Library &&orig) : sections(orig.sections), size(orig.size)
{
    orig.sections = nullptr;
    orig.size = 0;
}

Library &Library::operator=(const Library &right)
{
    if (this != &right)
    {
        Library tmp(right);
        swap(sections, tmp.sections);
        swap(size, tmp.size);
    }
    return *this;
}

Library &Library::operator=(Library &&right)
{
    if (this != &right)
    {
        swap(sections, right.sections);
        swap(size, right.size);
    }
    return *this;
}

Section &Library::operator[](size_t index) { return sections[index]; }
const Section &Library::operator[](size_t index) const { return sections[index]; }

size_t Library::GetSize() const { return size; }

Library::~Library()
{
    if (sections != nullptr)
        delete[] sections;
}

ostream &operator<<(ostream &ostr, const Library &l)
{
    for (size_t i = 0; i < l.size; ++i)
    {
        ostr << l.sections[i];
    }
    return ostr;
}