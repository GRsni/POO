#ifndef PEDIDO_H
#define PEDIDO_H

#include <iostream>

#include "fecha.hpp"
#include "usuario.hpp"
#include "usuario-pedido.hpp"
#include "tarjeta.hpp"
#include "pedido-articulo.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido
{
public:
    class Vacio
    {
    public:
        Vacio(const Usuario *u) : usuario_(u) {}
        const Usuario &usuario() const { return *usuario_; }

    private:
        const Usuario *usuario_;
    };

    class Impostor
    {
    public:
        Impostor(const Usuario *u) : usuario_(u) {}
        const Usuario &usuario() const { return *usuario_; }

    private:
        const Usuario *usuario_;
    };

    class SinStock
    {
    public:
        SinStock(const Articulo *a) : articulo_(a) {}
        const Articulo &articulo() const { return *articulo_; }

    private:
        const Articulo *articulo_;
    };

    Pedido(Usuario_Pedido &up, Pedido_Articulo &pa, Usuario &u, const Tarjeta &t, const Fecha &f = Fecha());
    Pedido(const Pedido &p) = delete;

    Pedido &operator=(const Pedido &p) = delete;

    unsigned int numero() const noexcept { return numPed; }
    const Tarjeta *tarjeta() const noexcept { return tarjeta_; }
    const Fecha fecha() const noexcept { return fecha_; }
    double total() const noexcept { return importe; }

    static unsigned int n_total_pedidos() noexcept { return contador_pedidos; }

private:
    unsigned int numPed;
    const Tarjeta *tarjeta_;
    Fecha fecha_;
    double importe;

    static unsigned int contador_pedidos;
};

std::ostream &operator<<(std::ostream &out, const Pedido &p);

#endif //PEDIDO_H