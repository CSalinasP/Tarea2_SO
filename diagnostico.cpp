#include "lectores_escritores.hpp"

#include <stdexcept>

void registrar_entrada_lectora(Diagnostico& /* diagnostico */) {
    // TODO: incrementar lectoras, comprobar exclusión y actualizar máximo.
    throw std::logic_error("Diagnostico de entrada lectora pendiente.");
}

void registrar_salida_lectora(Diagnostico& /* diagnostico */) {
    // TODO: descontar lectora activa.
    throw std::logic_error("Diagnostico de salida lectora pendiente.");
}

void registrar_entrada_escritora(Diagnostico& /* diagnostico */) {
    // TODO: incrementar escritoras y comprobar exclusión.
    throw std::logic_error("Diagnostico de entrada escritora pendiente.");
}

void registrar_salida_escritora(Diagnostico& /* diagnostico */) {
    // TODO: descontar escritora activa.
    throw std::logic_error("Diagnostico de salida escritora pendiente.");
}