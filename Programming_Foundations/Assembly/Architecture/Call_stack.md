# The stack
Refers to the logical structure used to manage function calls, consisting of stack frames.

This section of the Memory contains local variables, arguments passed on to the program, and the return address of the parent process that called the program.

It keeps track of all the active functions from the start of the program to the current point of execution, and handles allocation of all function parameters and local variables.

## The call stack segment
The stack segment refers to the physical region of memory that is allocated for the stack. This memory is used for storing all of the stack frames, including the frames used in the call stack.

- Physical Memory: The stack segment is a real, **reserved memory space provided by the operating system when a process or thread is started**.

## Lifo data structure
The stack's main mechanism is that it uses a "stack" data structure for manipulating the data. This is a last-in, first-out (LIFO) structure. This means that the last element pushed onto the stack is the first one to be popped out.
- elements get pushed onto the stack
- elements get popped off of the stack

> [!IMPORTANT]
> The stack grows negatively!
> 
> So, the higher up you go into the stack the more negative the items become.

![Stack DataStructure](/Info/Images/Stack_DataStructure.png)

## A stack frame
By default any function that you can call will create it's own "stack frame".

A stack frame is an individual block of data on the call stack that is created when a function is called. Stack frames are not pushed or popped, they are not a "real" thing. The stack frame is simply some specific range of memory that we can put into context with a specific function. It holds all the necessary information for a specific function call, including:

- The address of the instruction beyond the function call (called the return address). This is how the program remembers where to return to after the called function exits.
- All function arguments
- Memory for any local variables
- Saved copies of any registers modified by the function that need to be restored when the function returns (E.g. EBP)

## A stack frame in action
### Prologue
The CPU encounters a function call and jumps to the start of a stack frame. 

At this point in time the base pointer (ebp) still points to the base of the last stack frame where this function is being called from.
1. Push the base pointer (ebp) onto the stack.
2. Move the stack pointer (esp) onto the same position as ebp.
3. Push variables we want to preserve onto the stack
4. Sub esp by a certain amount, creating room for local variables
5. Move the local variables by a certain amount (under esp)

### The function body
This is where the function logic happens.

### Epilogue
When the function terminates, the following steps happen:
1. Move ebp into esp to restore the stack pointer.
2. Pop ebp to restore the caller's base pointer.
3. Return to the caller's stack frame.

![Stack in action](/Programming_Foundations/Assembly/Images/Stack_example.png)

<!--
(The x86 architecture has hardware support for an execution stack mechanism. Instructions such as push, pop, call and ret are used with the properly set up stack to pass parameters, to allocate space for local data, and to save and restore call-return points. The ret size instruction is very useful for implementing space efficient (and fast) calling conventions where the callee is responsible for reclaiming stack space occupied by parameters. When setting up a stack frame to hold local data of a recursive procedure there are several choices; the high level enter instruction (introduced with the 80186) takes a procedure-nesting-depth argument as well as a local size argument, and may be faster than more explicit manipulation of the registers (such as push bp ; mov bp, sp ; sub sp, size). Whether it is faster or slower depends on the particular x86-processor implementation as well as the calling convention used by the compiler, programmer or particular program code; most x86 code is intended to run on x86-processors from several manufacturers and on different technological generations of processors, which implies highly varying microarchitectures and microcode solutions as well as varying gate- and transistor-level design choices. The full range of addressing modes (including immediate and base+offset) even for instructions such as push and pop, makes direct usage of the stack for integer, floating point and address data simple, as well as keeping the ABI specifications and mechanisms relatively simple compared to some RISC architectures (require more explicit call stack details).)
-->

## The heap
While on the topic of memory, let's take a look at the heap. Keep in mind, the heap is not part of the stack, this is just relevant to memory.

The heap, also known as dynamic Memory, contains variables and data created and destroyed during program execution. When a variable is created, memory is allocated for that variable at runtime. And when that variable is deleted, the memory is freed. Hence the name dynamic memory.