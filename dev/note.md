# 1. Introduction and Running Threads

## Introduction

---

### **并发编程的背景与重要性**
- **传统编程的顺序执行**：
  - 传统编程中，程序的执行是线性的，即一个步骤接着另一个步骤，执行顺序是确定的。
  - 这种方式适用于单核处理器，但随着硬件的发展，这种方式无法充分利用现代多核处理器的性能。

- **并发（Concurrency）**：
  - 并发是指一个系统同时执行多个独立任务的能力。
  - 并发的目的是提高程序的效率和性能，特别是在现代多核硬件架构上。

- **并发与并行（Concurrency vs Parallelism）**：
  - **并发**：任务之间可能是交替执行的，通过快速切换任务给人一种“同时进行”的错觉。
  - **并行**：任务在同一时间点真正同时运行，需要多核或多处理器支持。
  - **硬件并发（Hardware Concurrency）**：指硬件实际能够同时运行的任务数量，通常由系统的核心数或硬件线程数决定。

- **多核处理器的兴起**：
  - 过去，硬件性能提升主要依赖于提高处理器的时钟频率（Clock Rate）。
  - 近年来，芯片制造商转向多核设计（如2核、4核、16核等），程序员需要通过并发编程来利用这些多核架构的潜力。

---

### **并发编程的基本概念**
- **线程（Thread）**：
  - 一个线程是程序中可独立执行的路径。
  - 使用多个线程的程序称为多线程程序（Multithreading）。

- **任务切换（Task Switching）**：
  - 在单核系统中，操作系统通过快速切换任务（Task Switching）来模拟并发。
  - 这种切换速度非常快，用户感知不到任务是交替执行的。

- **数据竞争（Data Race）**：
  - 当多个线程同时访问共享数据，并且至少有一个线程尝试修改数据时，会发生数据竞争。
  - 数据竞争是并发编程中一个常见且严重的问题，需要通过同步机制来避免。

- **同步机制（Synchronization Mechanism）**：
  - 用于保证线程之间的数据访问是安全的。
  - 关键技术包括互斥锁（Mutex）、锁（Lock）和条件变量（Condition Variable）。

---

### **C++并发编程的支持**
- **C++11标准的引入**：
  - C++11 标准为语言增加了对并发编程的原生支持，包括线程、锁、条件变量等。
  - 这些工具使得编写并发程序更加简单和高效。

- **硬件线程数（Hardware Threads）**：
  - 硬件线程数表示系统可以真正并行运行的任务数。
  - 当任务数量超过硬件线程数时，系统会通过任务切换来处理额外的任务。

---

### **课程内容概览**
- **第一课：线程与进程**：
  - 介绍线程和进程的区别。
  - 学习如何启动线程并编写第一个多线程程序。
  - 引入课程项目：并发交通模拟器。

- **第二课：线程间数据共享**：
  - 学习如何在线程之间共享数据。
  - 介绍C++中的`promise`和`future`，用于线程间的数据传递。
  - 讨论如何避免数据竞争。

- **第三课：数据安全共享**：
  - 学习互斥锁（Mutex）和锁（Lock）的概念，保护共享数据免受数据竞争的影响。

- **第四课：条件变量与消息队列**：
  - 进一步学习条件变量（Condition Variable）的使用。
  - 设计消息队列（Message Queue）以实现线程间的安全数据交换。

- **课程项目**：
  - 利用所学知识扩展交通模拟器，添加交通信号灯功能。
  - 每辆车运行在自己的线程中，模拟真实的并发场景。

---

### **总结**
这门课程的目标是帮助学习者掌握C++中的并发编程技术，以便充分利用现代多核处理器的性能。通过学习线程、数据共享、互斥锁、条件变量等技术，学习者将能够编写安全、高效的并发程序，并应用到实际项目中，如并发交通模拟器。



## Threads and Processes

---

### **并发的第一种方式：多进程**
- **定义**：
  - 并发的第一种方式是将程序分成多个独立的单线程进程（Processes），这些进程可以同时运行。

- **进程间通信（Inter-Process Communication, IPC）**：
  - **定义**：独立的进程通过某些通信机制来交换数据。
  - **常见的通信机制**：
    - **信号（Signals）**：用于通知进程发生了某个特定事件。
    - **套接字（Sockets）**：通过网络或本地通信交换数据。
    - **文件（Files）**：通过共享文件进行数据交换。
    - **其他机制**：如共享内存、管道（Pipes）等。

- **多进程的优缺点**：
  - **优点**：
    1. **高安全性**：操作系统提供了进程间的隔离，避免一个进程意外修改另一个进程的数据。
    2. **高级通信机制**：操作系统提供了易于使用的通信工具。
    3. **分布式架构支持**：多个进程可以分布在不同的计算机上（如通过网络运行）。
  - **缺点**：
    1. **通信速度慢**：进程间通信需要通过操作系统管理，效率较低。
    2. **管理复杂**：需要处理进程的启动、销毁以及通信。
    3. **资源消耗大**：启动一个新进程需要耗费较多时间和系统资源。

---

### **并发的第二种方式：多线程**
- **定义**：
  - 并发的第二种方式是运行多个线程（Threads），它们在一个单独的进程中运行。
  - 线程被称为“轻量级进程”（Lightweight Processes），因为它们独立运行并有自己的指令集，但共享进程的资源。

- **线程的特性**：
  - **共享地址空间**：线程在同一进程内运行，共享同一个地址空间。这意味着：
    - 线程之间可以直接访问共享数据。
    - 减少了进程间通信的开销。

- **多线程的优缺点**：
  - **优点**：
    1. **低开销**：线程共享进程资源，启动和切换的开销比进程小得多。
    2. **高效的数据共享**：线程可以直接访问共享数据，而不需要通过复杂的通信机制。
  - **缺点**：
    1. **数据一致性问题**：由于线程共享数据，可能会导致**数据竞争（Data Race）**或**不一致性**。
    2. **复杂的同步管理**：程序员需要确保数据在多个线程间的一致性，这需要使用同步机制（如互斥锁、条件变量等）。

---

### **多进程与多线程的比较**
| **特性**     | **多进程**                                             | **多线程**                                           |
| ------------ | ------------------------------------------------------ | ---------------------------------------------------- |
| **隔离性**   | 进程之间相互隔离，不共享地址空间，安全性高。           | 线程共享地址空间，容易出现数据竞争问题。             |
| **启动开销** | 启动新进程需要较多时间和资源。                         | 启动新线程开销较小，速度更快。                       |
| **通信机制** | 需要通过IPC（如信号、套接字）进行通信，效率较低。      | 线程可以直接访问共享数据，通信效率高。               |
| **适用场景** | 适用于需要高隔离性或分布式架构的情况（如分布式系统）。 | 适用于需要高效率和频繁数据交互的情况（如实时系统）。 |
| **复杂性**   | 通信机制复杂，管理进程的生命周期需要更多代码。         | 数据共享容易，但需要同步机制来管理数据一致性。       |



### Detailed Explanation

#### Synchronous & Asynchronous

In this lesson, you will learn how to start and manage your first parallel path of execution, which runs concurrently with the main program and is thus asynchronous. In contrast to synchronous programs, the main program can continue with its line of execution without the need to wait for the parallel task to complete. The following figure illustrates this difference.

![img](assets/c2-2-a2a.png)

Before we start writing a first asynchronous program in C++, let us take a look at the differences between two important concepts : **processes and threads**.

#### Processes

A ***process*** (also called a task) is a computer program at runtime. It is **comprised of** the **runtime environment** provided by the operating system (OS), as well as of the **embedded binary code** of the program during execution. **A process is controlled by the OS** through certain actions with which it sets the process into one of several carefully defined **states**:

![img](assets/c2-2-a2b.png)

- **Ready** : After its creation, a process enters the ready state and is loaded into main memory. The process now is ready to run and is waiting for CPU time to be executed. Processes that are ready for execution by the CPU are stored in a queue managed by the OS.
- **Running** : The operating system has selected the process for execution and the instructions within the process are executed on one or more of the available CPU cores.
- **Blocked** : A process that is blocked is one that is waiting for an event (such as a system resource becoming available) or the completion of an I/O operation.
- **Terminated** : When a process completes its execution or when it is being explicitly killed, it changes to the "terminated" state. The underlying program is no longer executing, but the process remains in the process table as a "zombie process". When it is finally removed from the process table, its lifetime ends.
- **Ready suspended** : A process that was initially in ready state but has been swapped out of main memory and placed onto external storage is said to be in suspend ready state. The process will transition back to ready state whenever it is moved to main memory again.
- **Blocked suspended** : A process that is blocked may also be swapped out of main memory. It may be swapped back in again under the same conditions as a "ready suspended" process. In such a case, the process will move to the blocked state, and may still be waiting for a resource to become available.

Processes are **managed by the *scheduler*** of the OS. The scheduler can either let a process **run until it ends or blocks** (**non-interrupting scheduler**), or it can ensure that the currently running process is interrupted after a short period of time. The scheduler can **switch** back and forth between **different active processes** (**interrupting scheduler**), alternately assigning them CPU time. The latter is the typical scheduling strategy of any modern operating system.

Since the administration of processes is computationally taxing, operating systems support a more resource-friendly way of realizing concurrent operations: the threads.

#### Threads

A ***thread*** represents **a concurrent execution unit within a process**. In contrast to full-blown processes as described above, threads are characterized as light-weight processes (LWP). These are significantly easier to create and destroy: In many systems the creation of a thread is up to 100 times faster than the creation of a process. This is especially advantageous in situations, when the need for concurrent operations changes dynamically.

![img](assets/c2-2-a2c.png)

Threads exist within processes and share their resources. As illustrated by the figure above, a process can contain several threads or - **if no parallel processing is provided for in the program flow - only a single thread**.

**A major difference between a process and a thread** is that **each process has its own address space**, while **a thread does not require a new address space to be created**. All the **threads in a process can access its shared memory**. **Threads also share other OS dependent resources** such as processors, files, and network connections. As a result, the **management overhead for threads is typically less than for processes**. Threads, **however**, are not protected against each other and **must carefully synchronize when accessing the shared process resources to avoid conflicts.**

Similar to processes, **threads exist in different states**, which are illustrated in the figure below:

![img](assets/c2-2-a2d.png)

- **New** : A thread is in this state once it has been created. Until it is actually running, it will not take any CPU resources.

- **Runnable** : In this state, a thread might actually be running or it might be ready to run at any instant of time. It is the responsibility of the thread scheduler to assign CPU time to the thread.

- **Blocked** : A thread might be in this state, when it is waiting for I/O operations to complete. When blocked, a thread cannot continue its execution any further until it is moved to the runnable state again. It will not consume any CPU time in this state. The thread scheduler is responsible for reactivating the thread.

    ![CleanShot 2024-12-27 at 14.28.39@2x](assets/CleanShot 2024-12-27 at 14.28.39@2x.png)

#### Summary

This section discusses the key differences between threads and processes, highlighting that **threads are the preferred concurrency tool in most major languages like C++ due to their low overhead and ease of use**. **However, challenges such as accessing shared memory are noted**. The next section will cover how to start a thread and perform parallel tasks alongside the main thread.



## Running a Single Thread

In this section, you will write your **first multi-threaded program using C++11 concurrency support** and determine the number of hardware threads available on your system. You are encouraged to run the code on your native hardware and compare results across different devices. For example, a MacBook Pro may support 4 threads, while an iMac Pro supports 20. You will **use the `std::thread` function to execute tasks in parallel** with the main thread and learn to **use the `join` command to ensure the worker thread completes its task before the program terminates**. Go ahead and start experimenting with concurrent programming!



### Concurrency Support in C++11

The concurrency support in C++ makes it possible for a program to execute multiple threads in parallel. Concurrency was first introduced into the standard with C++11. Since then, new concurrency features have been added with each new standard update, such as in C++14 and C++17. Before C++11, concurrent behavior had to be implemented using native concurrency support from the OS, using POSIX Threads, or third-party libraries such as BOOST. The standardization of concurrency in C++ now makes it possible to develop cross-platform concurrent programs, which is as significant improvement that saves time and reduces error proneness. Concurrency in C++ is provided by the thread support library, which can be accessed by including the header.

A running program consists of at least one thread. When the main function is executed, we refer to it as the "main thread". Threads are uniquely identified by their thread ID, which can be particularly useful for debugging a program. The code on the right prints the thread identifier of the main thread and outputs it to the console:

```cpp
#include <iostream>
#include <thread>

int main()
{
    std::cout << "Hello concurrent world from main! Thread id = " << std::this_thread::get_id() << std::endl;

    return 0;
}
```

These are the results when run:

```bash
Hello concurrent world from main! Thread id = 0x1f15c4240
```

You can compile this code from the terminal in the lower right using `g++` as follows:

```
g++ example_1.cpp
```

and run it with

```
./a.out
```

Note: The actual thread id and process exit message will vary from machine to machine.



Also, it is possible to retrieve the number of concurrent threads supported. The example on the right prints the number of concurrent threads supported to the console.

```cpp
#include <iostream>
#include <thread>

int main()
{
    unsigned int nThreads = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << nThreads << " concurrent threads available" << std::endl;

    return 0;
}
```

These are the results from a local machine at the time of writing:

```bash
This machine supports concurrency with 14 concurrent threads available
```

Try running this code to see what results you get!

### Starting a second thread

In this section, we will start a second thread in addition to the main thread of our program. To do this, we need to construct a thread object and pass it the function we want to be executed by the thread. Once the thread enters the runnable state, the execution of the associated thread function may start at any point in time.

```cpp
    // create thread
    std::thread t(threadFunction)
```

After the thread object has been constructed, the main thread will continue and execute the remaining instructions until it reaches the end and returns. It is possible that by this point in time, the thread will also have finished. But if this is not the case, the main program will terminate and the resources of the associated process will be freed by the OS. As the thread exists within the process, it can no longer access those resources and thus not finish its execution as intended.

To prevent this from happening and have the main program wait for the thread to finish the execution of the thread function, we need to call `join()` on the thread object. This call will only return when the thread reaches the end of the thread function and block the main thread until then.

The code on the right shows how to use `join()` to ensure that `main()` waits for the thread `t` to finish its operations before returning. It uses the function `sleep_for()`, which pauses the execution of the respective threads for a specified amount of time. The idea is to simulate some work to be done in the respective threads of execution.

```cpp
#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate work
    std::cout << "Finished work in thread\n"; 
}

int main()
{
    // create thread
    std::thread t(threadFunction);

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work in main\n";

    // wait for thread to finish
    t.join();

    return 0;
}
```

To compile this code with `g++`, you will need to use the `-pthread` flag. `pthread` adds support for multithreading with the pthreads library, and the option sets flags for both the preprocessor and linker:

```
g++ example_3.cpp -pthread
```

**Note:** If you compile without the `-pthread` flag, you will see an error of the form: `undefined reference to pthread_create`. You will need to use the `-pthread` flag for all other multithreaded examples in this course going forward.

The code produces the following output:

```bash
Finished work in main
Finished work in thread
```

Not surprisingly, the **main function finishes before** the thread **because the delay inserted into the thread function is much larger than in the main** path of execution. The call to `join()` at the end of the main function ensures that it will not prematurely return. As an experiment, comment out `t.join()` and execute the program. What do you expect will happen? yes we will get main program will terminate and thread will be stoped.

```bash
Finished work in main
libc++abi: terminating
[1]    67828 abort      ./example
```

### Randomness of events

One very important trait of concurrent programs is their **non-deterministic behavior**. It **can not be predicted which thread the scheduler will execute** at which point in time. In the code on the below, the amount of work to be performed both in the thread function and in main has been split into two separate jobs.

```cpp
#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work 1 in thread\n"; 

    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    std::cout << "Finished work 2 in thread\n"; 
}

int main()
{
    // create thread
    std::thread t(threadFunction);

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work 1 in main\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    std::cout << "Finished work 2 in main\n";
    
    // wait for thread to finish
    t.join();

    return 0;
}
```



The console output shows that the work packages in both threads have been interleaved with the first package being performed before the second package.

```bash
Finish work 1 in thread
Finish work 1 in main
Finish work 2 in thread
Finish work 2 in main
```

Interestingly, when executed on my local machine, the order of execution has changed. Now, instead of finishing the second work package in the thread first, main gets there first.

```cpp
Finish work 1 in thread
Finish work 1 in main
Finish work 2 in main
Finish work 2 in thread
```

Executing the code several times more shows that the two versions of program output interchange in a seemingly random manner. This element of **randomness is an important characteristic of concurrent programs** and we have to take measures to deal with it in a controlled way that prevent unwanted behavior or even program crashes.

**Reminder:** You will need to use the `-pthread` flag when compiling this code, just as you did with the previous example. This flag will be needed for all future multithreaded programs in this course as well.

### Using join() as a barrier

In the previous example, the order of execution is determined by the scheduler. If we wanted to ensure that the thread function completed its work before the main function started its own work (because it might be waiting for a result to be available), we could achieve this by repositioning the call to join.

In the file on the below, the `.join()` has been moved to before the work in `main()`. The order of execution now always looks like the following:

```cpp
#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work 1 in thread\n"; 

    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    std::cout << "Finished work 2 in thread\n"; 
}

int main()
{
    // create thread
    std::thread t(threadFunction);
    
    // wait for thread to finish
    t.join();

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work 1 in main\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    std::cout << "Finished work 2 in main\n";

    return 0;
}
```

```bash
Finished work 1 in thread
Finished work 2 in thread
Finished work 1 in main
Finished work 2 in main
```

In later sections of this course, we will make extended use of the join() function to carefully control the flow of execution in our programs and to ensure that results of thread functions are available and complete where we need them to be.

### Detach

Let us now take a look at what happens if we don’t join a thread before its destructor is called. When we comment out join in the example above and then run the program again, it aborts with an error. The reason why this is done is that the designers of the C++ standard wanted to make debugging a multi-threaded program easier: Having the program crash forces the programer to remember joining the threads that are created in a proper way. Such a hard error is usually much easier to detect than soft errors that do not show themselves so obviously.

**There are some situations however, where it might make sense to not wait for a thread to finish its work.** This can be achieved by "detaching" the thread, by which the internal state variable "joinable" is set to "false". This works by calling the `detach()` method on the thread. The destructor of a detached thread does nothing: It neither blocks nor does it terminate the thread. In the following example, detach is called on the thread object, which causes the main thread to immediately continue until it reaches the end of the program code and returns. Note that a detached thread can not be joined ever again.

```cpp
#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work in thread\n"; 
}

int main()
{
    // create thread
    std::thread t(threadFunction);

    // detach thread and continue with main
    t.detach();

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work in main\n";

    return 0;
}
```



You can run the code above using `example_6.cpp` over on the right side of the screen.

**Programmers should be very careful though when using the `detach()`-method**. You have to make sure that the thread does not access any data that might get out of scope or be deleted. Also, we do not want our program to terminate with threads still running. Should this happen, such threads will be terminated very harshly without giving them the chance to properly clean up their resources - what would usually happen in the destructor. So a well-designed program usually has a well-designed mechanism for joining all threads before exiting.

### Summary

This section introduced the basics of writing a concurrent program in C++11, **highlighting how easy it is to create threads**, put them to sleep, and **synchronize them using `join`**. While concurrency may seem straightforward initially, it also introduces the **randomness** of events, a **major source of errors in concurrent programming**. The next section will delve deeper into starting threads using function objects.



## Starting a Thread with Function Objects

### Functions and Callable Objects

In the previous section, we have created our first thread by passing it a function to execute. We did not discuss this concept in depth at the time, but in this section we will focus on the details of passing functions to other functions, which is one form of a ***callable object***.

In C++, callable objects are object that can appear as the left-hand operand of the call operator. These can be pointers to functions, objects of a class that defines an overloaded function call operator and *lambdas* (an anonymous inline function), with which function objects can be created in a very simple way. In the context of concurrency, we can use callable objects to attach a function to a thread.

**In the last section, we constructed a thread object by passing a function to it without any arguments**. If we were limited to this approach, t**he only way to make data available from within the thread function would be to use global variables - which is definitely not recommendable and also incredibly messy.**

In this section, we will therefore look at several ways of **passing data to a thread function**.

### Starting Threads with Function Objects

The `std::thread` constructor can also be called with instances of classes that implement the function-call operator. In the following, we will thus define a class that has an overloaded `()`-operator. In preparation for the final project of this course, which will be a traffic simulation with vehicles moving through intersections in a street grid, we will define a (very) early version of the Vehicle class in this example:

```cpp
#include <iostream>
#include <thread>

class Vehicle
{
public:
    void operator()()
    {
        std::cout << "Vehicle object has been created \n" << std::endl;
    }
};


int main()
{
    // create thread 
    std::thread t(Vehicle()); // C++'s most vexing parse

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t.join();

    return 0;
}
```

When executing this code, the g++ compiler generates a warning, which is followed by an error:

```bash
error: request for member ‘join’ in ‘t’, which is of non-class type ‘std::thread(Vehicle (*)())’
     t.join();
```

So you will see an error when you compile `example_1.cpp`!

The **extra parentheses** suggested by the compiler avoid what is known as C++'s "most vexing parse", which is a specific form of syntactic **ambiguity resolution** in the C++ programming language.

The expression was coined by Scott Meyers in 2001, who talks about it in details in his book "Effective STL". The "most vexing parse" comes from a rule in C++ that says that anything that could be considered as a function declaration, the compiler should parse it as a function declaration - even if it could be interpreted as something else.

In the previous code example, the line

```cpp
std::thread t1( Vehicle() ); 
```

is seemingly **ambiguous**, since it could be interpreted either as

1. a **variable definition** for variable `t` of class `std::thread`, initialized with an **anonymous instance** of class Vehicle or
2. a **function declaration** for a function `t` that returns an object of type `std::thread` and has a single (unnamed) **parameter** that is a **pointer to function** returning an object of type `Vehicle`

Most programmers would presumable expect the first case to be true, but the **C++ standard requires it to be interpreted as the second** - **hence the compiler warning**.

There are **three ways of forcing the compiler to consider the line as the first case**, which would create the thread object we want:

- Add an extra pair of parentheses
- Use copy initialization
- Use uniform initialization with braces

The following code shows all three variants:

```cpp
#include <iostream>
#include <thread>

class Vehicle
{
public:
    void operator()()
    {
        std::cout << "Vehicle object has been created \n" << std::endl;
    }
};


int main()
{
    // create thread 
    //std::thread t0(Vehicle()); // C++'s most vexing parse
    
    std::thread t1( (Vehicle()) ); // Add an extra pair of parantheses
    
    std::thread t2 = std::thread( Vehicle() ); // Use copy initialization
    
    std::thread t3{ Vehicle() };// Use uniform initialization with braces

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
```

The output of this code sample shows that all three threads are executed and the Vehicle object is properly initialized:

```bash
Vehicle object has been created 

Vehicle object has been created 

Vehicle object has been created 

Finished work in main 
```

**Whichever option we use, the idea is the same**: the **function object is copied into internal storage accessible to the new thread**, and the new thread invokes the operator `()`. The `Vehicle` class can of course have data members and other member functions too, and **this is one way of passing data to the thread function: pass it in as a constructor argument and store it as a data member**:

```cpp
#include <iostream>
#include <thread>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    void operator()()
    {
        std::cout << "Vehicle #" << _id << " has been created" << std::endl;
    }

private:
    int _id;
};

int main()
{
    // create thread
    std::thread t = std::thread(Vehicle(1)); // Use copy initialization

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t.join();

    return 0;
}
```

In the above code example, the class `Vehicle` has a constructor that takes an integer and it will store it internally in a variable `_id`. In the overloaded function call operator, the vehicle id is printed to the console. In `main()`, we are creating the `Vehicle` object using copy initialization. The output of the program is given below:

```bash
Finished work in main 
Vehicle #1 has been created
```

As can easily be seen, the integer ID has been successfully passed into the thread function.

### Lambdas

**Another very useful way of starting a thread** and **passing information to it** is by using a **lambda expression** ("Lambda" for short). With a Lambda you can easily create simple function objects.

The name "Lambda" comes from Lambda Calculus , a mathematical formalism invented by Alonzo Church in the 1930s to investigate questions of logic and computability. Lambda calculus formed the basis of LISP, a functional programming language. Compared to Lambda Calculus and LISP, **C ++ - Lambdas** have the **properties** of being **unnamed** and **capturing variables** from the surrounding context, but **lack the ability to execute and return functions**.

A Lambda is **often used as an argument for functions** that can take a callable object. This can be easier than creating a named function that is used only when passed as an argument. In such cases, Lambdas are generally preferred **because they allow the function objects to be defined inline**. If Lambdas were not available, we would have to define an extra function somewhere else in our source file - which would work but at the expense of the clarity of the source code.

**A Lambda is a function object** (a "functor"), so **it has a type and can be stored and passed around**. Its result object is called a "closure", which can be called using the operator `()` as we will see shortly.

A lambda formally **consists of three parts**: a capture list `[]` , a parameter list `()` and a main part `{}`, which contains the code to be executed when the Lambda is called. Note that in principal all parts could be empty.

***The capture list** `[]`*: By default, variables outside of the enclosing {} around the main part of the Lambda can not be accessed. **By adding a variable to the capture list** however, it **becomes available within the Lambda either as a copy or as a reference**. The **captured variables become a part of the Lambda**.

By default, **variables in the capture block can not be modified** within the Lambda. **Using the keyword "mutable" allows to modify the parameters captured by copy**, and to call their non-const member functions within the body of the Lambda. The following code examples show several ways of making the external variable "id" accessible within a Lambda.

```cpp
#include <iostream>

int main()
{
    // create lambdas
    int id = 0; // Define an integer variable

    //auto f0 = []() { std::cout << "ID = " << id << std::endl; }; // Error: 'id' cannot be accessed

    id++;
    auto f1 = [id]() { std::cout << "ID = " << id << std::endl; }; // OK, 'id' is captured by value

    id++;
    auto f2 = [&id]() { std::cout << "ID = " << id << std::endl; }; // OK, 'id' is captured by reference

    //auto f3 = [id]() { std::cout << "ID = " << ++id << std::endl; }; // Error, 'id' may not be modified

    auto f4 = [id]() mutable { std::cout << "ID = " << ++id << std::endl; }; // OK, 'id' may be modified

    // execute lambdas
    f1();
    f2();
    f4();

    return 0;
}
```

Even though we have been using Lambdas in the above example in various ways, **it is important to note that a Lambda does not exist at runtime.** The runtime effect of a Lambda is the generation of an object, which is known as *closure*. The difference between a **Lambda** and the **corresponding closure** is **similar to** the distinction between a **class** and an **instance of the class**. A class exists only in the source code while the objects created from it exist **at runtime**.

We can use **(a copy of) the closure (i.e. f0, f1, …)** to execute the code within the Lambda at a position in our program **different to the line where the function object was created.**

*The parameter list `()`* : The way **parameters are passed to a Lambda** is basically **identical to calling a regular function**. If the Lambda takes no arguments, these parentheses can be omitted (except when "mutable" is used).

The following example illustrates how the function object is first created and then used to pass the parameter id later in the code.

### **Quiz**

The code below shows how to capture variables by value and by reference, how to pass variables to a Lambda using the parameter list and how to use the closure to execute the Lambda.

```cpp
#include <iostream>

int main()
{
    int id = 0; // Define an integer variable

    // capture by reference (immutable)
    auto f0 = [&id]() { std::cout << "a) ID in Lambda = " << id << std::endl; };

    // capture by value (mutable)
    auto f1 = [id]() mutable { std::cout << "b) ID in Lambda = " << ++id << std::endl; };
    f1(); // call the closure and execute the code witin the Lambda
    std::cout << "c) ID in Main = " << id << std::endl;

    // capture by reference (mutable)
    auto f2 = [&id]() mutable { std::cout << "d) ID in Lambda = " << ++id << std::endl; };
    f2(); 
    std::cout << "e) ID in Main = " << id << std::endl; 

    // pass parameter 
    auto f3 = [](const int id) { std::cout << "f) ID in Lambda = " << id << std::endl; };   
    f3(++id);

    // observe the effect of capturing by reference at an earlier point in time
    f0(); 

    return 0;
}
```

Please think about the resulting output for a while. What would you say is the order in which the various strings are printed to the console? Also, what will be the value for ID for each output?

```bash
b) ID in Lambda = 1
c) ID in Main = 0
d) ID in Lambda = 1
e) ID in Main = 1
f) ID in Lambda = 2
a) ID in Lambda = 2

```

### Starting Threads with Lambdas

A **Lambda** is, as we’ve seen, **just an object** and, like other objects it may be **copied, passed as a parameter, stored in a container,** etc. The **Lambda object has its own scope and lifetime** which may, in some circumstances, be different to those objects it has ‘captured’. Programers need to **take special care when capturing local objects by reference** because **a Lambda’s lifetime may exceed the lifetime of its capture list:** It must be **ensured that the object to which the reference points is still in scope when the Lambda is called**. This is especially **important in multi-threading programs.**

So let us start a thread and pass it a Lambda object to execute:

```cpp
#include <iostream>
#include <thread>

int main()
{
    int id = 0; // Define an integer variable

    // starting a first thread (by reference)
    auto f0 = [&id]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "a) ID in Thread (call-by-reference) = " << id << std::endl;
    };
    std::thread t1(f0);

    // starting a second thread (by value)
    std::thread t2([id]() mutable {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "b) ID in Thread (call-by-value) = " << id << std::endl;
    });

    // increment and print id in main
    ++id;
    std::cout << "c) ID in Main (call-by-value) = " << id << std::endl;

    // wait for threads before returning
    t1.join();
    t2.join();

    return 0;
}
```

The output of the program looks like this

```
c) ID in Main (call-by-value) = 1
b) ID in Thread (call-by-value) = 0
a) ID in Thread (call-by-reference) = 1
```

As you can see, the output in the main thread is generated first, at which point the variable ID has taken the value 1. Then, the call-by-value thread is executed with ID at a value of 0. Then, the call-by-reference thread is executed with ID at a value of 1. This illustrates the effect of passing a value by reference : **when the data to which the reference refers changes before the thread is executed, those changes will be visible to the thread**. We will see other examples of such behavior later in the course, as this is a primary source of concurrency bugs.

- 多线程程序的执行顺序通常是非确定性的，具体取决于操作系统的线程调度。
- 但在这段代码中，由于两个线程分别休眠了 **100 毫秒** 和 **50 毫秒**，可以确定以下几点：
  1. 第二个线程（`t2`）会比第一个线程（`t1`）更早完成。
  2. 主线程的输出会先于两个子线程的输出。

1. **主线程输出 `id`**：
   ```cpp
   c) ID in Main (call-by-value) = 1
   ```
   - 主线程将 `id` 自增为 `1` 并输出。
   - 这是第一个输出，因为主线程的操作不受线程休眠的影响。

2. **第二个线程（`t2`）输出 `id`**：
   ```cpp
   b) ID in Thread (call-by-value) = 0
   ```
   - 第二个线程捕获的是 `id` 的副本，值为线程启动时的 `0`。
   - 由于线程休眠了 50 毫秒，因此这是第二个输出。

3. **第一个线程（`t1`）输出 `id`**：
   ```cpp
   a) ID in Thread (call-by-reference) = 1
   ```
   - 第一个线程捕获的是 `id` 的引用，因此它输出的是主线程中 `id` 的最新值（即自增后的 `1`）。
   - 由于线程休眠了 100 毫秒，因此这是最后一个输出。





## Starting a Thread with Variadic Templates & Member Functions





## Running Multiple Threads





## Exercise







# 2. Passing Data Between Threads



## Introduction







## Promises and Futures







## Threads vs. Tasks





## Avoiding Data Races







## Exercise





# 3. Mutexes and Locks



## Introduction





## Using a Mutex to Protect Shared Data





## Using Locks to Avoid Deadlocks





## Exercise







# 4. Condition Variable  and Message Queues



## Introduction







## The Monitor Object Pattern







## Building a Concurrent Message Queue

















