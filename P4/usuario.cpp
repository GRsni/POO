#include <iostream>
#include <unistd.h>
#include <random>
#include <cstddef>
#include <cstring>
#include <utility>
#include <iomanip>

#include "usuario.hpp"

Clave::Clave(const char *cad)
{
    if (std::strlen(cad) < 5)
    {
        throw Clave::Incorrecta(Clave::CORTA);
    }

    const char *simbolos = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    char *salt = new char[2];

    static std::random_device rd;
    static std::uniform_int_distribution<size_t> dist(0, 63);

    salt[0] = simbolos[dist(rd)];
    salt[1] = simbolos[dist(rd)];
    char *cifrada = crypt(cad, salt);

    delete[] salt;

    if (cifrada == nullptr)
    {
        throw Clave::Incorrecta(Clave::ERROR_CRYPT);
    }
    clave_ = Cadena(cifrada);
}

Clave::Clave(const Clave &C) noexcept : clave_(C.clave_) {}

Clave &Clave::operator=(const Clave &c) noexcept
{
    if (this != &c)
    {
        clave_ = c.clave_;
    }
    return *this;
}

const bool Clave::verifica(const char *cad) const
{
    const char *prueba = crypt(cad, clave_.c_str());
    if (prueba == nullptr)
    {
        throw Clave::Incorrecta(Clave::ERROR_CRYPT);
    }
    return strcmp(prueba, clave_.c_str()) == 0;
}

/*************************************METODOS USUARIO************************************/

std::unordered_set<Cadena> Usuario::identificadores;

Usuario::Usuario(const Cadena &id,
                 const Cadena &nom,
                 const Cadena &apel,
                 const Cadena &dir,
                 Clave clave) : identificador_(id),
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

void Usuario::es_titular_de(Tarjeta &t) noexcept
{
    if (t.titular() == this)
    {
        tarjetas_.insert(std::make_pair(t.numero(), &t));
    }
}

void Usuario::no_es_titular_de(Tarjeta &t) noexcept
{
    auto it = tarjetas_.find(t.numero());
    if (it != tarjetas_.end())
    {
        t.anula_titular();
        tarjetas_.erase(it);
    }
}

void Usuario::compra(Articulo &a, int cantidad) noexcept
{
    if (cantidad == 0)
    {
        articulos_.erase(&a);
    }
    else
    {
        articulos_[&a] = cantidad;
    }
}

Usuario::~Usuario() noexcept
{
    for (auto it = tarjetas_.begin(); it != tarjetas_.end(); ++it)
    {
        it->second->anula_titular();
    }
    Usuario::identificadores.erase(identificador_);
}

std::ostream &operator<<(std::ostream &out, const Usuario &u) noexcept
{
    //out.imbue(std::locale(std::locale("es_ES.UTF-8"), new sin_separador()));
    out << u.id() << " [" << u.contrasenna_.clave() << "] " << u.nombre()
        << " " << u.apellidos() << std::endl;
    out << u.direccion() << "\nTarjetas:\n";
    if (u.tarjetas_.size() > 0)
    {
        for (auto it = u.tarjetas_.begin(); it != u.tarjetas_.end(); ++it)
        {
            out << *it->second;
        }
    }
    out << std::endl;
    return out;
}

std::ostream &mostrar_carro(std::ostream &out, const Usuario &u) noexcept
{
    setlocale(LC_ALL, "");

    out << "Carrito de la compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]" << std::endl
        << " Cant.\tArticulo" << std::endl
        << "=================================================================" << std::endl;
    for (auto it = u.articulos_.begin(); it != u.articulos_.end(); ++it)
    {
        out << "   " << it->second << "\t"
            << "[" << it->first->referencia() << "] \"" << it->first->titulo()
            << "\", " << it->first->f_publi().anno() << ". " << std::setprecision(2)
            << std::fixed << it->first->precio() << " €" << std::endl;
    }

    out << std::endl;
    return out;
}
