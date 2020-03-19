#include <iostream>
#include <ctime>

#include "fecha.hpp"

int main()
{
    try
    {
        Fecha a(10, 10, 2010), b(11, 10, 2010), c(10, 11, 2010), hoy;
        std::cout << a << "<" << b << " " << (a < b) << std::endl;
        std::cout << a << ">" << b << " " << (a > b) << std::endl;
        std::cout << a << "<" << a << " " << (a < a) << std::endl;
        std::cout << a << ">" << a << " " << (a < a) << std::endl;
        std::cout << a << ">=" << b << " " << (a <= b) << std::endl;
        std::cout << a << ">" << c << " " << (a < c) << std::endl;
        std::cout << a << "<=" << b << " " << (a <= b) << std::endl;
        std::cout << Fecha() << "==" << hoy << " " << (Fecha() == hoy) << std::endl;
    }
    catch (Fecha::Invalida e)
    {
        e.por_que();
    }

    std::cout << "Fin" << std::endl;
}