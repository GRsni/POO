#include "tarjeta.hpp"

Numero::Numero(const Cadena &C)
{
    size_t tam = C.length();
    Cadena normalizada;
    for (unsigned int i = 0; i < tam; i++)
    {
        if (C[i] >= '0' && C[i] <= '9')
        {
            normalizada += Cadena(1, C[i]);
        }
        else if (C[i] != ' ')
        {
            throw Numero::Incorrecto(Numero::DIGITOS);
        }
    }
    if (normalizada.length() < 13 || normalizada.length() > 19)
    {
        throw Numero::Incorrecto(Numero::LONGITUD);
    }

    if (!luhn(normalizada))
    {
        throw Numero::Incorrecto(Numero::NO_VALIDO);
    }
    numero_ = normalizada;
}

bool Numero::operator<(const Numero &N)
{
    return num() < N.num();
}

double Numero::num() const
{
    double num = 0;
    for (int i = numero_.length() - 1; i >= 0; i--)
    {
        num *= 10;
        num += (double)(numero_[i] - '0');
    }
    return num;
}