# Advanced Static analysis
 In Advanced Static Analysis, we will move further and reverse engineer malware into the disassembled code and `analyze the assembly instructions` to understand the malware's core functionality in a better way.

Advanced static analysis is a technique used to analyze the code and structure of malware without executing it. This can help us identify the malware's behavior and weaknesses and develop signatures for antivirus software to detect it. By analyzing the code and structure of malware, researchers can also better understand how it works and develop new techniques for defending against it.

## Malware analysis overview
| Technique | Description |
|-|-|
| Basic static analysis | Aims to understand the malware's `structure`. Involves examining the malware's `code`, `file headers`, and `other static properties`. |
| Advanced static analysis | Aims to uncover `hidden or obfuscated code and functionality` within the malware. Involves using more advanced techniques to analyze the malware's code, such as `deobfuscation` and `code emulation`. |
| Basic dynamic analysis | Aims to observe the malware's `behavior during execution` in a controlled environment. Involves `executing` the malware in a sandbox or virtual machine and `monitoring` its `system activity`, `network traffic`, and `process behavior`. |
| Advanced dynamic analysis | Aims to uncover more `complex and evasive malware behavior` using advanced monitoring techniques. Involves using more sophisticated sandboxes and monitoring tools to `capture the malware's behavior in greater detail`. |

## How advanced static analysis is performed
To perform advanced static analysis, `disassemblers` such as `IDA Pro`, `Binary Ninja`, and `radare2` are commonly used. These disassemblers allow the analyst to explore the malware's code and `identify its functions and data structures`.

The steps involved in performing advanced static analysis of malware are as follows:
-  Identify the `entry point` of the malware and the `system calls` it makes.
-  Identify the malware's `code sections` and analyze them using available tools such as `debuggers` and `hex editors`.
-  Analyze the malware's `control flow` graph to identify its `execution path`.
-  Trace the malware's dynamic behavior by `analyzing the system calls` it makes during execution.
-  Use the above information to understand the malware's `evasion techniques` and the `potential damage it can cause`.

## Ghidra
Many `disassemblers` like Cutter, radare2, Ghidra, and IDA Pro can be used to disassemble malware. However, we will explore Ghidra because it's `free`, `open-source`, and has `many features` that can be utilized to get proficient in reverse engineering.

>[!NOTE]
> The objective is to get comfortable with the main usage of a disassembler and use that knowledge to use any disassembler.

`Ghidra` is a software reverse engineering tool that allows users to analyze compiled code to understand its functionality. It is designed to help analysts and developers understand how the software works by providing a platform to `decompile`, `disassemble`, and `debug binaries`.

Ghidra includes many features that make it a powerful reverse engineering tool. Some of these features include:
- `Decompilation`: Ghidra can `decompile` binaries `into readable C code`, making it easier for developers to understand how the software works.
- `Disassembly`: Ghidra can `disassemble` binaries `into assembly language`, allowing analysts to examine the low-level operations of the code.
- `Debugging`: Ghidra has a built-in `debugger` that allows users to `step through` code and examine its behavior.
- `Analysis`: Ghidra can `automatically identify functions`, `variables`, and `other code` to help users understand the `structure of the code`.

### How to use Ghidra
1. Open Ghidra and create a `new project`.
2. Select `Non-Shared Project`.

    Selecting Shared Project would allow us to share our analysis with other analysts.

3. Name the project and `set the directory` or leave the default path.
4. `Import` the executable you want to analyze. Now that we have created an empty project, let's Drag & Drop the executable and select the program.
5. Once it's imported, it shows us the summary of the program.
6. `Double-click on the .exe` to open it in the Code Browser. When asked to analyze the executable, `click on Yes`.
7. The next window that appears shows us various analysis options. We can `check or uncheck them based on our needs`. These plug-ins or add-ons assist Ghidra during the analysis.
8. It will take some time to analyze. The bar on the bottom-right shows the progress. `Wait` until the analysis is 100%.

### Ghidra layout
![Ghidra layout](/Reverse_Engineering/Images/Ghidra_layout.png)

1. `Program Trees`: Shows (PE) sections of the program. We can click on different sections to see the content within each.

2. `Symbol Tree`:
    - `Imports`: This section contains information about the `libraries being imported` by the program. Clicking on each API call shows the assembly code that uses that API.
    - `Exports`: This section contains the API/function calls being exported by the program. This section is `useful when analyzing a DLL`, as it will show all the functions dll contains.
    - `Functions`: This section contains the functions it finds within the code. Clicking on each function will take us to the disassembled code of that function. It also contains the `entry function`. Clicking on the entry function will take us to the `start of the program` we are analyzing. Functions with `generic names` starting with `FUN_VirtualAddress` are the ones that `Ghidra does not give any names to`.

3. `Data Type Manager`: This section shows various data types found in the program.

4. `Listing`: This window shows the disassembled code of the binary, which includes the following values in order.
    - `Virtual Address`
    - `Opcode`
    - `Assembly Instruction (PUSH, POP, ADD, XOR, etc.)`
    - `Operands`
    - `Comments`

5. `Decompile`: Ghidra translates the assembly code into a `pseudo C code` here. This is a very important section to look at during analysis as it gives a better understanding of the assembly code.

6. `Toolbar`: It has various `options to use` during the analysis.
   
   - `Graph View`: The Graph View in the toolbar is an important option, allowing us to see the graph view of the disassembly:

    ![Graph view](/Reverse_Engineering/Images/Graph_view.png)

   - The `Memory Map` option shows the memory mapping of the program as shown below:
    
    ![Memory map](/Reverse_Engineering/Images/Memory_map.png)

   - This `navigation toolbar` shows different options to navigate through the code.

    ![Navigation toolbar](/Reverse_Engineering/Images/Navigation_toolbar.png)

   - `Explore Strings`. Go to `Search -> For Strings` and click Search will give us the strings that Ghidra finds within the program. This window can contain very juicy information to help us during the analysis.

    ![Strings](/Reverse_Engineering/Images/Strings.png)

## Identifying C code constructs in Assembly
Analyzing the assembly code of the compiled binary can be overwhelming for beginners.
Understanding the assembly instructions and how various programming components are translated/reflected into the assembly is important.
Here, we will examine various C constructs and their corresponding assembly code. This will help us identify and focus on the key parts of the malware during analysis.

> [!NOTE]
> Different compilers add their own code for various checks while compiling.
> 
> Therefore expect some garbage assembly code that does not make sense.

There are different approaches to begin analyzing the disassembled code:

- Locate the `main` function from the `Symbol Tree` section.
- Check the `.text` code from the `Program Trees` section to see the code section and find the entry point.
- Search for interesting `strings` and locate the code from where those strings are referenced.

### Hello World example

C code:
```C
#include <stdio.h>

int main()
{
    printf("Hello, world!");
    return 0;
}
```

Assembly code:
```asm
section .data 
    message db 'HELLO WORLD!!', 0

section .text
    global _start

_start:
    ; write the message to stdout
    mov eax, 4      ; write system call
    mov ebx, 1      ; file descriptor for stdout
    mov ecx, message    ; pointer to message
    mov edx, 13     ; message length
    int 0x80        ; call kernel
```

This program defines a string "HELLO WORLD!!" in the .data section and then uses the `write system call` to `print the string to stdout`.

![Hello World example](/Reverse_Engineering/Images/Hello_world.png)

If we look at the disassembled code in the Listings View, we can see instructions to push HELLO WORLD!! to the stack before calling the print function.

### For loop example
```C
int main()
{
    for (int i = 1; i <= 5; i++)
    {
        std::cout << i << std::endl;
    }
    return 0;
}
```
```asm
main:
    ; initialize loop counter to 1
    mov ecx, 1

    ; loop 5 times
    mov edx, 5
loop:
    ; print the loop counter
    push ecx
    push format
    call printf
    add esp, 8

    ; increment loop counter
    inc ecx

    ; check if the loop is finished
    cmp ecx, edx
    jle loop
```

### Function example
```C
int add(int a, int b)
{
    int result = a + b;
    return result;
}
```
```asm
add:
    push ebp          ; save the current base pointer value
    mov ebp, esp      ; set base pointer to current stack pointer value
    mov eax, dword ptr [ebp+8]  ; move the value of 'a' into the eax register
    add eax, dword ptr [ebp+12] ; add the value of 'b' to the eax register
    mov dword ptr [ebp-4], eax  ; move the sum into the 'result' variable
    mov eax, dword ptr [ebp-4]  ; move the value of 'result' into the eax register
    pop ebp           ; restore the previous base pointer value
    ret               ; return to calling function
```

The add function starts by saving the current base pointer value onto the stack.
Then, it sets the base pointer to the current stack pointer value.
The function then moves the values of a and b into the eax register, adds them, and store the result in the result variable.
Finally, the function moves the value of the result into the eax register, restores the previous base pointer value, and returns to the calling function.

## An overview of API calls
The Windows API is a `collection of functions and services` the Windows Operating System provides to `enable developers to create Windows applications`.
These functions include `creating windows`, `menus`, `buttons`, and `other user-interface elements` and `performing tasks` such as file input/output and network communication.

### CreateProcessA example
The `CreateProcessA` function creates a new process and its primary thread. The function takes several parameters, including the name of the executable file, command-line arguments, and security attributes.

![Windows API syntax](/Reverse_Engineering/Images/Win_syntax.png)

Here is an example of C code that uses the CreateProcessA function to launch a new process:

```C
#include <windows.h>

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL, "C:\\\\Windows\\\\notepad.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d).\\n", GetLastError());
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
```

When compiled into assembly code, the CreateProcessA function call looks like this:
```asm
push 0
lea eax, [esp+10h+StartupInfo]
push eax
lea eax, [esp+14h+ProcessInformation]
push eax
push 0
push 0
push 0
push 0
push 0
push 0
push dword ptr [hWnd]
call CreateProcessA
```

This assembly code `pushes the necessary parameters onto the stack in reverse order` and then calls the CreateProcessA function. The CreateProcessA function then launches a new process and returns a handle to the process and its primary thread.

During malware analysis, identifying the API call and examining the code can help understand the malware's purpose.

## Common APIs used by Malware
Malware authors heavily rely on Windows APIs to accomplish their goals. It's important to know the Windows APIs used in different malware variants. It's an important step in advanced static analysis to examine the `import` functions, which can reveal much about the malware.

### Keylogger
- `SetWindowsHookEx`: Installs an `application-defined hook procedure into a hook chain`. Used to `monitor and intercept system events`, such as `keystrokes` or `mouse clicks`.
- `GetAsyncKeyState`: Retrieves the status of a virtual key when the function is called. Used to `determine if a key is being pressed` or `released`.
- `GetKeyboardState`: Retrieves the status of all virtual keys. Used to `determine the status of all key`s on the keyboard.
- `GetKeyNameText`: Retrieves the `name of a key`. Used to `determine the name of the pressed key`.

### Downloader
Designed to download other malware onto a victim's system.

- `URLDownloadToFile`: `Downloads a file` from the internet and saves it to a local file. Used to `download additional malicious code` or updates to the malware.
- `WinHttpOpen`: `Initializes the WinHTTP API`. Used to `establish an HTTP connection to a remote server` and download additional malicious code.
- `WinHttpConnect`: `Establishes a connection` to a remote server using the WinHTTP API. Used to `connect to a remote server and download additional malicious code`.
- `WinHttpOpenRequest`: `Opens HTTP request` using the WinHTTP API. Used to `send HTTP requests to a remote server` and download additional malicious code or steal data.

### C2 Communication
Command and Control (C2) communication is a method malware uses to communicate with a remote server or attacker.

- `InternetOpen`: `Initializes a session for connecting to the internet`. Used to `connect to a remote server and communicate with a command-and-control (C2) server`.
- `InternetOpenUrl`:` Opens a URL` for download. Used to `download additional malicious code` or steal data from a C2 server.
- `HttpOpenRequest`: `Opens HTTP request`. Used to `send HTTP requests to a C2 server and receive commands` or additional malicious code.
- `HttpSendRequest`: Sends `HTTP request to a C2 server`. Used to `send data or receive commands` from a C2 server.

### Data Exfiltration
Unauthorized data transfer from an organization to an external destination.

- `InternetReadFile`: `Reads data from a handle to an open internet resource`. Used to `steal data from a compromised system and transmit it to a C2 server`.
- `FtpPutFile`: `Uploads a file to an FTP server`. Used to `exfiltrate stolen data to a remote server`.
- `CreateFile`: `Creates or opens a file or device`. Used to `read or modify files containing sensitive information` or `system configuration data`.
- `WriteFile`: `Writes data to a file or device`. Used to `write stolen data to a file and then exfiltrate it` to a remote server.
- `GetClipboardData`: Used to `retrieve data from the clipboard`. Used to `retrieve sensitive data that is copied to the clipboard`.

### Dropper
Designed to install other malware onto a victim's system.

- `CreateProcess`: `Creates a new process and its primary thread`. Used to `execute its code in the context of a legitimate process`, making it more difficult to detect and analyze.
- `VirtualAlloc`: Reserves or commits a region of memory within the virtual address space of the calling process. Malware can use this function to `allocate memory to store its code`.
- `WriteProcessMemory`: Writes data to an area of memory within the address space of a specified process. Used to `write its code to the allocated memory`.

### API Hooking
`Intercept calls to Windows APIs and modify their behavior`.

- `GetProcAddress`: `Retrieves the address of an exported function or variable` from a specified dynamic-link library (DLL). Used to `locate and hook API calls made by other processes`.
- `LoadLibrary`: Loads a dynamic-link library (DLL) into a process's address space. Used to `load and execute additional code from a DLL or other module`.
- `SetWindowsHookEx` This API is used to `install a hook procedure that monitors messages sent to a window or system event`. Used to `intercept calls to other Windows APIs and modify their behavior`.

### Anti-debugging and VM detection
Evade detection and analysis by security researchers.

- `IsDebuggerPresent`: Checks whether a process is running under a debugger. Used to `determine whether it is being analyzed` and take appropriate action to evade detection.
- `CheckRemoteDebuggerPresent`: Checks whether a remote debugger is debugging a process. Used to `determine whether it is being analyzed` and take appropriate action to evade detection.
- `NtQueryInformationProcess`: Retrieves information about a specified process. Used to `determine whether the process is being debugged` and take appropriate action to evade detection.
- `GetTickCount`: Retrieves the number of milliseconds that have elapsed since the system was started. Used to `determine whether it is running in a virtualized environment`, which may indicate that it is being analyzed.
- `GetModuleHandle`: Retrieves a handle to a specified module. Used to `determine whether it is running under a virtualized environment`, which may indicate that it is being analyzed.
- `GetSystemMetrics`: Retrieves various system metrics and configuration settings. Used to `determine whether it is running under a virtualized environment`, which may indicate that it is being analyzed.

Read more on [malapi.io](https://malapi.io/) to learn about APIs used in different malware families.

## Analyzing process hollowing
Let's take analyze a code sample that uses [process hollowing](https://attack.mitre.org/techniques/T1055/012/).

An important point to note is that almost all malware comes `packed with known or custom packers` and also have employed different Anti-debugging / VM detection techniques to hinder the analysis. 

This sample is not packed and has no Anti-debugging / VM detection techniques is applied.

Our objective of advanced static analysis would be to:
- `Examine the API calls` to find a pattern or suspicious call.
- Look at the suspicious `strings`.
- Find `interesting or malicious functions`.
- Examine the disassembled/decompiled code to `find as much information as possible`.

> [!NOTE]
>
> It's important to mention that starting to search for the CreateProcessA function right away is not how an analyst would start analyzing an unknown binary. This whole example is just to get comfertable with Ghidra.

### CreateProcess
The suspicious process creates a victim process in the suspended state.

To confirm, let's search for the CreateProcessA API in the Symbol Tree section.

Then, `right-click on the Show References` to option to display all the program sections where this function is called.

Clicking on the first reference will take us to the disassembled code and show the decompiled C code in the Decompile section.

It clearly shows how the parameters on the stack are being pushed in reverse order before calling the function. The value `0x4` in the `process creation flag` is being pushed into the stack, representing the `suspended state`.

### Graph View
Clicking on the Display Function Graph in the toolbar will show the graph view of the disassembled code we are examining.

![Function graph](/Reverse_Engineering/Images/Function_graph.png)

In the above case, if the program:
- Fails to create a victim process in the suspended state, it will move to block 1. The `red arrow represents the failure` to meet the condition mentioned above.
- Successfully creates the victim process, it will move to block 2. The `green arrow represents the success` of the jump condition.

### Example of further analysis
1. Opening a suspicous file

    The CreateFileA API is used to either create or open an existing file.

2. Hollowing the process

    Malware use ZwUnmapViewOfSection or NtUnmapViewOfSection API calls to unmap the target process's memory.

    NtUnmapViewOfSection takes exactly two arguments, the base address (virtual address) to be unmapped and the handle to the process that needs to be hollowed.

3. Allocating memory

    Once the process is hollowed, malware must allocate the memory using VirtualAllocEx before writing the process.

    Arguments passed to the function include a handle to the process, address to be allocated, size, allocation type, and memory protection flag.

4. Writing down the memory

    Once the memory is allocated, the malware will attempt to write the suspicious process/code into the memory of the hollowed process. The WriteProcessMemory API is used for this purpose.

    There were three calls to the WriteProcessMemory Function. The last call references to the code in the Kernel32 DLL; therefore, we can ignore that. From the decompiled code, it seems the program is copying different sections of the suspicious process one by one.

5. Resuming the thread

    Once all is sorted out, the malware will get hold of the thread using the SetThreadContext and then resume the thread using the ResumeThread API to execute the code.