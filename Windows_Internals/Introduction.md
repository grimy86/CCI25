# Windows Internals
Windows Internals is an umbrella term that refers to the architecture and it's back-end components that make up the Windows Operating System.

These internals cannot change without compromising how the operating system operates. Because of this, this architecture is also where the system is most vulnerable.

This can include processes, file formats, COM (Component Object Model), task scheduling, I/O System, etc.

## Securable objects
At the lowest level, nearly everything in windows is a securable object. This means that all of these components that make up the internals architecutre are all able to have security descriptors attached to them:
- It's owner
- DACL (Discretionary Access Control List)
- SACL (System Access Control List)
- Permissions

These are managed through the Windows Security Model and enforced by the Object Manager in the Windows Kernel.

Eventually this could lead to insecure permissions:
- Service executables
- DLLs loaded by privileged processes
- Registry keys with configurations settings
- Named pipes
- Process and thread objects
- Service configurations
- etc.

This is something we dove into when covering [Windows Privesc](/Cybersecurity_Operations/Maintaining%20Access/WinPrivesc.md).

## Oversimplified Architectural overview
```mermaid
graph BT;
    subgraph Computer
    direction BT
        Hardware --> firmware["Firmware  (BIOS or UEFI)"]

        subgraph OS[Windows Operating System]
        direction BT
            bootldr[Windows bootloader]

            subgraph km[Kernel-mode]
            direction BT
                HAL["Kernel run-time
                &
                Hardware Abstraction Layer (HAL)"]
                Kernel
                dd[Device drivers]
                es["Executive (Subsystems)"]
                wg[Windowing and graphics]
            end

            subgraph um[User-mode]
                SDLL[Subsystem DLLs] --> NTDLL["NTDLL.DLL (run-time library)"]
                up[Processes] --> SDLL
                servp[Services] --> SDLL
                sysp[System processes] --> SDLL
                sysp --> NTDLL
                env[Environment subsystems] --> NTDLL
            end
        end
    end

    firmware -.-> bootldr
    bootldr -.-> HAL
    km <-.-> um
```

<!-- TO DO:
11. Syscalls

## Syscalls
User-mode syscalls start with `Zw`, E.g: `ZwSuspendThread`.

12. Callbacks
13. Process Monitor -->