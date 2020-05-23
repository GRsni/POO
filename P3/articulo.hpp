#ifndef ARTICULO_H
#define ARTICULO_H

#include <iostream>
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

class Articulo
{
public:
    Articulo(const Cadena &ref, const Cadena &c, const Fecha &f, double precio, unsigned int stock = 0);

    //Articulo &operator=(const Articulo &A);

    const Cadena &referencia() const { return referencia_; };
    const Cadena &titulo() const { return titulo_; };
    const Fecha &f_publi() const { return f_publi_; };
    const double precio() const { return precio_; };
    double &precio() { return precio_; };
    const unsigned int stock() const { return stock_; };
    unsigned int &stock() { return stock_; };

    ~Articulo();

private:
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha f_publi_;
    double precio_;
    unsigned int stock_;
};

std::ostream &operator<<(std::ostream &in, Articulo &A);

#endif //ARTICULO_H
