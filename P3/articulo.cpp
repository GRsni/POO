#include <iostream>
#include <iomanip>

#include "articulo.hpp"

Articulo::Articulo(const Cadena &ref, const Cadena &C, const Fecha &F, double precio, unsigned int stock) : referencia_(ref),
                                                                                                            titulo_(C),
                                                                                                            f_publi_(F),
                                                                                                            precio_(precio),
                                                                                                            stock_(stock) {}

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