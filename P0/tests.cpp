#include <iostream>
#include <ctime>

#include "fecha.hpp"
#include "cadena.hpp"

int main()
{
    Cadena a(5, 'A'), b(5), c, d = a, e("hola"), f(a), g = "hola";
    std::cout << "Tam: " << a.length() << " Cadena: " << a << "." << std::endl;
    std::cout << "Tam: " << b.length() << " Cadena: " << b << "." << std::endl;
    std::cout << "Tam: " << c.length() << " Cadena: " << c << "." << std::endl;
    std::cout << "Tam: " << d.length() << " Cadena: " << d << "." << std::endl;
    std::cout << "Tam: " << e.length() << " Cadena: " << e << "." << std::endl;
    std::cout << "Tam: " << f.length() << " Cadena: " << f << "." << std::endl;
    std::cout << "Tam: " << g.length() << " Cadena: " << g << "." << std::endl;

    a = g;
    std::puts(a);
    a = "C++11";
    std::puts(a);

    std::cout << "Fin" << std::endl;
}