# The .NET Framework
.NET is a software framework for building software .

It helps developers create `Windows` applications, websites, games, and even mobile apps without having to build everything from scratch.

It provides:
- A set of built-in tools and libraries (so you don’t have to write everything yourself).
- Support for multiple programming languages (like C#, VB.NET, and F#).
- A system that runs and manages your code (so it works smoothly on Windows, and now also on Mac & Linux).

## .NET Framework vs. .NET core vs .NET
The old .NET, initially name the .NET Framework worked only on Windows and wasn't catered toward cross-platform development. Later the .NET Framework has been renamed ".NET core" and works with Windows, Mac and Linux. Later .NET Core evolved into just “.NET” starting with .NET 5 (released in 2020).

Don't try to make any of this naming convention make sense cause it won't.

## Versions
| Windows version | .NET Framework version |
|-|-|
| Windows 8 | 4.5 |
| Windows 8.1 | 4.5.1 |
| Windows 10 | 4.6 |
| Windows 10.1511 | 4.6.1 |
| Windows 10.1607 | 4.6.2 |
| Windows 10.1703 | 4.7 |
| Windows 10.1709 | 4.7.1 |
| Windows 10.1803 | 4.7.2 |
| Windows 10 May Update | 4.8 |
| Windows 11.22621 | 4.8.1 |

## Components
The .NET Framework consists of two main components:
1. The Common Language Runtime (CLR):

    This is the run-time engine for .NET and it includes:
    - A JIT (Just-In-Time) compiler named `Roslyn`. Roslyn translates CIL (Common Intermediate Language) instructions to the cpu.
    - A garbage collector
    - Type verification
    - Code access security
    - Etc.
    The CLR is implemented as a COM in-process server (DLL) and uses the Windows API for it's facilities.

2. The .NET Framework Class Library (FCL):

    This is just a large collection of types / classes for the programmer to be used.