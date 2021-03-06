#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <cstddef>
#include <iterator>
#include <string>
#include <system_error>

class Cadena
{
public:
    explicit Cadena(size_t t = 0, char c = ' ') noexcept;
    Cadena(const char *cad) noexcept;
    Cadena(const Cadena &C) noexcept;
    Cadena(Cadena &&C) noexcept;

    Cadena &operator=(const Cadena &C) noexcept;
    Cadena &operator=(Cadena &&C) noexcept;

    const char *c_str() const noexcept { return s_; };
    char *c_str() noexcept { return s_; };
    size_t length() const noexcept { return tam_; };

    Cadena &operator+=(const Cadena &B) noexcept;

    typedef char *iterator;
    typedef const char *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin() noexcept { return &s_[0]; }
    iterator end() noexcept { return &s_[tam_]; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); };
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); };

    const_iterator begin() const noexcept { return &s_[0]; }
    const_iterator end() const noexcept { return &s_[tam_]; }
    const_iterator cbegin() const noexcept { return const_iterator(begin()); }
    const_iterator cend() const noexcept { return const_iterator(end()); }

    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); };
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); };
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); };
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); };

    const char operator[](size_t n) const noexcept { return s_[n]; }
    char &operator[](size_t n) noexcept { return s_[n]; }
    const char at(size_t n) const;
    char &at(size_t n);

    Cadena substr(size_t index, size_t tam) const;

    ~Cadena();

private:
    char *s_;
    size_t tam_;
};

Cadena operator+(const Cadena &A, const Cadena &B) noexcept;
bool operator==(const Cadena &A, const Cadena &B) noexcept;
bool operator!=(const Cadena &A, const Cadena &B) noexcept;
bool operator<(const Cadena &A, const Cadena &B) noexcept;
bool operator>(const Cadena &A, const Cadena &B) noexcept;
bool operator<=(const Cadena &A, const Cadena &B) noexcept;
bool operator>=(const Cadena &A, const Cadena &B) noexcept;

std::ostream &operator<<(std::ostream &out, const Cadena &C) noexcept;
std::istream &operator>>(std::istream &in, Cadena &C) noexcept;

// Para P2 y ss.// Especialización de la plantilla hash<T>para definir la9
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].
namespace std
{           // Estaremos dentro del espacio de nombres std
template <> // Es una especialización de una plantilla para Cadena
struct hash<Cadena>
{                                              // Es una clase con solo un operador publico
    size_t operator()(const Cadena &cad) const // El operador función
    {
        hash<string> hs;             // Creamos un objeto hash de string
        const char *p = cad.c_str(); // Obtenemos la cadena de la Cadena
        string s(p);                 // Creamos un string desde una cadena
        size_t res = hs(s);          // El hash del string. Como hs.operator()(s);
        return res;                  // Devolvemos el hash del string
    }
};
} // namespace std

#endif //CADENA__HPP