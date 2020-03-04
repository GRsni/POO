#include <iostream>
#include <ctime>

#include "fecha.hpp"

Fecha::Fecha(int d, int m, int a) : dia(d), mes(m), anno(a) {}

Fecha::Fecha(int d, int m, int a) : dia(d), mes(m)
{

    if (a = 0)
    {
        anno = Fecha::getAnnoActual();
    }
}

Fecha::Fecha(int d, int m, int a) : dia(d)
{
    if (m == 0)
    {
        mes = Fecha::getMesActual();
    }
    if (a == 0)
    {
        anno = Fecha::getAnnoActual();
    }
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