#include <map>
#include <set>

#include "usuario-pedido.hpp"
#include "usuario.hpp"
#include "pedido.hpp"

void Usuario_Pedido::asocia(Usuario &u, Pedido &p) noexcept
{
    usuario_pedidos[&u].insert(&p);
    pedido_usuario.insert(std::make_pair(&p, &u));
}

void Usuario_Pedido::asocia(Pedido &p, Usuario &u) noexcept
{
    asocia(u, p);
}

Usuario_Pedido::Pedidos &Usuario_Pedido::pedidos(Usuario &u) noexcept
{
    return usuario_pedidos.find(&u)->second;
}

Usuario *Usuario_Pedido::cliente(Pedido &p) noexcept
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