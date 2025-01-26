section .data
    message db 'Hello, World!', 0   ; The message to display
    caption db 'MessageBox', 0       ; The caption of the message box

section .text                       ; The text section is used for keeping the actual code.
global _start                       ; Global _start, tells the kernel where the program execution begins.
extern MessageBoxA, ExitProcess    ; Import MessageBoxA and ExitProcess

_start:
    ; Calling MessageBoxA
    ; MessageBoxA(HWND, LPCSTR, LPCSTR, UINT)
    ; Parameters: hwnd = 0, message, caption, MB_OK (0x0)
    push 0                          ; MB_OK (0x0)
    push caption                    ; Caption of the message box
    push message                    ; Message to display
    push 0                          ; HWND (0 means no parent)
    call MessageBoxA                ; Call the MessageBoxA function

    ; Exit the program
    push 0                          ; Exit code (0)
    call ExitProcess                ; Call ExitProcess to exit the program