# Philosophers
Simulate the dining philosophers problem [wiki](https://en.wikipedia.org/wiki/Dining_philosophers_problem) through the use of multithreading and multiprocesses.

## Table of Contents

- [Overview](#overview)
- [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [Build Instructions](#build-instructions)
- [Usage](#usage)

## Overview

- The Project is split into two versions:
    - Mandatory part (philo)
        - Create the program with threads & mutexes
    - Bonus part (philo_bonus)
        - Create the program with child processes & semaphores
- [Subject](./subject_en.pdf)
- Mark: 125/100

## Installation

### Prerequisites

- GCC compiler

### Build Instructions

1. Clone the repository:
   ```sh
   git clone https://github.com/BWG31/Philosophers
2. Compile the executable:
    ```sh
    make
    #inside either philo/ or philo_bonus/
## Usage
- Run the simulation:
    ```sh
    ./philo
    # or
    ./philo_bonus
    # Further usage instructions will be displayed on the STD output.