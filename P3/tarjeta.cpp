#include <ctype.h>
#include <iomanip>
#include <cstring>
#include <utility>
#include <functional>
#include <algorithm>

#include "tarjeta.hpp"

Numero::Numero(const Cadena &C)
{
    numero_ = C;

    Cadena::iterator it = std::remove_if(numero_.begin(), numero_.end(), EsBlanco());

    if (it != numero_.end())
    {
        *it = '\0';
        Cadena aux = (numero_.c_str());
        numero_ = aux;
    }
    std::cout << "tam numero:" << numero_.length() << std::endl;
    if (std::find_if(numero_.begin(), numero_.end(), std::not_fn(EsDigito())) != numero_.end())
    {
        throw Numero::Incorrecto(Numero::DIGITOS);
    }

    if (numero_.length() < 13 || numero_.length() > 19)
    {
        throw Numero::Incorrecto(Numero::LONGITUD);
    }

    if (!luhn(numero_))
    {
        throw Numero::Incorrecto(Numero::NO_VALIDO);
    }
}

bool operator<(const Numero &a, const Numero &b)
{
    return strcmp(a, b) < 0;
}

std::set<Numero> Tarjeta::coleccion;

Cadena Tarjeta::tipos[] = {"American Express", "JCB", "VISA", "Mastercard", "Maestro", "Otro"};

Tarjeta::Tarjeta(const Numero &num, const Usuario &us, const Fecha &f) : numero_(&num),
                                                                         titular_(&us),
                                                                         caducidad_(f),
                                                                         activa_(true)
{
    if (caducidad_ < Fecha())
    {
        throw Tarjeta::Caducada(caducidad_);
    }
    if (!Tarjeta::coleccion.insert(*numero_).second)
    {
        throw Tarjeta::Num_duplicado(*numero_);
    }

    const_cast<Usuario *>(titular_)->es_titular_de(*this);
}

bool Tarjeta::activa(bool act)
{
    activa_ = act;
    return act;
}

const Tarjeta::Tipo Tarjeta::tipo() const
{
    if (*numero_[0] == '3')
    {
        if (*numero_[1] == '4' || *numero_[1] == '7')
        {
            return Tarjeta::Tipo::AmericanExpress;
        }
        else
        {
            return Tarjeta::Tipo::JCB;
        }
    }
    else if (*numero_[0] == '4')
    {
        return Tarjeta::Tipo::VISA;
    }
    else if (*numero_[0] == '5')
    {
        return Tarjeta::Tipo::Mastercard;
    }
    else if (*numero_[0] == '6')
    {
        return Tarjeta::Tipo::Maestro;
    }
    else
    {
        return Tarjeta::Tipo::Otro;
    }
}

void Tarjeta::anula_titular()
{
    titular_ = nullptr;
    activa_ = false;
}

Tarjeta::~Tarjeta()
{
    if (titular_ != nullptr)
    {
        const_cast<Usuario *>(titular_)->no_es_titular_de(*this);
    }
    Tarjeta::coleccion.erase(*numero_);
}

bool operator<(const Tarjeta &a, const Tarjeta &b)
{
    return a.numero() < b.numero();
}

std::ostream &operator<<(std::ostream &out, const Tarjeta::Tipo &t)
{
    out << Tarjeta::tipos[t];
    return out;
}

std::ostream &operator<<(std::ostream &out, const Tarjeta &t)
{
    int tam = t.titular()->nombre().length() + t.titular()->apellidos().length() + 2;
    Cadena titular_facial(t.titular()->nombre() + " " + t.titular()->apellidos());
    out << "+" << std::setfill(' ') << Cadena(tam + 1, '-') << "+" << std::endl
        << "| " << std::setw(tam) << std::left << t.tipo() << "|" << std::endl
        << "| " << std::setw(tam) << std::left << t.numero() << "|" << std::endl
        << "| ";
    for (auto it = titular_facial.begin(); it != titular_facial.end(); ++it)
    {
        out << (char)toupper(*it);
    }
    out << " |" << std::endl
        << "| Caduca: " << std::setw(2) << std::setfill('0') << std::right << t.caducidad().mes() << "/"
        << (t.caducidad().anno() % 100) << Cadena(tam - 13, ' ') << "|" << std::endl
        << "+" << Cadena(tam + 1, '-') << "+" << std::endl;
    out << std::resetiosflags(std::ios::showbase);
    return out;
}