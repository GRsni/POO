#ifndef ARTICULO_H
#define ARTICULO_H

#include <iostream>
#include <map>
#include <set>

#include "cadena.hpp"
#include "fecha.hpp"

class Autor
{
public:
    Autor(const Cadena &nom,
          const Cadena &apel,
          const Cadena &dir) : nombre_(nom), apellidos_(apel), direccion_(dir) {}

    const Cadena &nombre() const { return nombre_; }
    const Cadena &apellidos() const { return apellidos_; }
    const Cadena &direccion() const { return direccion_; }

private:
    const Cadena nombre_, apellidos_, direccion_;
};

class Articulo
{
public:
    typedef std::set<Autor *> Autores;

    class Autores_vacios
    {
    };

    Articulo(const Autores &a, const Cadena &ref, const Cadena &tit,
             const Fecha &f, double precio);

    virtual const Cadena &referencia() const { return referencia_; };
    virtual const Cadena &titulo() const { return titulo_; };
    virtual const Fecha &f_publi() const { return f_publi_; };
    virtual double precio() const { return precio_; };
    virtual double &precio() { return precio_; };
    virtual const Autores &autores() const { return autores_; }

    virtual void
    impresion_especifica(std::ostream &out) const = 0;

    virtual ~Articulo();

private:
    const Autores autores_;
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha f_publi_;
    double precio_;
};

std::ostream &operator<<(std::ostream &in, const Articulo &A);

class ArticuloAlmacenable : public Articulo
{
public:
    ArticuloAlmacenable(const Autores &a, const Cadena &ref,
                        const Cadena &tit, const Fecha &f, double precio,
                        unsigned int stock = 0);

    const unsigned int stock() const { return stock_; };
    unsigned int &stock() { return stock_; };

    virtual ~ArticuloAlmacenable();

protected:
    unsigned int stock_;
};

class Libro : public ArticuloAlmacenable
{
public:
    Libro(const Autores &a, const Cadena &ref,
          const Cadena &tit, const Fecha &f, double precio,
          unsigned int pags, unsigned int stock = 0);

    inline unsigned int n_pag() const { return paginas_; }

    void impresion_especifica(std::ostream &out) const;

    ~Libro();

private:
    const unsigned int paginas_;
};

class Cederron : public ArticuloAlmacenable
{
public:
    Cederron(const Autores &a, const Cadena &ref,
             const Cadena &tit, const Fecha &f, double precio,
             unsigned int mb, unsigned int stock = 0);

    inline unsigned int tam() const { return MB; }

    void impresion_especifica(std::ostream &out) const;

    ~Cederron();

private:
    const unsigned int MB;
};

class LibroDigital : public Articulo
{
public:
    LibroDigital(const Autores &a, const Cadena &ref, const Cadena &tit,
                 const Fecha &f, double precio, const Fecha &exp);

    const Fecha &f_expir() const { return expiracion; }

    void impresion_especifica(std::ostream &out) const;

    ~LibroDigital();

private:
    const Fecha expiracion;
};

#endif //ARTICULO_H
