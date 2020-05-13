#ifndef PEDIDO_H
#define PEDIDO_H

#include <iostream>

#include "../P1/fecha.hpp"
#include "usuario.hpp"
#include "usuario-pedido.hpp"
#include "tarjeta.hpp"
#include "pedido-articulo.hpp"

class Pedido
{
public:
    class Vacio
    {
    public:
        Vacio(const Usuario &u) : usuario_(&u) {}
        const Usuario *usuario() const { return usuario_; }

    private:
        const Usuario *usuario_;
    };

    class Impostor
    {
    public:
        Impostor(const Usuario &u) : usuario_(&u) {}
        const Usuario *usuario() const { return usuario_; }

    private:
        const Usuario *usuario_;
    };

    class SinStock
    {
    public:
        SinStock(const Articulo &a) : articulo_(&a) {}
        const Articulo *articulo() const { return articulo_; }

    private:
        const Articulo *articulo_;
    };

    Pedido(Usuario_Pedido &up, Pedido_Articulo &pa, Usuario &u, const Tarjeta &t, const Fecha f = ());
    double numero() const { return numPed; }
    const Tarjeta &tarjeta() const { return *tarjeta_; }
    const Fecha &fecha() const { return *fecha_; }
    double total() const { return importe; }
    double n_total_pedidos() const { return pedidosTotales; }

private:
    double numPed;
    const Tarjeta *tarjeta_;
    const Fecha *fecha_;
    double importe;
    double pedidosTotales;

    static int contador_pedidos = 0;
};

std::ostream &operator<<(std::ostream &out, const Pedido &p);

#endif //PEDIDO_H