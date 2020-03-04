#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <ctime>

class Fecha
{
public:
    int dia, mes, anno;

    Fecha(int dia, int mes, int anno);
    Fecha();

    ~Fecha();

private:
    std::tm *getTiempoDesc();
    const int getDiaActual();
    const int getMesActual();
    const int getAnnoActual();
};

#endif //FECHA_H