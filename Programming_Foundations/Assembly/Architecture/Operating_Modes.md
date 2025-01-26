# Modes of Operation
## Protective mode
The native processor state (default mode, therefor most commonly used)
- Multiple processes can run but they are each given their own section of memory
- They are forced to stay within that section of memory and can't interact with other processes memory
- Every feature is available to you and you can do anything you want to do as long as you stay within the bounds of the memory

## Real Address mode
Implements early intel programming environment with the ability to switch modes.
- Allows you to directly access hardware components

## System Management mode
Provides an operating system with mechanisms such as power management and security.
- Useful when designing a system that's very specific to the processor