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

Cadena Cadena::operator+=(const Cadena &B)
{
    tam_ += B.length();
    std::strcat(s_, B.s_);
    return *this;
}

Cadena Cadena::operator+(const Cadena &C)
{
    Cadena aux(*this);
    aux += C;
    return aux;
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