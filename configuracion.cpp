#include "lectores_escritores.hpp"

#include <charconv>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <system_error>

namespace {

long leer_numero(std::string_view texto, long minimo) {
    long valor = 0;

    const auto resultado = std::from_chars(
        texto.data(), texto.data() + texto.size(), valor
    );

    if (resultado.ec != std::errc{} ||
        resultado.ptr != texto.data() + texto.size() ||
        valor < minimo) {
        throw std::invalid_argument("Parametro numerico invalido.");
    }

    return valor;
}

} // namespace

Configuracion leer_argumentos(int argc, char* argv[]) {
    if (argc != 8 && argc != 9) {
        throw std::invalid_argument(
            "Uso: ./rw <cond|atomic> <lectores|escritores|fifo> "
            "<L> <E> <K> <dur_lec_us> <dur_esc_us> [notraza]"
        );
    }

    Configuracion config{};

    const std::string_view modo = argv[1];
    const std::string_view politica = argv[2];

    if (modo == "cond") {
        config.modo = Modo::Cond;
    } else if (modo == "atomic") {
        config.modo = Modo::Atomic;
    } else {
        throw std::invalid_argument("Modo invalido.");
    }

    if (politica == "lectores") {
        config.politica = Politica::Lectores;
    } else if (politica == "escritores") {
        config.politica = Politica::Escritores;
    } else if (politica == "fifo") {
        config.politica = Politica::Fifo;
    } else {
        throw std::invalid_argument("Politica invalida.");
    }

    if (config.modo == Modo::Atomic &&
        config.politica != Politica::Escritores) {
        throw std::invalid_argument(
            "El modo atomic solo admite prioridad de escritores."
        );
    }

    config.lectores = leer_numero(argv[3], 1);
    config.escritores = leer_numero(argv[4], 1);
    config.operaciones = leer_numero(argv[5], 1);
    config.duracion_lectura_us = leer_numero(argv[6], 0);
    config.duracion_escritura_us = leer_numero(argv[7], 0);

    if (config.lectores > 1000 ||
        config.escritores > 1000 ||
        config.lectores + config.escritores > 1000) {
        throw std::invalid_argument("Se permiten hasta 1000 hebras.");
    }

    const long limite = std::numeric_limits<long>::max();

    if (config.operaciones > limite / config.escritores / 2 ||
        config.operaciones > limite / (config.lectores + config.escritores)) {
        throw std::invalid_argument("Las operaciones exceden el rango de long.");
    }

    if (argc == 9) {
        if (std::string_view(argv[8]) != "notraza") {
            throw std::invalid_argument("Parametro opcional invalido.");
        }
        config.traza = false;
    }

    return config;
}