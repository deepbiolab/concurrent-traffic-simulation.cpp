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

### Passing Arguments using a Variadic Template

In the previous section, we have seen that one way to pass arguments in to the thread function is to package them in a class using the function call operator. Even though this worked well, it would be very cumbersome to write a special class every time we need to pass data to a thread. We can also use a Lambda that captures the arguments and then calls the function. But there is a simpler way: The thread constructor may be called with a function and all its arguments. That is possible because the **thread constructor is a *variadic template* that takes multiple arguments.**

Before C++11, classes and functions could only accept a fixed number of arguments, which had to be specified during the first declaration. **With variadic templates it is possible to include any number of arguments of any type.**

```cpp
#include <iostream>
#include <thread>
#include <string>

void printID(int id)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "ID = " << id << std::endl;
    
}

void printIDAndName(int id, std::string name)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "ID = " << id << ", name = " << name << std::endl;
}

int main()
{
    int id = 0; // Define an integer variable

    // starting threads using variadic templates
    std::thread t1(printID, id);
    std::thread t2(printIDAndName, ++id, "MyString");
    std::thread t3(printIDAndName, ++id); // this procudes a compiler error

    // wait for threads before returning
    t1.join();
    t2.join();
    //t3.join();


    return 0;
}
```

As seen in the code example above, a first thread object is constructed by passing it the function `printID` and an integer argument. Then, a second thread object is constructed with a function `printIDAndName`, which requires an integer and a string parameter. If only a single argument was provided to the thread when calling `printIDAndName`, a compiler error would occur (see `std::thread t3` in the example) - which is the same type checking we would get when calling the function directly.

There is **one more difference** between **calling a function directly** and **passing it to a thread**: With the former, arguments may be passed by value, by reference or by using move semantics - depending on the signature of the function. **When calling a function using a variadic template, the arguments are by default either moved or copied - depending on wether they are rvalues or lvalues.** There are ways however which allow us to overwrite this behavior. If you want to move an lvalue for example, we can call `std::move`. In the following example, two threads are started, each with a different string as a parameter. **With `t1`, the string name1 is copied by value,** which **allows us to print name1 even after `join`** has been called. The second string `name2` is passed to the thread function using **move semantics**, which means that it is not available any more after `join` has been called on `t2`.

```cpp
#include <iostream>
#include <thread>
#include <string>

void printName(std::string name, int waitTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    std::cout << "Name (from Thread) = " << name << std::endl;
}

int main()
{
    std::string name1 = "MyThread1";
    std::string name2 = "MyThread2";

    // starting threads using value-copy and move semantics 
    std::thread t1(printName, name1, 50);
    std::thread t2(printName, std::move(name2), 100);

    // wait for threads before returning
    t1.join();
    t2.join();

    // print name from main
    std::cout << "Name (from Main) = " << name1 << std::endl;
    std::cout << "Name (from Main) = " << name2 << std::endl;

    return 0;
}
```

The console output shows how using copy-by-value and `std::move` affect the string parameters:

```
Name (from Thread) = MyThread1
Name (from Thread) = MyThread2
Name (from Main) = MyThread1
Name (from Main) = 
```

In the following example, the signature of the thread function is modified to take a non-const reference to the string instead.

```cpp
#include <iostream>
#include <thread>
#include <string>

void printName(std::string &name, int waitTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    name += " (from Thread)";
    std::cout << name << std::endl;
}

int main()
{
    std::string name("MyThread");

    // starting thread
    std::thread t(printName, std::ref(name), 50);

    // wait for thread before returning
    t.join();

    // print name from main
    name += " (from Main)";
    std::cout << name << std::endl;

    return 0;
}
```

When passing the string variable name to the thread function, we need to **explicitly mark it as a reference**, so the compiler will treat it as such. This can be done by using the **`std::ref`** function. In the console output it becomes clear that the string has been successfully modified within the thread function before being passed to `main`.

```
MyThread (from Thread)
MyThread (from Thread) (from Main)
```

**Even though the code works, we are now sharing mutable data between threads - which will be something we discuss in later sections of this course as a primary source for concurrency bugs.**



### Starting Threads with Member Functions

In the previous sections, you have seen how to start threads with functions and function objects, with and without additional arguments. Also, you now know how to pass arguments to a thread function by reference. **But what if we wish to run a member function other than the function call operator**, **such as a member function of an existing object**? Luckily, the C++ library can handle this use-case: For calling member functions, the `std::thread` function requires an additional argument for the object on which to invoke the member function.

```cpp
#include <iostream>
#include <thread>

class Vehicle
{
public:
    Vehicle() : _id(0) {}
    void addID(int id) { _id = id; }
    void printID()
    {
        std::cout << "Vehicle ID=" << _id << std::endl;
    }

private:
    int _id;
};

int main()
{
    // create thread
    Vehicle v1, v2;
    std::thread t1 = std::thread(&Vehicle::addID, v1, 1); // call member function on object v
    std::thread t2 = std::thread(&Vehicle::addID, &v2, 2); // call member function on object v

    // wait for thread to finish
    t1.join();
    t2.join();

    // print Vehicle id
    v1.printID();
    v2.printID();

    return 0;
}
```

In the example above, the Vehicle object v1 is passed to the thread function by value, thus a copy is made which does not affect the "original" living in the main thread. Changes to its member variable `_id` will thus not show when printing calling `printID()` later in main. The second `Vehicle` object `v2` is instead passed by reference. Therefore, changes to its `_id` variable will also be visible in the `main` thread - hence the following console output:

```cpp
Vehicle ID=0
Vehicle ID=2
```

In the previous example, we **have to ensure that the existence of `v2` outlives the completion of the thread `t2` - otherwise there will be an attempt to access an invalidated memory address**. An **alternative** is to use a **heap-allocated object** and **a reference-counted pointer such as `std::shared_ptr<Vehicle>`** to **ensure that the object lives as long as it takes the thread to finish its work**. The following example shows how this can be implemented:

```cpp
int main()
{
    // create thread
    std::shared_ptr<Vehicle> v(new Vehicle);
    std::thread t = std::thread(&Vehicle::addID, v, 1); // call member function on object v
    
    // wait for thread to finish
    t.join();
    
    // print Vehicle id
    v->printID();
    
    return 0;
}
```



### Adding a Member Function

Change the code from the previous example in a way that a new member variable `_name` of type `std::string` is added to the `Vehicle` class. Then, define a function `setName` which takes a string as an argument and assigns this to `_name`. The function `setName` needs to be started as a thread from `main`. Also, add a function `printName` to the `Vehicle` class which is used at the end of `main` to print the name to the console.

```cpp
#include <iostream>
#include <thread>

class Vehicle
{
public:
    Vehicle() : _id(0) {}
    void addID(int id) { _id = id; }
    void setName(std::string name) { _name = name; }
    void printID()
    {
        std::cout << "Vehicle ID=" << _id << std::endl;
    }
    void printName()
    {
        std::cout << "Vehicle name=" << _name << std::endl;
    }

private:
    int _id;
    std::string _name;
};

int main()
{
    // create thread 1
    std::shared_ptr<Vehicle> v(new Vehicle);
    std::thread t1 = std::thread(&Vehicle::addID, v, 1); 

    // create thread 2
    std::thread t2 = std::thread(&Vehicle::setName, v, "MyVehicle"); 

    // wait for thread to finish
    t1.join();
    t2.join();

    // print Vehicle id
    v->printID();
    v->printName();

    return 0;
}
```



## Running Multiple Threads

### Introduction

#### 1. 分叉-合并并行（Fork-Join Parallelism）
- **概念**：这是一种基本的并行编程模式
- **工作方式**：
  - **分叉（Fork）**：主线程创建（分叉）多个子线程执行任务
  - **合并（Join）**：等待所有子线程完成后，再继续执行主线程
- **特点**：
  - 结构清晰
  - 易于理解和实现
  - 适合处理可以并行的独立任务

#### 2. 线程屏障（Thread Barriers）
- **作用**：同步多个线程的执行点
- **工作原理**：
  - 设置一个同步点（屏障点）
  - 当线程达到屏障点时会等待
  - 直到所有线程都到达屏障点才继续执行
- **应用场景**：
  - 需要等待所有并行任务完成后才能继续的情况
  - 多个线程需要同步进行的场合

#### 3. 线程句柄管理（Thread Handles in Vector）
- **目的**：更好地管理多个线程
- **优势**：
  - 可以批量管理线程
  - 便于进行循环操作
  - 更容易实现动态线程数量的调整
- **实现方式**：
  ```cpp
  std::vector<std::thread> threads;
  // 添加线程
  threads.push_back(std::thread(...));
  ```

#### 4. 并发限制（Concurrency Ban）
- **含义**：在并发编程中的各种限制和约束
- **类型**：
  - 正式限制：语言规范或标准库强制的限制
  - 非正式限制：最佳实践或性能考虑导致的限制
- **目的**：
  - 避免数据竞争
  - 确保线程安全
  - 提高程序可靠性

#### 总结
这个章节主要介绍：
1. 如何同时管理和运行多个线程
2. 基本的并行编程模式
3. 线程同步机制
4. 线程管理的实用技巧
5. 并发编程中需要注意的限制和约束



### Fork-Join Parallelism

Using threads follows a basic concept called "fork-join-parallelism". The basic mechanism of this concept follows a simple **three-step pattern**:

1. **Split** the flow of execution into a parallel thread ("fork")
2. **Perform** some work in both the main thread and the parallel thread
3. **Wait** for the parallel thread to finish and unite the split flow of execution again ("join")

The following diagram illustrates the basic idea of forking:

![C2-6-A2 multithreading](assets/C2-6-A2 multithreading-5373669.jpg)

In the main thread, the program flow is forked into three parallel branches. In both worker branches, some work is performed - which is why threads are often referred to as "worker threads". Once the work is completed, the flow of execution is united again in the main function using the `join()` command. In this example, **join acts as a barrier where all threads are united**. The execution of main is in fact halted, until both worker threads have successfully completed their respective work.

```cpp
#include <iostream>
#include <thread>
#include <vector>

void printHello()
{
    // perform work
    std::cout << "Hello from Worker thread #" << std::this_thread::get_id() << std::endl;
}

int main()
{
    // create threads
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 5; ++i)
    {
        // copying thread objects causes a compile error
        /*
        std::thread t(printHello);
        threads.push_back(t); 
        */

        // moving thread objects will work
        threads.emplace_back(std::thread(printHello));
    }

    // do something in main()
    std::cout << "Hello from Main thread #" << std::this_thread::get_id() << std::endl;

    // call join on all thread objects using a range-based loop
    for (auto &t : threads)
        t.join();

    return 0;
}

```

In the following example, a number of threads is created and added to a vector. **The basic idea is to loop over the vector at the end of the main function and call join on all the thread objects inside the vector**.

When we try to compile the program using the **`push_back()`** function (which is the usual way in most cases), we get a **compiler error**. The problem with our code is that by pushing the thread object into the vector, we **attempt to make a copy of it**. However, **thread objects do not have a copy constructor and thus can not be duplicated**. **If this were possible, we would create yet another branch** in the flow of execution - **which is not what we want**. The solution to this problem is to use move semantics, which provide a convenient way for the contents of objects to be 'moved' between objects, rather than copied. It might be a good idea at this point to refresh your knowledge on move semantics, on rvalues and lvalues as well as on rvalue references, as we will make use of these concepts throughout the course.

**To solve our problem, we can use the function `emplace_back()` instead of `push_back()`**, which **internally uses move semantics** to move our thread object into the vector without making a copy. When executing the code, we get the following output:

```
Hello from Worker thread #Hello from Worker thread #140370329347840140370337740544
Hello from Worker thread #140370320955136
Hello from Worker thread #140370346133248

Hello from Main thread #140370363660096
Hello from Worker thread #140370312562432
```

This is surely not how we intended the console output to look like. When we take a close look at the call to `std::cout` in the thread function, we can see that it actually consists of three parts: the string "Hello from worker…", the respective thread id and finally the line break at the end. In the output, **all three components are completely intermingled**. Also, when the program is run several times, the output will look different with each execution. **This shows us two important properties of concurrent programs:**

1. **The order in which threads are executed is non-deterministic**. Every time a program is executed, there is a chance for a completely different order of execution.
2. **Threads may get preempted in the middle of execution** and another thread may be selected to run.

These **two properties pose a major problem with concurrent applications**: A program may run correctly for thousands of times and suddenly, due to a particular interleaving of threads, there might be a problem. From a debugging perspective, **such errors are very hard to detect as they can not be reproduced easily.**



### A First Concurrency Bug

Let us adjust the program code from the previous example and use a Lambda instead of the function `printHello()`. Also, we will pass the loop counter i into the Lambda to enforce an individual wait time for each thread. The idea is to prevent the interleaving of text on the command line which we saw in the previous example.

```cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>

int main()
{
    // create threads
    std::vector<std::thread> threads;
    for (size_t i = 0; i < 10; ++i)
    {
        // create new thread from a Lambda
        threads.emplace_back([&i]() {

            // wait for certain amount of time
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * i));

            // perform work
            std::cout << "Hello from Worker thread #" << i << std::endl;
        });
    }

    // do something in main()
    std::cout << "Hello from Main thread" << std::endl;

    // call join on all thread objects using a range-based loop
    for (auto &t : threads)
        t.join();

    return 0;
}

```

When executing the code however, the following output is generated on the console:

<img src="assets/CleanShot 2024-12-28 at 16.42.17@2x.png" alt="CleanShot 2024-12-28 at 16.42.17@2x" style="zoom:25%;" />

Clearly this is not what we expected. Can you find the bug and fix the code so that each thread gets the corresponding integer ranging from 0 to 9?

```cpp
// change below 
[&i]() {

            // wait for certain amount of time
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * i));

            // perform work
            std::cout << "Hello from Worker thread #" << i << std::endl;
        }
// to this
[i]() {

            // wait for certain amount of time
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * i));

            // perform work
            std::cout << "Hello from Worker thread #" << i << std::endl;
        }
```



## Exercise: Traffic Simulation

### Overview

The purpose of the program is to **simulate traffic in a city grid** consisting of **vehicles**, **streets**, and **intersections**. Vehicles will move randomly across the grid and change direction whenever they reach an intersection. Each object in the simulation (vehicles, streets, intersections) will operate independently in its own thread, making this a **concurrent simulation**.

The goal is to carefully manage threads and synchronize them to avoid crashes, undefined behavior, and concurrency errors.

---

### **Class Structure**

The simulation consists of the following main components:

<img src="assets/CleanShot 2024-12-28 at 18.28.08@2x.png" alt="CleanShot 2024-12-28 at 18.28.08@2x" style="zoom:50%;" />

- **`TrafficObject`**: A base class encapsulating default behavior shared by all traffic-related objects. It is abstract and will not have direct instances.
- **`Intersection`**, **`Vehicle`**, and **`Street`**: Derived classes inheriting from `TrafficObject`.
- **`Graphics`**: Handles visualization by rendering all `TrafficObject` instances on a top-view map of a city (e.g., New York, Paris).

---

### **Program Workflow**

The program has two primary flows of execution:

1. **Main Function Workflow**: Responsible for initializing the simulation.
2. **Vehicle Execution Workflow**: Manages the behavior of each vehicle in its thread.

<img src="assets/CleanShot 2024-12-28 at 18.28.50@2x.png" alt="CleanShot 2024-12-28 at 18.28.50@2x" style="zoom:50%;" />

#### **Main Function Workflow**
1. **Create and Connect Intersections and Streets**: Establish relationships between intersections and streets.
2. **Assign Street and Target Intersection to Vehicles**: Each vehicle is assigned a street and a destination intersection.
3. **Simulate Vehicles**: Start a thread for each vehicle, running its `drive()` function.
4. **Visualize TrafficObjects**: Continuously update and render the positions of all objects.

#### **Vehicle Execution Workflow**
1. **Initialize Stopwatch**: Used to track elapsed time.
2. **Compute Time Difference**: Calculate the time since the last update.
3. **Update Vehicle Position**: Adjust the vehicle's position based on its velocity and heading.
4. **Check for End of Street**: Determine if the vehicle has reached the end of its current street.
5. **Pick New Destination**: If yes, select a new intersection and street to continue driving. Else back to step 3
6. **Reset Stopwatch**: Restart the stopwatch for the next iteration.

---

### **Tasks**

#### **Task 1.1**: Thread Barrier in Destructor
- In the `TrafficObject` base class, implement a **thread barrier** in the destructor to ensure all threads stored in the `_threads` vector are joined before the object is destroyed.

#### **Task 1.2**: Start Vehicle Threads
- In the `Vehicle` class, start a thread that runs the `drive()` member function.
- Add the created thread to the `_threads` vector in the parent class (`TrafficObject`).

#### **Task 1.3**: Analyze Thread Usage
- Vary the number of vehicles (e.g., 2, 5, 20) and observe the number of threads created using tools like `top` (Linux) or Task Manager (Windows).
- Measure the CPU load for different vehicle counts and analyze performance.

---

### **Expected Simulation Output**

Once the tasks are completed, the simulation should look like this:
- **Green dots** represent intersections.
- **Streets** are implied between intersections but not directly visualized.
- **Vehicles** (large circles) move along streets, slow down at intersections, and change direction.

### Build Instructions

*To run this code, you will need to use the virtual desktop*. In the desktop you can use Terminator or the terminal in Visual Studio Code.

Once in the virtual desktop, to compile and run the code, create a `build` directory and use `cmake` and `make` as follows:

```bash
mkdir build
cd build
cmake ..
make
./traffic_simulation
```

Here's a detailed text summary of the traffic simulation project, incorporating both the flow diagrams and actual code snippets:



### Code Walkthrough

The project simulates traffic in a city grid using three main types of objects:
- Vehicles
- Streets 
- Intersections

All these objects inherit from a common base class `TrafficObject`:

```cpp
// TrafficObject.cpp
class TrafficObject {
protected:
    ObjectType _type;                 // identifies the class type
    int _id;                         // every traffic object has its own unique id
    double _posX, _posY;             // vehicle position in pixels
    std::vector<std::thread> _threads;// holds all threads that have been launched within this object

private:
    static int _idCnt;               // global variable for counting object ids
};
```

The main program consists of three major parts:

```cpp
// TrafficSimulator-L1.cpp
int main() {
    /* PART 1 : Set up traffic objects */
    std::vector<std::shared_ptr<Street>> streets;
    std::vector<std::shared_ptr<Intersection>> intersections;
    std::vector<std::shared_ptr<Vehicle>> vehicles;
    std::string backgroundImg;
    
    int nVehicles = 4;
    createTrafficObjects(streets, intersections, vehicles, backgroundImg, nVehicles);

    /* PART 2 : simulate traffic objects */
    std::for_each(vehicles.begin(), vehicles.end(), [](std::shared_ptr<Vehicle> &v) {
        v->simulate();
    });

    /* PART 3 : Launch visualization */
    // ... visualization code ...
}
```

The core of the simulation happens in the Vehicle class's `drive()` method:

```cpp
// Vehicle_Student.cpp
void Vehicle::drive() {
    // print id of the current thread
    std::cout << "Vehicle #" << _id << "::drive: thread id = " 
              << std::this_thread::get_id() << std::endl;

    // initialize variables
    bool hasEnteredIntersection = false;
    double cycleDuration = 1; // duration of a single simulation cycle in ms
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    // init stop watch
    lastUpdate = std::chrono::system_clock::now();
    while (true) {
        // sleep to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now() - lastUpdate).count();

        if (timeSinceLastUpdate >= cycleDuration) {
            // update position with constant velocity model
            _posStreet += _speed * timeSinceLastUpdate / 1000;
            
            // ... position updates and intersection handling ...
        }
    }
}
```

1. **Thread Management**: Each vehicle runs in its own thread, with the base class `TrafficObject` managing thread lifecycles.

2. **CPU Load Management**: To prevent excessive CPU usage, each vehicle thread includes a small sleep:
```cpp
std::this_thread::sleep_for(std::chrono::milliseconds(1));
```

3. **Smart Pointer Usage**: The project uses modern C++ shared pointers instead of raw pointers:
```cpp
std::vector<std::shared_ptr<Street>> streets;
std::vector<std::shared_ptr<Intersection>> intersections;
std::vector<std::shared_ptr<Vehicle>> vehicles;
```

4. **Vehicle Movement**: Vehicles move along streets using a constant velocity model, with speed adjustments near intersections:
```cpp
// Slow down when approaching intersection
if (completion >= 0.9 && !hasEnteredIntersection) {
    _speed /= 10.0;
    hasEnteredIntersection = true;
}
```

**Performance Considerations**

- Vehicle speed is set to 400 m/s for demonstration purposes
- The number of vehicles should not exceed the number of available streets/intersections
- Thread synchronization is crucial for proper simulation behavior
- CPU usage is managed through strategic thread sleeping

The simulation visualizes vehicles as circles moving along streets, with intersections marked as green dots on a city map background.



<img src="assets/CleanShot 2024-12-28 at 18.46.21@2x.png" alt="CleanShot 2024-12-28 at 18.46.21@2x" style="zoom:50%;" />











# 2. Passing Data Between Threads

## Introduction

### 概览

1. **Promise 和 Future 机制**
   - 这是线程间的私有通信通道
   - 只能使用一次
   - 可以在线程创建后的任意时刻使用
   - 用于在工作线程和父线程之间传递数据和异常

2. **线程(Thread)与任务(Task)的区别**
   - Task 是更高层级的抽象
   - 系统可以自动决定是并行还是同步执行
   - 使用 Task 可以更容易地建立 Promise-Future 链接
   - 比标准线程需要的代码更少

3. **数据传递机制**
   - 按值传递（making copies）
   - 移动语义（move semantics）
     - C++11 引入的特性
     - 避免不必要的数据复制
     - 比传引用更安全

4. **并发编程中的问题**
   - 数据竞争（data races）
     - 并发编程中的主要错误来源
     - 发生在多个线程同时访问同一内存位置时

### 术语解释

1. **并发编程相关**
   - `Thread`（线程）：程序中可以并行执行的最小单位
   - `Barrier`（屏障）：用于同步多个线程的机制
   - `Promise`：发送端的对象，用于设置值或异常
   - `Future`：接收端的对象，用于获取值或异常
   - `Task`：高级抽象的并行执行单元

2. **C++ 特性相关**
   - `Move Semantics`（移动语义）：
     - C++11 引入的重要特性
     - 通过转移资源所有权来避免不必要的复制
     - 提高性能和资源利用效率
   
3. **并发问题相关**
   - `Data Race`（数据竞争）：
     - 多个线程同时访问共享数据
     - 至少有一个线程进行写操作
     - 没有同步机制保护的情况

该部分将重点关注：
1. 线程创建后的数据传递
2. 高级并发概念（Promise/Future）
3. 安全的数据传递方式
4. 并发问题的处理

这节课的内容对于理解现代 C++ 并发编程非常重要，特别是移动语义和 Promise/Future 机制的使用，这些都是构建高效且安全的并发程序的基础。



## Promises and Futures

### Introduction

1. **背景问题**：
    - 之前学习的内容主要是关于在**线程启动阶段**向线程传递数据。
    - 例如：
        - 使用 **Lambda 函数** 的捕获方式（capture options）传递数据。
        - 使用 **可变参数模板（variadic templates）** 传递数据。
    - 局限性:
        - 这些方法只能实现数据从父线程（如主线程 `main`）流向工作线程（worker thread）。
        - 无法实现数据从工作线程返回到父线程。
2. **新的需求**：
    - 本节课的目标是研究如何实现**数据从工作线程传回父线程**。
    - 例如，从工作线程将数据或异常返回给主线程（`main` 函数）。
3. **Promise 和 Future 机制**：
    - **Promise** 和 **Future** 是 C++ 提供的一种机制，用于在线程之间创建一个**单次使用的通信通道**。
    - Promise是通道的发送端：
        - 工作线程通过 Promise 发送数据或异常。
    - Future是通道的接收端：
        - 父线程通过 Future 接收数据或异常。
4. **Promise 和 Future 的作用**：
    - 通过这种机制，父线程可以在工作线程执行完成后，获取工作线程的结果（数据或异常）。
    - 这种机制为线程间的通信提供了更灵活、更安全的方式。



### The promise - future communication channel

The methods for passing data to a thread we have discussed so far are both useful during thread construction: We can **either pass arguments to the thread function using variadic templates** or we can **use a Lambda to capture arguments by value or by reference.** The following example illustrates the use of these methods again:

```cpp
#include <iostream>
#include <thread>

void printMessage(std::string message)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // simulate work
    std::cout << "Thread 1: " << message << std::endl;
}

int main()
{
    // define message
    std::string message = "My Message";

    // start thread using variadic templates
    std::thread t1(printMessage, message);

    // start thread using a Lambda
    std::thread t2([message] {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // simulate work
        std::cout << "Thread 2: " << message << std::endl;
    });

    // thread barrier
    t1.join();
    t2.join();

    return 0;
}
```

A **drawback** of these two approaches is that the **information flows from the parent thread (`main`) to the worker threads** (`t1` and `t2`). In this section, **we want to look at a way to pass data in the opposite direction** - that is from the worker threads back to the parent thread.

**In order to achieve this**, the threads need to **adhere to a strict synchronization protocol.** There is such a mechanism available in the C++ standard that we can use for this purpose. This mechanism acts as a **single-use channel between the threads**. The **sending** end of the **channel** is called "**promise**" while the **receiving** end is called "**future**".

In the C++ standard, the class template `std::promise` provides a convenient way to store a value or an exception that will acquired asynchronously at a later time via a `std::future` object. Each `std::promise` object is meant to be used **only a single time.**

In the following example, we want to declare a promise which allows for transmitting a string between two threads and modifying it in the process.

```cpp
#include <iostream>
#include <thread>
#include <future>

void modifyMessage(std::promise<std::string> && prms, std::string message)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // simulate work
    std::string modifiedMessage = message + " has been modified"; 
    prms.set_value(modifiedMessage);
}

int main()
{
    // define message
    std::string messageToThread = "My Message";

    // create promise and future
    std::promise<std::string> prms;
    std::future<std::string> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(modifyMessage, std::move(prms), messageToThread);

    // print original message to console
    std::cout << "Original message from main(): " << messageToThread << std::endl;

    // retrieve modified message via future and print to console
    std::string messageFromThread = ftr.get();
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;

    // thread barrier
    t.join();

    return 0;
}

```

After defining a message, we have to create a suitable promise that can take a string object. **To obtain the corresponding future, we need to call the method `get_future()`** on the promise. Promise and future are the two types of the communication channel we want to use to pass a string between threads. The communication channel set up in this manner can only pass a string.

We can now create a thread that takes a function and we will pass it the promise as an argument as well as the message to be modified. **Promises can not be copied and wish to own by worker thread**, because the promise-future concept is a two-point communication channel for one-time use. Therefore, we must **pass the promise to the thread function using `std::move` which transfer promise to rvalue reference**. The thread will then, during its execution, use the promise to pass back the modified message.

The **thread function** takes the promise as an **rvalue reference** in accordance with move semantics. After waiting for several seconds, the message is modified and the method `set_value()` is called on the promise.

Back in the main thread, after starting the thread, the original message is printed to the console. **Then, we start listening on the other end of the communication channel by calling the function `get()` on the future**. **This method will block until data is available** - which happens as soon as set_value has been called on the promise (from the thread). **If the result is movable (which is the case for `std::string`), it will be moved - otherwise it will be copied instead**. After the data has been received (with a considerable delay), the modified message is printed to the console.

```
Original message from main(): My Message
Modified message from thread(): My Message has been modified
```

It is also possible that the worker value calls **set_value on the promise** **before `get()` is called** on the future. **In this case, `get()` returns immediately without any delay**. **After `get()` has been called once, the future is no longer usable**. This makes sense as the normal mode of data exchange between promise and future works with `std::move` - and in this case, the data is no longer available in the channel after the first call to `get()`. If `get()` is called a second time, an exception is thrown.

### Quiz: get() vs. wait()

There are some situations where it might be interesting to separate the waiting for the content from the actual retrieving. **Futures allow us to do that using the `wait()` function. This method will block until the future is ready**. **Once it returns, it is guaranteed that data is available and we can use `get()` to retrieve it without delay.**

In addition to wait, the C++ standard **also offers the method `wait_for`,** which **takes a time duration as an input** and **also waits for a result** to become available. The **method `wait_for()` will block either until the specified timeout duration has elapsed** or **the result becomes available** - whichever comes first. **The return value identifies the state of the result.**

In the following example, please use the `wait_for` method to wait for the availability of a result for one second. After the time has passed (or the result is available) print the result to the console. Should the time be up without the result being available, print an error message to the console instead.

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <cmath>

void computeSqrt(std::promise<double> &&prms, double input)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // simulate work
    double output = sqrt(input);
    prms.set_value(output);
}

int main()
{
    // define input data
    double inputData = 42.0;

    // create promise and future
    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(computeSqrt, std::move(prms), inputData);

		// Student task STARTS here
		auto status = ftr.wait_for(std::chrono::milliseconds(2050)); // try less 2000, you will get a timeout
		if (status == std::future_status::ready) {
			std::cout << ftr.get() << std::endl;
		} else {
			std::cout << "timeout" << std::endl;
		}

		// Student task ENDS here    

    // thread barrier
    t.join();

    return 0;
}

```

### Passing exceptions

The future-promise communication channel **may also be used for passing exceptions**. To do this, **the worker thread simply sets an exception rather than a value in the promise**. In the parent thread, **the exception is then re-thrown once `get()` is called on the future.**

Let us take a look at the following example to see how this mechanism works:

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

void divideByNumber(std::promise<double> &&prms, double num, double denom)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
    try
    {
        if (denom == 0)
            throw std::runtime_error("Exception from thread: Division by zero!");
        else
            prms.set_value(num / denom);
    }
    catch (...)
    {
        prms.set_exception(std::current_exception());
    }
}

int main()
{
    // create promise and future
    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    // start thread and pass promise as argument
    double num = 42.0, denom = 0.0;
    std::thread t(divideByNumber, std::move(prms), num, denom);

    // retrieve result within try-catch-block
    try
    {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }

    // thread barrier
    t.join();

    return 0;
}

```

**In the thread function**, we **need to implement a try-catch block** which can be set to catch a particular exception or - **as in our case - to catch all exceptions**. **Instead of setting a value, we now want to throw a `std::exception` along with a customized error message**. In the **catch-block, we catch this exception and throw it to the parent thread** using the promise with `set_exception`. The function `std::current_exception` allows us to **easily retrieve the exception which has been thrown**.

On the parent side, we now need to catch this exception. In order to do this, **we can use a try-block around the call to `get()`**. We can **set the catch-block to catch all exceptions** or - as in this example - **we could also catch a particular one such as the standard exception**. Calling the **method `what()` on the exception allows us to retrieve the message from the exception** - which is the one defined on the promise side of the communication channel.

When we run the program, we can see that the exception is being thrown in the worker thread with the main thread printing the corresponding error message to the console.

**So a promise future pair can be used to pass either values or exceptions between threads.**

### Summary

This section explains **how to use promises and futures** to pass strings between threads, emphasizing the importance of move semantics for efficient concurrent programming. **Move semantics, especially with rvalue references,** can greatly enhance code performance and are recommended for deeper exploration. Futures allow you to control when to **retrieve data using the `Get` functio**n, ensuring results are available at specific points in time. **However, promises and futures have two major limitations: they only allow one-way data transfer** (from worker to parent) and **are intended for single use**. **Alternatives will be discussed later**, followed by a comparison of threads and tasks in the next section.

---

## Threads vs. Tasks

### Introduction

#### 线程（Threads）与任务（Tasks）的区别
- **线程方式**：
  - 使用 `std::thread`、`std::promise` 和 `std::future`
  - 需要编写大量样板代码（boilerplate code）
  - 管理复杂，开销较大

- **任务方式**：
  - 使用 `std::async`
  - 代码更简洁
  - 更高层次的抽象
  - 系统可以自动决定执行方式

#### 性能考虑

1. **线程开销**
   - 创建和管理线程有显著的系统开销
   - 不是所有情况下使用线程都能提升性能
   - 有时过多的线程反而会降低运行时性能

2. **任务的优势**
   - 更灵活的执行模型
   - 减少了手动线程管理的复杂性
   - 系统可以优化执行策略

#### 实际应用建议

1. **使用 `std::async` 的场景**
   - 当需要从工作线程返回数据或异常时
   - 需要简单快速的并行处理时
   - 不需要精细控制线程行为时

2. **使用 `std::thread` 的场景**
   - 需要更细粒度的线程控制时
   - 特定的线程同步需求时
   - 复杂的线程交互场景

### Starting threads with async

In the last section we have seen how data can be passed from a worker thread to the parent thread using promises and futures. A **disadvantage** of the **promise-future** approach however is that it is very **cumbersome** (and involves a lot of **boilerplate code**) to pass the promise to the thread function using an rvalue reference and `std::move`. **For** the straight-forward **task** of returning data or exceptions **from a worker thread to the parent thread** however, there is a **simpler** and more convenient way using **`std::async()`** instead of `std::thread()`.

Let us adapt the code example from the last section to use `std::async`:

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

double divideByNumber(double num, double denom)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work

    if (denom == 0)
        throw std::runtime_error("Exception from thread: Division by zero!");

    return num / denom;
}


int main()
{
    // use async to start a task
    double num = 42.0, denom = 2.0;
    std::future<double> ftr = std::async(divideByNumber, num, denom);

    // retrieve result within try-catch-block
    try
    {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
```

The first change we are making is in the thread function: We are **removing the promise from the argument list as well as the try-catch block.** Also, the **return type of the function is changed from void to double** as the result of the computation will be channeled back to the main thread using a simple return. After these changes, the function has no knowledge of threads, nor of futures or promises - **it is a simple function that takes two doubles as arguments and returns a double as a result.** Also, **it will throw an exception when a division by zero is attempted.**

In the main thread, we need to **replace the call to `std::thread` with `std::async`**. Note that **async returns a future**, which we will **use later in the code to retrieve the value** that is returned by the function. A promise, as with `std::thread`, is no longer needed, so the code becomes much shorter. In the try-catch block, nothing has changed - we are still calling `get()` on the future in the try-block and exception-handling happens unaltered in the catch-block. **Also, we do not need to call `join()` any more.** With `async`, **the thread destructor will be called automatically** - which reduces the risk of a concurrency bug.

When we execute the code in the previous example, the output is identical to before, so we **seemingly have the same functionality as before** - or do we? When we use the `std::this_thread::get_id()` to print the system thread ids of the main and of the worker thread, we get the following command line output:

![image_0](assets/image_0.png)

As expected, the **ids between the two threads differ from each other** - **they are running in parallel**. **However, one of the major differences between `std::thread` and `std::async` is that with the latter**, **the system decides wether the associated function should be run asynchronously or synchronously**. **By adjusting the launch parameters of `std::async` manually, we can directly influence wether the associated thread function will be executed synchronously or asynchronously.**

The line

```cpp
    std::future<double> ftr = std::async(std::launch::deferred, divideByNumber, num, denom);
```

enforces the **synchronous** execution of `divideByNumber`, which results in the following output, where the thread ids for main and worker thread are identical.

<img src="assets/image_1.png" alt="image_1" style="zoom:50%;" />

If we were to use the launch option "**async**" instead of "**deferred**", we would enforce an asynchronous execution whereas the option "**any**" would **leave it to the system to decide** - which is the default.

At this point, let us compare `std::thread` with `std::async`: **Internally**, `std::async` creates a promise, gets a future from it and runs a template function that takes the promise, calls our function and then either sets the value or the exception of that promise - depending on function behavior. **The code used internally by `std::async` is more or less identical to the code we used in the previous example**, except that this time it has been generated by the compiler and it is hidden from us - which means that the code we write appears much cleaner and leaner. Also, **`std::async` makes it possible to control the amount of concurrency by passing an optional launch parameter,** which enforces either **synchronous or asynchronous** behavior. This ability, especially when left to the system, allows us to prevent an overload of threads, which would eventually slow down the system as threads consume resources for both management and communication. If we were to use too many threads, the increased resource consumption would outweigh the advantages of parallelism and slow down the program. By leaving the decision to the system, we can ensure that the number of threads is chosen in a carefully balanced way that optimizes runtime

### Task-based concurrency

**Determining the optimal number of threads to use is a hard problem**. It usually depends on the number of available cores wether it makes sense to execute code as a thread or in a sequential manner. The use of **`std::async` (and thus tasks)** **take the burden of this decision away from the user** and **let the system decide wether to execute the code sequentially or as a thread**. With **tasks**, the programmer decides what CAN be run in parallel in principle and the system then decides at runtime what WILL be run in parallel.

**Internally**, this is achieved by using **thread-pools** wich represent the number of available threads based on the cores/processors as well as **by using work-stealing queues,** where tasks are re-distributed among the available processors dynamically. The following diagram shows the principal of task distribution on a multi-core system using work stealing queues.

<img src="assets/C3-3-A3a-5551381.png" alt="C3-3-A3a" style="zoom:50%;" />

As can be seen, the first core in the example is heavily oversubscribed with several tasks that are waiting to be executed. The other cores however are running idle. **The idea of a work-stealing queue is to have a watchdog program running in the background that regularly monitors the amount of work performed by each processor and redistributes it as needed.** For the above example this would mean that tasks waiting for execution on the first core would be shifted (or "stolen") from busy cores and added to available free cores such that idle time is reduced. After this rearranging procedire, the task distribution in our example could look as shown in the following diagram.

![C3-3-A3b](assets/C3-3-A3b-5551393.png)

**A work distribution in this manner can only work, when parallelism is explicitly described in the program by the programmer. If this is not the case, work-stealing will not perform effectively.**

To conclude this section, a general **comparison** of task-based and thread-based programming is given in the following:

- With **tasks**
    - the **system takes care** of many details (e.g. join). 
    - Tasks on the other hand are more **light-weight** as they will be using a pool of already created threads (the "**thread pool**").

- With **threads**
    - the **programmer is responsible** for many details. 
    - As far as resources go, threads are usually more **heavy-weight** as they are generated by the operating system (OS). It takes time for the OS to be called and to allocate memory / stack / kernel data structures for the thread. Also, destroying the thread is expensive. 

**Threads** and **tasks** are used for different problems. 

| **场景类型**   | **任务（Tasks）使用场景**                                    | **线程（Threads）使用场景**                                  |
| -------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **计算处理**   | • 大数据并行计算<br>• 图像处理<br>• 科学计算<br>• 批量数据转换 | • 需要精确控制执行顺序的计算<br>• 实时计算处理<br>• 持续性的数据处理 |
| **I/O 操作**   | • 短期的异步文件读写<br>• 并发 API 调用<br>• 快速数据库查询  | • 长连接网络通信<br>• 持续性文件监控<br>• 阻塞式 I/O 操作    |
| **用户交互**   | • UI 事件处理<br>• 短期后台任务<br>• 动画渲染                | • 用户输入监听<br>• 后台服务进程<br>• 实时数据更新           |
| **服务端应用** | • HTTP 请求处理<br>• 微服务调用<br>• 快速数据缓存            | • WebSocket 连接<br>• 数据库连接池<br>• 消息队列处理         |
| **系统服务**   | • 定时任务执行<br>• 系统状态检查<br>• 配置更新               | • 守护进程<br>• 系统监控<br>• 日志记录服务                   |
| **资源管理**   | • 内存池操作<br>• 临时资源分配<br>• 缓存管理                 | • 持久连接管理<br>• 设备监控<br>• 资源锁控制                 |
| **并发控制**   | • 自动负载均衡<br>• 动态任务调度<br>• 并行计算加速           | • 手动线程同步<br>• 临界区控制<br>• 死锁预防                 |
| **实时处理**   | • 快速响应事件<br>• 实时数据分析<br>• 即时计算               | • 实时数据流处理<br>• 传感器数据采集<br>• 持续性监控         |

选择建议：

1. **选择任务（Tasks）当：**
   - 需要快速完成的并行操作
   - 任务之间相对独立
   - 不需要复杂的线程控制
   - 系统资源有限

2. **选择线程（Threads）当：**
   - 需要长期运行的操作
   - 需要精细的线程控制
   - 处理阻塞式操作
   - 需要自定义线程行为

### Assessing the advantage of parallel execution

In this section, we want to explore the **influence of the number of threads** on the performance of a program with respect to its **overall runtime**. The example below has a thread function called "workerThread" which contains a loop with an adjustable number of cycles in which a mathematical operation is performed.

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <vector>
#include <chrono>

void workerFunction(int n)
{
    // print system id of worker thread
    std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl;

    // perform work
    for (int i = 0; i < n; ++i)
    {
        sqrt(12345.6789);
    }
}

int main()
{
    // print system id of worker thread
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    // start time measurement
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    
    // launch various tasks
    std::vector<std::future<void>> futures;
    int nLoops = 10, nThreads = 5;
    for (int i = 0; i < nThreads; ++i)
    {
        futures.emplace_back(std::async(workerFunction, nLoops));
    }

    // wait for tasks to complete
    for (const std::future<void> &ftr : futures)
        ftr.wait();

    // stop time measurement and print execution time
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Execution finished after " << duration <<" microseconds" << std::endl;
    
    return 0;
}
```

In `main()`, a for-loop starts a configurable number of tasks that can either be executed synchronously or asynchronously. As an experiment, we will now use a number of different parameter settings to execute the program and evaluate the time it takes to finish the computations. The idea is to gauge the effect of the number of threads on the overall runtime:

1. int nLoops = 1e7 , nThreads = 4 , std::launch::async

    ![image_2](assets/image_2.png)

    - **描述**：在 4 个线程中并行计算 10,000,000 次平方根。
    - **结果**：总运行时间约为 45 毫秒。
    - 分析：
        - 使用 `std::launch::async`，任务以异步方式运行，线程间并行执行。
        - 并行执行显著加快了计算速度，充分利用了 4 核处理器的性能。

2. int nLoops = 1e7 , nThreads = 5 , std::launch::deferred

    ![image_3](assets/image_3-5571053.png)

    - **描述**：在 5 个线程中顺序计算 10,000,000 次平方根。
    - **结果**：总运行时间约为 126 毫秒。
    - 分析：
        - 使用 `std::launch::deferred`，任务按顺序执行，未利用多核并行能力。
        - 与设置 1 相比，运行时间显著增加，但仍然是合理的，因为任务是顺序执行的。

3. int nLoops = 10 , nThreads = 5 , std::launch::async

    ![image_4](assets/image_4.png)

    - **描述**：在 5 个线程中并行计算 10 次平方根。
    - **结果**：总运行时间约为 3 毫秒。
    - 分析：
        - 尽管任务以异步方式运行，但计算量很小，线程管理的开销（如线程启动和切换）占据了较大比例。
        - 总体运行时间较短，但并行化的优势不明显。

4. int nLoops = 10 , nThreads = 5 , std::launch::deferred

    ![image_5](assets/image_5-5571228.png)

    - **描述**：在 5 个线程中顺序计算 10 次平方根。
    - **结果**：总运行时间约为 0.01 毫秒。
    - 分析：
        - 使用 `std::launch::deferred`，任务按顺序执行，避免了线程管理的开销。
        - 由于计算量极小，顺序执行的效率更高。

    ### **5. 关键结论**

    - **并行化的优劣**：并行执行（异步模式）并不总是更快。对于小任务，线程管理的开销可能超过计算本身的时间。
    - 任务量与线程数量的平衡：
        - 对于计算量大的任务（如设置 1 和 2），并行化可以显著提高效率。
        - 对于计算量小的任务（如设置 3 和 4），顺序执行可能更高效。
    - **硬件限制**：并行化的速度提升受限于硬件（如 CPU 核心数）。在多核机器上，线程数超过核心数可能导致性能下降。

### Summary

The text discusses the choice between using `std::thread` and `std::async` in C++ for managing threads. Generally, `std::async` is simpler and requires less boilerplate code, as it eliminates the need for explicitly calling `join` or managing promises. It provides a future per task, which can handle data exchange, parsing exceptions, and act as a barrier. However, `std::thread` offers finer control in certain situations, making it preferable for more complex tasks. Bjarne Stroustrup, the creator of C++, emphasizes that `std::async` is designed for simplicity and common cases, **while `std::thread` is better suited for complex scenarios involving I/O, mutexes, or thread interactions.** The text concludes by hinting at the challenges of data races in concurrent programming.







---

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

















