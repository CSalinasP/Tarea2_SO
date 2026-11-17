#include "lectores_escritores.hpp"

#include <stdexcept>

thread_local int id_hebra = -1;

namespace {

[[noreturn]] void pendiente() {
    throw std::logic_error("Protocolo de sincronizacion pendiente.");
}

} // namespace

MonitorRW::MonitorRW(Politica p, bool habilitar_traza)
    : politica(p), registrar_traza(habilitar_traza) {}

void MonitorRW::entrar_lectura() {
    std::unique_lock<std::mutex> lock(m);

    // TODO: registrar Pide, esperar admisión y registrar Entra.
    pendiente();
}

void MonitorRW::salir_lectura() {
    std::unique_lock<std::mutex> lock(m);

    // TODO: actualizar estado, registrar Sale y notificar.
    pendiente();
}

void MonitorRW::entrar_escritura() {
    std::unique_lock<std::mutex> lock(m);

    // TODO: registrar Pide, esperar admisión y registrar Entra.
    pendiente();
}

void MonitorRW::salir_escritura() {
    std::unique_lock<std::mutex> lock(m);

    // TODO: actualizar estado, registrar Sale y notificar.
    pendiente();
}

std::vector<AnotacionTraza> MonitorRW::obtener_traza() {
    std::unique_lock<std::mutex> lock(m);
    return traza;
}

void ControlAtomicoRW::entrar_lectura() {
    // TODO: comprobar condiciones y admitir mediante CAS.
    pendiente();
}

void ControlAtomicoRW::salir_lectura() {
    // TODO: descontar una lectora activa.
    pendiente();
}

void ControlAtomicoRW::entrar_escritura() {
    // TODO: registrar espera y admitir mediante CAS.
    pendiente();
}

void ControlAtomicoRW::salir_escritura() {
    // TODO: desmarcar la escritora activa.
    pendiente();
}