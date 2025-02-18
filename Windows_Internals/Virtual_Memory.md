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

## Virtual Memory
Virtual memory provides each process with a [`private virtual address space (VAS)`](https://learn.microsoft.com/en-us/windows/win32/memory/virtual-address-space) that allows them to access a private address space without directly interacting with physical memory (RAM). Because of this interact with memory as if it was physical memory `without the risk of collisions`.

The theoretical maximum virtual address space is `4 GB on a 32-bit x86 system`.

The theoretical maximum virtual address space is `256 TB on a 64-bit modern system`.

This address space is split in half, the lower half (`0x00000000 - 0x7FFFFFFF`) is allocated to processes as mentioned above. The upper half (`0x80000000 - 0xFFFFFFFF`) is allocated to OS memory utilization. 

The exact address `layout ratio` from the 32-bit system is allocated to the 64-bit system.

![Layout ratio](/Windows_Internals/Images/Layout_ratio.png)

Administrators can alter this allocation layout for applications that require a larger address space through settings (`increaseUserVA`) or the AWE (`Address Windowing Extensions`). Most issues that require settings or AWE are resolved with the increased theoretical maximum.

Although this concept does not directly translate to Windows internals or concepts, it is crucial to understand. If understood correctly, it can be leveraged to aid in abusing Windows internals.

## Why use virtual memory?
- Programs used to crash because they would use more memory than physically available.

    Solution:
    
    A `memory map` or `mapper` that is responsible for translating virtual addresses to physical addresses:
    - `Efficient memory usage`: To prevent a program from using more physical memory than physically possible memory can be `swapped between RAM and disk` as needed. Shared libraries can also be mapped so that both programs use the same shared library.
    - `Swap memory`: Whenever this data swapping happens the OS will find the oldest data move it to disk and load the accessed address.

- Memory fragmentation used to be an issue. Programs would take up the middle part of the memory space and there would be unusable chunks at the top and bottom. Essentially running out of space.

    Solution: With virtual memory we can map parts of the program into the available chunks.

- If a program wouldn't have it's own seperate memory contain then all memory would be shared. This could lead to security issues where a program could write to the same memory as another program.

    Solution: Because of the mapper, programs can still write to the same memory address within their own address space. These addresses then get mapped to different location in the physical address space.

![Pages](/Windows_Internals/Images/Pages.png)


> [!NOTE]
> When data is not available in RAM and the OS has to read it from disk, we call this a `PAGE FAULT`.

## Page Tables & Pages
To manage memory efficiently, the system needs a way to track where virtual addresses are stored in physical memory. This is done using `Page Tables`.

Each entry in a page table is called a `Page Table Entry (PTE)`, and it maps a chunk of virtual memory (a "page") to a location in physical memory.

### Why use page tables?
Imagine every byte or WORD in memory has a unique address, like a street address. Instead of keeping track of every single byte individually, the system groups memory into `pages` (blocks of memory, `typically 4KB in size`).

How does it work?:
- A 32-bit system has `4GB of virtual address space`.
- Instead of managing 4 billion individual addresses, memory is divided into `pages of 4KB each`.
- Each page table now only needs one `entry per page` instead of one per byte.
- This `reduces the size` of page tables from 4GB to 4MB per program.

Each process gets its own page table, which allows the system to manage memory efficiently without conflicts between programs.

## Two main data structures in virtual memory
Data structures do essentially what the word means, they structure the data. The two main structures used in memory are the `stack` and the `heap`. But there are actually a lot more and they're also important.

## Memory layout overview
Here is an extremely simplified overview of how memory is laid out in Windows.

Remember that everything within the `User-Space or Userland get mapped randomly into memory` because of `Address space layout randomization (ASLR)`.

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

### Memory Directives or Segments
Directives are commands recognized by the compiler used for assembling the program used for different segments/sections in which data or code is stored in memory. 
- NOT part of the intel instruction set. Recognized by the MASM assembler itself, rather than actual CPU instructions that the processor executes.
- DO NOT execute at runtime
- NOT case sensitive

### Key Differences Between x86 and x86-64 Directives
| Aspect | x86 (32-bit) | x86-64 (64-bit) |
|-|-|-|
| Address Space | `4 GB` total for all sections. | Vastly larger (up to `256 TB` practical). | 
| Instruction Size | 32-bit instructions. | 64-bit instructions, with access to more registers and addressing modes. | 
| Data Size | Variables and pointers are typically `32 bits wide`. | Variables and pointers can be `64 bits wide`. | 
| Register Access | Limited to `8 general-purpose registers` (EAX, EBX, etc.). | Access to `16 general-purpose registers` (RAX, RBX, etc.). |

### Two main directives
- `.data`: Stores initialized global and static variables. Values are known at compile time. Like identifiers.
- `.code`: Stores the executable instructions (program code).

### Other directives
- `.bss`: Stores uninitialized global and static variables. Initialized to zero at runtime.

- `.stack`: Allocated for the runtime stack (automatic variables, function calls).

- `.heap`: Allocated for dynamically allocated memory (e.g., malloc, new).

## PEB
The Process Environment Block (PEB) is a small memory range that stores `information about the process and the loaded modules`. One piece of information the PEB contains is "`BeingDebugged`" which can be used to determine if the current process is being debugged.

To read more about the PEB structure layout read [microsoft learn PEB structure (winternl.h)](https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb)

| Storage for process-specific information |
|-|
| Environment variables (inherited from the previous process) |
| Command line arguments |
| Current working directory |
| Current loaded modules |
| Heap pointer |

## TEB
The Thread Environment Block (TEB) is a small memory range that stores `information about the currently running thread(s)`.

| Storage for thread-specific information |
|-|
| Thread ID |
| Stack range |
| GetLastError |
| [TLS](/Windows_Internals/Processes_And_Threads.md#thread-context) |

<details>
<summary> Kernel structure </summary>

```C
//0x38 bytes (sizeof)
struct _NT_TIB
{
    struct _EXCEPTION_REGISTRATION_RECORD* ExceptionList;                   //gs: [0x0]
    VOID* StackBase;                                                        //0x8
    VOID* StackLimit;                                                       //0x10
    VOID* SubSystemTib;                                                     //0x18
    union
    {
        VOID* FiberData;                                                    //0x20
        ULONG Version;                                                      //0x20
    };
    VOID* ArbitraryUserPointer;                                             //0x28
    struct _NT_TIB* Self;                                                   //0x30
}; 
```
</details>