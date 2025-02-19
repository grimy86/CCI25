# Processor modes
The Windows operating system has a `user mode` and a `kernel mode`. This security measure is implemented through processor `acces modes` and `privilege levels`. Some processors might use terms like `code privilege level`, `ring level`, `supervisor mode` and `application mode`.

An application by default cannot interact with the kernel or modify critical OS data. This is a safety mechanism that ensures that User-mode applications won't disrupt the stability of the system. 

 The processor will switch between these modes `depending on access and requested mode`. Even if the processor supports multiple modes, Windows will only ever use two for compatibility reasons with other operating systems.

| User mode | Kernel Mode |
|-|-|
| No direct hardware access | Direct hardware access |
| Creates a process in a private virtual address space | Ran in a single shared virtual address space |
| Access to "owned memory locations" in the VAS | access to all system memory and all CPU instructions |
| Runs user application code | Runes OS code |

## Privilidge levels
You might have noticed that these modes like user-mode and kernel-mode provide different priviledges associated with the mode. As a general rule: user-mode has access to anything that's withing userland or user-space: `ring 3`. Essentially, kernel-mode has access to everything: `ring 0`.

> [!NOTE]
> x86 and x86-64 processors define four rings. 
>
> Again, Windows will only use two for: compatibility reasons, efficiency and portability and because the other x86/x86-x64 ring levels do not provide the same guarantees.

## System calls and the Switching Point
Applications that start in `user mode` (also known as `userland`) remain in that mode until they make a `system call (syscall)` or interact with the OS via an API. When a syscall occurs, the application transitions into kernel mode to execute privileged operations.

> [!NOTE]
> User-mode has many terms; User-mode, userspace, userland, etc.
>
> Userland is a common term, however, it's not a term defined by Windows.

- User applications switch to kernel mode when making system calls (e.g., `ReadFile`).
- A special processor instruction triggers this transition, allowing access to protected system structures in `Ntoskrnl.exe` or `Win32k.sys`.
- The processor switches back to user mode before returning control to the application, ensuring system protection.
- Mode transitions are not context switches and do not affect thread scheduling.
- Graphics-intensive apps spend more time in kernel mode since the windowing system runs there.
- Newer technologies like `Direct2D` and `DirectComposition` reduce kernel mode time by handling more computations in user mode before passing data to the kernel.

### Syscall naming conventions
System calls in Windows are often prefixed with `Nt`, which stands for `Windows New Technology (NT)`. These calls are the lower-level APIs used internally by the OS. However, some system calls use the `Zw` prefix. While `Zw` has no official meaning, it was chosen to avoid naming conflicts with other APIs and to preserve other useful two-letter prefixes for future use.

Additionally, many Windows driver support routines use standardized prefixes that indicate which kernel-mode system component implements them:
| Prefix | Kernel component | Example routine |
|-|-|-|
| `Cm` | Configuration manager | `CmRegisterCallbackEx` |
| `Ex` | Executive | `ExAllocatePool` |
| `Hal` | Hardware abstraction layer | `HalGetAdapter` |
| `Io` | I/O manager | `IoAllocateIrp` |
| `Ke` | Kernel core | `KeSetEvent` |
| `Mm` | Memory manager | `MmUnlockPages` |
| `Ob` | Object manager | `ObReferenceObject` |
| `Po` | Power manager | `PoSetPowerState` |
| `Tm` | Transaction manager | `TmCommitTransaction` |
| `Nt` and `Zw` | Native system services | `NtCreateFile` and `ZwCreateFile` |

### The Switching Point
The `switch between user mode and kernel mode` is facilitated by `system and API calls`. In some documentation, this transition is referred to as the `Switching Point`.

![Switching point](/Windows_Internals/Images/Switching_point.png)

### Performance Counters for Mode Transitions
The following performance counters help track the time spent in user and kernel modes:

| Object | Counter | Function |
|-|-|-|
| Processor | % Privileged Time | Percentage of time that an individual CPU (or all CPUs) has run in kernel mode during a specified interval. |
| Processor | % User Time | Percentage of time that an individual CPU (or all CPUs) has run in user mode during a specified interval. |
| Process | % Privileged Time | Percentage of time that the threads in a process have run in kernel mode during a specified interval. |
| Process | % User Time | Percentage of time that the threads in a process have run in user mode during a specified interval. |
| Thread | % Privileged Time | Percentage of time that a thread has run in kernel mode during a specified interval. |
| Thread | % User Time | Percentage of time that a thread has run in user mode during a specified interval. |

## The kernel
The `kernel` itself refers specifically to the OS core that enforces rules and handles system-wide operations. You could see it as the "heart" of the operating system. 

Essentially, it's a software component that sits / interfaces between your hardware and the rest of the OS and software.

Here's a simplified list of what the core kernel component actually does:

-  Manage hardware interaction:

    Abstract away the physical differences between hardware setups by providing other software with a standardized surface area to interface with.

- Privilege Separation:

    Provide a safety mechanism for security and stability by separating user-mode and kernel-mode operations, preventing regular applications from directly accessing hardware.

- Manage processes & memory:

    The kernel handles process creation, scheduling, and termination while also managing memory allocation and enforcing access protections.

- Resource Scheduling & Allocation:

    The kernel decides how CPU time, memory, and I/O resources are distributed among processes.

- Inter-Process Communication (IPC):

    It enables different processes to communicate and share data safely.

- Event Handling & Interrupts:

    The kernel responds to hardware and software interrupts to keep the system running smoothly.

- Handle system calls:

    The kernel provides a controlled way for user-mode applications to request services (e.g., file access, networking, or process management) through system calls.


### Types
| Kernel type | Description | Advantage |
|-|-|-|
| Monolithic kernel | The kernel incorporates most of the OS's main functions. | Higher performance and easier for programmers to work with. |
| Micro-Kernel | The kernel only handles basic functionality leaving other components to the user-space. | Ability to kill problematic processes without crashing the system. |
| Hyrbid kernel | Tries to incorporate the advantage of both modules. | Fast and modular. |

### Memory
Contrary to user-mode virtual address space, kernel-mode and device-driver code share a single virtual address space. Each page in virtual memory is protected with a "tag" that indicates which read and / or write-operation could be used on that memory based on the processor mode.

However, read-only pages that contain static read-only data are not writable from any mode. Additionally, `Data Execution Prevention (DEP)` if enabled stops code from running in memory areas meant for data, preventing exploits like buffer overflows. However, in kernel mode, there are no such protections—drivers and system code can access any part of system memory without restrictions.

### Driver signing and security
Since kernel-mode code has full system access, Microsoft enforces strict driver-signing policies to improve security and stability.

- Windows 2000 introduced `driver signing` to warn/block unsigned plug-and-play drivers.
- Windows 8.1 (64-bit & ARM) requires all drivers to be signed by a `recognized certification authority` (`Kernel-Mode Code Signing, KMCS`). Users cannot install unsigned drivers unless they enable "Test Mode."
- Windows 10 (Anniversary Update, 2016) tightened requirements:
    - Drivers must be `SHA-2 EV signed and submitted` to Microsoft for attestation.
    - Only `Microsoft-signed drivers` can load, except in "Test Mode."
    - Pre-2015 signed drivers remain valid for now.
- Windows Server 2016 further restricts drivers, requiring `WHQL certification` for additional security and stability.
- Enterprise configurations (e.g., `Device Guard`) can customize these policies, enforcing stricter requirements where needed.

These measures are an effort by Microsoft to reduce untrusted third-party drivers in kernel memory, strengthening system security.


<!--
- CPU MEM MANAGEMENT UNIT MMU
- KERNEL CRASH DUMP
- KERNEL PATCH PROTECTION / PATCHGUARD
-->