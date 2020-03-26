#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstddef>

class Cadena
{
public:
    Cadena(int t = 0, char c = ' ');
    Cadena(const char *cad);
    Cadena(const Cadena &C);

    Cadena &operator=(const Cadena &C);
    inline operator const char *() const { return s_; };
    inline operator char *() { return s_; };
    inline size_t length() const { return tam_; };

    Cadena operator+=(const Cadena &B);

    const char operator[](size_t n) const;
    char &operator[](size_t n);
    const char at(size_t n) const;
    char &at(size_t n);

    Cadena substr(size_t index, size_t tam);

    ~Cadena();

private:
    char *s_;
    int tam_;
};

Cadena operator+(const Cadena &A, const Cadena &B);
bool operator==(const Cadena &A, const Cadena &B);
bool operator!=(const Cadena &A, const Cadena &B);
bool operator<(const Cadena &A, const Cadena &B);
bool operator>(const Cadena &A, const Cadena &B);
bool operator<=(const Cadena &A, const Cadena &B);
bool operator>=(const Cadena &A, const Cadena &B);

#endif //CADENA__HPP