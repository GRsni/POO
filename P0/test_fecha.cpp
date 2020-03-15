#include <iostream>
#include <ctime>

#include "fecha.hpp"

int main()
{
    try
    {
        Fecha hoy;
        hoy.imprimeFecha();
        hoy += 100;
        hoy.imprimeFecha();
        hoy -= 100;
        hoy.imprimeFecha();
        ++hoy;
        hoy.imprimeFecha();
        --hoy;
        hoy.imprimeFecha();
        hoy++;
        hoy.imprimeFecha();
        hoy--;
        hoy.imprimeFecha();
    }
    catch (Fecha::Invalida i)
    {
        i.por_que();
    }
    try
    {
        Fecha armagedon(31, 12, Fecha::AnnoMaximo),
            big_bang(1, 1, Fecha::AnnoMinimo);
        // armagedon++;  // Error, desbordamiento superior en armagedon
        big_bang - 3; // Error, desbordamiento inferior en la Fecha devuelta
    }
    catch (Fecha::Invalida e)
    {
        e.por_que();
    }

    std::cout << "Fin" << std::endl;
}