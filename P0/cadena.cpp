#include <iostream>
#include <cstring>

#include "cadena.hpp"

Cadena::Cadena(int tam, char c) : tam_(tam)
{
    s_ = new char[tam_ + 1];
    s_[tam] = 0;
    if (tam > 0)
    {
        for (int i = 0; i < tam_; i++)
        {
            s_[i] = c;
        }
    }
}

Cadena::Cadena(const char *cad) : tam_(std::strlen(cad))
{
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

const char Cadena::at(size_t n) const
{
    if (n > tam_ - 1)
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
    if (n > tam_ - 1)
    {
        throw std::out_of_range("Indice fuera del rango");
    }
    else
    {
        return s_[n];
    }
}

Cadena Cadena::substr(size_t index, size_t tam)
{
    if (index >= tam_ || index > tam_ - index)
    {
        throw std::out_of_range("Indice fuera de la cadena.");
    }
    else
    {
        char *subcad = new char[tam];
        strncpy(subcad, s_ + tam, tam + 1);
        return Cadena(subcad);
    }
}

Cadena Cadena::operator+=(const Cadena &B)
{
    tam_ += B.length() + 1;
    char *aux = new char[tam_ + 1];
    std::strcpy(aux, s_);
    std::strcat(aux, B.s_);
    delete[] s_;
    s_ = new char[tam_];
    strcpy(s_, aux);
    delete[] aux;
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