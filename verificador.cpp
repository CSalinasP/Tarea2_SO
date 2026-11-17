#include "lectores_escritores.hpp"

#include <stdexcept>

ResultadoTraza verificar_traza(
    const std::vector<AnotacionTraza>& /* traza */,
    Politica /* politica */
) {
    // TODO: reconstruir solicitudes pendientes y activas.
    // TODO: comprobar exclusión y reglas de la política.
    // TODO: contar evidencia e identificar la anotación inválida.
    throw std::logic_error("Verificador de traza pendiente.");
}

bool verificar_invariantes(
    const Configuracion& /* config */,
    const ResultadoEjecucion& /* resultado */
) {
    // TODO: comprobar version == E*K y doble_version == 2*E*K.
    // TODO: comprobar inconsistencias y violaciones de exclusión.
    throw std::logic_error("Verificacion de invariantes pendiente.");
}