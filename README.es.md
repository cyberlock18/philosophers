# Philosophers

Simulación del clásico problema de concurrencia de los **Filósofos Comensales**, implementada en C con hilos POSIX (`pthreads`) y mutexes.

## Resumen del proyecto

Cada filósofo se sienta alrededor de una mesa circular. Entre cada par de filósofos adyacentes hay un tenedor. Para comer, un filósofo debe tomar el tenedor de su izquierda y el de su derecha. El programa simula este escenario de forma concurrente, evitando deadlocks y condiciones de carrera, y detectando cuándo un filósofo muere de inanición.

## Habilidades adquiridas

- Trabajo con hilos POSIX (`pthread_create`, `pthread_join`)
- Sincronización con mutexes (`pthread_mutex_lock`, `pthread_mutex_unlock`)
- Detección y prevención de deadlocks y condiciones de carrera
- Temporización precisa con `gettimeofday`
- Gestión de memoria y diseño de estructuras de datos en C
- Validación de argumentos y programación defensiva

## Compilación y ejecución

**Requisitos:** un compilador de C (`cc`) y un sistema operativo compatible con POSIX (Linux / macOS).

```bash
# Compilar
make

# Eliminar archivos objeto
make clean

# Eliminar binario y archivos objeto
make fclean

# Recompilar desde cero
make re
```

### Uso

```
./philo número_de_filósofos tiempo_para_morir tiempo_para_comer tiempo_para_dormir [número_de_veces_que_cada_filósofo_debe_comer]
```

| Argumento | Descripción |
|---|---|
| `número_de_filósofos` | Número de filósofos (y tenedores). Debe estar entre 2 y 200. |
| `tiempo_para_morir` | Tiempo en ms antes de que un filósofo muera si no ha comenzado a comer. Debe ser ≥ 60. |
| `tiempo_para_comer` | Tiempo en ms que tarda un filósofo en comer. Debe ser ≥ 60. |
| `tiempo_para_dormir` | Tiempo en ms que duerme un filósofo después de comer. Debe ser ≥ 60. |
| `número_de_veces_que_cada_filósofo_debe_comer` | *(Opcional)* La simulación se detiene cuando todos los filósofos han comido este número de veces. |

**Ejemplos:**

```bash
# 5 filósofos, mueren a los 800ms, comen 200ms, duermen 200ms
./philo 5 800 200 200

# Igual, pero se detiene tras 7 comidas por filósofo
./philo 5 800 200 200 7
```

## Estructura del proyecto

```
philosophers/
├── main.c       – Punto de entrada; inicia la simulación de la cena
├── init.c       – Inicialización de datos y mutexes
├── parsing.c    – Validación y análisis de argumentos
├── process.c    – Rutinas de hilo del filósofo y del monitor
├── utils.c      – Funciones de utilidad (temporización, impresión, limpieza)
├── philo.h      – Cabecera: structs, macros, prototipos de funciones
└── Makefile
```

## Autor

**ruortiz-**
