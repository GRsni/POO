#ifndef PEDIDO_H
#define PEDIDO_H

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

    Pedido(Usuario_Pedido &up, Pedido_Articulo &pa, Usuario &u, Tarjeta &t, Fecha f = ());

private:
    double numPed;
    const Tarjeta *tarjeta_;
    Fecha fecha_;
    double importe;
    double pedidosTotales;
};

#endif //PEDIDO_H