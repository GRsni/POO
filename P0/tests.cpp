#include <iostream>
#include <ctime>

#include "fecha.hpp"
#include "cadena.hpp"

int main()
{
    Cadena a = "Hola", b("Adios");
    std::cout << (a + b) << std::endl;
    std::cout << "Fin" << std::endl;
}