#include "lectores_escritores.hpp"

#include <chrono>
#include <memory>
#include <stdexcept>
#include <thread>

void simular_trabajo(long duracion_us) {
    if (duracion_us > 0) {
        std::this_thread::sleep_for(
            std::chrono::microseconds(duracion_us)
        );
    }
}

void ejecutar(const Configuracion& config) {
    std::unique_ptr<ControlRW> control;

    if (config.modo == Modo::Cond) {
        control = std::make_unique<MonitorRW>(
            config.politica, config.traza
        );
    } else {
        control = std::make_unique<ControlAtomicoRW>();
    }

    // TODO:
    // 1. Crear Registro y contadores atómicos de diagnóstico.
    Registro registro;
    Diagnostico diagnostico;
    std::vector<EstadisticasHebra> stats_lectoras(config.lectores);
    std::vector<EstadisticasHebra> stats_escritoras(config.escritores);
    // 2. Crear L lectoras y E escritoras con std::thread. 
    std::vector<std::thread> hebras;
    hebras.reserve(config.lectores + config.escritores);

    try{
        for (long i = 0; i < config.lectores; ++i) {
        hebras.emplace_back(
            ejecutar_lectora,
            static_cast<int>(i),
            std::cref(config),
            std::ref(*control),
            std::ref(registro),
            std::ref(diagnostico),
            std::ref(stats_lectoras[i])
        );
    }

    for (long i = 0; i < config.escritores; ++i) {
        hebras.emplace_back(
            ejecutar_escritora,
            static_cast<int>(config.lectores + i),
            std::cref(config),
            std::ref(*control),
            std::ref(registro),
            std::ref(diagnostico),
            std::ref(stats_escritoras[i])
        );
    }
}
catch (...) {
    for (auto& hebra : hebras) {
        if (hebra.joinable()) {
            hebra.join();
        }
    }
    throw;
}
for (auto& hebra : hebras) {
    if (hebra.joinable()) {
        hebra.join();
    }
}
    // 3. Asignar id_hebra al comenzar cada hebra.
    // 4. Repetir K operaciones usando entrar_*() y salir_*().
    // 5. Acceder al registro y simular trabajo dentro del intervalo.
    // 6. Hacer join(), incluso si falla la creación de alguna hebra.
    // 7. Comprobar invariantes y verificar la traza.
    // 8. Mostrar tiempos, esperas y resultados.
}