
#include <map>
#include <set>

#include "usuario-pedido.hpp"
#include "usuario.hpp"
#include "pedido.hpp"

void Usuario_Pedido::asocia(Usuario &u, Pedido &p)
{
    usuario_pedidos[&u].insert(&p);
    pedido_usuario[&p] = &u;
}

void Usuario_Pedido::asocia(Pedido &p, Usuario &u)
{
    asocia(u, p);
}

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario &u)
{
    auto set_pedidos = usuario_pedidos.find(&u);
    if (set_pedidos != usuario_pedidos.end())
    {
        return set_pedidos->second;
    }
    else
    {
        return Pedidos();
    }
}

Usuario *Usuario_Pedido::cliente(Pedido &p)
{
    auto usuario = pedido_usuario.find(&p);
    if (usuario != pedido_usuario.end())
    {
        return usuario->second;
    }
    else
    {
        return nullptr;
    }
}