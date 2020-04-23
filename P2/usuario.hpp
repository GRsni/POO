#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <random>
#include <cstddef>
#include <map>
#include <unordered_map>
#include <unordered_set>

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

    Usuario(Cadena id, Cadena nom, Cadena apel, Cadena dir, Clave clave);
    Usuario(const Usuario &U) = delete;
    Usuario &operator=(const Usuario &U) = delete;

    const Cadena id() const { return identificador_; }
    const Cadena nombre() const { return nombre_; }
    const Cadena apellidos() const { return apellidos_; }
    const Cadena direccion() const { return direccion_; }
    const Tarjetas tarjetas() const { return tarjetas_; }
    const Articulos compra() const { return articulos_; }
    void compra(Articulo &a, int cantidad = 1);

    void es_titular_de(Tarjeta &T);
    void no_es_titular_de(Tarjeta &T);

    size_t n_articulos() const { return articulos_.size(); }

    friend std::ostream &operator<<(std::ostream &out, const Usuario &u);

    friend std::ostream &mostrar_carro(std::ostream &out, const Usuario &u);

    ~Usuario();

private:
    const Cadena identificador_,
        nombre_,
        apellidos_,
        direccion_;
    const Clave contrasenna_;
    Tarjetas tarjetas_;
    Articulos articulos_;

    static std::unordered_set<Cadena> identificadores;
};

#endif //USUARIO_H