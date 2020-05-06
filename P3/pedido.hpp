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
    Pedido(Usuario_Pedido &up, Pedido_Articulo &pa, Usuario &u, Tarjeta &t, Fecha f = ());

private:
    double numPed;
    const Tarjeta *tarjeta_;
    Fecha fecha_;
    double importe;
    double pedidosTotales;
};

#endif //PEDIDO_H