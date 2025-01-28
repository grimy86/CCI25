# Windows Internals
Windows Internals refers to the core components that make up the architecture of the Windows operating system.

Think of Windows Internals as the “engine” of the operating system—it’s what keeps everything running smoothly behind the scenes. Without it, applications wouldn’t work, hardware wouldn’t communicate with software, and the system itself wouldn’t even boot up.

These internals cannot change without compromising how the operating system operates at a bare-bones level. Because of this, this architecture is also where the system is most vulnerable.

## Securable objects
At the lowest level, everything in windows is a securable object. This means that all of these components that make up the internals architecutre are all able to have security permissions attached to them.

Eventually this could lead to insecure permissions:
- Service executables
- DLLs loaded by privileged processes
- Registry keys with configurations settings
- Named pipes
- Process and thread objects
- Service configurations
- etc.

This is something we dove into when covering [Windows Privesc](/Cybersecurity_Operations/Maintaining%20Access/WinPrivesc.md).

## Processes
First off, think of a `program` like a recipe, it's a static set of instructions inside of a .exe `file` that just sits there and does nothing unless you tell your operating system to "run" the program. When you actually run the program, it becomes a `process` (or multiple). It's an `instance of the program that is being ran`.

A process maintains and represents the execution of a program; an application can contain one or more processes. A process has many `components` that it gets broken down into to be stored and interacted with. The [Microsoft docs](https://learn.microsoft.com/en-us/windows/win32/procthread/about-processes-and-threads) break down these other components.

Here's a few examples of default applications that start processes:
- MsMpEng (Microsoft Defender)
- wininit (keyboard and mouse)
- lsass (credential storage)

### Process components
Processes have many components they can be split into key characteristics that we can use to describe processes.

#### Named pipes
Named pipes are just a mechanism for two processes to talk to eachother. This comes with another more windows-specific vulnerability; name squatting.

1. Create a named pipe that is used for client-server communication.
2. Start a client that uses said pipe.
3. Use client impersonation to get client priveleges.

#### High-level components
| Component | Purpose |
|-|-|
| `Name` | Define the name of the process, typically inherited from the application. |
| `Status` | Determines how the process is running (running, suspended, etc.) |
| `User name` | User that initiated the process. Can denote privilege of the process |
| `Private Virtual Address Space` | Virtual memory addresses that the process is allocated. |
| `Executable Program` | Defines code and data stored in the virtual address space. |
| `Open Handles` | Defines handles to system resources accessible to the process. |
| `Security Context` | The access token defines the user, security groups, privileges, and other security information. |
| `Process ID (PID)` | Unique numerical identifier of the process. |
| `Threads` | Section of a process scheduled for execution. |

#### Low-level components
| Component | Purpose |
|-|-|
| `Code` | Code to be executed by the process. |
| `Global Variables` | Stored variables. |
| `Process Heap` | Defines the heap where data is stored. |
| `Process Resources` | Defines further resources of the process. |
| `Environment Block` | Data structure to define process information. |

![Process](/Windows_Internals/Images/Process.png)

#### Tools
There are multiple utilities available that make observing processes easier:
- [Process Hacker 2 / System informer](https://github.com/winsiderss/systeminformer)
- [Process Explorer](https://learn.microsoft.com/en-us/sysinternals/downloads/process-explorer)
- [Procmon](https://learn.microsoft.com/en-us/sysinternals/downloads/procmon)

## Threads
A `thread` is an `executable unit` employed by a process and scheduled based on device factors.

Device factors can vary based on CPU and memory specifications, priority and logical factors, and others.

We can simplify the definition of a thread: `controlling the execution of a process`.

Since threads control execution, this is a commonly targeted component. Thread abuse can be used on its own to aid in code execution, or it is more widely used to chain with other API calls as part of other techniques. 

Threads share the same details and resources as their parent process, such as code, global variables, etc. 

Threads also have their unique values and data:
| Component | Purpose |
|-|-|
| `Stack` | All data relevant and specific to the thread (exceptions, procedure calls, etc.) |
| `Thread Local Storage` | Pointers for allocating storage to a unique data environment |
| `Stack Argument` | Unique value assigned to each thread |
| `Context Structure` | Holds machine register values maintained by the kernel |

Threads may seem like bare-bones and simple components, but their function is critical to processes.

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

## Dynamic Link Libraries

TO DO:
1. Introduction
2. Processes
3. Process creation (Kernel)
4. PE file format
5. PEB & TEB
6. Calling conventions
7. DllMain / TLS Callbacks
8. Debuggers
9. LdrInitializeThunk
10. RtlUserThreadStart
11. Syscalls
12. Callbacks
13. Process Monitor