# Introduction
## What is assembly?
Assembly is a family of low-level programming languages that are one step above machine code. Each assembly language is specific to a particular CPU architecture (e.g., x86, ARM, MIPS) and directly corresponds to the processor's instruction set.

It is a human-readable representation of the binary instructions that a computer's processor (CPU) understands and executes. The main takeaway here being that it's a representation meaning that it's essentially the same as binary instructions.

## Why use assembly?
Low-level languages provide direct control over hardware components making them 'closer' to the machine. It's so close to the processor that the way it's written actually resembles the way the processor processes the instructions.

## What is an architecture?
In computing, architecture refers to the design and organization of a computer system, particularly the central processing unit (CPU) and its instruction set. It determines how a computer processes data, executes instructions, and communicates with memory and peripherals. Code written for one architecture won't run on another without modification.

Key aspects of architecture:
- Instruction Set Architecture or ISA
- Processor word sizes
- Endianness
- Microarchitecture such as pipelines, cache, clock speed, etc.
- Memory model
- Peripheral Interfaces

### Common CPU architecures
| Architecture | Description | Use cases |
|-|-|-|
| x86 | A complex instruction set computer architecture (CISC) used in most desktops, laptops and servers. | PCs |
| x86-64 | An extension of x86 that supports 64-bit processing and larger memory addressing | Modern PCs |
| ARM | A reduced instruction set computer (RISC) architecture optimized for low power and high efficiency. | Smartphones, tablets, embedded systems |
| MIPS | RISC architecture commonly used in embedded systems and networking equipment. | Routers, IoT devices |
| RISC-V | Open-source RISC architecture designed for flexibility and extensibility. | Research, education |
| PowerPC | RISC architecture developed by IBM, used in servers and older Apple computers. | High-performance computing, legacy systems |

## What is an instruction set?
An instruction set is the collection of basic operations (instructions) that a CPU can perform. These instructions are part of the Instruction Set Architecture (ISA).

### What are CISC and RISC?
CISC (Complex Instruction Set Computing) and RISC (Reduced Instruction Set Computing) are two design philosophies for how instruction sets are created and executed.

CISC designs focus on having a large set of complex instructions, where a single instruction can perform multiple low-level operations. This reduces the number of instructions a programmer needs to write but increases the complexity of the CPU.

RISC designs focus on having a smaller set of simple instructions, where each instruction performs a single operation. This simplifies the CPU design and enables faster execution.