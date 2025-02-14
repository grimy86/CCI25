# Windows API
This is a type of local / OS API that provides native functionality to interact with key components of the Windows operating system.

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

You may see the `Win32 API` being used for offensive tool and malware development, EDR (Endpoint Detection & Response) engineering, and general software applications. For more information about all of the use cases for the API, check out the Windows API Index.

> [!NOTE]
> The Win32 API is the API commonly referred to as the Windows API. However, in reality the Windows API is the entire collection of API's listed above.
>
> We will be looking at the Win32 API, which might be referred to as the Windows API from here on out.

## Win32 API
The Win32 API is the name given to the original platform for [native C/C++ Windows applications](https://en.wikipedia.org/wiki/Windows.h) that require direct access to Windows and hardware. It provides a first-class development experience without depending on a managed runtime environment such as .NET. That makes the Win32 API a great choice for applications that need the highest level of performance, and direct access to system hardware. You can use the Win32 API on 32-bit and 64-bit Windows.

## Subsystem and Hardware Interaction
Programs often need to access or modify Windows subsystems or hardware but are `restricted to maintain machine stability`. To solve this problem, Microsoft released the Win32 API, a library to `interface between user-mode applications and the kernel`.

Windows distinguishes hardware access by two distinct modes: `user` and `kernel` mode. These modes determine the hardware, kernel, and memory access an application or driver is permitted. `API or system calls interface between each mode`, sending information to the system to be `processed in kernel mode`.

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

## OS Libraries
Each API call of the Win32 library resides in memory and requires a pointer to a memory address. The process of obtaining pointers to these functions is obscured because of `ASLR` (Address Space Layout Randomization) implementations; each language or package has a unique procedure to overcome ASLR.

We will discuss the two most popular implementations: `P/Invoke` and the `Windows header file`.

### Windows Header File
Microsoft has released the Windows header file, also known as the `Windows loader`, as a direct solution to the problems associated with ASLR’s implementation.

Keeping the concept at a high level, at runtime, the loader will determine what calls are being made and create a `thunk table` to obtain function addresses or pointers.

Once the `windows.h` file is included at the top of an unmanaged program; any Win32 function can be called.

Take a loot at the bottom [ExtProc.h](https://github.com/grimy86/AssaultCubeTrainer/blob/master/AssaultCubeTrainer/ExtProc.h) which uses [ReadProcessMemory](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-readprocessmemory) and [WriteProcessMemory](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-writeprocessmemory).

### P/Invoke
Microsoft describes P/Invoke or `platform invoke` as “a technology that allows you to access structs, callbacks, and functions in unmanaged libraries from your managed code.”

- Managed code:
  Code managed by a CLR (Common Language Runtime) like .NET which is used for C#, VB.NET and F#.

  Managed code benefits from automatic garbage collection, type safety, and runtime security features.

- Unmanaged code:
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

## C API Implementations
Microsoft provides low-level programming languages such as C and C++ with a pre-configured set of libraries that we can use to access the API calls.

The `windows.h header file`, is used to define call structures and obtain function pointers. To include the windows header, prepend the line below to any C or C++ program.

```cpp
#include <windows.h>
```