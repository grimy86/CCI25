# Declaring variables
Declare variables in the .data section. The 'd' stands for defined / declared. So db is a defined or declared byte.

| type  | size      |
|-------|-----------|
| db    | 1 byte    |
| dw    | 2 bytes   |
| dd    | 4 bytes   |
| dq    | 8 bytes   |
| dt    | 10 bytes  |

We can also set aside uninitialized data, which is an empty section of memory that gets prepared for us to store data into.