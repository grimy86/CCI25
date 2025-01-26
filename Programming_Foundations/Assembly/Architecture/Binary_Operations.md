# Binary operations

True / false: In programming 1 is generally respresented as a value being "True" and 0 as one being "False".

| **Operation** | **Symbol** | **Description** | **Example** | **Result** |
|---------------|------------|-------------------|-------------|------------|
| **NOT** | `!` | Flips the bit (1 becomes 0, 0 becomes 1). | `NOT 1` | `0` |
| | | | `NOT 0` | `1` |
| **AND** | `&` | Returns 1 if **both bits** are 1; otherwise, returns 0. | `1 & 1` | `1` |
| | | | `1 & 0` | `0` |
| | | | `0 & 0` | `0` |
| **OR** | `\|` | Returns 1 if **either bit** is 1; otherwise, returns 0. | `1 \| 1` | `1` |
| | | | `1 \| 0` | `1` |
| | | | `0 \| 0` | `0` |
| **XOR** | `^` | Returns 1 if **only one bit** is 1 (i.e., the bits are different); otherwise, returns 0. | `1 ^ 1` | `0` |
| | | | `1 ^ 0` | `1` |
| | | | `0 ^ 0` | `0` |
