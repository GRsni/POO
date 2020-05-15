#include <iostream>
#include <iomanip>

#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"

int Pedido::contador_pedidos = 0;

Pedido::Pedido(Usuario_Pedido &up,
               Pedido_Articulo &pa,
               Usuario &u,
               const Tarjeta &t,
               const Fecha &f) : numPed(Pedido::contador_pedidos + 1),
                                 tarjeta_(&t),
                                 fecha_(&f),
                                 importe(0)
{
    if (tarjeta_->titular() != &u)
    {
        throw Pedido::Impostor(u);
    }
    if (!tarjeta_->activa())
    {
        throw Tarjeta::Desactivada();
    }
    if (tarjeta_->caducidad() < f)
    {
        throw Tarjeta::Caducada(f);
    }
    if (u.n_articulos() == 0)
    {
        throw Pedido::Vacio(u);
    }
    for (auto a : u.compra())
    {
        if (a.second > a.first->stock())
        {
            throw Pedido::SinStock(*a.first);
        }
    }

    Usuario::Articulos carro = u.compra();

    for (auto c : carro)
    {
        pa.pedir(*this, *c.first, c.first->precio(), c.second);
        importe += c.first->precio();
        c.first->stock() -= c.second; //Se reduce el stock del articulo
        u.compra(*c.first, 0);
    }

    up.asocia(*this, u);

    contador_pedidos++;
}

std::ostream &operator<<(std::ostream &out, const Pedido &p)
{
    out << "Núm. pedido: \t" << p.numero() << "\n"
        << "Fecha: \t\t" << p.fecha() << "\n"
        << "Pagado con: \t" << p.tarjeta().tipo() << " n.º: " << p.tarjeta().numero() << "\n"
        << "Importe: \t" << std::fixed << std::setprecision(2) << p.total() << " \u20AC" << std::endl;
    out << std::resetiosflags(std::ios::fixed);
    return out;
}