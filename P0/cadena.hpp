#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstddef>

class Cadena
{
public:
    explicit Cadena(size_t t = 0, char c = ' ') noexcept;
    Cadena(const char *cad) noexcept;
    Cadena(const Cadena &C) noexcept;

    Cadena &operator=(const Cadena &C) noexcept;
    operator const char *() const noexcept { return s_; };
    //operator char *() { return s_; };
    size_t length() const noexcept { return tam_; };

    Cadena &operator+=(const Cadena &B) noexcept;

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