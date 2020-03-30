#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstddef>

class Cadena
{
public:
    Cadena(size_t t = 0, char c = ' ');
    Cadena(const char *cad);
    Cadena(const Cadena &C);

    Cadena &operator=(const Cadena &C);
    operator const char *() const { return s_; };
    operator char *() { return s_; };
    inline size_t length() const { return tam_; };

    Cadena &operator+=(const Cadena &B);

    const char operator[](size_t n) const;
    char &operator[](size_t n);
    char at(size_t n) const;
    char &at(size_t n);

    Cadena substr(size_t index, size_t tam) const;

    ~Cadena();

private:
    char *s_;
    size_t tam_;
};

Cadena operator+(const Cadena &A, const Cadena &B);
bool operator==(const Cadena &A, const Cadena &B);
bool operator!=(const Cadena &A, const Cadena &B);
bool operator<(const Cadena &A, const Cadena &B);
bool operator>(const Cadena &A, const Cadena &B);
bool operator<=(const Cadena &A, const Cadena &B);
bool operator>=(const Cadena &A, const Cadena &B);

#endif //CADENA__HPP