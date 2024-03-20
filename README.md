<!-- markdownlint-disable MD032 MD033-->
# **C, From Zero to Hero**

## Overview

This README documents the journey from basic to advanced C programming concepts, covering a wide range of topics from basic syntax and data types to multi-threading and network programming.

## Table of Contents

1. **Introduction to C**
    - Syntax Basics
    - Data Types
    - Control Structures

2. **Functions and Memory Management**
    - Function Declarations and Definitions
    - Stack vs Heap Memory
    - Dynamic Memory Allocation (`malloc`, `free`)

3. **Data Structures**
    - Arrays and Strings
    - Structs and Unions
    - Pointers and Pointer Arithmetic

4. **File I/O**
    - Reading and Writing Files
    - Binary vs Text Files

5. **Multi-threading**
    - Creating Threads (`pthread_create`)
    - Mutexes for Synchronization
    - Condition Variables

6. **Signal Handling**
    - Basic Signal Handling (`signal`)
    - Real-time Signals
    - Sending Information with Signals (`sigqueue`)

7. **Network Programming**
    - Sockets and Connections
    - Building a Simple TCP Client
    - HTTP Requests and Responses

8. **Advanced Topics**
    - Thread Safety and Async-Signal Safety
    - Managing Signal Masks (`sigprocmask`)
    - Signal Handling in Multi-threaded Contexts

## Key Concepts and Examples

### Multi-threading in C

Multi-threading allows for concurrent execution paths within a program. Using `pthread` library, we explored thread creation, mutexes for mutual exclusion, and condition variables for thread synchronization.

### Signal Handling

We discussed how to handle UNIX signals in C, including setting up signal handlers and using real-time signals for inter-process communication.

### Network Programming

Creating networked applications in C, we built a simple TCP client that connects to a server and sends an HTTP GET request to fetch a web page.

### Advanced Topics

Delving into advanced C programming, we covered thread and signal safety, manipulating signal masks, and the nuances of signal handling in a multi-threaded environment.

## Conclusion

This journey through C programming has touched upon many fundamental and advanced topics. By building on the basics and progressively introducing more complex concepts, we've developed a solid foundation in C programming and systems programming.
