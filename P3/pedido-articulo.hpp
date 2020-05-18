#ifndef PEDIDO_ARTICULO_H
#define PEDIDO_ARTICULO_H

#include <iostream>
#include <map>
#include <set>

#include "pedido.hpp"
#include "articulo.hpp"

class Pedido;
class Articulo;

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
    struct OrdenaArticulos
    {
        bool operator()(const Articulo *a, const Articulo *b) const
        {
            return a->referencia() < b->referencia();
        }
    };

    struct OrdenaPedidos
    {
        bool operator()(const Pedido *a, const Pedido *b) const;
    };

public:
    typedef std::map<Articulo *, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido *, LineaPedido, OrdenaPedidos> Pedidos;

    void pedir(Pedido &p, Articulo &a, double precio, unsigned int cantidad = 1);
    void pedir(Articulo &a, Pedido &p, double precio, unsigned int cantidad = 1);
    const ItemsPedido &detalle(Pedido &p) const;
    const Pedidos &ventas(Articulo &a) const;

    void mostrarDetallePedidos(std::ostream &out);
    void mostrarVentasArticulos(std::ostream &out);

private:
    std::map<Pedido *, ItemsPedido, OrdenaPedidos> pedido_articulos;
    std::map<Articulo *, Pedidos, OrdenaArticulos> articulo_pedidos;
};

std::ostream &operator<<(std::ostream &out, const Pedido_Articulo::ItemsPedido &ip);
std::ostream &operator<<(std::ostream &out, const Pedido_Articulo::Pedidos &ps);

#endif //PEDIDO_ARTICULO_H