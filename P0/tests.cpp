#include <iostream>
#include <ctime>

#include "fecha.hpp"
#include "cadena.hpp"

int main()
{
    Cadena a(5, 'A'), b(5), c, d = a, e("hola"), f(a), g = "hola";

    std::cout << "Fin" << std::endl;
}