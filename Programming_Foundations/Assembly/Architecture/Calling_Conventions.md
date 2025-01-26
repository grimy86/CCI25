# Calling Conventions
Calling conventions are the blueprint for functions within a program:

## cdecl
Cdecl stand for C declaration. This is the default calling convention used by most compilers for compiling C code on x86.

Take a close look at the following example:
```C
//This is our function in C.
Add(int a, int b) { return a + b; }

int main()
{
    Add(2, 1);
    return 0;
}
```
```asm
main:
    push ebp
    mov ebp, esp
    push 0x1
    push 0x2
    call Add ; return_address = main+0x54

Add:
    push ebp
    mov ebp, esp
    mov eax, [ebp+0x8]
    mov ebx, [ebp+0xC]
    add eax, ebx
    pop ebp
    ret ; eip = return_address

main+0x54:
    add esp, 0x8 ; caller stack cleanup
    mov eax, 0x0 ; exit code
    mov ebp, esp
    pop ebp, esp
    pop ebp
    ret
```

1. Notice how the last arguments being pushed onto the stack is actually the first parameter (right to left). This is called "Reverse Order" and it's one of the cdecl characteristics.

## stdcall
1. arguments are pushed onto the stack in reverse order

Mostly the same as cdecl except the ret instruction now has an operand next to it. The operands is optional and specifies how many bytes to remove from the stack.

```asm
Add:
    push ebp
    mov ebp, esp
    mov eax, [ebp+0x8]
    mov ebx, [ebp+0xC]
    add eax, ebx
    pop ebp
    ret 0x8 ; callee cleanup instead of caller cleanup

main+0x54:
    ; note: there is no caller stack cleanup
    mov eax, 0x0 ; exit code
    mov ebp, esp
    pop ebp, esp
    pop ebp
    ret
```

## fastcall
Fastcall has two variations:
1. fastcall
   - 2-register: First two arguments are passed into registers and the rest are passed into the stack.
2. msfastcall (mainly used in 64-bit systems)
   - 4-register: Four arguments are passed into registers and the rest are passed into the stack.

Let's modify our C function to add 3 numbers togheter.
```C
//This is our function in C.
Add(int a, int b, int c) { return a + b +c; }

int main()
{
    Add(2, 1, 0);
    return 0;
}
```

```asm
main:
    push ebp
    mov ebp, esp
    push 0x0        ; int c -> stack
    mov edx, 0x1    ; int b -> register
    mov ecx, 0x2    ; int a -> register
    call Add ; return_address = main+0x54

Add:
    push ebp
    mov ebp, esp
    add ecx, edx
    mov eax, [ebp-0x4]
    add eax, ecx
    leave
    ret 0x4 ; callee stack cleanup
```

## thiscall
The thiscall calling convention is used in x86 for calling C++ member functions (non-static).

Purpose:
   - Used for calling instance methods of a class.
   - Passes a pointer to the instance (the this pointer) to the method.

1. this pointer: Stored in the ecx register.
2. Arguments: Passed on the stack, from right to left.
3. Return Value: Placed in the eax register, like most x86 conventions.
4. The callee cleans up the stack, similar to stdcall.

```asm
main:
    ; Arguments pushed onto the stack in reverse order
    push b
    push a
    ; `this` pointer placed in ecx
    mov ecx, obj
    ; Call the method
    call method

c++ member func:
    ; Step 1: Prologue (Preserve the stack frame)
    push ebp           ; Save the old base pointer
    mov ebp, esp       ; Set up the new base pointer

    ; Step 2: Access 'this' and arguments
    mov eax, [ecx]     ; Access a member of the object via 'this' (ECX points to the object)
    add eax, [ebp+8]   ; Use the first argument (a) from the stack
    add eax, [ebp+12]  ; Use the second argument (b) from the stack

    ; Step 3: Epilogue (Restore stack and return)
    mov esp, ebp       ; Restore the stack pointer
    pop ebp            ; Restore the old base pointer
    ret 0x8            ; Clean up 8 bytes of arguments (2 arguments, 4 bytes each)
```

For calling conventions in x86-64 take a loot at [microsoft learn x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170&viewFallbackFrom=vs-2019) and its [x64 ABI conventions](https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions?view=msvc-170&viewFallbackFrom=vs-2019).

Additionally, for more info about pro- and epilogue look at [microsoft learn prologue and epilogue](https://learn.microsoft.com/en-us/cpp/build/prolog-and-epilog?view=msvc-170&viewFallbackFrom=vs-2019).