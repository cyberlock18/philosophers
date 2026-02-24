# Philosophers

A simulation of the classic **Dining Philosophers Problem** built as part of the 42 school curriculum. The program models `N` philosophers sitting at a round table, each alternating between eating, sleeping, and thinking. The challenge is to avoid **deadlocks** and **data races** while ensuring no philosopher starves.

---

## What You Learn

- **POSIX threads (`pthreads`)** – creating and joining threads with `pthread_create` / `pthread_join`.
- **Mutexes** – protecting shared resources (forks, print output, simulation state) using `pthread_mutex_lock` / `pthread_mutex_unlock`.
- **Concurrency & synchronization** – reasoning about race conditions, deadlocks, and thread-safe design.
- **Precise timing** – measuring elapsed time with `gettimeofday` and implementing sub-millisecond sleeps.
- **Resource management** – allocating and cleanly freeing heap memory and destroying mutex objects.
- **Argument parsing & validation** – converting and range-checking command-line integers robustly.

---

## Build

```bash
make        # compile → produces the 'philo' binary
make clean  # remove object files
make fclean # remove object files and the binary
make re     # fclean + all
```

Requires a C compiler (`cc`) and a POSIX-compliant system with `pthread` support.

---

## Usage

```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks). Must be between **2** and **200**. |
| `time_to_die` | Time in **milliseconds** before a philosopher who hasn't started eating dies. Must be ≥ 60. |
| `time_to_eat` | Time in **milliseconds** a philosopher takes to eat. Must be ≥ 60. |
| `time_to_sleep` | Time in **milliseconds** a philosopher spends sleeping. Must be ≥ 60. |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation ends once every philosopher has eaten this many times. |

### Examples

```bash
# 5 philosophers, die after 800 ms, eat for 200 ms, sleep for 200 ms
./philo 5 800 200 200

# Same scenario, stop after each philosopher has eaten 7 times
./philo 5 800 200 200 7
```

---

## Project Structure

| File | Purpose |
|---|---|
| `main.c` | Entry point – validates arguments, initializes data, and starts the simulation. |
| `init.c` | Allocates and initializes philosopher structs, forks, and mutexes. |
| `parsing.c` | Parses and validates command-line arguments. |
| `process.c` | Philosopher lifecycle (eat / sleep / think) and thread routines. |
| `utils.c` | Helper utilities: timing, printing, and clean-up. |
| `philo.h` | Shared header – structs, macros, and function prototypes. |
| `Makefile` | Build rules. |
