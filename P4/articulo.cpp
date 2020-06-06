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
        throw Articulo::Autores_vacios();
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
                                                      n_pag_(pags) {}

void Libro::impresion_especifica(std::ostream &out) const noexcept
{
    out << n_pag_ << " págs., " << stock_ << " unidades.";
}

Libro::~Libro() {}
Cederron::Cederron(const Autores &A, const Cadena &ref,
                   const Cadena &tit, const Fecha &f, double precio,
                   unsigned int mb, unsigned int stock) : ArticuloAlmacenable(A, ref, tit, f, precio, stock),
                                                          tam_(mb) {}

void Cederron::impresion_especifica(std::ostream &out) const noexcept
{
    out << tam_ << " MB, " << stock_ << " unidades.";
}

Cederron::~Cederron() {}

LibroDigital::LibroDigital(const Autores &A, const Cadena &ref, const Cadena &tit,
                           const Fecha &f, double precio, const Fecha &exp) : Articulo(A, ref, tit, f, precio),
                                                                              f_expir_(exp) {}

void LibroDigital::impresion_especifica(std::ostream &out) const noexcept
{
    out << "A la venta hasta el " << f_expir_ << ".";
}

LibroDigital::~LibroDigital() {}

std::ostream &operator<<(std::ostream &out, const Articulo &A)
{
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