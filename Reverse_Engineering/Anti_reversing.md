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

### Anti-Debugging using Suspend Thread


## Process Hollowing: Overview
A process injection technique, mostly used to evade detection. Another technique used by malware to hide in plain sight is Process Hollowing. In this technique, the malware binary hollows an already running legitimate process by removing all its code from its memory and injecting malicious code in place of the legitimate code. 

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