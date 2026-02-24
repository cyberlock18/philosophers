# Philosophers

Simulación del clásico **Problema de los Filósofos Comensales** desarrollada como parte del currículo de la escuela 42. El programa modela `N` filósofos sentados alrededor de una mesa redonda, cada uno alternando entre comer, dormir y pensar. El desafío consiste en evitar **interbloqueos** (*deadlocks*) y **condiciones de carrera** (*data races*) garantizando que ningún filósofo muera de hambre.

---

## Qué Aprenderás

- **Hilos POSIX (`pthreads`)** – creación y espera de hilos con `pthread_create` / `pthread_join`.
- **Mutexes** – protección de recursos compartidos (tenedores, salida por pantalla, estado de la simulación) mediante `pthread_mutex_lock` / `pthread_mutex_unlock`.
- **Concurrencia y sincronización** – razonamiento sobre condiciones de carrera, interbloqueos y diseño seguro para hilos.
- **Temporización precisa** – medición del tiempo transcurrido con `gettimeofday` e implementación de esperas de sub-milisegundo.
- **Gestión de recursos** – reserva y liberación correcta de memoria dinámica y destrucción de objetos mutex.
- **Análisis y validación de argumentos** – conversión y comprobación de rangos en enteros pasados por línea de comandos de forma robusta.

---

## Compilación

```bash
make        # compila → genera el binario 'philo'
make clean  # elimina los archivos objeto
make fclean # elimina los archivos objeto y el binario
make re     # fclean + all
```

Se requiere un compilador C (`cc`) y un sistema compatible con POSIX que tenga soporte para `pthread`.

---

## Uso

```
./philo <número_de_filósofos> <tiempo_para_morir> <tiempo_para_comer> <tiempo_para_dormir> [número_de_veces_que_cada_filósofo_debe_comer]
```

| Argumento | Descripción |
|---|---|
| `número_de_filósofos` | Número de filósofos (y tenedores). Debe estar entre **2** y **200**. |
| `tiempo_para_morir` | Tiempo en **milisegundos** que puede pasar sin que un filósofo empiece a comer antes de morir. Debe ser ≥ 60. |
| `tiempo_para_comer` | Tiempo en **milisegundos** que tarda un filósofo en comer. Debe ser ≥ 60. |
| `tiempo_para_dormir` | Tiempo en **milisegundos** que duerme un filósofo. Debe ser ≥ 60. |
| `número_de_veces_que_cada_filósofo_debe_comer` | *(Opcional)* La simulación termina cuando cada filósofo ha comido este número de veces. |

### Ejemplos

```bash
# 5 filósofos, mueren después de 800 ms, comen durante 200 ms, duermen 200 ms
./philo 5 800 200 200

# Mismo escenario, se detiene tras que cada filósofo haya comido 7 veces
./philo 5 800 200 200 7
```

---

## Estructura del Proyecto

| Archivo | Propósito |
|---|---|
| `main.c` | Punto de entrada – valida argumentos, inicializa datos y arranca la simulación. |
| `init.c` | Reserva e inicializa las estructuras de filósofos, tenedores y mutexes. |
| `parsing.c` | Analiza y valida los argumentos de la línea de comandos. |
| `process.c` | Ciclo de vida del filósofo (comer / dormir / pensar) y rutinas de hilo. |
| `utils.c` | Utilidades auxiliares: temporización, impresión y limpieza. |
| `philo.h` | Cabecera compartida – estructuras, macros y prototipos de funciones. |
| `Makefile` | Reglas de compilación. |
