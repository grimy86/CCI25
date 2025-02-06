# Anti-reverse engineering
alware authors are constantly looking for ways to evade detection and analysis to maintain the effectiveness of their malware. At the same time, security professionals are working to develop new methods and tools for detecting and mitigating the threat posed by malware. This ongoing "arms race" can lead to the development of increasingly sophisticated and effective malware defences as both sides seek to stay ahead of their counterparts.

Reverse engineering is the process of studying a technology product, software, or hardware to learn how it works and extract its functionality or design information. In cybersecurity, reverse engineering is used to understand how malware works, extract indicators of compromise (IOCs), and develop adequate detections, protections, and countermeasures.

As a response, malware authors are motivated to protect their malware from analysts. They use anti-reverse engineering techniques to make malware more challenging to analyze, so it can continue propagating and infecting more systems before security measures are implemented.

This constant back and forth between malware analysts and authors can be aptly described as an "`arms race`". Malware authors develop new and sophisticated techniques to avoid detection and analysis, and security professionals respond by developing new methods and tools to detect and mitigate the threat posed by malware. As each side grows new techniques, the other responds with even more advanced ones, creating a cycle of escalation.

We will explore some of the various anti-reverse engineering techniques malware uses. These include:

- `VM Detection`
- `Obfuscation using Packers`
- `Anti-Debugging`

Many more techniques exist, but we will focus on these three for this room.

## Anti-debugging
Debugging is the process of examining software to understand its inner workings and identify potential vulnerabilities or issues. Debugging involves software tools called `debuggers` that allow analysts to `step through the code and monitor its execution`. 

Here are the commonly used debuggers for malware analysis nowadays:
- x64dbg
- Ollydbg
- Ida Pro
- Ghidra

### Anti-Debugging techniques
Some of the most common anti-debugging measures include, but are not limited to:
- `Checking for the presence of debuggers`:

    Malware code looks for processes or files associated with debugging tools or hardware-based techniques, such as detecting hardware breakpoints. For example, a common anti-debugging technique uses the Windows API function `IsDebuggerPresent` to check if a debugger is running.

- `Tampering with debug registers`:

    Malware may try to modify or corrupt debug logs, which debuggers use to control the execution of code. This prevents the debugger from functioning correctly.

- `Using self-modifying code`:

    This is a sophisticated technique where malware modifies itself while running, making it difficult for a debugger to follow the code flow.

### Suspend Thread
[Suspend thread](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-suspendthread) is a Windows API function that is used to `pause the execution of a thread in a running process`. This function has legitimate uses but can also be `called from within a malware process to suspend any threads attempting to debug or analyze it`. In turn, making the debugger not work.

Take a look at this [proof of concept](/Reverse_Engineering/SuspendThread_POC.cpp).

If you don't want to be bothered with reading the source code, here is a short explanation of the steps used by this technique:

1. The malware `goes through all` threads in the Windows system.
2. `For each` thread, it calls `EnumWindow` to go through each window displayed on the screen.
3. `If the name` of the window `has the strings debugger`, `dbg`, or `debug`, then the malware knows that a debugger is running.
4. `If` a `debugger is present`, the malware calls `SuspendThread`, which suspends the threads of the debugger, `making it crash`.

### Patching
Patching is one of the most critical skills required of an analyst. In cases like this we want to patch the function SuspendThread so that our debugger won't get suspended.

A good way to patch this would be to go to the `entry point` and search the `current module` for `intermodular calls` (the SuspendThread call).
Once we've found it we just fill the function call with `NOP` instructions and resume execution.

> [!NOTE]
> However,  if you try debugging again, you'll discover it will start crashing again. This is because our patches are reset and are now gone. To avoid re-applying patches in the future, we can export and import our patches for future use.

## VM Detection
Virtual Machines (VMs) are software platforms that simulate a computer environment inside another computer system.
These are useful in reverse engineering because they provide a `cost-effective`, `controlled`, and `isolated environment` for monitoring and analyzing suspicious software or malware.
VMs also allow for the creation of snapshots and checkpoints that can be used to restore the system to a previous state, which helps test different scenarios and maintain a history of the analysis process.

When malware identifies that it is running on a VM, it may decide to respond differently; for example, it may change its behaviour by:
- Executing only a `minimal subset of its functionality`
- `Self-destructing` by deleting itself or overwriting parts of its code
- `Cause damage` to the system by deleting or encrypting files; or
- `Not run at all`

### VM Detection Techniques
- `Checking running processes`:

    VMs have easily identifiable processes; for example, VMWare runs a process called vmtools, while VirtualBox has vboxservice.
    Malware can use the EnumProcess Windows API to list all the processes running on the machine and look for the presence of these tools.

- `Checking installed software`:

    Malware can look in the Windows Registry for a list of installed software under the SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall Registry key.
    From here, it can check for installed programs like debuggers, decompilers, forensics tools, etc.

- `Network fingerprinting`:

    Malware can look for specific MAC and network addresses unique to VMs.
    For example, VMs autogenerate MAC addresses that start with any of the following numbers: 00-05-69, 00-0c-29, 00-1c-14 or 00-50-56.
    These numbers are unique and are specifically assigned to a VM vendor called the OUI (Organizationally Unique Identifier).

- `Checking machine resources`:

    Malware can look at a machine's resources like RAM and CPU Utilization percentages.
    For example, a machine with RAM amounting to less than 8GB can indicate a virtual machine, as they are typically not assigned a significant amount.

- `Detecting peripherals`:

    Some malware checks for connected printers because this is rarely configured properly on VMs, sometimes not even configured at all.

- `Checking for domain membership`:

    Corporate networks are a usual target for malware.
    An easy way to determine this is by checking if the current machine is part of an Active Directory domain.
    This can quickly be done without the use of API calls by checking the LoggonServer and ComputerName environment variables.

- `Timing-based attacks`:

    Malware can measure the time it takes to execute specific instructions or access particular machine resources.
    For example, some instructions can be faster on a physical machine compared to a virtual machine.

- `Checking temperature`:

    `Win32_TemperatureProbe` is a `Windows Management Instrumentation (WMI)` class that contains real-time temperature readings from the hardware through the `SMBIOS (System Management BIOS)` data structure. In a virtualized environment, the value returned is Not Supported, which is what malware looks for.

    Note: `Win32_TemperatureProbe` may also return Not Supported even on physical machines if the hardware doesn't support this SMBIOS feature. This makes it unreliable but valuable when used with the other techniques.

## Anti-VM Detection
To prevent malware from using some of the techniques above, we can apply several changes to the system that will remove VM-related artefacts making the VM look less like a VM. For example, we can remove or modify the Registry entries that malware checks for installed programs to hide our debuggers, change the MAC addresses, or configure the VM to appear connected to a printer.

But you can see how tedious this becomes. With the myriad of options available to malware, it would be challenging to cover all of them.

Some researchers have made scripts  (See [`VMwareCloak`](https://github.com/d4rksystem/VMwareCloak) and [`VBoxCloak`](https://github.com/d4rksystem/VBoxCloak)) to help automate this process. Despite this, even if all the known techniques are addressed, minor architectural checks can still be made by malware, as you will see in the next task.

Architectural checks like checking the temperature can be challenging to prevent. However, there are still ways around this. We can patch a function with nops to prevent it from executing. We can do the same thing here, but for the sake of giving you more tools to help you with reverse engineering, there's two other approaches:
- Manipulating memory directly
- Changing the execution flow with EIP

## Packers(Overview)
Obfuscation is a technique that aims to intentionally obscure data and code so that it is harder to understand or analyze. 

The most common obfuscation techniques used by malware authors include:
- `Using encoding techniques`:
 
    This involves `encoding data` (i.e. command line strings, domain names, etc.) using popular encoding techniques like XOR or Base64. You may have seen a Base64 encoded strings that look like this VGhpcyBpcyBhbiBCQVNFNjQgZW5jb2RlZCBzdHJpbmcu==.

- `Using encryption techniques`:
 
    This involves encrypting data such as communications to a command and control server, file formats, and network traffic. The most common types used are `symmetric key and public key encryption`.

- `Code obfuscation`:
 
    This involves various techniques such as manipulating the code to `alter its syntax and structure`, `renaming functions`, or `splitting code across multiple files or code segments`.




## Process Hollowing: Overview
A process injection technique, mostly used to evade detection. Another technique used by malware to hide in plain sight is Process Hollowing.
In this technique, the malware binary hollows an already running legitimate process by removing all its code from its memory and injecting malicious code in place of the legitimate code. 

Used to inject malicious code into a legitimate process running on a victim's computer.

The malware `creates a suspended process and replaces its memory space with its own code`. Then it `resumes the process`, causing it to execute the injected code.

1. Create a new process using the `CreateProcessA()` API. This `process will act as a legitimate process` and will be hollowed out.
2. `NtSuspendProcess()` is then used to `suspend the new process`.
3. `Allocate memory` in the suspended process using the `VirtualAllocEx()` API. This memory will be used to hold the malicious code.
4. Write the malicious `code to the allocated memory` using the `WriteProcessMemory()` API.
5. `Modify the entry point of the process to point to the address of the malicious code` using the `SetThreadContext()` and `GetThreadContext()` APIs.
6. Resume the suspended process using the `NtResumeProcess()` API. This will cause the process to `execute the malicious code`.

This allows the malware to `bypass security measures` that may be in place, as the malicious code is executed within the context of a legitimate process.

[Process hollowing proof of concept](/Reverse_Engineering/Hollowing_POC.cpp)

## Process Masquerading: Overview
As seen in the above screenshot, the properties function shows us a lot of information about a process in its different tabs. Malware authors sometimes use process names similar to Windows processes or commonly used software to hide from an analyst's prying eyes. The 'Image' tab, as shown in the above screenshot, helps an analyst defeat this technique. By clicking the 'Verify' button on this tab, an analyst can identify if the executable for the running process is signed by the relevant organization, which will be Microsoft in the case of Windows binaries. In this particular screenshot, we can see that the Verify option has already been clicked. Furthermore, we can see the text '(No signature was present in the subject) Microsoft Corporation' at the top. This means that although the executable claims to be from Microsoft, it is not digitally signed by Microsoft and is masquerading as a Microsoft process. This can be an indication of a malicious process.

We must note here that this verification process only applies to the Image of the process stored on the disk. If a signed process has been hollowed and its code has been replaced with malicious code in the memory, we might still get a verified signature for that process. To identify hollowed processes, we have to look somewhere else.