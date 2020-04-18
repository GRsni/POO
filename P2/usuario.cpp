#include <iostream>
#include <unistd.h>
#include <random>
#include <cstddef>
#include <cstring>
#include <ctime>

#include "usuario.hpp"

Clave::Incorrecta::Incorrecta(const Clave::Razon r) : razon_(r) {}

std::random_device Clave::rd;
std::uniform_int_distribution<std::size_t> Clave::dist(0, 63);

Clave::Clave(const char *cad)
{
    if (std::strlen(cad) < 5)
    {
        throw Clave::Incorrecta(Clave::CORTA);
    }
    const char *salt_ = salt();
    char *cifrada = crypt(cad, salt_);
    delete[] salt_;
    if (cifrada == nullptr)
    {
        throw Clave::Incorrecta(Clave::ERROR_CRYPT);
    }
    clave_ = Cadena(cifrada);
}

const bool Clave::verifica(const char *cad) const
{
    return strcmp(crypt(cad, clave_.c_str()), clave_.c_str()) == 0;
}

/****************************METODOS PRIVADOS CLAVE***********************************/

const char *Clave::salt() const
{
    const Cadena simbolos = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    char *salt = new char[3]{0};

    salt[0] = simbolos[Clave::dist(Clave::rd)];
    salt[1] = simbolos[Clave::dist(Clave::rd)];

    return salt;
}
