#include <iostream>
#include <unistd.h>
#include <random>
#include <cstddef>
#include <cstring>
#include <ctime>
#include <utility>

#include "usuario.hpp"

Clave::Incorrecta::Incorrecta(const Clave::Razon r) : razon_(r) {}

std::random_device Clave::rd;
std::uniform_int_distribution<std::size_t> Clave::dist(0, 63);

Clave::Clave(const char *cad)
{
    if (std::strlen(cad) < 5)
    {
        throw Clave::Incorrecta(Clave::CORTA);
    }
    const char *salt_ = salt();
    char *cifrada = crypt(cad, salt_);
    delete[] salt_;
    if (cifrada == nullptr)
    {
        throw Clave::Incorrecta(Clave::ERROR_CRYPT);
    }
    clave_ = Cadena(cifrada);
}

Clave::Clave(const Clave &C) : clave_(C.clave_) {}

Clave &Clave::operator=(const Clave &c)
{
    if (this != &c)
    {
        clave_ = c.clave_;
    }
    return *this;
}

const bool Clave::verifica(const char *cad) const
{
    return strcmp(crypt(cad, clave_.c_str()), clave_.c_str()) == 0;
}

/****************************METODOS PRIVADOS CLAVE***********************************/

const char *Clave::salt() const
{
    const Cadena simbolos = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    char *salt = new char[3]{0};

    salt[0] = simbolos[Clave::dist(Clave::rd)];
    salt[1] = simbolos[Clave::dist(Clave::rd)];

    return salt;
}

std::unordered_set<Cadena> Usuario::identificadores;

Usuario::Usuario(Cadena id, Cadena nom, Cadena apel, Cadena dir, Clave clave) : identificador_(id),
                                                                                nombre_(nom),
                                                                                apellidos_(apel),
                                                                                direccion_(dir),
                                                                                contrasenna_(clave)
{
    if (!Usuario::identificadores.insert(identificador_).second)
    {
        throw Usuario::Id_duplicado(identificador_);
    }
}

void Usuario::es_titular_de(Tarjeta &t)
{
    if (t.titular() == this)
    {
        tarjetas_.insert(std::make_pair(t.numero(), &t));
    }
}

void Usuario::no_es_titular_de(Tarjeta &t)
{
    t.anula_titular();
    tarjetas_.erase(t.numero());
}

void Usuario::compra(Articulo &a, int cantidad)
{
    if (cantidad == 0)
    {
        articulos_.erase(&a);
    }
    else
    {
        articulos_.insert(std::make_pair(&a, cantidad));
    }
}

Usuario::~Usuario()
{
    for (auto it = tarjetas_.begin(); it != tarjetas_.end(); ++it)
    {
        it->second->anula_titular();
    }
    Usuario::identificadores.erase(identificador_);
}

std::ostream &operator<<(std::ostream &out, const Usuario &u)
{
    out << u.id() << " [" << u.contrasenna_.clave() << "] " << u.nombre() << " " << u.apellidos() << std::endl;
    out << u.direccion() << "\nTarjetas:\n";
    if (u.tarjetas_.size() > 0)
    {
        for (auto it = u.tarjetas_.begin(); it != u.tarjetas_.end(); ++it)
        {
            out << *it->second;
        }
    }
    return out;
}

std::ostream &mostrar_carro(std::ostream &out, const Usuario &u)
{
    out << "Carrito de la compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]" << std::endl;
    out << " Cant.  Articulo" << std::endl;
    out << "=======================================================================" << std::endl;
    if (u.articulos_.size() > 0)
    {
        for (auto it = u.articulos_.begin(); it != u.articulos_.end(); ++it)
        {
            out << "   " << it->second << "       " << *it->first << std::endl;
        }
    }
    return out;
}
