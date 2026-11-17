#include "lectores_escritores.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        const Configuracion config = leer_argumentos(argc, argv);
        ejecutar(config);

        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}