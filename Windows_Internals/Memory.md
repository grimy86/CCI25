# Memory
If you're unfamiliar with what memory is at all take a look at the [x86-64 assembly guide](/Programming_Foundations/Assembly/Architecture/Memory.md).

For the sake of windows internals we'll cover memory a little more in-depth.

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
Data structures do essentially what the word means, they structure the data. The two main structures used in memory are the stack and the heap. But there are actually a lot more and they're also important.

## Memory layout overview
The system's memory is organized in a specific way. This is done to make sure everything has a place to reside in. Here is a general overview of how memory is laid out in Windows. This is extremely simplified.

In here we'll also dive just a bit deeper into how the stack and the heap are layed out in memory. Before we do so, remember that everything within the `User-Space or Userland get mapped randomly into memory`.

![Windows memory layout](/Programming_Foundations/Assembly/Images/WindowsMemoryLayoutRF.png)

Here's another depiction of memory.

![Win32 memory map](/Windows_Internals/Images/Win32_memory_map.png)

> [!IMPORTANT]
>
> The diagram above shows the direction variables (and any named data, even structures) are put into or taken out of memory. The actual data is put into memory differently. This is why stack diagrams vary so much. You'll often see stack diagrams with the stack and heap growing towards each other or high memory addresses at the top. However, this diagram is the most relevant for reverse engineering. Low addresses being at the top is also the most realistic depiction.

## Stack
The stack is a region of memory located in RAM, typically near the upper end of the process's allocated memory space.

 Its specific location is determined by the operating system and hardware architecture, but it always adheres to certain principles.

For now it's important to take note of two things:
1. When data is pushed onto the stack, the stack grows up (negatively), towards lower memory addresses.
2. When data is popped off the stack, the stack shrinks down, towards higher addresses.

That all may seem odd but remember, it's like a normal numerical list where 1, the lower number, is at the top. 10, the higher number, is at the bottom.

 To dive deeper into how the stack works read the [Call stack file](/Programming_Foundations/Assembly/Architecture/Call_stack.md).

## Heap
The heap is a region of memory in RAM that is used for dynamic memory allocation, where variables or objects are created and destroyed at runtime (long-time large data objects). Unlike the stack, the heap is not managed automatically by the CPU; it is managed by the programmer or a memory manager (e.g., the operating system or language runtime).

The heap is not really ordered in any way and can just be extended at runtime.

Languages like C++ make you manage dynamically allocated objects yourself while other languages like C# have the CLR (Common Language Runtime) of it's .NET framework that manages this.

The heap is typically used for data that is dynamic (changing or unpredictable). Things such as structures and user input might be stored on the heap. If the size of the data isn't known at compile-time, it's usually stored on the heap. When you add data to the heap it grows towards higher addresses.

## Program image
This is the `program/executable loaded into memory`. On Windows, this is typically `a Portable Executable (PE)`.

## Key Differences Between x86 and x86-64 Directives
| Aspect | x86 (32-bit) | x86-64 (64-bit) |
|-|-|-|
| Address Space | `4 GB` total for all sections. | Vastly larger (up to `256 TB` practical). | 
| Instruction Size | 32-bit instructions. | 64-bit instructions, with access to more registers and addressing modes. | 
| Data Size | Variables and pointers are typically `32 bits wide`. | Variables and pointers can be `64 bits wide`. | 
| Register Access | Limited to `8 general-purpose registers` (EAX, EBX, etc.). | Access to `16 general-purpose registers` (RAX, RBX, etc.). |

## Memory Directives or Segments
Directives are commands recognized by the compiler used for assembling the program used for different segments/sections in which data or code is stored in memory. 
- NOT part of the intel instruction set. Recognized by the MASM assembler itself, rather than actual CPU instructions that the processor executes.
- DO NOT execute at runtime
- NOT case sensitive

### Two main directives
- `.data`: Stores initialized global and static variables. Values are known at compile time. Like identifiers.
- `.code`: Stores the executable instructions (program code).

### Other directives
- `.bss`: Stores uninitialized global and static variables. Initialized to zero at runtime.

- `.stack`: Allocated for the runtime stack (automatic variables, function calls).

- `.heap`: Allocated for dynamically allocated memory (e.g., malloc, new).

## PEB
The Process Environment Block (PEB) stores `information about the process and the loaded modules`. One piece of information the PEB contains is "`BeingDebugged`" which can be used to determine if the current process is being debugged.

To read more about the PEB structure layout read [microsoft learn PEB structure (winternl.h)](https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb)

## TEB
The Thread Environment Block (TEB) `stores information about the currently running thread(s)`.

## Virtual memory
`Virtual memory` is a critical component of how Windows internals work and interact with each other. Virtual memory allows other internal components to interact with memory `as if it was physical memory without the risk of collisions between applications`.

Virtual memory provides each process with a [`private virtual address space`](https://learn.microsoft.com/en-us/windows/win32/memory/virtual-address-space). A `memory manager` is used to `translate virtual addresses to physical addresses`. By having a private virtual address space and not directly writing to physical memory, `processes have less risk of causing damage`. The memory manager will also use `pages or transfers` to handle memory.

Applications may use more virtual memory than physical memory allocated; the memory manager will transfer or page virtual memory to the disk to solve this problem. You can visualize this concept in the diagram below.

![Pages](/Windows_Internals/Images/Pages.png)

The theoretical maximum virtual address space is `4 GB on a 32-bit x86 system`.

The theoretical maximum virtual address space is `256 TB on a 64-bit modern system`.

This address space is split in half, the lower half (`0x00000000 - 0x7FFFFFFF`) is allocated to processes as mentioned above. The upper half (`0x80000000 - 0xFFFFFFFF`) is allocated to OS memory utilization. 

The exact address `layout ratio` from the 32-bit system is allocated to the 64-bit system.

![Layout ratio](/Windows_Internals/Images/Layout_ratio.png)

Administrators can alter this allocation layout for applications that require a larger address space through settings (`increaseUserVA`) or the AWE (`Address Windowing Extensions`). Most issues that require settings or AWE are resolved with the increased theoretical maximum.

Although this concept does not directly translate to Windows internals or concepts, it is crucial to understand. If understood correctly, it can be leveraged to aid in abusing Windows internals.

Watch [Tech with Nikola's video about virtual memory](https://www.youtube.com/watch?v=A9WLYbE0p-I).
