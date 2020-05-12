#ifndef USUARIO_PEDIDO_H
#define USUARIO_PEDIDO_H

#include <map>

#include "usuario.hpp"
#include "pedido.hpp"

class Usuario_Pedido
{
public:
    typedef std::set<Pedido *> Pedidos;

    void asocia(Usuario &u, Pedido &p);
    void asocia(Pedido &p, Usuario &u);
    Pedidos pedidos(Usuario &u);
    Usuario *cliente(Pedido &p);

private:
    typedef std::map<Usuario *, Pedidos> UP;
    typedef std::map<Pedido *, Usuario *> PU;

    UP usuario_pedidos;
    PU pedido_usuario;
};

#endif //USUARIO_PEDIDO_H