# Memory
You could see memory as a collection of small and large databases or containers to store our information for later processing. Every byte of memory has a unique address that allows the CPU to locate it.

All of this memory is managed by the operating system.

## Types
Memory in computers is typically divided into two broad categories: volatile and non-volatile. Each serves a different purpose and operates at varying speeds and capacities.

### Volatile memory
Volatile memory requires power to retain data. When the system is powered off, the data is lost.
- Random access memory (RAM): emporary storage for data and instructions that the CPU is actively using.
  - DRAM (Dynamic RAM): Most common type of RAM, slower but cheaper.
  - SRAM (Static RAM): Faster and more expensive, used for CPU caches.
- Cache: A very small, high-speed memory located inside or close to the CPU.
- Registers: The fastest form of memory inside the CPU.

### Non-volatile memory
- ROM (Read-Only Memory): Permanent storage for critical data, such as the system's firmware.
- Storage (e.g., SSDs, HDDs): Long-term data storage for the operating system, applications, and user files.
  - HDD (Hard Disk Drive): Magnetic storage, slower but cheaper and durable.
  - SSD (Solid State Drive): Flash-based, faster and more reliable, but more expensive per GB.
- Flash Memory: Used in USB drives, SD cards, and some SSDs.

## Memory Hierarchy
Memory in a computer system is structured as a hierarchy, based on speed, size, and proximity to the CPU:
| Level | Type | Speed | Capacity | Proximity |
|-|-|-|-|-|
| 1 (Fastest) | Registers | Fastest | Very small | Inside the CPU |
| 2 | Cache (L1, L2, L3) | Very fast | Small | Near / inside the CPU |
| 3 | RAM | Fast | Medium | Motherboard slots |
| 4 (Slowest) | Storage (SSD/HDD) | Slow | Large | External |

## How Memory Works Together
- Registers hold immediate data for the CPU to process.
- Cache stores frequently accessed data to reduce the time needed to fetch it from RAM.
- RAM acts as a workspace for active programs and the operating system.
- Storage holds long-term data, which is loaded into RAM when needed.
- Virtual Memory (a part of storage) is used when RAM is full, though it is much slower.

## Programs
As we know the operating system manages where our memory goes. For programs that need to be executed they get allocated to RAM.

### Data structures
Data structures do essentially what the word means, they structure the data. The two main structures used in memory are the stack and the heap.

## Memory layout
The system's memory is organized in a specific way. This is done to make sure everything has a place to reside in.

### Memory Directives or Segments
Directives are commands recognized by the compiler used for assembling the program used for different segments/sections in which data or code is stored in memory. 
- NOT part of the intel instruction set. Recognized by the MASM assembler itself, rather than actual CPU instructions that the processor executes.
- DO NOT execute at runtime
- NOT case sensitive

#### Two main directives
- `.data`: Stores initialized global and static variables. Values are known at compile time. Like identifiers.
- `.code`: Stores the executable instructions (program code).

#### Other directives
- `.bss`: Stores uninitialized global and static variables. Initialized to zero at runtime.

- `.stack`: Allocated for the runtime stack (automatic variables, function calls).

- `.heap`: Allocated for dynamically allocated memory (e.g., malloc, new).

### Overview of Memory Sections
Here is a general overview of how memory is laid out in Windows. This is extremely simplified.

In here we'll also dive just a bit deeper into how the stack and the heap are layed out in memory.

![Windows memory layout](/Programming_Foundations/Assembly/Images/WindowsMemoryLayoutRF.png)

> [!IMPORTANT]
>
> The diagram above shows the direction variables (and any named data, even structures) are put into or taken out of memory. The actual data is put into memory differently. This is why stack diagrams vary so much. You'll often see stack diagrams with the stack and heap growing towards each other or high memory addresses at the top. However, this diagram is the most relevant for reverse engineering. Low addresses being at the top is also the most realistic depiction.

### Stack
The stack is a region of memory located in RAM, typically near the upper end of the process's allocated memory space.

 Its specific location is determined by the operating system and hardware architecture, but it always adheres to certain principles.

For now it's important to take note of two things:
1. When data is pushed onto the stack, the stack grows up (negatively), towards lower memory addresses.
2. When data is popped off the stack, the stack shrinks down, towards higher addresses.

That all may seem odd but remember, it's like a normal numerical list where 1, the lower number, is at the top. 10, the higher number, is at the bottom.

 To dive deeper into how the stack works read the [Call stack file](/Programming_Foundations/Assembly/Architecture/Call_stack.md).

### Heap
The heap is a region of memory in RAM that is used for dynamic memory allocation, where variables or objects are created and destroyed at runtime (long-time large data objects). Unlike the stack, the heap is not managed automatically by the CPU; it is managed by the programmer or a memory manager (e.g., the operating system or language runtime).

The heap is not really ordered in any way and can just be extended at runtime.

Languages like C++ make you manage dynamically allocated objects yourself while other languages like C# have the CLR (Common Language Runtime) of it's .NET framework that manages this.

The heap is typically used for data that is dynamic (changing or unpredictable). Things such as structures and user input might be stored on the heap. If the size of the data isn't known at compile-time, it's usually stored on the heap. When you add data to the heap it grows towards higher addresses.

### TEB
The Thread Environment Block (TEB) stores information about the currently running thread(s).

### PEB
The Process Environment Block (PEB) stores information about the process and the loaded modules. One piece of information the PEB contains is "BeingDebugged" which can be used to determine if the current process is being debugged.

To read more about the PEB structure layout read [microsoft learn PEB structure (winternl.h)](https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb)

### Program image
This is the program/executable loaded into memory. On Windows, this is typically a Portable Executable (PE).

## Key Differences Between x86 and x86-64 Directives
| Aspect | x86 (32-bit) | x86-64 (64-bit) |
|-|-|-|
| Address Space | 4 GB total for all sections. | Vastly larger (up to 256 TB practical). | 
| Instruction Size | 32-bit instructions. | 64-bit instructions, with access to more registers and addressing modes. | 
| Data Size | Variables and pointers are typically 32 bits wide. | Variables and pointers can be 64 bits wide. | 
| Register Access |Limited to 8 general-purpose registers (EAX, EBX, etc.). | Access to 16 general-purpose registers (RAX, RBX, etc.). |

