#include <iostream>
#include <iomanip>

#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"

unsigned int Pedido::contador_pedidos = 0;

Pedido::Pedido(Usuario_Pedido &up,
               Pedido_Articulo &pa,
               Usuario &u,
               const Tarjeta &t,
               const Fecha &f) : numPed(contador_pedidos + 1),
                                 tarjeta_(&t),
                                 fecha_(f),
                                 importe(0)
{
    if (t.titular() != &u)
    {
        throw Pedido::Impostor(&u);
    }
    if (!t.activa())
    {
        throw Tarjeta::Desactivada();
    }
    if (t.caducidad() < f)
    {
        throw Tarjeta::Caducada(t.caducidad());
    }
    if (u.n_articulos() == 0)
    {
        throw Pedido::Vacio(&u);
    }

    for (auto a : u.compra())
    {
        if (ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable *>(a.first))
        {
            if (a.second > aa->stock())
            {
                const_cast<Usuario::Articulos &>(u.compra()).clear();
                throw Pedido::SinStock(a.first);
            }
        }
    }

    for (auto c : u.compra())
    {

        if (LibroDigital *ld = dynamic_cast<LibroDigital *>(c.first))
        {
            if (ld->f_expir() < fecha_)
            {
            }
        }
        else
        {
            pa.pedir(*this, *c.first, c.first->precio(), c.second);
            importe += c.first->precio() * c.second;
            if (ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable *>(c.first))
            {
                aa->stock() -= c.second; //Se reduce el stock del articulo
            }
        }
    }
    if (importe == 0)
    {
        throw Pedido::Vacio(&u);
    }

    const_cast<Usuario::Articulos &>(u.compra()).clear();

    up.asocia(*this, u);

    contador_pedidos++;
}

std::ostream &operator<<(std::ostream &out, const Pedido &p)
{
    out.imbue(std::locale("es_ES.UTF-8"));
    out << "Núm. pedido: \t" << p.numero() << std::endl
        << "Fecha: \t\t" << p.fecha() << std::endl
        << "Pagado con: \t" << p.tarjeta()->tipo() << " n.º: " << p.tarjeta()->numero() << std::endl
        << "Importe: \t" << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl;
    return out;
}
