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