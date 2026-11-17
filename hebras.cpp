#include "lectores_escritores.hpp"

#include <stdexcept>

thread_local EstadisticasHebra* estadisticas_hebra_actual = nullptr;

void ejecutar_lectora(
    int /* id */,
    const Configuracion& /* config */,
    ControlRW& /* control */,
    Registro& /* registro */,
    Diagnostico& /* diagnostico */,
    EstadisticasHebra& /* estadisticas */
) {
    // TODO: asignar id_hebra y estadisticas_hebra_actual.
    // TODO: repetir K lecturas y medir cada espera.
    // TODO: actualizar diagnósticos dentro del intervalo admitido.
    // TODO: comprobar ambos campos del registro.
    // TODO: simular trabajo antes de salir.

    throw std::logic_error("Hebra lectora pendiente.");
}

void ejecutar_escritora(
    int /* id */,
    const Configuracion& /* config */,
    ControlRW& /* control */,
    Registro& /* registro */,
    Diagnostico& /* diagnostico */,
    EstadisticasHebra& /* estadisticas */
) {
    // TODO: asignar id_hebra y estadisticas_hebra_actual.
    // TODO: repetir K escrituras y medir cada espera.
    // TODO: actualizar diagnósticos dentro del intervalo admitido.
    // TODO: incrementar version y actualizar doble_version.
    // TODO: simular trabajo antes de salir.

    throw std::logic_error("Hebra escritora pendiente.");
}

// Estos marcadores no deben ejecutarse en std::thread todavía.
// Al implementar las hebras, gestionar sus errores dentro de ellas.