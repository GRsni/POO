#include <iostream>
#include <iomanip>

#include "pedido-articulo.hpp"

std::ostream &operator<<(std::ostream &out, const LineaPedido &lp)
{
    out << std::fixed << std::setprecision(2);
    out << lp.precio_venta() << " \u20AC\t" << std::setprecision(0) << lp.cantidad();
    return out;
}
