# Services, functions and routines
Some Windows internals terms have different meanings based on it's context.

| Term | Description | Example |
|-|-|-|
| Windows API functions | Documented, callable subroutines in the Windows API. | `CreateProcess` |
| Native system services (or system calls) | Undocumented, underlying services that are callable from User-mode. | `NtCreateUserProcess` is the internal system service that the Windows `CreateProcess` function calls. |
| Kernel support functions (or routines) | Subroutines of the Windows OS called from Kernel-mode. | `ExAllocatePoolWithTag`, device drivers call this to allocate memory from the `Windows system heaps (pools)` |
| Windows services | Processes started by the Windows service control manager. | The `Task Scheduler service` runs in a User-mode process that supports the `schtasks` command. |
| Dynamic Link Libraries (DLLs) | Callable subroutines linked togheter as a binary file that can be dynamically loade by programs that use these subroutines. | `Msvcrt.dll`, `Kernel32.dll`, etc. |