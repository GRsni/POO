#include <iostream>

int main()
{
    std::string cadena = "Hola Mundo!";
    std::cout << cadena << std::endl;
    for (int i = 0; i < cadena.length(); i++)
    {
        std::cout << (int)cadena[i] << " ";
    }
}