
#include <map>
#include <set>

#include "usuario-pedido.hpp"
#include "usuario.hpp"
#include "pedido.hpp"

void Usuario_Pedido::asocia(Usuario &u, Pedido &p)
{
    auto set_pedidos = usuario_pedidos.find(&u);
    if (set_pedidos != usuario_pedidos.end())
    {
        set_pedidos->second.insert(&p);
    }
    else
    {
        usuario_pedidos.insert(std::make_pair(&u, Pedidos{&p}));
    }

    pedido_usuario[&p] = &u;
}

void Usuario_Pedido::asocia(Pedido &p, Usuario &u)
{
    asocia(u, p);
}