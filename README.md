# Philosophers

Philosophers is a multithreaded simulation of the dining philosophers problem, written in C.

## General Rules

- The program should not crash under any circumstances, even when it runs out of memory, and should not quit unexpectedly.
- All heap allocated memory space must be properly freed when necessary. No leaks will be tolerated.
- The Makefile must at least contain the rules: `$(NAME)`, `all`, `clean`, `fclean` and `re`.
- Each philosopher has a number ranging from 1 to `number_of_philosophers`.
- Philosopher number 1 sits next to philosopher number `number_of_philosophers`. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

## Simulation Rules

- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.

## Bonus Part

- All the forks are put in the middle of the table.
- They have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a process. But the main process should not be a philosopher.

## Usage

To run the program, use the following command:

```bash
./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
