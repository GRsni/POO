#ifndef PEDIDO_ARTICULO_H
#define PEDIDO_ARTICULO_H

#include <iostream>

#include "pedido.hpp"
#include "articulo.hpp"

class LineaPedido
{
public:
    explicit LineaPedido(double precio, double cantidad = 1) noexcept : precio_(precio),
                                                                        cantidad_(cantidad) {}

    const double precio_venta() const noexcept { return precio_; }
    const double cantidad() const noexcept { return cantidad_; }

private:
    const double precio_;
    const double cantidad_;
};

std::ostream &operator<<(std::ostream &out, const LineaPedido &lp);

class Pedido_Articulo
{
};

#endif //PEDIDO_ARTICULO_H