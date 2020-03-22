#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstddef>

class Cadena
{
public:
    explicit Cadena(int t = 0, char c = ' ');
    Cadena(const char *cad);
    Cadena(const Cadena &C);

    inline operator const char *() const { return s_; };
    inline size_t length() const { return tam_; };

    ~Cadena();

private:
    char *s_;
    int tam_;
};

#endif //CADENA__HPP