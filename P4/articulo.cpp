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
    out << paginas_ << " págs., " << stock_ << " unidades.";
}

Libro::~Libro() {}
Cederron::Cederron(const Autores &A, const Cadena &ref,
                   const Cadena &tit, const Fecha &f, double precio,
                   unsigned int mb, unsigned int stock) : ArticuloAlmacenable(A, ref, tit, f, precio, stock),
                                                          MB(mb) {}

void Cederron::impresion_especifica(std::ostream &out) const
{
    out << MB << " MB, " << stock_ << " unidades.";
}

Cederron::~Cederron() {}

LibroDigital::LibroDigital(const Autores &A, const Cadena &ref, const Cadena &tit,
                           const Fecha &f, double precio, const Fecha &exp) : Articulo(A, ref, tit, f, precio),
                                                                              expiracion(exp) {}

void LibroDigital::impresion_especifica(std::ostream &out) const
{
    out << "A la venta hasta el " << expiracion << ".";
}

LibroDigital::~LibroDigital() {}

std::ostream &operator<<(std::ostream &out, const Articulo &A)
{
    setlocale(LC_ALL, "");

    out << "[" << A.referencia() << "] \"" << A.titulo() << "\", de ";

    int numAutores = A.autores().size();
    for (auto a : A.autores())
    {
        out << a->apellidos();
        if (numAutores > 1)
        {
            out << ", ";
        }
        numAutores--;
    }

    out << ". " << A.f_publi().anno() << ". "
        << std::fixed << std::setprecision(2) << A.precio() << " €" << std::endl
        << "\t";

    A.impresion_especifica(out);
    return out;
}