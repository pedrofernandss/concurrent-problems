# Concurrent Programming Problems

This repository centralizes implementations and studies on **concurrent programming and process synchronization**. The goal is to explore solutions to classical concurrency problems, dealing with race conditions, deadlocks, and starvation.

The solutions are implemented using the POSIX Threads (`pthreads`) library in C, applying synchronization primitives such as **Mutexes**, **Condition Variables**, and **Semaphores**.

## 🧠 Classic Problems Addressed

In this repository, you will find variations and solutions for the following classic problems:

* **Readers-Writers Problem:** Implementations featuring reader priority as well as fair solutions (using *Turnstiles*) to prevent writer starvation.
* **Baboons Crossing (Monkeys on a Rope):** Bidirectional flow control on shared resources using directional mutual exclusion.

## 🛠️ Technologies & Concepts

* **Language:** C
* **Libraries:** `pthread.h`, `unistd.h`
* **Concepts:** Race Conditions, Critical Sections, Deadlocks, Starvation, Mutexes, Turnstiles.
