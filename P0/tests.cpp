#include <iostream>
#include <ctime>

//#include "fecha.hpp"
#include "cadena.hpp"

int main()
{
    Cadena a("Esta es una cadena de prueba");
    std::cout << a.substr(4, 6) << ".\n";
    std::cout << (a += Cadena("Hola")) << ".\n";
}