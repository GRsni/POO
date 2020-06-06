#ifndef TARJETA_H
#define TARJETA_H

#include <iostream>
#include <set>
#include "usuario.hpp"
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

class Usuario;

bool luhn(const Cadena &numero);

class Numero
{
public:
    enum Razon
    {
        LONGITUD,
        DIGITOS,
        NO_VALIDO
    };

    struct EsBlanco
    {
        bool operator()(char c) const { return isspace(c); };
    };

    struct EsDigito
    {
        bool operator()(char c) const { return isdigit(c); };
    };

    class Incorrecto
    {
    public:
        Incorrecto(const Numero::Razon r) : razon_(r) {}
        const Numero::Razon razon() const noexcept { return razon_; }

    private:
        const Numero::Razon razon_;
    };

    Numero(const Cadena &c);
    operator const char *() const noexcept { return numero_.c_str(); };

private:
    Cadena numero_;
};

bool operator<(const Numero &a, const Numero &b);

class Tarjeta
{
    friend class Usuario;

public:
    static Cadena tipos[6];

    enum Tipo
    {
        AmericanExpress,
        JCB,
        VISA,
        Mastercard,
        Maestro,
        Otro
    };

    class Num_duplicado
    {
    public:
        Num_duplicado(const Numero num) : num_(num) {}

        const Numero que() const noexcept { return num_; }

    private:
        const Numero num_;
    };

    class Caducada
    {
    public:
        Caducada(const Fecha f) : fecha(f) {}

        const Fecha cuando() const noexcept { return fecha; }

    private:
        const Fecha fecha;
    };

    class Desactivada
    {
    };

    Tarjeta(const Numero &num, Usuario &us, const Fecha &fecha);
    Tarjeta(const Tarjeta &T) = delete;
    Tarjeta(const Tarjeta &&T) = delete;
    Tarjeta &operator=(const Tarjeta &T) = delete;
    Tarjeta &operator==(const Tarjeta &&T) = delete;

    const Numero &numero() const noexcept { return numero_; }
    const Usuario *titular() const noexcept { return titular_; }
    const Fecha &caducidad() const noexcept { return caducidad_; }
    bool activa() const noexcept { return activa_; }
    bool activa(bool act = true) noexcept;
    const Tipo tipo() const noexcept;

    ~Tarjeta();

private:
    const Numero numero_;
    const Usuario *titular_;
    const Fecha caducidad_;
    bool activa_ = true;

    static std::set<Numero> coleccion;

    //anula_titular() es privado para que solo la clase Usuario (amiga) tenga acceso
    void anula_titular() noexcept;
};

bool operator<(const Tarjeta &a, const Tarjeta &b) noexcept;

std::ostream &operator<<(std::ostream &out, const Tarjeta::Tipo t);
std::ostream &operator<<(std::ostream &out, const Tarjeta &T);

#endif //TARJETA_H