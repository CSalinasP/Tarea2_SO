#include "lectores_escritores.hpp"

// Función para registrar la entrada de una hebra lectora en la sección crítica.
void registrar_entrada_lectora(Diagnostico& diagnostico) {
    long actuales = diagnostico.lectoras_activas.fetch_add(1, std::memory_order_relaxed) + 1;
    if (diagnostico.escritoras_activas.load(std::memory_order_relaxed) > 0) {
        diagnostico.violaciones_exclusion.fetch_add(1, std::memory_order_relaxed);
    }

    long prev_max = diagnostico.max_lectoras_simultaneas.load(std::memory_order_relaxed);
    while (actuales > prev_max &&
           !diagnostico.max_lectoras_simultaneas.compare_exchange_weak(
               prev_max, actuales, std::memory_order_relaxed)) {
    }
}

// Función para registrar la salida de una hebra lectora de la sección crítica.
void registrar_salida_lectora(Diagnostico& diagnostico) {
    diagnostico.lectoras_activas.fetch_sub(1, std::memory_order_relaxed);
}

// Función para registrar la entrada de una hebra escritora en la sección crítica.
void registrar_entrada_escritora(Diagnostico& diagnostico) {
    long esc = diagnostico.escritoras_activas.fetch_add(1, std::memory_order_relaxed) + 1;
    long lec = diagnostico.lectoras_activas.load(std::memory_order_relaxed);
    if (esc > 1 || lec > 0) {
        diagnostico.violaciones_exclusion.fetch_add(1, std::memory_order_relaxed);
    }
}

// Función para registrar la salida de una hebra escritora de la sección crítica.
void registrar_salida_escritora(Diagnostico& diagnostico) {
    diagnostico.escritoras_activas.fetch_sub(1, std::memory_order_relaxed);
}