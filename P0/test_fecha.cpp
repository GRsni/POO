#include <iostream>
#include <ctime>

#include "fecha.hpp"

int main()
{
    Fecha a(2, 3, 5);
    std::cout << "Hoy es " << a.dia << "/" << a.mes << "/" << a.anno << std::endl;
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm *tiempo_descompuesto = std::localtime(&tiempo_calendario);
    int dia = tiempo_descompuesto->tm_mday;
    int mes = tiempo_descompuesto->tm_mon + 1;
    int anno = tiempo_descompuesto->tm_year + 1900;
    std::cout << "Hoy es " << dia << "/" << mes << "/" << anno << std::endl;
}