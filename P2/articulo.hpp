#ifndef ARTICULO_H
#define ARTICULO_H

#include <iostream>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

class Articulo
{
public:
    Articulo(const Cadena &ref, const Cadena &c, const Fecha &f, double precio, double stock = 0);
    Articulo(const Articulo &A);

    Articulo &operator=(const Articulo &A);

    const Cadena &referencia() const;
    const Cadena &titulo() const;
    const Fecha &f_publi() const;
    const double precio() const;
    double &precio();
    const double stock() const;
    double &stock();

    ~Articulo();

private:
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha f_publi_;
    double precio_;
    double stock_;
};

std::ostream &operator<<(std::ostream &in, Articulo &A);

#endif //ARTICULO_H
