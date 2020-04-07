#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <cstddef>
#include <iterator>

class Cadena
{
public:
    // typedef std::reverse_iterator<iterator> reverse_iterator;
    //typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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
    friend std::ostream &operator<<(std::ostream &out, const Cadena &C) noexcept;
    friend std::istream &operator>>(std::istream &in, Cadena &C) noexcept;

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

#endif //CADENA__HPP