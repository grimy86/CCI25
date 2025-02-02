# Anti-reverse engineering
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