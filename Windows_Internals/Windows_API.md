# Windows API
> [!NOTE]
> IF you don't know what an API is, check out [API introduction](/Windows_Internals/API_Introduction.md).

The Windows API is a type of local / OS API that provides native functionality in `User-mode` to interact with key components of the Windows operating system.

## Windows API list
Microsoft has brought out [a bunch of API's](https://learn.microsoft.com/en-us/windows/apps/api-reference/), all with different purposes:
- Windows SDK:
    - WinRT API
    - WinUI 2 for UWP API
    - Win32 API

- Windows App SDK:
    - WinRT API
    - Win32 API
    - COM interop APIs for WinUI
    - C# Interop APIs for WinUI
    - Bootstrapper C# APIs

- .NET:
  - .NET API

- Schema specifications
  - File and XML schema specifications for UWP apps

## Win32 API
> [!NOTE]
> The Win32 API is the API commonly referred to as the Windows API. However, in reality the Windows API is the entire collection of API's listed above.
>
> We will be looking at the Win32 API, which might be referred to as the Windows API from here on out.

The Win32 API is the name given to the original platform for [native C/C++ Windows applications](https://en.wikipedia.org/wiki/Windows.h) that require direct access to Windows and hardware.

Before there were 64-bit version of Windows the programming interface to the 32-bit versions of Windows was named the `Win32 API (WinNT/Win9x)` to distinguish it from the 16-bit `Win16 API (DOS)`. However, you can use the Win32 API on 32-bit and 64-bit Windows, it just hasn't been renamed.

 It provides a first-class development experience without depending on a managed runtime environment such as .NET. That makes the Win32 API a great choice for applications that need the highest level of performance, and direct access to system hardware.

## History: DDE, OLE & COM
Originally, Windows provided system functions through the Windows API, which was just a huge collection of C functions. But over time, as Windows grew, this approach became messy. There were thousands of functions with no real organization—just a bunch of names that weren’t always consistent.

Enter `COM (Component Object Model)`, to fix this, Microsoft introduced `COM (Component Object Model)`. You can think of COM as a better way to organize and access Windows features, making it easier for different programs to work together. Originally, COM was called `OLE 2` and it started as a way for Office programs (like Word and Excel) to share data with each other.

This sharing of data between processes is what we call `Inter-Process Communications (IPC)`.

The ability to exchange data was originally implemented through `OLE (Object Linking and Embedding)`. Which in turn implemented using and older Windows mechanism named `DDE (Dynamic Data Exchange)`. However, DDE also had it's own limitations and eventually OLE came along.

COM is based on two simple ideas:
1. Programs talk to COM objects by obtaining `interfaces`.

   - An interface is just a list of functions that a program can call, like a menu of available actions.
   - These interfaces are designed to work across different programming languages, so they don’t rely on how a specific language (like C++ or C#) handles function calls.
   - This makes it easier for different programs to communicate without running into compatibility issues.

2. COM objects are `loaded dynamically`. Along with managed `object lifetime`.

  - Instead of being built directly into a program, COM objects are stored in separate files (DLLs or EXEs).
  - This means programs can load them only when needed, making the system more flexible and modular.

In the end COM provided:
- Better organization of Windows features
- A way for different programs to work togheter.
- It worked across many programming languages (C, C++, C#, VB, etc.).
- It allowed Windows features to be updated separately without breaking programs.

COM became the foundation for many later Microsoft technologies, like `ActiveX`, `DirectX`, `Windows Shell Extensions`, and even parts of `.NET`.

## Practical COM example
Let’s say you’re building a program that needs to generate a Word document, add some text, and save it without actually opening Word on the screen.

How does this work?:
- Microsoft Word exposes a COM object that allows other programs to control it.
- Your program can ask Windows to load Word’s COM object in the background (inside a DLL).
- Your program can then send commands to this hidden instance of Word to create a document, add text, and save it.

## What is a COM server?
A `COM server` is just a file (`a DLL or an EXE`) that contains COM objects / classes. These objects provide specific functionality, like handling files, networking, or controlling Microsoft Word from another program.

For example, if a program wants to open and edit a Word document without launching Word itself, it can ask a COM object in Word’s DLL to do it in the background.

## Subsystem and Hardware Interaction
Programs often need to access or modify Windows subsystems or hardware but are `restricted to maintain machine stability`. To solve this problem, Microsoft released the Win32 API, a library to `interface between user-mode applications and the kernel`.

Windows distinguishes hardware access by two distinct modes: `user` and `kernel` mode. These modes determine the hardware, kernel, and memory access an application or driver is permitted. `API or system calls interface between each mode`, sending information to the system to be `processed in kernel mode`.

Read [processor modes and system calls](/Windows_Internals/Processor_Modes.md) to learn more.

![Modes](/Windows_Internals/Images/Modes.png)

## Win32 API components
The Win32 API, more commonly known as the Windows API, has several dependent components that are used to define the structure and organization of the API.

Let’s break the Win32 API up via a top-down approach. We’ll assume the API is the top layer and the parameters that make up a specific call are the bottom layer. In the table below, we will describe the top-down structure at a high level and dive into more detail later.

| Layer | Explanation |
|-|-|
| API | A top-level/general term or theory used to describe any call found in the win32 API structure. |
| Header files or imports | Defines libraries to be imported at run-time, defined by header files or library imports. Uses pointers to obtain the function address. |
| Core DLLs | A group of four DLLs that define call structures. (KERNEL32, USER32, and ADVAPI32). These DLLs define kernel and user services that are not contained in a single subsystem. |
| Supplemental DLLs | Other DLLs defined as part of the Windows API. Controls separate subsystems of the Windows OS. ~36 other defined DLLs. (NTDLL, COM, FVEAPI, etc.) |
| Call Structures | Defines the API call itself and parameters of the call. |
| API Calls | The API call used within a program, with function addresses obtained from pointers. |
| In/Out Parameters | The parameter values that are defined by the call structures. |

## OS Libraries and ASLR
Windows provides a bunch of built-in functions that programs can use. These functions live inside DLL files (Dynamic Link Libraries), which are like toolboxes full of useful code that programs can borrow instead of writing everything from scratch.

Examples of Windows DLLs:
- `kernel32.dll` → Handles things like memory, files, and processes.
- `user32.dll` → Deals with windows, buttons, and user input.
- `gdi32.dll` → Helps with graphics and drawing.

Every time a program wants to use one of these functions, it needs to `find the function inside the DLL` and `get its memory address (a pointer)`.

We can't just statically hand out references to the memory address of the function since `ASLR (Address Space Layout Randomization)` loads it randomly.

This is a security feature called ASLR, which makes it harder for malware to predict where functions are in memory. Since the function address changes every time the program runs, we need a way to find it dynamically.

The two most popular implementations to do this are:
- `P/Invoke (Platform Invocation Services)`

  Used in C#, VB.NET. other .NET languages to manually tell Windows to use a function from a DLL since because don’t natively work with Windows API functions.

- The `Windows header file`

  A header file that includes these function pointers provided by Windows that used in C and C++.

## The Windows Header File
Microsoft provides low-level programming languages such as C and C++ with a pre-configured set of libraries that we can use to access the API calls.

Keeping the concept at a high level, at runtime, the loader will determine what calls are being made and create a `thunk table` to obtain function addresses or pointers.

Once the `windows.h` file is included at the top of an unmanaged program; any Win32 function can be called.

```cpp
#include <windows.h>
```

Take a loot at the bottom [ExtProc.h](https://github.com/grimy86/AssaultCubeTrainer/blob/master/AssaultCubeTrainer/ExtProc.h) which uses [ReadProcessMemory](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-readprocessmemory) and [WriteProcessMemory](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-writeprocessmemory).

## P/Invoke
Microsoft describes P/Invoke or `platform invoke` as “a technology that allows you to access structs, callbacks, and functions in unmanaged libraries from your managed code.”

- `Managed code`:
  Code managed by a CLR (Common Language Runtime) like .NET which is used for C#, VB.NET and F#.

  Managed code benefits from automatic garbage collection, type safety, and runtime security features.

- `Unmanaged code`:
  Unmanaged code manages its own memory and execution. It's code that runs directly on the OS, without CLR intervention.

  Examples include: C, C++, Win32 API, and system DLLs like kernel32.dll or user32.dll (which are written in those unmanaged languages).

P/invoke provides tools to handle the entire process of `invoking an unmanaged function from managed code` or, in other words, calling the Win32 API in a language like C#. P/invoke will kick off by importing the desired DLL that contains the unmanaged function or Win32 API call.

Below is an example of importing a DLL with options.

```cs
using System;
using System.Runtime.InteropServices;

public class Program
{
  // Importing the DLL user32 using the attribute: DLLImport.
  [DllImport("user32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
  ...
} 
```

Note: a semicolon is not included because the p/invoke function is not yet complete. In the second step, we must `define a managed method as an external one`. The `extern` keyword will inform the runtime of the specific DLL that was previously imported.

```cs
using System;
using System.Runtime.InteropServices;

public class Program
{
...
private static extern int MessageBox(IntPtr hWnd, string lpText, string lpCaption, uint uType);
}
```

Now we can invoke the function as a managed method, but we are calling the unmanaged function!

## API Call Structure
API calls are the second main component of the Win32 library. These calls offer extensibility and flexibility that can be used to meet a plethora of use cases. Most Win32 API calls are well documented under the Windows API documentation and pinvoke.

API call functionality can be extended by modifying the naming scheme and appending a representational character.

Microsoft supported API calls naming scheme:

| Character | Explanation |
|-|-|
| A | Represents an 8-bit character set with ANSI encoding |
| W | Represents a Unicode encoding |
| Ex | Provides extended functionality or in/out parameters to the API call |

Each API call also has a pre-defined structure to define its in/out parameters. You can find most of these structures on the corresponding API call document page of the Windows documentation, along with explanations of each I/O parameter.

The Win32 API functions follow a common format:
 
- Prefix:
  - Create
  - Get
  - Set
  - Open
  - Close
- Keyword:
  - Reg
  - File
  - Process
  - Library
- Suffix:
  - Ex
  - A
  - W

Examples:
- `CreateProcess`
- `LoadLibrary`
- `CloseHandle`

Let’s take a look at the WriteProcessMemory API call as an example. Below is the I/O structure for the call obtained [here](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-writeprocessmemory).

```cpp
BOOL WriteProcessMemory(
  [in]  HANDLE  hProcess,
  [in]  LPVOID  lpBaseAddress,
  [in]  LPCVOID lpBuffer,
  [in]  SIZE_T  nSize,
  [out] SIZE_T  *lpNumberOfBytesWritten
);
```
For each I/O parameter, Microsoft also explains its use, expected input or output, and accepted values.

## Commonly Abused API Calls
Several API calls within the Win32 library lend themselves to be easily leveraged for malicious activity.

While many calls are abused, some are seen in the wild more than others. 

Here's a list of the most common DLLs and what they're used for:

| Win32 Dynamic Link Library | Purpose |
|-|-|
| `kernel32.dll` | Manage processes and threads |
| `kernel32.dll` | Manage memory |
| `kernel32.dll` | Manage files |
| `user32.dll` | Manage the user interface (GUI) |
| `advapi32.dll` | Manage the registry |
| `ws2_32.dll` | Manage networking |
| `ws2_32.dll` | Manage internet activities |

Below is a table of the most commonly abused API organized by frequency in a collection of samples:

| API Call | Description |
|-|-|
| `LoadLibraryA` | Maps a specified DLL  into the address space of the calling process |
| `GetUserNameA` | Retrieves the name of the user associated with the current thread |
| `GetComputerNameA` | Retrieves a NetBIOS or DNS  name of the local computer |
| `GetVersionExA` | Obtains information about the version of the operating system currently running |
| `GetModuleFileNameA` | Retrieves the fully qualified path for the file of the specified module and process |
| `GetStartupInfoA` | Retrieves contents of STARTUPINFO structure (window station, desktop, standard handles, and appearance of a process) |
| `GetModuleHandle` | Returns a module handle for the specified module if mapped into the calling process's address space |
| `GetProcAddress` | Returns the address of a specified exported DLL  function |
| `VirtualProtect` | Changes the protection on a region of memory in the virtual address space of the calling process |

## The Windows Runtime API (WinRT)
Windows 8 introduced a new API and the `Windows Runtime (WinRT)`, the runtime is designed for Windows Apps (previously called Metro, Modern, Immersive, or Windows Store Apps). These apps run on various devices, from IoT and phones to desktops, Xbox One, even on HoloLens.

> [!NOTE]
> `WinRT` is not to be confused with `Windows RT`, a discontinued ARM-based OS version.

### WinRT and COM
WinRT is built on / and accesed by COM interfaces, but extends the base COM infrastructure with:
- Complete type metadata stored in WINMD files (based on .NET metadata).
- A more structured API with namespaces, consistent naming, and patterns.

However, unlike traditional Windows applications (now called desktop or classic apps), Windows Apps follow stricter rules called "management mechanisms".

### API Relationships
WinRT is not a new completely separate or independent system-level API (native API) for the system. Similar to .NET, which provides a modern, high-level framework but still internally leverages the traditional Windows APIs for things like file handling, networking, and UI rendering.

- Desktop apps can use some WinRT APIs.
- Windows Apps can use a limited set of Win32 and COM APIs.
- WinRT itself is not a new native API, it still relies on traditional Windows binaries and APIs, similar to .NET.

Even though WinRT introduces a new programming model, at the binary level, it still interacts with legacy Windows binaries and APIs. In other words, WinRT is more of a structured wrapper around existing Windows functionality rather than a complete replacement.

> [!NOTE]
> Not all traditional Windows APIs are accessible from a Windows App. Likewise, not all WinRT APIs are available to classic desktop applications. Some APIs are documented and officially supported, while others exist but are restricted or undocumented.
>
> For precise details on which APIs can be used in different types of applications, Microsoft provides official documentation.

### WinRT and Programming Languages
WinRT APIs are accessible in multiple languages through `language projections`:
- C++: Uses C++/CX, a Microsoft-specific extension to simplify WinRT usage.
- C#/.NET: Works naturally with the existing COM interop layer.
- JavaScript: Uses WinJS but requires HTML for UI design.

> [!NOTE]
> Windows Apps using HTML are still local client apps, not web applications loaded from a server.