#include "lectores_escritores.hpp"

#include <stdexcept>

thread_local EstadisticasHebra* estadisticas_hebra_actual = nullptr;

void ejecutar_lectora(
    int id,
    const Configuracion& config,
    ControlRW& control,
    Registro& registro,
    Diagnostico& diagnostico,
    EstadisticasHebra& estadisticas
) {
    // TODO: asignar id_hebra y estadisticas_hebra_actual.
    id_hebra = id;
    estadisticas_hebra_actual = &estadisticas;
    // TODO: repetir K lecturas y medir cada espera.
    for (long k = 0; k < config.operaciones; ++k) {
        control.entrar_lectura();
        registrar_entrada_lectora(diagnostico);

        long v = registro.version;
        long dv = registro.doble_version;
        if (dv != 2 * v) {
            diagnostico.inconsistencias.fetch_add(1, std::memory_order_relaxed);
        }

        simular_trabajo(config.duracion_lectura_us);
        registrar_salida_lectora(diagnostico);

        control.salir_lectura();
    }
    // TODO: actualizar diagnósticos dentro del intervalo admitido.
    // TODO: comprobar ambos campos del registro.
    // TODO: simular trabajo antes de salir.
}

void ejecutar_escritora(
    int id,
    const Configuracion& config,
    ControlRW& control,
    Registro& registro,
    Diagnostico& diagnostico,
    EstadisticasHebra& estadisticas
) {
    // TODO: asignar id_hebra y estadisticas_hebra_actual.
    id_hebra = id;
    estadisticas_hebra_actual = &estadisticas;
    // TODO: repetir K escrituras y medir cada espera.
    for (long k = 0; k < config.operaciones; ++k) {
        control.entrar_escritura();
        registrar_entrada_escritora(diagnostico);

        registro.version++;
        registro.doble_version = 2 * registro.version;

        simular_trabajo(config.duracion_escritura_us);
        registrar_salida_escritora(diagnostico);

        control.salir_escritura();
    }
    // TODO: actualizar diagnósticos dentro del intervalo admitido.
    // TODO: incrementar version y actualizar doble_version.
    // TODO: simular trabajo antes de salir.
}

// Estos marcadores no deben ejecutarse en std::thread todavía.
// Al implementar las hebras, gestionar sus errores dentro de ellas.