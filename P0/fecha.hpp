#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <ctime>

class Fecha
{
public:
    static const int AnnoMaximo = 2037;
    static const int AnnoMinimo = 1972;

    explicit Fecha(int d = 0, int m = 0, int a = 0);
    Fecha(const char in[]);

    int getDia() const;
    int getMes() const;
    int getAnno() const;
    void imprimeFecha() const;

    ~Fecha();

private:
    int dia, mes, anno;

    std::tm *getTiempoDesc();
    const int getDiaActual();
    const int getMesActual();
    const int getAnnoActual();
};

#endif //FECHA_H