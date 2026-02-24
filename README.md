# Philosophers

A simulation of the classic **Dining Philosophers** concurrency problem, implemented in C using POSIX threads (`pthreads`) and mutexes.

## Project Summary

Each philosopher sits at a round table. There is a fork between each pair of adjacent philosophers. To eat, a philosopher must pick up both the fork to their left and the fork to their right. The program simulates this scenario concurrently, avoiding deadlocks and data races, and detects when a philosopher dies of starvation.

## Skills Acquired

- Working with POSIX threads (`pthread_create`, `pthread_join`)
- Synchronisation with mutexes (`pthread_mutex_lock`, `pthread_mutex_unlock`)
- Detecting and preventing deadlocks and race conditions
- Precise timing with `gettimeofday`
- Memory management and structured data design in C
- Argument validation and defensive programming

## Build & Run

**Requirements:** a C compiler (`cc`) and a POSIX-compliant OS (Linux / macOS).

```bash
# Build
make

# Clean object files
make clean

# Remove binary and object files
make fclean

# Rebuild from scratch
make re
```

### Usage

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks). Must be between 2 and 200. |
| `time_to_die` | Time in ms before a philosopher dies if they haven't started eating. Must be ≥ 60. |
| `time_to_eat` | Time in ms a philosopher takes to eat. Must be ≥ 60. |
| `time_to_sleep` | Time in ms a philosopher sleeps after eating. Must be ≥ 60. |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation stops when all philosophers have eaten this many times. |

**Examples:**

```bash
# 5 philosophers, die at 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# Same, but stop after each philosopher has eaten 7 times
./philo 5 800 200 200 7
```

## Project Structure

```
philosophers/
├── main.c       – Entry point; starts the dinner simulation
├── init.c       – Data and mutex initialisation
├── parsing.c    – Argument validation and parsing
├── process.c    – Philosopher and monitor thread routines
├── utils.c      – Utility functions (timing, printing, cleanup)
├── philo.h      – Header: structs, macros, function prototypes
└── Makefile
```

## Author

**ruortiz-**
