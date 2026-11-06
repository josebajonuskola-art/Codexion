*This project has been created as part of the 42 curriculum by juskola-*

## Description

**Codexion** is a concurrent programming project developed in C using POSIX threads (`pthreads`). Its main objective is to simulate multiple coders working simultaneously while sharing a limited set of resources called *dongles*.

Each coder follows a repetitive workflow consisting of three stages: compiling, debugging, and refactoring. Dongles are required only during the compilation stage, and each dongle must observe a cooldown period before it can be used again.

The project focuses on managing concurrency and resource allocation while preventing race conditions and deadlocks. It also implements scheduling policies, such as FIFO and EDF, to determine the order in which coders access the shared resources.


## Instructions

### Compilation

To compile the project, clone the repository and run the following command from the root directory:

```bash
make
```

This will compile the source files and generate the `codexion` executable.

To remove the generated object files and executable, run:

```bash
make clean
make fclean
```

To rebuild the project from scratch, use:

```bash
make re
```

### Execution

Run the program using the following syntax:

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_iterations dongle_cooldown scheduler
```

### Arguments

| Argument | Description |
|---|---|
| `number_of_coders` | Number of coders participating in the simulation. |
| `time_to_burnout` | Maximum time a coder can go without starting a new compilation. |
| `time_to_compile` | Time required to complete the compilation stage. |
| `time_to_debug` | Time required to complete the debugging stage. |
| `time_to_refactor` | Time required to complete the refactoring stage. |
| `number_of_iterations` | Number of compilation cycles each coder must complete. |
| `dongle_cooldown` | Minimum time a dongle must remain unavailable after being used. |
| `scheduler` | Scheduling policy: `fifo` or `edf`. |

### Example

```bash
./codexion 10 1200 300 200 100 4 60 fifo
```

This command starts a simulation with 10 coders. Each coder must complete 4 iterations, following the FIFO scheduling policy.

## Resources

### Documentation and References

- **POSIX Threads (pthreads):** [POSIX Threads Programming](https://man7.org/linux/man-pages/man7/pthreads.7.html) — Documentation on thread creation, synchronization, mutexes, and condition variables.
- **Mutexes:** [pthread_mutex_lock(3)](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html) — Reference for mutex locking and thread synchronization.
- **Condition Variables:** [pthread_cond_wait(3)](https://man7.org/linux/man-pages/man3/pthread_cond_wait.3.html) — Documentation on condition variables and coordinating concurrent threads.
- **Valgrind Helgrind:** [Official Helgrind Manual](https://valgrind.org/docs/manual/hg-manual.html) — A tool for detecting potential data races, synchronization errors, and inconsistent lock ordering.
- **42 Codexion Visualizer:** [Codexion Visualizer](https://codexion-visualizer.sacha-dev.me/) — A visual tool used to represent and better understand the Codexion simulation, including coder activity and resource allocation.
- **C Programming Language:** [GNU C Library Documentation](https://www.gnu.org/software/libc/manual/) — Reference for C programming, POSIX interfaces, and system-level programming concepts.

### Artificial Intelligence Usage

Artificial intelligence tools were used as a support resource during the development of this project.

AI assistance was used for the following tasks:

- **Scheduling analysis:** Understanding FIFO and EDF scheduling policies, heap-based request management, resource allocation, and the effects of thread execution order.
- **Testing and validation:** Analyzing simulation logs from repeated executions with different numbers of coders and timing configurations.
- **Documentation:** Assisting with the writing and organization of this README.md.

## Blocking Cases Handled

The project addresses several concurrency challenges to ensure that coders can safely access shared resources and that the simulation behaves consistently.

### Deadlock Prevention

- **Controlled resource allocation:** Each coder requires two adjacent dongles to start compiling. Access to shared resources is synchronized using mutexes.
- **Lock ordering:** Mutex acquisition must follow a consistent global order to prevent circular wait conditions.
- **Coffman conditions:** The implementation aims to prevent deadlocks by controlling resource allocation and avoiding circular wait. Particular attention is given to avoiding nested locks with inconsistent acquisition orders.

### Starvation and Scheduling

- **FIFO scheduling:** Requests are processed according to their arrival order, ensuring that older requests are not arbitrarily overtaken by newer ones.
- **EDF scheduling:** Requests are prioritized according to their remaining time before burnout, giving priority to coders with the closest deadlines.
- **Request management:** A heap-based priority queue manages pending requests and determines which coder should be considered next.

### Dongle Cooldown Management

- **Cooldown enforcement:** After a compilation, both dongles become temporarily unavailable for the configured cooldown period.
- **Availability checks:** A coder can only start compiling when both required dongles are available.
- **Timed waiting:** Condition variables and timed waits are used to avoid unnecessary polling while waiting for resources to become available.

### Burnout Detection

- **Compilation-based deadline:** The burnout timer starts when a coder begins compiling.
- **Deadline monitoring:** The simulation monitors the time elapsed since the coder's last compilation start and detects when the configured burnout limit is reached.
- **Precise timing:** Millisecond timestamps are used to evaluate deadlines and cooldown periods.

### Log Serialization

- **Synchronized output:** Logging operations are protected to prevent messages from different threads from overlapping or becoming corrupted.
- **Consistent timestamps:** Events are timestamped so that the simulation's execution can be followed and analyzed.

### Thread Synchronization

- **Mutex protection:** Shared data structures and resources are protected against concurrent modifications.
- **Condition variables:** Threads are notified when relevant state changes occur, allowing them to resume waiting operations without continuous polling.
- **Simulation termination:** Shared termination state is checked so that threads can stop processing when the simulation ends.

## Thread Synchronization Mechanisms

The project uses POSIX thread synchronization primitives to coordinate the execution of multiple coders and the monitoring thread. These mechanisms protect shared resources, prevent concurrent modifications, and ensure thread-safe communication.

### Mutexes (`pthread_mutex_t`)

Mutexes are used to provide exclusive access to shared data and resources.

The implementation uses mutexes to protect:

- **Dongles:** Access to dongles is synchronized to prevent multiple coders from acquiring the same dongle simultaneously. A coder must successfully acquire both required dongles before starting compilation.
- **Heap and scheduling requests:** The heap mutex protects the priority queue, ensuring that requests are inserted, removed, and inspected safely.
- **Logging:** A dedicated logging mutex ensures that messages from different threads are printed without overlapping or becoming corrupted.
- **Monitor state:** Shared simulation information, such as termination status and coder states, must be accessed under the appropriate synchronization mechanism.

For example, when a coder starts compiling, access to the dongle resources is protected by a mutex. This prevents another thread from modifying their availability at the same time.

### Condition Variables (`pthread_cond_t`)

Condition variables allow threads to wait efficiently until a particular condition becomes true, rather than continuously checking it.

They are used to coordinate operations such as:

- Waiting for the required dongles to become available.
- Waiting until a coder's request reaches the appropriate position in the scheduling queue.
- Notifying waiting threads when the heap or resource availability changes.
- Waking threads when the simulation state changes or termination is requested.

A condition variable is used together with a mutex. Threads check the relevant condition inside a loop while holding the associated mutex, preventing missed notifications and ensuring that the condition is checked safely.

### Custom Event Handling

The simulation can also coordinate events through shared state and notification mechanisms.

Examples of relevant events include:

- A coder starting or finishing a compilation.
- A dongle becoming available after its cooldown period.
- A new scheduling request being added to the heap.
- The monitor detecting a burnout or the simulation reaching its termination condition.

When an event changes shared state, the corresponding synchronization mechanism ensures that other threads can observe the update safely. Condition-variable notifications can then wake threads waiting for that event.

### Race Condition Prevention

Race conditions are prevented by protecting shared variables and data structures with the appropriate mutexes.

For example:

- Two coders cannot simultaneously claim the same dongle.
- Multiple threads cannot modify the heap at the same time.
- Log messages are serialized through the logging mutex.
- Shared monitor information is accessed using synchronization rather than unsafely reading and writing the same variables from different threads.

The general rule is that every shared variable must have a clearly defined synchronization strategy.

### Thread-Safe Communication Between Coders and the Monitor

Coder threads and the monitoring thread communicate through shared simulation state.

Coder threads update their state as they move through the compilation, debugging, and refactoring stages. The monitor observes this information to detect burnout conditions and determine when the simulation must terminate.

Mutexes protect shared state during updates and inspections, while condition variables allow threads to notify one another when relevant changes occur.

This approach provides a coordinated way for the monitor to observe coder activity without relying on unsynchronized access to shared memory.

