#include <iostream>
#include <ctime>
#include <cstdio>

#include "fecha.hpp"

Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), anno_(a)
{
    std::tm *tiempoStruct = getTiempoDesc();

    if (anno_ == 0)
    {
        anno_ = extraeAnno(tiempoStruct);
    }
    else
    {
        if (!esAnnoValido())
        {
            throw Fecha::Invalida("ERROR: Anno fuera de rango valido.");
        }
    }

    if (mes_ == 0)
    {
        mes_ = extraeMes(tiempoStruct);
    }
    else
    {
        if (!esMesValido())
        {
            throw Fecha::Invalida("ERROR: Mes fuera de rango valido.");
        }
    }

    if (dia_ == 0)
    {
        dia_ = extraeDia(tiempoStruct);
    }
    else
    {
        if (!esDiaValido())
        {
            throw Fecha::Invalida("ERROR: Dia no valido.");
        }
    }
}

const char *Fecha::cadena() const noexcept
{
    std::locale::global(std::locale("es_ES.UTF-8"));

    std::tm tAux{0};
    tAux.tm_mday = dia_;
    tAux.tm_mon = mes_ - 1;
    tAux.tm_year = anno_ - 1900;

    std::mktime(&tAux);
    static char salida[36]{0};
    std::strftime(salida, 36, "%A %d de %B de %Y", &tAux);
    std::locale::global(std::locale("C"));
    return salida;
}

Fecha::Fecha(const char in[])
{
    int d, m, a;
    char format[] = u8"%d/%d/%d";
    int numCampos = sscanf(in, format, &d, &m, &a);
    if (numCampos == 3)
    {
        *this = Fecha(d, m, a);
    }
    else
    {
        throw Fecha::Invalida("Cadena de entrada no valida");
    }
}

Fecha &Fecha::operator+=(int n)
{
    std::tm tAux{0};
    tAux.tm_mday = dia_ + n;
    tAux.tm_mon = mes_ - 1;
    tAux.tm_year = anno_ - 1900;

    std::mktime(&tAux);

    dia_ = extraeDia(&tAux);
    mes_ = extraeMes(&tAux);
    anno_ = extraeAnno(&tAux);

    if (!esAnnoValido())
    {
        throw Fecha::Invalida("ERROR: Anno fuera de rango valido.");
    }

    return *this;
}

Fecha &Fecha::operator-=(int n)
{
    return *this += -n;
}

Fecha &Fecha::operator++()
{
    return *this += 1;
}

Fecha &Fecha::operator--()
{
    return *this += -1;
}

Fecha Fecha::operator++(int)
{
    const Fecha f(*this);
    *this += 1;
    return f;
}

Fecha Fecha::operator--(int)
{
    const Fecha f(*this);
    *this += -1;
    return f;
}

Fecha Fecha::operator+(int n) const
{
    Fecha aux(*this);
    aux += n;
    return aux;
}

Fecha Fecha::operator-(int n) const
{
    Fecha aux(*this);
    aux += -n;
    return aux;
}

bool operator==(const Fecha &A, const Fecha &B) noexcept
{
    return A.dia() == B.dia() &&
           A.mes() == B.mes() &&
           A.anno() == B.anno();
}

bool operator!=(const Fecha &A, const Fecha &B) noexcept
{
    return !(A == B);
}

bool operator<(const Fecha &A, const Fecha &B) noexcept
{
    if (A.anno() > B.anno())
    {
        return false;
    }
    else if (A.anno() < B.anno())
    {
        return true;
    }
    else
    {
        if (A.mes() > B.mes())
        {
            return false;
        }
        else if (A.mes() < B.mes())
        {
            return true;
        }
        else
        {
            if (A.dia() < B.dia())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Fecha &F) noexcept
{
    out << F.cadena();
    return out;
}

std::istream &operator>>(std::istream &in, Fecha &F)
{
    char cad[11]{0};
    in.width(11);
    in >> cad;
    try
    {
        F = Fecha(cad);
    }
    catch (const Fecha::Invalida &e)
    {
        in.setstate(std::ios::failbit);
        throw e;
    }
    return in;
}

bool operator>(const Fecha &A, const Fecha &B) noexcept
{
    return B < A;
}

bool operator<=(const Fecha &A, const Fecha &B) noexcept
{
    return !(B < A);
}

bool operator>=(const Fecha &A, const Fecha &B) noexcept
{
    return !(A < B);
}

/**********************************METODOS PRIVADOS**************************************/

std::tm *Fecha::getTiempoDesc() const noexcept
{
    std::time_t tiempo_calendario = std::time(nullptr);
    return std::localtime(&tiempo_calendario);
}

const int Fecha::extraeDia(const std::tm *t) const noexcept
{
    return t->tm_mday;
}

const int Fecha::extraeMes(const std::tm *t) const noexcept
{
    return t->tm_mon + 1;
}

const int Fecha::extraeAnno(const std::tm *t) const noexcept
{
    return t->tm_year + 1900;
}

const int Fecha::getDiasEnMes(int mes) noexcept
{
    if (mes <= Fecha::JULIO)
    {
        if (mes == Fecha::FEBRERO)
        {
            return esAnnoBisiesto(anno_) ? 29 : 28;
        }
        else
        {
            return mes % 2 == 0 ? 30 : 31;
        }
    }
    else
    {
        return mes % 2 == 0 ? 31 : 30;
    }
}

const bool Fecha::esFechaValida() noexcept
{
    return esDiaValido() && esMesValido() && esAnnoValido();
}

const bool Fecha::esAnnoValido() noexcept
{
    return anno_ >= AnnoMinimo && anno_ <= AnnoMaximo;
}

const bool Fecha::esMesValido() noexcept
{
    return mes_ >= Fecha::ENERO && mes_ <= Fecha::DICIEMBRE;
}

const bool Fecha::esDiaValido() noexcept
{
    return dia_ >= 1 && dia_ <= getDiasEnMes(mes_);
}

bool Fecha::esAnnoBisiesto(int a) noexcept
{
    return a % 4 == 0 && (a % 400 == 0 || a % 100 != 0);
}