#include <iostream>
#include <ctime>

#include "fecha.hpp"

int main()
{
    Fecha completa(2, 7, 5), mes(2, 7), dia(2), vacia;
    completa.imprimeFecha();
    mes.imprimeFecha();
    dia.imprimeFecha();
    vacia.imprimeFecha();
    Fecha cad2("01/"), cadena("03/02/1000");
    cadena.imprimeFecha();
    Fecha f("22/03");
    Fecha k("22-2-1965");
    Fecha j("03/02/99");
    j.imprimeFecha();

    std::cout << "Fin" << std::endl;
}