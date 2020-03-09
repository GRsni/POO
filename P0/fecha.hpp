#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <ctime>

class Fecha
{
public:
    Fecha(int d, int m, int a);

    int getDia();
    int getMes();
    int getAnno();

    ~Fecha();

private:
    int dia, mes, anno;

    std::tm *getTiempoDesc();
    const int getDiaActual();
    const int getMesActual();
    const int getAnnoActual();
};

#endif //FECHA_H