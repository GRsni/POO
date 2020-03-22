#include <iostream>
#include <ctime>
#include <cstdio>

#include "fecha.hpp"

Fecha::Invalida::Invalida(const char mot[]) : motivo(mot) {}

void Fecha::Invalida::por_que()
{
    std::cerr << motivo << std::endl;
}

Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), anno_(a)
{
    if (anno_ == 0)
    {
        anno_ = extraeAnno(getTiempoDesc());
    }
    else
    {
        if (!esAnnoValido())
        {
            throw Invalida("ERROR: Anno fuera de rango valido.");
        }
    }

    if (mes_ == 0)
    {
        mes_ = extraeMes(getTiempoDesc());
    }
    else
    {
        if (!esMesValido())
        {
            throw Invalida("ERROR: Mes fuera de rango valido.");
        }
    }

    if (dia_ == 0)
    {
        dia_ = extraeDia(getTiempoDesc());
    }
    else
    {
        if (!esDiaValido())
        {
            throw Invalida("ERROR: Dia no valido.");
        }
    }
}

Fecha::operator const char *() const
{
    std::locale::global(std::locale("es_ES.UTF-8"));
    std::tm *t = getTiempoDescNormalizado(dia_, mes_, anno_);
    std::strftime(salida, 35, "%A %d de %B de %Y", t);
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
        throw Invalida("Cadena de entrada no valida");
    }
}

Fecha Fecha::operator+=(int n)
{
    std::tm *t = getTiempoDescNormalizado(dia_ + n, mes_, anno_);

    dia_ = extraeDia(t);
    mes_ = extraeMes(t);
    anno_ = extraeAnno(t);

    if (!esAnnoValido())
    {
        throw Invalida("ERROR: Anno fuera de rango valido.");
    }

    return *this;
}

Fecha Fecha::operator-=(int n)
{
    return *this += -n;
}

Fecha Fecha::operator++()
{
    return *this += 1;
}

Fecha Fecha::operator--()
{
    return *this += -1;
}

Fecha Fecha::operator++(int)
{
    Fecha f = *this;
    *this += 1;
    return f;
}

Fecha Fecha::operator--(int)
{
    Fecha f = *this;
    *this += -1;
    return f;
}

Fecha Fecha::operator+(int n)
{
    Fecha aux(*this);
    aux += n;
    return aux;
}

Fecha Fecha::operator-(int n)
{
    Fecha aux(*this);
    aux += -n;
    return aux;
}

bool Fecha::operator==(const Fecha &F)
{
    return dia_ == F.dia() && mes_ == F.mes() && anno_ == F.anno();
}

bool Fecha::operator!=(const Fecha &F)
{
    return !(*this == F);
}

bool Fecha::operator<(const Fecha &F)
{
    if (anno_ > F.anno())
    {
        return false;
    }
    else if (anno_ < F.anno())
    {
        return true;
    }
    else
    {
        if (mes_ > F.mes())
        {
            return false;
        }
        else if (mes_ < F.mes())
        {
            return true;
        }
        else
        {
            if (dia_ < F.dia())
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

bool Fecha::operator>(const Fecha &F)
{
    return F < *this;
}

bool Fecha::operator<=(const Fecha &F)
{
    return !(F < *this);
}

bool Fecha::operator>=(const Fecha &F)
{
    return !(*this < F);
}

/**********************************METODOS PRIVADOS**************************************/

std::tm *Fecha::getTiempoDesc() const
{
    std::time_t tiempo_calendario = std::time(nullptr);
    return std::localtime(&tiempo_calendario);
}

std::tm *Fecha::getTiempoDescNormalizado(const int d, const int m, const int a) const
{
    std::tm *tAux = getTiempoDesc();
    tAux->tm_mday = d;
    tAux->tm_mon = m - 1;
    tAux->tm_year = a - 1900;

    std::time_t tiempo_cal = std::mktime(tAux);
    return std::localtime(&tiempo_cal);
}

int Fecha::extraeDia(const std::tm *t) const
{
    return t->tm_mday;
}

int Fecha::extraeMes(const std::tm *t) const
{
    return t->tm_mon + 1;
}

int Fecha::extraeAnno(const std::tm *t) const
{
    return t->tm_year + 1900;
}

const int Fecha::getDiasEnMes(int mes)
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

const bool Fecha::esFechaValida()
{
    return esDiaValido() && esMesValido() && esAnnoValido();
}

const bool Fecha::esAnnoValido()
{
    return anno_ >= AnnoMinimo && anno_ <= AnnoMaximo;
}

const bool Fecha::esMesValido()
{
    return mes_ >= Fecha::ENERO && mes_ <= Fecha::DICIEMBRE;
}

const bool Fecha::esDiaValido()
{
    return dia_ >= 1 && dia_ <= getDiasEnMes(mes_);
}
bool Fecha::esAnnoBisiesto(int a)
{
    return a % 4 == 0 && (a % 400 == 0 || a % 100 != 0);
}