#include <iostream>
#include <iomanip>

#include "pedido-articulo.hpp"
#include "pedido.hpp"
#include "articulo.hpp"

bool Pedido_Articulo::OrdenaPedidos::operator()(const Pedido *a, const Pedido *b) const
{
    return a->numero() < b->numero();
}

std::ostream &operator<<(std::ostream &out, const LineaPedido &lp)
{
    out << std::fixed << std::setprecision(2);
    out << lp.precio_venta() << " \u20AC\t" << std::setprecision(0) << lp.cantidad();
    return out;
}

void Pedido_Articulo::pedir(const Pedido &p, const Articulo &a, double precio, unsigned int cantidad)
{
    LineaPedido lp(a.precio(), cantidad);
    pedido_articulos[const_cast<Pedido *>(&p)].insert(std::make_pair(const_cast<Articulo *>(&a), lp));
    articulo_pedidos[const_cast<Articulo *>(&a)].insert(std::make_pair(const_cast<Pedido *>(&p), lp));
}

void Pedido_Articulo::pedir(const Articulo &a, const Pedido &p, double precio, unsigned int cantidad)
{
    pedir(p, a, precio, cantidad);
}

const Pedido_Articulo::ItemsPedido &Pedido_Articulo::detalle(const Pedido &p) const
{
    auto it = pedido_articulos.find(const_cast<Pedido *>(&p));
    if (it != pedido_articulos.end())
    {
        return it->second;
    }
    else
    {
        return {};
    }
}

const Pedido_Articulo::Pedidos &Pedido_Articulo::ventas(const Articulo &a) const
{
    auto it = articulo_pedidos.find(const_cast<Articulo *>(&a));
    if (it != articulo_pedidos.end())
    {
        return it->second;
    }
    else
    {
        return {};
    }
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream &out)
{
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream &out)
{
}

std::ostream &operator<<(std::ostream &out, const Pedido_Articulo::ItemsPedido &ip)
{
    double total = 0;
    out << "  PVP\tCantidad\t\tArticulo\n"
        << Cadena(30, '=') << std::endl;

    for (auto it : ip)
    {
        out << (*it.first);
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const Pedido_Articulo::Pedidos &p)
{
    double total = 0;

    out << "[Pedidos: " << p.size() << "]\n"
        << Cadena(30, '=') << std::endl
        << "  PVP\tCantidad\t\tFecha de venta\n"
        << Cadena(30, '=') << std::endl;

    return out;
}
