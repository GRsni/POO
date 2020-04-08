#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <cstddef>
#include <iterator>

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
    char *c_str() { return s_; };
    size_t length() const noexcept { return tam_; };

    Cadena &operator+=(const Cadena &B) noexcept;

    typedef char *iterator;
    typedef const char *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin() noexcept { return &s_[0]; }
    iterator end() noexcept { return &s_[tam_]; }
    const iterator begin() const noexcept { return &s_[0]; }
    const iterator end() const noexcept { return &s_[tam_]; }

    const_iterator cbegin() noexcept { return &s_[0]; }
    const_iterator cend() noexcept { return &s_[tam_]; }
    const const_iterator cbegin() const noexcept { return &s_[0]; }
    const const_iterator cend() const noexcept { return &s_[tam_]; }

    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const reverse_iterator rbegin() const noexcept;
    const reverse_iterator rend() const noexcept;

    const_reverse_iterator crbegin() noexcept;
    const_reverse_iterator crend() noexcept;
    const const_reverse_iterator crbegin() const noexcept;
    const const_reverse_iterator crend() const noexcept;

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

inline Cadena::reverse_iterator Cadena::rbegin() noexcept
{
    return reverse_iterator(end());
}

inline Cadena::reverse_iterator Cadena::rend() noexcept
{
    return reverse_iterator(begin());
}

inline const Cadena::reverse_iterator Cadena::rbegin() const noexcept
{
    return reverse_iterator(end());
}

inline const Cadena::reverse_iterator Cadena::rend() const noexcept
{
    return reverse_iterator(begin());
}

inline Cadena::const_reverse_iterator Cadena::crbegin() noexcept
{
    return const_reverse_iterator(cend());
}

inline Cadena::const_reverse_iterator Cadena::crend() noexcept
{
    return const_reverse_iterator(cbegin());
}

inline const Cadena::const_reverse_iterator Cadena::crbegin() const noexcept
{
    return const_reverse_iterator(cend());
}

inline const Cadena::const_reverse_iterator Cadena::crend() const noexcept
{
    return const_reverse_iterator(cbegin());
}

#endif //CADENA__HPP