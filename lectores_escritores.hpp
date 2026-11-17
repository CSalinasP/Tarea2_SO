#ifndef LECTORES_ESCRITORES_HPP
#define LECTORES_ESCRITORES_HPP

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

// Modos y políticas.

enum class Modo {
    Cond,
    Atomic
};

enum class Politica {
    Lectores,
    Escritores,
    Fifo
};

enum class Tipo {
    Lectora,
    Escritora
};

enum class Accion {
    Pide,
    Entra,
    Sale
};

// Configuración del programa.

struct Configuracion {
    Modo modo;
    Politica politica;

    long lectores;
    long escritores;
    long operaciones;

    long duracion_lectura_us;
    long duracion_escritura_us;

    bool traza = true;
};

// Registro compartido.

struct Registro {
    long version = 0;
    long doble_version = 0;
};

// Traza de admisión.

struct AnotacionTraza {
    int hebra;
    Tipo tipo;
    Accion accion;
    long turno;
};

extern thread_local int id_hebra;

// Interfaz común de sincronización.

class ControlRW {
public:
    virtual ~ControlRW() = default;

    virtual void entrar_lectura() = 0;
    virtual void salir_lectura() = 0;

    virtual void entrar_escritura() = 0;
    virtual void salir_escritura() = 0;
};

// Monitor con mutex y variables de condición.

class MonitorRW : public ControlRW {
public:
    explicit MonitorRW(
        Politica politica,
        bool registrar_traza = true
    );

    void entrar_lectura() override;
    void salir_lectura() override;

    void entrar_escritura() override;
    void salir_escritura() override;

    std::vector<AnotacionTraza> obtener_traza();

private:
    Politica politica;
    bool registrar_traza;

    std::mutex m;
    std::condition_variable lectores_cv;
    std::condition_variable escritores_cv;

    std::vector<AnotacionTraza> traza;

    // TODO: definir contadores, banderas y turnos de admisión.
};

// Control con operaciones atómicas y CAS.

class ControlAtomicoRW : public ControlRW {
public:
    void entrar_lectura() override;
    void salir_lectura() override;

    void entrar_escritura() override;
    void salir_escritura() override;

private:
    static_assert(
        std::atomic<std::uint64_t>::is_always_lock_free,
        "Se requiere un atomic<uint64_t> siempre lock-free."
    );

    std::atomic<std::uint64_t> estado{0};

    // TODO: definir y documentar los campos de bits de estado.
};

// Diagnósticos independientes del estado de admisión.

struct Diagnostico {
    std::atomic<long> lectoras_activas{0};
    std::atomic<long> escritoras_activas{0};

    std::atomic<long> max_lectoras_simultaneas{0};

    std::atomic<long> inconsistencias{0};
    std::atomic<long> violaciones_exclusion{0};
};

// Cada hebra modifica únicamente su propia instancia.

struct EstadisticasHebra {
    long operaciones_completadas = 0;

    double espera_total_us = 0;
    double espera_maxima_us = 0;

    long fallos_recurso_ocupado = 0;
    long fallos_escritoras_esperando = 0;
    long fallos_cas = 0;
};

// Permite que el control atómico registre los intentos fallidos
// en las estadísticas de la hebra que lo llama.

extern thread_local EstadisticasHebra* estadisticas_hebra_actual;

// Resultados.

struct ResumenEspera {
    double promedio_us = 0;
    double maximo_us = 0;
};

struct ResultadoTraza {
    bool politica_ok = false;
    long evidencia = 0;

    long indice_error = -1;
    std::string regla_incumplida;
};

struct ResultadoEjecucion {
    long version_final = 0;
    long doble_version_final = 0;

    long inconsistencias = 0;
    long violaciones_exclusion = 0;
    long max_lectoras_simultaneas = 0;

    double tiempo_pared_s = 0;
    double tiempo_cpu_s = 0;

    ResumenEspera espera_lectoras;
    ResumenEspera espera_escritoras;

    long fallos_recurso_ocupado = 0;
    long fallos_escritoras_esperando = 0;
    long fallos_cas = 0;

    bool correcto = false;
    bool traza_verificada = false;

    ResultadoTraza resultado_traza;
};

// configuracion.cpp

Configuracion leer_argumentos(int argc, char* argv[]);

// simulacion.cpp

void simular_trabajo(long duracion_us);

void ejecutar(const Configuracion& config);

// hebras.cpp

void ejecutar_lectora(
    int id,
    const Configuracion& config,
    ControlRW& control,
    Registro& registro,
    Diagnostico& diagnostico,
    EstadisticasHebra& estadisticas
);

void ejecutar_escritora(
    int id,
    const Configuracion& config,
    ControlRW& control,
    Registro& registro,
    Diagnostico& diagnostico,
    EstadisticasHebra& estadisticas
);

// diagnostico.cpp

void registrar_entrada_lectora(Diagnostico& diagnostico);

void registrar_salida_lectora(Diagnostico& diagnostico);

void registrar_entrada_escritora(Diagnostico& diagnostico);

void registrar_salida_escritora(Diagnostico& diagnostico);

// verificador.cpp

ResultadoTraza verificar_traza(
    const std::vector<AnotacionTraza>& traza,
    Politica politica
);

bool verificar_invariantes(
    const Configuracion& config,
    const ResultadoEjecucion& resultado
);

// mediciones.cpp

double obtener_tiempo_cpu_s();

ResumenEspera resumir_esperas(
    const std::vector<EstadisticasHebra>& estadisticas
);

void acumular_fallos(
    const std::vector<EstadisticasHebra>& estadisticas,
    ResultadoEjecucion& resultado
);

void imprimir_resultados(
    const Configuracion& config,
    const ResultadoEjecucion& resultado
);

#endif // LECTORES_ESCRITORES_HPP