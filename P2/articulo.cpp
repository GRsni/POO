#include <iostream>
#include <iomanip>

#include "articulo.hpp"

Articulo::Articulo(const Cadena &ref, const Cadena &C, const Fecha &F, double precio, double stock) : referencia_(ref),
                                                                                                      titulo_(C),
                                                                                                      f_publi_(F),
                                                                                                      precio_(precio),
                                                                                                      stock_(stock) {}

Articulo::Articulo(const Articulo &a) : referencia_(a.referencia()),
                                        titulo_(a.titulo()),
                                        f_publi_(a.f_publi()),
                                        precio_(a.precio()),
                                        stock_(a.stock()) {}

const Cadena &Articulo::referencia() const { return referencia_; }
const Cadena &Articulo::titulo() const { return titulo_; }
const Fecha &Articulo::f_publi() const { return f_publi_; }
const double Articulo::precio() const { return precio_; }
double &Articulo::precio() { return precio_; }
const double Articulo::stock() const { return stock_; }
double &Articulo::stock() { return stock_; }

Articulo::~Articulo() {}

std::ostream &operator<<(std::ostream &out, Articulo &A)
{
    std::locale::global(std::locale("es_ES.UTF-8"));
    out << std::setprecision(2)
        << "[" << A.referencia() << "] \"" << A.titulo() << "\", " << A.f_publi().anno() << ". "
        << std::fixed << std::setprecision(2) << A.precio() << " €"
        << std::defaultfloat;
    std::locale::global(std::locale("C"));
    return out;
}