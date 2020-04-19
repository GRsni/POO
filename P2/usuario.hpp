#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <random>
#include <cstddef>
#include <map>
#include <unordered_map>

#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

class Tarjeta;
class Numero;

class Clave
{
public:
    enum Razon
    {
        CORTA,
        ERROR_CRYPT
    };

    class Incorrecta
    {
    public:
        Incorrecta(const Clave::Razon r);
        const Clave::Razon razon() const { return razon_; };

    private:
        const Clave::Razon razon_;
    };

    Clave(const char *cad);
    Clave(const Clave &C);

    Clave &operator=(const Clave &C);

    const Cadena clave() const { return clave_; };
    const bool verifica(const char *cad) const;

private:
    Cadena clave_;

    const char *salt() const;

    static std::random_device rd;
    static std::uniform_int_distribution<std::size_t> dist;
};

class Usuario
{
public:
    typedef std::map<Numero, Tarjeta *> Tarjetas;
    typedef std::unordered_map<Articulo *, unsigned int> Articulos;

    class Id_duplicado
    {
    public:
        Id_duplicado(const Cadena id) : idd_(id) {}

        const Cadena idd() const { return idd_; }

    private:
        const Cadena idd_;
    };

    Usuario(Cadena id, Cadena nom, Cadena apel, Cadena dir, Clave clave) : identificador_(id),
                                                                           nombre_(nom),
                                                                           apellidos_(apel),
                                                                           direccion_(dir),
                                                                           contraseña_(clave) {}

    Usuario(const Usuario &U) = delete;
    Usuario &operator=(const Usuario &U) = delete;

    const Cadena id() const { return identificador_; }
    const Cadena nombre() const { return nombre_; }
    const Cadena apellidos() const { return apellidos_; }
    const Cadena direccion() const { return direccion_; }
    //Tarjetas tarjetas() { return tarjetas; }
    const Articulos compra() const { return articulos; }

private:
    const Cadena identificador_,
        nombre_,
        apellidos_,
        direccion_;
    Clave contraseña_;
    Tarjetas tarjetas;
    Articulos articulos;
};

#endif //USUARIO_H