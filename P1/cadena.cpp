#include <iostream>
#include <cstring>
#include <cstddef>
#include <stdexcept>
#include <stdio.h>

#include "cadena.hpp"

Cadena::Cadena(size_t tam, char c) noexcept : tam_(tam)
{
    s_ = new char[tam_ + 1]{0};
    if (tam_ > 0)
    {
        for (int i = 0; i < tam_; i++)
        {
            s_[i] = c;
        }
    }
}

Cadena::Cadena(const char *cad) noexcept
{
    if (cad != nullptr)
    {
        tam_ = strlen(cad);
    }
    s_ = new char[tam_ + 1];
    std::strcpy(s_, cad);
}

Cadena::Cadena(const Cadena &C) noexcept : tam_(C.tam_)
{
    s_ = new char[tam_ + 1];
    std::strcpy(s_, C.s_);
}

Cadena::Cadena(Cadena &&C) noexcept : tam_(C.tam_)
{
    s_ = C.s_;
    C.tam_ = 0;
    C.s_ = nullptr;
}

Cadena &Cadena::operator=(const Cadena &C) noexcept
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

Cadena &Cadena::operator=(Cadena &&C) noexcept
{
    if (this != &C)
    {
        delete[] s_;
        tam_ = C.tam_;
        s_ = C.s_;
        C.tam_ = 0;
        C.s_ = nullptr;
    }
    return *this;
}

Cadena &Cadena::operator+=(const Cadena &B) noexcept
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

const char Cadena::at(size_t n) const
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

Cadena::~Cadena()
{
    delete[] s_;
}

Cadena operator+(const Cadena &A, const Cadena &B) noexcept
{
    Cadena aux = A;
    aux += B;
    return aux;
}

bool operator==(const Cadena &A, const Cadena &B) noexcept
{
    return std::strcmp(A.c_str(), B.c_str()) == 0;
}

bool operator!=(const Cadena &A, const Cadena &B) noexcept
{
    return std::strcmp(A.c_str(), B.c_str()) != 0;
}

bool operator>(const Cadena &A, const Cadena &B) noexcept
{
    return std::strcmp(A.c_str(), B.c_str()) > 0;
}

bool operator<(const Cadena &A, const Cadena &B) noexcept
{
    return std::strcmp(A.c_str(), B.c_str()) < 0;
}

bool operator<=(const Cadena &A, const Cadena &B) noexcept
{
    return !(std::strcmp(A.c_str(), B.c_str()) > 0);
}

bool operator>=(const Cadena &A, const Cadena &B) noexcept
{
    return !(std::strcmp(A.c_str(), B.c_str()) < 0);
}

std::ostream &operator<<(std::ostream &out, const Cadena &C) noexcept
{
    out << C.c_str();
    return out;
}

std::istream &operator>>(std::istream &in, Cadena &C) noexcept
{
    char cad[33]{0};
    in.width(33);
    in >> cad;
    C = cad;
    return in;
}
