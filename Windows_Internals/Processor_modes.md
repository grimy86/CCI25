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