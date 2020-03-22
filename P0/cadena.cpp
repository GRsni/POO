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
    std::cout << "Tam: " << tam_ << " Cadena: " << s_ << "." << std::endl;
}

Cadena::Cadena(const char cad[]) : tam_(std::strlen(cad))
{
    s_ = new char[tam_ + 1];
    std::strcpy(s_, cad);
    std::cout << "Tam: " << tam_ << " Cadena: " << s_ << "." << std::endl;
}

Cadena::Cadena(const Cadena &C) : tam_(C.tam_)
{
    s_ = new char[tam_ + 1];
    std::strcpy(s_, C.s_);
    std::cout << "Tam: " << tam_ << " Cadena: " << s_ << "." << std::endl;
}

Cadena::~Cadena()
{
    delete[] s_;
    s_ = nullptr;
}