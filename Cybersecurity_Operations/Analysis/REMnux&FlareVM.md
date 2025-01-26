# REMnux Cheat Sheet
REMnux is a Linux distribution designed for reverse engineering and analyzing malware. It includes a variety of tools for analyzing files, network traffic, and more.

| Tool                        | Description                                                | Example                                                   | Used For                           |
|-----------------------------|------------------------------------------------------------|-----------------------------------------------------------|------------------------------------|
| `radare2`                    | A framework for analyzing binaries and disassembling code.  | `radare2 malware.bin`                                      | Binary analysis                    |
| `binwalk`                    | A tool for extracting firmware images and files embedded in binaries. | `binwalk firmware.img`                                      | Extract embedded files from firmware |
| `gdb`                        | The GNU debugger, used for debugging programs.             | `gdb malware.bin`                                          | Debugging programs and binaries    |
| `strace`                     | A diagnostic tool to trace system calls and signals.       | `strace -p 1234`                                           | Analyzing system calls             |
| `objdump`                    | Displays information about object files.                   | `objdump -d malware.bin`                                    | Disassembling binaries              |
| `yara`                       | A tool for pattern matching against files using rules.     | `yara rules.yar malware.bin`                               | Malware detection and analysis     |
| `file`                       | Determines the type of a file.                             | `file malware.bin`                                          | Identifying file types             |
| `strings`                    | Extracts human-readable strings from binaries.             | `strings malware.bin`                                       | String extraction from binaries    |
| `tcpdump`                    | A network traffic capture tool.                            | `tcpdump -i eth0`                                           | Capturing network traffic          |
| `floss`                      | A tool for extracting strings from executables that are obfuscated. | `floss malware.exe`                                        | Analyzing obfuscated strings      |
| `peframe`                    | A tool to analyze PE files for potential indicators of compromise. | `peframe malware.exe`                                      | Analyzing PE file headers          |

## Common REMnux Workflow
1. **Extract Strings from a Binary**
   ```bash
   strings malware.bin

# FLARE VM Cheat Sheet

FLARE VM is a Windows-based environment for reverse engineering and malware analysis, offering a wide array of tools for static and dynamic analysis.

| Tool                        | Description                                                | Example                                                   | Used For                           |
|-----------------------------|------------------------------------------------------------|-----------------------------------------------------------|------------------------------------|
| `x64dbg`                     | A powerful Windows debugger for reverse engineering.        | `x64dbg malware.exe`                                       | Debugging Windows applications    |
| `IDAPython`                  | A plugin for IDA Pro to add Python scripting capabilities.  | `import idapython`                                         | Extending IDA Pro with Python      |
| `Procmon`                    | Monitors and logs system calls, file system activity, and more. | `procmon /Minimized`                                      | Monitoring system activity         |
| `Wireshark`                  | A network protocol analyzer for capturing and inspecting network traffic. | `wireshark -i 1`                                         | Capturing network traffic          |
| `PEiD`                       | A tool for identifying packers, cryptors, and compilers used to create executables. | `PEiD malware.exe`                                        | Identifying packed executables     |
| `Immunity Debugger`          | A debugger that can be used to analyze Windows applications. | `immunitydebugger malware.exe`                            | Windows application debugging      |
| `OllyDbg`                    | A 32-bit assembler-level debugger for Windows.              | `ollydbg malware.exe`                                     | Analyzing 32-bit executables       |
| `CFF Explorer`               | A tool to inspect and edit PE files and headers.            | `cffe.exe malware.exe`                                    | PE file analysis and modification  |
| `ApateDNS`                   | A DNS server manipulation tool for redirection.            | `ApateDNS.exe`                                             | Manipulating DNS requests          |
| `Volatility`                 | A tool for memory forensics to analyze memory dumps.        | `volatility -f memory.dmp --profile=Win7SP1x64 pslist`     | Memory forensics                   |
| `RegShot`                    | A registry comparison tool to track changes between two snapshots. | `regshot`                                                | Registry analysis                  |

## Common FLARE VM Workflow

1. **Run a Basic Malware Analysis (x64dbg)**
   ```bash
   x64dbg malware.exe
