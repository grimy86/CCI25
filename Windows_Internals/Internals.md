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
Read [x86-64 Memory](/Programming_Foundations/Assembly/Architecture/Memory.md) & [Windows Internals Memory](/Windows_Internals/Memory.md) for more.

## Dynamic Link Libraries
The [Microsoft docs](https://learn.microsoft.com/en-us/troubleshoot/windows-client/setup-upgrade-and-drivers/dynamic-link-library) describe a `DLL` as "`a library that contains code and data that can be used by more than one program at the same time`."

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

## Portable executable (PE) file format
Read [Portable executable file format](/Windows_Internals/PE.md) for more.

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