#include <iostream>
#include <ctime>

#include "fecha.hpp"

int main()
{
    try
    {
        Fecha armagedon(30, 12, Fecha::AnnoMaximo), big_bang(2, 1, Fecha::AnnoMinimo);
        armagedon++; // Error, desbordamiento superior en armagedon
        armagedon.imprimeFecha();
        big_bang.imprimeFecha();
        //armagedon = big_bang + 1; // Error, desbordamiento inferior en la Fecha devuelta
    }
    catch (Fecha::Invalida e)
    {
        e.por_que();
    }

    std::cout << "Fin" << std::endl;
}