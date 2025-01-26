# Registers
Registers are for storing data. There are 8 common registers in assembly and 6 are used for general purpose.
In general you could use these registers in whatever way you like but there are common conventions.

## Difference between x86 and x86-64 registers
What is the difference between the "E" and "R" prefixes? Besides one being a 64-bit register and the other 32 bits, the "E" stands for extended. The "R" stands for register. The "R" registers were newly introduced in x64, and no, you won't see them on 32-bit systems.


## General purpose
| Register  | Usage                                 | Description       |
|-----------|---------------------------------------|-------------------|
| EAX - RAX | multiplication and division           | Accumulator       |
| EBX - RBX | General purpose                       | Base register     |
| ECX - RCX | Loop counter                          | Counter           |
| EDX - RDX | General purpose                       | Data              |
| EDI - RDX | High speed memory transfer            | Destination index |
| ESI - RSX | High speed memory transfer            | Source index      |


## Specific purpose
| Register  | Usage                                                          | Description           |
|-----------|----------------------------------------------------------------|-----------------------|
| ESP - RSP | Reference function parameters and local variables on the stack | Stack pointer         |
| EBP - RBP | A pointer to the current stack address                         | Base pointer          |
| EIP - RIP | Points to the address of the next instruction                  | Instruction pointer   |

## Sub-registers
The registers are 32-bits in width but can be split up into less bits. the 'E' stands for extended and is the maximum capacity of the register (32 bits).

| 64-bit | 32-bit  | 16-bit | 8-bit | 8-bit  |
|--------|---------|--------|-------|--------|
| RAX    | EAX     | AX     | AH    | AL     |
| RBX    | EBX     | BX     | BH    | BL     |

For more information look at [microsoft learn x64 architecture](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/x64-architecture)

## XMM0-XMM15 and YMM0-YMM15 registers
Different data types can't be put in just any register. Floating-point values are represented differently than integers. Because of this, floating-point values have special registers.

These registers include YMM0 to YMM15 (64-bit) and XMM0 to XMM15 (32-bit). The XMM registers are the lower half of the YMM registers, similar to how EAX is the lower 32 bits of RAX.

Something unique about these registers is that they can be treated as arrays. In other words, they can hold multiple values. For example, YMM# registers are 256-bit wide each and can hold 4 64-bit values or 8 32-bit values. Similarly, the XMM# registers are 128-bits wide and can hold 2 64-bit values or 4 32-bit values.

Special instructions are needed to utilize these registers as vectors.

## Segment registers
Segment Registers are 16-bit registers that convert the flat memory space into different segments for easier addressing. There are six segment registers:

- Code Segment: The Code Segment (`CS` ) register points to the Code section in the memory.
- Data Segment: The Data Segment (`DS`) register points to the program's data section in the memory.
- Stack Segment: The Stack Segment (`SS`) register points to the program's Stack in the memory.
- Extra Segments (`ES`, `FS`, and `GS`): These extra segment registers point to different data sections. These and the DS register divide the program's memory into four distinct data sections.

## EFLAGS & RFLAGS
Flags are contained in a register called EFLAGS (x86) or RFLAGS (x64).

## Extra registers
There are additional registers that should be mentioned. These registers don't have any special uses. There are registers r8 to r15 which are designed to be used by integer type values (not floats or doubles).

Again these can also be split up into:
- R8 - 8 bytes
- R8D - 4 bytes
- R8W - 2 bytes
- R8B - 1 byte