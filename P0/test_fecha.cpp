#include <iostream>
#include <ctime>

#include "fecha.hpp"

int main()
{
    Fecha a(2, 3, 5);
    std::cout << "Hoy es " << a.getDia() << "/" << a.getMes() << "/" << a.getAnno() << std::endl;
    std::cout << "Fin" << std::endl;
}