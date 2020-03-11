#include <iostream>
#include <ctime>
#include <cstdio>

#include "fecha.hpp"

Fecha::Fecha(int d, int m, int a) : dia(d), mes(m), anno(a)
{

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

Fecha::Fecha(const char in[])
{
    int d, m, a;
    char separator1, separator2;
    char format[] = u8"%d/%d/%4d";
    int numCampos = sscanf(in, format, &d, &m, &a);
    if (numCampos == 3)
    {
        *this = Fecha(d, m, a);
    }
    else
    {
        std::cout << "Parametros de entrada no validos." << std::endl;
    }
}

int Fecha::getDia() const
{
    return dia;
}

int Fecha::getMes() const
{
    return mes;
}

int Fecha::getAnno() const
{
    return anno;
}

void Fecha::imprimeFecha() const
{
    std::cout << "Hoy es " << getDia()
              << "/" << getMes() << "/" << getAnno() << std::endl;
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