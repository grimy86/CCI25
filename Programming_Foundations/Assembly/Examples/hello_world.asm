include C:\masm32\include\masm32rt.inc
; use console build all in masm32 editor to build


.data
hello_msg db "This is invoked!", 10, 0 ; newline and null-termination

prompt db "Input a string here: ", 0
string db 50 dup(?)

prompt2 db "Input another string here: ", 0
string2 db 50 dup(?)

same_msg db "The strings are the same.", 0
diff_msg db "The strings are different.", 0

execute_path db "C:\Windows\system32\calc.exe", 0


.code
start:

COMMENT*
    Invoke is just another way of pushing and calling (not recommended).
    Note: Using invoke with 2 or more parameters we want to push the first parameter as the last one.
    E.g:
        invoke MessageBoxA, 0, offset caption, offset title, MB_OK
*

    invoke StdOut, offset hello_msg
    push offset prompt
    call StdOut
    push 50
    push offset string
    call StdIn

    push offset prompt2
    call StdOut
    push 50
    push offset string2
    call StdIn

    push offset string
    push offset string2
    call crt__stricmp
    cmp eax, 0
    je same
    jne diff

same:
    push MB_OK
    push offset same_msg ;title
    push offset same_msg ;caption
    push 0
    call MessageBoxA
    jmp after_cmp

diff:
    push MB_OK
    push offset diff_msg
    push offset diff_msg
    push 0
    call MessageBoxA
    jmp after_cmp

after_cmp:
    push SW_NORMAL
    push offset execute_path
    call WinExec
end start