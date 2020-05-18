#include <iostream>
#include <iomanip>

#include "pedido-articulo.hpp"
#include "pedido.hpp"
#include "articulo.hpp"

bool Pedido_Articulo::OrdenaPedidos::operator()(Pedido *a, Pedido *b) const
{
    return a->numero() < b->numero();
}

std::ostream &operator<<(std::ostream &out, const LineaPedido &lp)
{
    out << std::fixed << std::setprecision(2);
    out << lp.precio_venta() << " €\t" << std::fixed << std::setprecision(0) << lp.cantidad();
    return out;
}

void Pedido_Articulo::pedir(Pedido &p, Articulo &a, double precio, unsigned int cantidad)
{
    // LineaPedido lp(a.precio(), cantidad);
    pedido_articulos[&p].insert(std::make_pair(&a, LineaPedido(precio, cantidad)));
    articulo_pedidos[&a].insert(std::make_pair(&p, LineaPedido(precio, cantidad)));
}

void Pedido_Articulo::pedir(Articulo &a, Pedido &p, double precio, unsigned int cantidad)
{
    pedir(p, a, precio, cantidad);
}

const Pedido_Articulo::ItemsPedido &Pedido_Articulo::detalle(Pedido &p)
{
    static ItemsPedido items;
    auto it = pedido_articulos.find(&p);
    if (it != pedido_articulos.end())
    {
        return it->second;
    }
    else
    {
        return items;
    }
}

const Pedido_Articulo::Pedidos &Pedido_Articulo::ventas(Articulo &a)
{
    static Pedidos pedidos;
    auto it = articulo_pedidos.find(&a);
    if (it != articulo_pedidos.end())
    {
        return it->second;
    }
    else
    {
        return pedidos;
    }
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream &out)
{
    double totalVentas = 0;

    for (auto pedido : pedido_articulos)
    {
        out << "Pedido núm. " << pedido.first->numero() << std::endl
            << "Cliente: " << pedido.first->tarjeta()->titular()->id() << "\t\t"
            << "Fecha: " << pedido.first->fecha() << "\n\n";
        out << pedido.second;
        totalVentas += pedido.first->total();
    }
    out << "\nTOTAL VENTAS \t" << std::fixed << std::setprecision(2) << totalVentas << " €" << std::endl;
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream &out)
{
    for (auto articulo : articulo_pedidos)
    {
        out << "Ventas de [" << articulo.first->referencia() << "] \"" << articulo.first->titulo() << "\"\n\n";
        out << articulo.second << std::endl;
    }
}

std::ostream &operator<<(std::ostream &out, const Pedido_Articulo::ItemsPedido &ip)
{
    double total = 0;
    out << "  PVP\tCantidad\tArticulo" << std::endl;
    //    << "=================================================================" << std::endl;

    out << std::setw(2) << std::setprecision(2);
    for (auto it : ip)
    {
        out << it.second << "\t\t"
            << "[" << it.first->referencia() << "] \""
            << it.first->titulo() << "\"" << std::endl;
        total += it.second.cantidad() * it.second.precio_venta();
    }

    //out << "=================================================================" << std::endl
    out << "Total: " << std::fixed << std::setprecision(2) << total << " \u20AC" << std::endl
        << std::endl;

    return out;
}

std::ostream &operator<<(std::ostream &out, const Pedido_Articulo::Pedidos &ps)
{
    double total = 0;
    unsigned int items = 0;

    out << "[Pedidos: " << ps.size() << "]" << std::endl
        << "=================================================================" << std::endl
        << "  PVP\tCantidad\t\tFecha de venta" << std::endl
        << "=================================================================" << std::endl;

    for (auto it : ps)
    {
        out << it.second << "\t\t" << it.first->fecha() << std::endl;
        total += it.second.precio_venta() * it.second.cantidad();
        items += it.second.cantidad();
    }
    out << "=================================================================" << std::endl
        << std::setprecision(2) << total << " \u20AC \t" << items << std::endl;

    return out;
}
