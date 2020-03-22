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
        //std::cout << mes << " tiene " << getDiasEnMes(mes) << "dias.\n";
        if (!esDiaValido())
        {
            throw Invalida("ERROR: Dia no valido.");
        }
    }
}

const std::string Fecha::nombreDias[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};

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
    std::tm *tAux = getTiempoDesc();
    tAux->tm_mday = dia_ + n;
    tAux->tm_mon = mes_ - 1;
    tAux->tm_year = anno_ - 1900;

    std::time_t tiempo_cal = std::mktime(tAux);
    std::tm *t = std::localtime(&tiempo_cal);

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

void Fecha::imprimeFecha() const
{
    std::cout << "Hoy es " << Fecha::dia()
              << "/" << Fecha::mes() << "/" << Fecha::anno() << std::endl;
}

/**********************************METODOS PRIVADOS**************************************/

std::tm *Fecha::getTiempoDesc() const
{
    std::time_t tiempo_calendario = std::time(nullptr);
    return std::localtime(&tiempo_calendario);
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