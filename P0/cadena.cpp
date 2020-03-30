#include <iostream>
#include <cstring>

#include "cadena.hpp"

Cadena::Cadena(size_t tam, char c) : tam_(tam)
{
    s_ = new char[tam_ + 1]{0};
    for (int i = 0; i < tam_; i++)
    {
        s_[i] = c;
    }
}

Cadena::Cadena(const char *cad)
{
    if (cad != nullptr)
    {
        tam_ = strlen(cad);
    }
    s_ = new char[tam_ + 1];
    std::strcpy(s_, cad);
}

Cadena::Cadena(const Cadena &C) : tam_(C.tam_)
{
    s_ = new char[tam_ + 1];
    std::strcpy(s_, C.s_);
}

Cadena &Cadena::operator=(const Cadena &C)
{
    if (this != &C)
    {
        delete[] s_;
        tam_ = C.tam_;
        s_ = new char[tam_ + 1];
        std::strcpy(s_, C.s_);
    }
    return *this;
}

const char Cadena::operator[](size_t n) const
{
    return s_[n];
}

char &Cadena::operator[](size_t n)
{
    return s_[n];
}

char Cadena::at(size_t n) const
{
    if (n >= tam_)
    {
        throw std::out_of_range("Indice fuera del rango.");
    }
    else
    {
        return s_[n];
    }
}

char &Cadena::at(size_t n)
{
    if (n >= tam_)
    {
        throw std::out_of_range("Indice fuera del rango");
    }
    else
    {
        return s_[n];
    }
}

Cadena Cadena::substr(size_t index, size_t tam) const
{
    if (index >= tam_ || index > tam_ - index)
    {
        throw std::out_of_range("Indice fuera de la cadena.");
    }
    else
    {
        static char *subcad = new char[tam + 1]{0};
        strncpy(subcad, s_ + index, tam);
        return Cadena(subcad);
    }
}

Cadena &Cadena::operator+=(const Cadena &B)
{
    char *copia = new char[tam_ + 1];
    std::strcpy(copia, s_);
    delete[] s_;
    tam_ += B.length();
    s_ = new char[tam_ + 1];
    sprintf(s_, "%s%s", copia, B.s_);
    delete[] copia;
    return *this;
}

Cadena operator+(const Cadena &A, const Cadena &B)
{
    Cadena aux = A;
    aux += B;
    return aux;
}

bool operator==(const Cadena &A, const Cadena &B)
{
    return std::strcmp(A, B) == 0;
}

bool operator!=(const Cadena &A, const Cadena &B)
{
    return std::strcmp(A, B) != 0;
}

bool operator>(const Cadena &A, const Cadena &B)
{
    return std::strcmp(A, B) > 0;
}

bool operator<(const Cadena &A, const Cadena &B)
{
    return std::strcmp(A, B) < 0;
}

bool operator<=(const Cadena &A, const Cadena &B)
{
    return !(std::strcmp(A, B) > 0);
}

bool operator>=(const Cadena &A, const Cadena &B)
{
    return !(std::strcmp(A, B) < 0);
}

Cadena::~Cadena()
{
    delete[] s_;
}