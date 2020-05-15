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

const Pedido_Articulo::ItemsPedido &Pedido_Articulo::detalle(Pedido &p) const
{
    return pedido_articulos.find(&p)->second;
}

const Pedido_Articulo::Pedidos &Pedido_Articulo::ventas(Articulo &a) const
{
    return articulo_pedidos.find(&a)->second;
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream &out)
{
    double totalVentas = 0;

    for (auto pedido : pedido_articulos)
    {
        out << "Pedido núm. " << pedido.first->numero() << "\n"
            << "Cliente: " << pedido.first->tarjeta().titular()->id() << "\t\t"
            << "Fecha: " << pedido.first->fecha() << "\n\n";
        out << detalle(*pedido.first);
        for (auto itemsPed : detalle(*pedido.first))
        {
            totalVentas += itemsPed.second.precio_venta() * itemsPed.second.cantidad();
        }
    }

    out << "\nTOTAL VENTAS \t\t" << std::setw(2) << std::fixed << std::setprecision(2) << totalVentas << "\n";
    out << std::resetiosflags(std::ios::fixed);
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream &out)
{
    for (auto articulo : articulo_pedidos)
    {
        out << "Ventas de [" << articulo.first->referencia() << "] \"" << articulo.first->titulo() << "\"\n";
    }
}

std::ostream &operator<<(std::ostream &out, const Pedido_Articulo::ItemsPedido &ip)
{
    double total = 0;
    out << "  PVP\tCantidad\tArticulo\n"
        << Cadena(72, '=') << std::endl;

    out << std::setw(2) << std::setprecision(2);
    for (auto it : ip)
    {
        out << it.second << "\t\t"
            << "[" << it.first->referencia() << "] \""
            << it.first->titulo() << "\"" << std::endl;
        total += (*it.first).precio();
    }

    out << Cadena(72, '=') << "\n"
        << "Total: " << std::setw(2) << std::setprecision(2) << total << " \u20AC\n"
        << std::endl;
    out << std::resetiosflags(std::ios::fixed);
    return out;
}

std::ostream &operator<<(std::ostream &out, const Pedido_Articulo::Pedidos &ps)
{
    double total = 0;
    unsigned int items = 0;

    out << "[Pedidos: " << ps.size() << "]\n"
        << Cadena(72, '=') << std::endl
        << "  PVP\tCantidad\t\tFecha de venta\n"
        << Cadena(72, '=') << std::endl;

    for (auto it : ps)
    {
        out << it.second << "\t\t" << it.first->fecha() << "\n";
        total += it.second.precio_venta() * it.second.cantidad();
        items += it.second.cantidad();
    }

    out << std::setw(2) << std::setprecision(2) << total << " \u20AC \t" << items << std::endl;

    out << std::resetiosflags(std::ios::fixed);
    return out;
}
