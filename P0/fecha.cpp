#include <iostream>
#include <ctime>

#include "fecha.hpp"

Fecha::Fecha(int d = 0, int m = 0, int a = 0)
{
    dia = d;
    mes = m;
    anno = a;

    if (dia == 0)
    {
        dia = getDiaActual();
    }
    if (mes == 0)
    {
        mes = getMesActual();
    }
    if (anno == 0)
    {
        anno = getAnnoActual();
    }
}

int Fecha::getDia()
{
    return dia;
}

int Fecha::getMes()
{
    return mes;
}

int Fecha::getAnno()
{
    return anno;
}

Fecha::~Fecha()
{
}

/****METODOS PRIVADOS****/

std::tm *Fecha::getTiempoDesc()
{
    std::time_t tiempo_calendario = std::time(nullptr);
    return std::localtime(&tiempo_calendario);
}

const int Fecha::getDiaActual()
{
    std::tm *tiempo_descompuesto = Fecha::getTiempoDesc();
    return tiempo_descompuesto->tm_mday;
}

const int Fecha::getMesActual()
{
    std::tm *tiempo_descompuesto = Fecha::getTiempoDesc();
    return tiempo_descompuesto->tm_mon + 1;
}

const int Fecha::getAnnoActual()
{
    std::tm *tiempo_descompuesto = Fecha::getTiempoDesc();
    return tiempo_descompuesto->tm_year + 1900;
}