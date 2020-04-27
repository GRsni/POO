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
        Incorrecta(const Clave::Razon r) noexcept;
        const Clave::Razon razon() const noexcept { return razon_; };

    private:
        const Clave::Razon razon_;
    };

    Clave(const char *cad);
    Clave(const Clave &C) noexcept;

    Clave &operator=(const Clave &C) noexcept;

    const Cadena clave() const noexcept { return clave_; };
    const bool verifica(const char *cad) const noexcept;

private:
    Cadena clave_;

    const char *salt() const noexcept;

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

        const Cadena idd() const noexcept { return idd_; }

    private:
        const Cadena idd_;
    };

    Usuario(const Cadena &id, const Cadena &nom, const Cadena &apel, const Cadena &dir, const Clave &clave);
    Usuario(const Usuario &U) = delete;
    Usuario &operator=(const Usuario &U) = delete;

    const Cadena id() const noexcept { return identificador_; }
    const Cadena nombre() const noexcept { return nombre_; }
    const Cadena apellidos() const noexcept { return apellidos_; }
    const Cadena direccion() const noexcept { return direccion_; }
    const Tarjetas &tarjetas() const noexcept { return tarjetas_; }
    const Articulos compra() const noexcept { return articulos_; }
    void compra(Articulo &a, int cantidad = 1) noexcept;

    void es_titular_de(Tarjeta &T) noexcept;
    void no_es_titular_de(Tarjeta &T) noexcept;

    size_t n_articulos() const noexcept { return articulos_.size(); }

    friend std::ostream &operator<<(std::ostream &out, const Usuario &u) noexcept;

    friend std::ostream &mostrar_carro(std::ostream &out, const Usuario &u) noexcept;

    ~Usuario() noexcept;

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