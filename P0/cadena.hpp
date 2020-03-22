#ifndef CADENA_HPP
#define CADENA_HPP

class Cadena
{
public:
    explicit Cadena(int t = 0, char c = ' ');
    Cadena(const char *cad);
    Cadena(const Cadena &C);

    
    ~Cadena();

private:
    char *s_;
    int tam_;
};

#endif //CADENA__HPP