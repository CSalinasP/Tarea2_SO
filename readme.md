# Tarea 2 — Lectores y escritores

Proyecto base en C++17 para la tarea de Sistemas Operativos.

## Estado actual

Incluye las interfaces, estructuras de datos, validación de argumentos
y organización de archivos.

La sincronización, las hebras, los diagnósticos, el verificador de traza
y las mediciones están pendientes de implementación, señalados con TODO.

## Requisitos

- Linux
- g++ compatible con C++17
- make

## Compilación

```bash
make
```

Se genera el ejecutable `rw`.

## Ejecución

```bash
./rw <modo> <politica> <L> <E> <K> <dur_lec_us> <dur_esc_us> [notraza]
```

- `modo`: `cond` o `atomic`.
- `politica`: `lectores`, `escritores` o `fifo`.
- `L`: cantidad de lectoras, al menos 1.
- `E`: cantidad de escritoras, al menos 1.
- `K`: operaciones por hebra, al menos 1.
- `dur_lec_us`: duración de cada lectura en microsegundos.
- `dur_esc_us`: duración de cada escritura en microsegundos.
- `notraza`: opción para desactivar la traza.

Se permiten hasta 1000 hebras en total y duraciones no negativas.
El modo `atomic` solo admite la política `escritores`.

Ejemplo:

```bash
./rw cond escritores 6 2 100 200 500
```

Actualmente, una ejecución con argumentos válidos termina con:

```text
Error: Base preparada: falta implementar sincronizacion y simulacion.
```

Este mensaje es esperado mientras no se complete la implementación.

## Archivos

- `main.cpp`: entrada del programa y manejo de errores.
- `lectores_escritores.hpp`: clases, estructuras y declaraciones.
- `configuracion.cpp`: lectura y validación de argumentos.
- `controles.cpp`: monitor y control atómico pendientes.
- `simulacion.cpp`: coordinación de la ejecución pendiente.
- `hebras.cpp`: funciones lectoras y escritoras pendientes.
- `diagnostico.cpp`: comprobaciones de concurrencia pendientes.
- `verificador.cpp`: verificación de traza e invariantes pendiente.
- `mediciones.cpp`: tiempos, estadísticas y salida pendientes.
- `Makefile`: compilación del proyecto.

## Limpieza

```bash
make clean
```