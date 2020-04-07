#include <iostream>

#include "cadena.hpp"

int main()
{
    Cadena c;
    std::cin >> c;
    std::cout << "palabra 1: " << c << "\nCaracter actual: "
              << static_cast<char>(std::cin.peek()) << "," << std::endl;
    std::cin >> c;
    std::cout << "palabra 2: " << c << std::endl;
}