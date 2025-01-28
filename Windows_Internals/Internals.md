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

<!--### Process creation (Kernel)??-->


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

Watch [Tech with Nikola's video about virtual memory](https://www.youtube.com/watch?v=A9WLYbE0p-I).

## Dynamic Link Libraries
The [Microsoft docs](https://learn.microsoft.com/en-us/troubleshoot/windows-client/setup-upgrade-and-drivers/dynamic-link-library) describe a `DLL` as "a `library that contains code and data that can be used by more than one program at the same time`."

DLLs are used as one of the core functionalities behind application execution in Windows. From the Windows documentation, "The use of DLLs helps promote modularization of code, code reuse, efficient memory usage, and reduced disk space. So, the operating system and the programs load faster, run faster, and take less disk space on the computer."

When a DLL is loaded as a function in a program, the DLL is assigned as a `dependency`. Since a program is dependent on a DLL, attackers can target the DLLs rather than the applications to control some aspect of execution or functionality.

DLLs are created no different than any other project/application; they only require slight syntax modification to work. Below is an example of a DLL from the `Visual C++ Win32 Dynamic-Link Library project`:

```cpp
#include "stdafx.h"
#define EXPORTING_DLL
#include "sampleDLL.h"
BOOL APIENTRY DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved
)
{
    return TRUE;
}
void HelloWorld()
{
    MessageBox( NULL, TEXT("Hello World"), TEXT("In a DLL"), MB_OK);
}
```

Below is the `header file` for the DLL; it will define what functions are imported and exported:

```cpp
#ifndef INDLL_H
    #define INDLL_H
    #ifdef EXPORTING_DLL
        extern __declspec(dllexport) void HelloWorld();
    #else
        extern __declspec(dllimport) void HelloWorld();
    #endif
#endif
```

### How are they used by an application?
#### load-time dynamic linking:
When loaded using load-time dynamic linking, `explicit calls to the DLL functions are made from the application`. You can only achieve this type of linking by `providing a header (.h) and import library (.lib) file`. Below is an example of calling an exported DLL function from an application.

```cpp
#include "stdafx.h"
#include "sampleDLL.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HelloWorld();
    return 0;
}
```

#### run-time dynamic linking:
When loaded using run-time dynamic linking, a `separate function` (`LoadLibrary` or `LoadLibraryEx`) is `used to load the DLL at run time`. Once loaded, you need to use `GetProcAddress to identify the exported DLL function to call`. Below is an example of loading and importing a DLL function in an application.

```cpp
...
typedef VOID (*DLLPROC) (LPTSTR);
...
HINSTANCE hinstDLL;
DLLPROC HelloWorld;
BOOL fFreeDLL;
hinstDLL = LoadLibrary("sampleDLL.dll");
if (hinstDLL != NULL)
{
    HelloWorld = (DLLPROC) GetProcAddress(hinstDLL, "HelloWorld");
    if (HelloWorld != NULL)
        (HelloWorld);
    fFreeDLL = FreeLibrary(hinstDLL);
}
...
```

## Portable Executable Format
Executables and applications are a large portion of how Windows internals operate at a higher level. The `PE` (Portable Executable) format `defines the information about the executable and stored data`. The PE format `also defines the structure of how data components are stored`.

The PE (Portable Executable) format is an overarching `structure for executable and object files`. The `PE` (Portable Executable) and `COFF` (Common Object File Format) files make up the PE format.
PE data is most commonly seen in the `hex dump` of an executable file. Below we will break down a hex dump of `calc.exe` into the sections of PE data.

![PE structure](/Windows_Internals/Images/PE_structure.png)

### Header (PE Format)
#### DOS header
The DOS Header defines the type of file.

The `MZ DOS header` defines the file format as `.exe`. The DOS header can be seen in the hex dump section below.

```
Offset(h) 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
00000000  4D 5A 90 00 03 00 00 00 04 00 00 00 FF FF 00 00  MZ..........ÿÿ..
00000010  B8 00 00 00 00 00 00 00 40 00 00 00 00 00 00 00  ¸.......@.......
00000020  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
00000030  00 00 00 00 00 00 00 00 00 00 00 00 E8 00 00 00  ............è...
00000040  0E 1F BA 0E 00 B4 09 CD 21 B8 01 4C CD 21 54 68  ..º..´.Í!¸.LÍ!Th
```

#### DOS stub
The `DOS Stub` is a program run by default at the beginning of a file that prints a compatibility message. This does not affect any functionality of the file for most users.

The DOS stub prints the message: "`This program cannot be run in DOS mode`".

```
00000040  0E 1F BA 0E 00 B4 09 CD 21 B8 01 4C CD 21 54 68  ..º..´.Í!¸.LÍ!Th
00000050  69 73 20 70 72 6F 67 72 61 6D 20 63 61 6E 6E 6F  is program canno
00000060  74 20 62 65 20 72 75 6E 20 69 6E 20 44 4F 53 20  t be run in DOS 
00000070  6D 6F 64 65 2E 0D 0D 0A 24 00 00 00 00 00 00 00  mode....$.......
```

#### PE file header
The PE File Header provides `PE header information of the binary`. Defines the `format` of the file, contains the `signature` and `image file header`, and `other information headers`.

The PE file header is the section with the least human-readable output. You can identify the start of the PE file header from the `PE stub` in the hex dump section below.

```
000000E0  00 00 00 00 00 00 00 00 50 45 00 00 64 86 06 00  ........PE..d†..
000000F0  10 C4 40 03 00 00 00 00 00 00 00 00 F0 00 22 00  .Ä@.........ð.".
00000100  0B 02 0E 14 00 0C 00 00 00 62 00 00 00 00 00 00  .........b......
00000110  70 18 00 00 00 10 00 00 00 00 00 40 01 00 00 00  p..........@....
00000120  00 10 00 00 00 02 00 00 0A 00 00 00 0A 00 00 00  ................
00000130  0A 00 00 00 00 00 00 00 00 B0 00 00 00 04 00 00  .........°......
00000140  63 41 01 00 02 00 60 C1 00 00 08 00 00 00 00 00  cA....`Á........
00000150  00 20 00 00 00 00 00 00 00 00 10 00 00 00 00 00  . ..............
00000160  00 10 00 00 00 00 00 00 00 00 00 00 10 00 00 00  ................
00000170  00 00 00 00 00 00 00 00 94 27 00 00 A0 00 00 00  ........”'.. ...
00000180  00 50 00 00 10 47 00 00 00 40 00 00 F0 00 00 00  .P...G...@..ð...
00000190  00 00 00 00 00 00 00 00 00 A0 00 00 2C 00 00 00  ......... ..,...
000001A0  20 23 00 00 54 00 00 00 00 00 00 00 00 00 00 00   #..T...........
000001B0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
000001C0  10 20 00 00 18 01 00 00 00 00 00 00 00 00 00 00  . ..............
000001D0  28 21 00 00 40 01 00 00 00 00 00 00 00 00 00 00  (!..@...........
000001E0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
```

#### Image optional header
The `Image Optional Header` has a deceiving name and is an important part of the PE File Header.

#### Data dictionaries
The `Data Dictionaries` are part of the image optional header. They point to the image data directory structure.

#### Section Table
The `Section Table` will define the `available sections` and information in the image. As previously discussed, sections store the contents of the file, such as `code`, `imports`, and `data`. You can identify each section definition from the table in the hex dump section below.

```
000001F0  2E 74 65 78 74 00 00 00 D0 0B 00 00 00 10 00 00  .text...Ð.......
00000200  00 0C 00 00 00 04 00 00 00 00 00 00 00 00 00 00  ................
00000210  00 00 00 00 20 00 00 60 2E 72 64 61 74 61 00 00  .... ..`.rdata..
00000220  76 0C 00 00 00 20 00 00 00 0E 00 00 00 10 00 00  v.... ..........
00000230  00 00 00 00 00 00 00 00 00 00 00 00 40 00 00 40  ............@..@
00000240  2E 64 61 74 61 00 00 00 B8 06 00 00 00 30 00 00  .data...¸....0..
00000250  00 02 00 00 00 1E 00 00 00 00 00 00 00 00 00 00  ................
00000260  00 00 00 00 40 00 00 C0 2E 70 64 61 74 61 00 00  ....@..À.pdata..
00000270  F0 00 00 00 00 40 00 00 00 02 00 00 00 20 00 00  ð....@....... ..
00000280  00 00 00 00 00 00 00 00 00 00 00 00 40 00 00 40  ............@..@
00000290  2E 72 73 72 63 00 00 00 10 47 00 00 00 50 00 00  .rsrc....G...P..
000002A0  00 48 00 00 00 22 00 00 00 00 00 00 00 00 00 00  .H..."..........
000002B0  00 00 00 00 40 00 00 40 2E 72 65 6C 6F 63 00 00  ....@..@.reloc..
000002C0  2C 00 00 00 00 A0 00 00 00 02 00 00 00 6A 00 00  ,.... .......j..
000002D0  00 00 00 00 00 00 00 00 00 00 00 00 40 00 00 42  ............@..B
```

Now that the headers have defined the format and function of the file, the `sections can define the contents and data of the file`.
### Sections (contents)
| Section | Purpose |
|-|-|
| `.text` | Contains executable code and entry point |
| `.data`  | Contains initialized data (strings, variables, etc.) |
| `.rdata` or `.idata` | Contains imports (Windows API) and DLLs. |
| `.reloc` | Contains relocation information |
| `.rsrc` | Contains application resources (images, etc.) |
| `.debug` | Contains debug information |

### Tools used to dissect the PE file
Use `Detect it easy` to look at the PE structure.

## Interacting with Windows Internals
### Windows API
Interacting with Windows internals may seem daunting, but it has been dramatically simplified. The most accessible and researched option to interact with Windows Internals is to `interface through Windows API calls`.

- The Windows API provides `native functionality` to interact with the Windows operating system.
- The API contains the `Win32 API` and, less commonly, the `Win64 API`.

The Windows `kernel` will control all programs and processes and `bridge all software and hardware interactions`. This is especially important since most Windows internals components require interaction with memory (or other hardware) in some form.

### Processor modes
An application by default normally cannot interact with the kernel or modify physical hardware and requires an interface. This problem is solved through the use of processor modes and access levels.

A Windows processor has a `user mode` and a `kernel mode`. The processor will switch between these modes `depending on access and requested mode`.
The switch between user mode and kernel mode is often `facilitated by system and API calls`. In documentation, this point is sometimes referred to as the "`Switching Point`."

| User mode | Kernel Mode |
| No direct hardware access | Direct hardware access |
| Creates a process in a private virtual address space | Ran in a single shared virtual address space |
| Access to "owned memory locations" | Access to entire physical memory |

Applications started in user mode or "`userland`" will `stay in that mode until a system call is made or interfaced through an API`. When a system call is made, the application will switch modes.

![Switching point](/Windows_Internals/Images/Switching_point.png)

When looking at how languages interact with the Win32 API, this process can become further warped; the application will go through the language runtime before going through the API. The most common example is C# executing through the CLR before interacting with the Win32 API and making system calls.

<!-- TO DO:
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
13. Process Monitor -->