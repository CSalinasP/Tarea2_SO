#include "lectores_escritores.hpp"

#include <stdexcept>

double obtener_tiempo_cpu_s() {
    // TODO: usar clock_gettime con CLOCK_PROCESS_CPUTIME_ID.
    throw std::logic_error("Medicion de CPU pendiente.");
}

ResumenEspera resumir_esperas(
    const std::vector<EstadisticasHebra>& /* estadisticas */
) {
    // TODO: calcular promedio por solicitud y máximo global.
    throw std::logic_error("Resumen de esperas pendiente.");
}

void acumular_fallos(
    const std::vector<EstadisticasHebra>& /* estadisticas */,
    ResultadoEjecucion& /* resultado */
) {
    // TODO: sumar intentos fallidos separados por causa.
    throw std::logic_error("Resumen de intentos fallidos pendiente.");
}

void imprimir_resultados(
    const Configuracion& /* config */,
    const ResultadoEjecucion& /* resultado */
) {
    // TODO: imprimir configuración, invariantes y estadísticas.
    // TODO: mostrar verificación de traza solo cuando corresponda.
    throw std::logic_error("Salida de resultados pendiente.");
}