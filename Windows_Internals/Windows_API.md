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

### OS Libraries
