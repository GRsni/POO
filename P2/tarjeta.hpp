#ifndef TARJETA_H
#define TARJETA_H

#include <iostream>
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

    class Incorrecto
    {
    public:
        Incorrecto(const Numero::Razon r) : razon_(r) {}
        const Numero::Razon razon() const { return razon_; }

    private:
        const Numero::Razon razon_;
    };

    Numero(const Cadena &c);
    operator const char *() const { return numero_.c_str(); };

    bool operator<(const Numero &N);

private:
    Cadena numero_;

    double num() const;
};

class Tarjeta
{

public:
    enum Tipo
    {
        Otro,
        VISA,
        MasterCard,
        Maestro,
        JCB,
        AmericanExpress
    };

    class Num_duplicado
    {
    public:
        Num_duplicado(const Numero num) : num_(num) {}

        const Numero que() const { return num_; }

    private:
        const Numero num_;
    };

    class Caducada
    {
    public:
        Caducada(Fecha f) : fecha(f) {}

        const Fecha cuando() const { return fecha; }

    private:
        const Fecha fecha;
    };

    class Desactivada;

    Tarjeta(Numero num, Usuario us, Fecha fecha, bool activa = true);
    Tarjeta(const Tarjeta &T) = delete;
    Tarjeta &operator=(const Tarjeta &T) = delete;

    const Numero numero() const { return numero_; }
    const Usuario *titular() const { return usuario_; }
    const Fecha caducidad() const { return caducidad_; }
    const bool activa() const { return activa_; }
    const bool activa(bool act = true);
    const Tipo tipo() const;

    void anula_titular();

private:
    const Numero numero_;
    const Usuario *usuario_;
    const Fecha caducidad_;
    bool activa_ = true;
};

std::ostream &operator<<(std::ostream &out, const Tarjeta &T);

#endif //TARJETA_H