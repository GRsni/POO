#include <iostream>
#include <iomanip>

#include "articulo.hpp"

Articulo::Articulo(const Autores &A,
                   const Cadena &ref,
                   const Cadena &tit,
                   const Fecha &F,
                   double precio) : autores_(A),
                                    referencia_(ref),
                                    titulo_(tit),
                                    f_publi_(F),
                                    precio_(precio)
{

    if (autores_.empty())
        throw Autores_vacios();
}

Articulo::~Articulo() {}

ArticuloAlmacenable::ArticuloAlmacenable(const Autores &A,
                                         const Cadena &ref,
                                         const Cadena &tit,
                                         const Fecha &f,
                                         double precio,
                                         unsigned int stock) : Articulo(A, ref, tit, f, precio),
                                                               stock_(stock) {}

ArticuloAlmacenable::~ArticuloAlmacenable() {}

Libro::Libro(const Autores &A, const Cadena &ref,
             const Cadena &tit, const Fecha &f, double precio,
             unsigned int pags, unsigned int stock) : ArticuloAlmacenable(A, ref, tit, f, precio, stock),
                                                      paginas_(pags) {}

void Libro::impresion_especifica(std::ostream &out) const
{
    out.imbue(std::locale("es_ES.UTF-8"));
    out << "\t\t" << paginas_ << " págs., " << stock() << " unidades." << std::endl;
}

Libro::~Libro() {}
Cederron::Cederron(const Autores &A, const Cadena &ref,
                   const Cadena &tit, const Fecha &f, double precio,
                   unsigned int mb, unsigned int stock) : ArticuloAlmacenable(A, ref, tit, f, precio, stock),
                                                          MB(mb) {}

void Cederron::impresion_especifica(std::ostream &out) const
{
    out.imbue(std::locale("es_ES.UTF-8"));
    out << "\t\t" << MB << " MB, " << stock() << " unidades." << std::endl;
}

Cederron::~Cederron() {}

LibroDigital::LibroDigital(const Autores &A, const Cadena &ref, const Cadena &tit,
                           const Fecha &f, double precio, const Fecha &exp) : Articulo(A, ref, tit, f, precio),
                                                                              expiracion(exp) {}

void LibroDigital::impresion_especifica(std::ostream &out) const
{
    out.imbue(std::locale("es_ES.UTF-8"));
    out << "\t\tA la venta hasta el " << expiracion << "." << std::endl;
}

LibroDigital::~LibroDigital() {}

std::ostream &operator<<(std::ostream &out, const Articulo &A)
{
    out.imbue(std::locale("es_ES.UTF-8"));
    out << std::setprecision(2)
        << "[" << A.referencia() << "] \"" << A.titulo() << "\", de ";
    for (auto a : A.autores())
    {
        out << a->apellidos() << ", ";
    }

    out << ". " << A.f_publi().anno() << ". "
        << std::fixed << std::setprecision(2) << A.precio() << " €"
        << std::defaultfloat << std::endl;

    A.impresion_especifica(out);

    std::locale::global(std::locale("C"));
    return out;
}