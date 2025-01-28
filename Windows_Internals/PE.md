# Portable executable file format
## Introduction
In the Windows Operating System, you might have often seen files with extension .exe which stands for executable (file).

As the name suggests, an executable file contains code that can be executed. Therefore, anything that needs to be run on a Windows Operating System is executed using an executable file, also called a `Portable Executable file (PE file)`, as it can be run on any Windows system.

A PE file is a `Common Object File Format (COFF) data structure`.

The COFF consists of:
- Windows PE files
- DLLs
- Shared objects in Linux
- ELF files

> [!TIP]
> Before dissecting any PE headers familiarize yourself with the concept of [`endianness`](https://en.wikipedia.org/wiki/Endianness)

## Overview
On disk, a PE executable looks the same as any other form of digital data, i.e., a combination of bits.

If we open a PE file in a Hex editor, we will see a random bunch of Hex characters. This bunch of Hex characters are the instructions a Windows OS needs to execute this binary file.

Some of the important headers that we will discuss are:
- IMAGE_DOS_HEADER
- IMAGE_NT_HEADERS
- FILE_HEADER
- OPTIONAL_HEADER
- IMAGE_SECTION_HEADER
- IMAGE_IMPORT_DESCRIPTOR

All of these headers are of the data type `STRUCT`. A struct is a user-defined data type that combines several different types of data elements in a single variable. Since it is user-defined, we need to see the documentation to understand the type for each STRUCT variable. The documentation for each header can be found on [Microsoft learn](https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-image_nt_headers32), where you can find the data types of the different fields inside these headers.

![PE structure](/Windows_Internals/Images/PE_structure_02.png)

## Basic file info
Below properties are common to find, note that they are always relevant to the section you are looking at. In this case since we're looking at information about the PE file they're applied to the entire PE file.


The higher the value of Entropy, the more random the data is. We will learn about the utility of Entropy as we learn more about malware analysis.

- Size: denotes the `size of the section in bytes`.
- Hashes: unique identifiers to check the validity of the program
- Entropy: the amount of randomness found in data
- Architecture: refers to the CPU architecture the program is compiled for
- Compile date: the data on which the code was compiled into the executeable

The header starts below this information, with the heading IMAGE_DOS_HEADER.

## IMAGE_DOS_HEADER
The IMAGE_DOS_HEADER consists of the first 64 bytes of the PE file. The first two bytes say `4D 5A`. They translate to the `MZ` characters in ASCII.

The MZ characters denote the `initials` of [Mark Zbikowski](https://en.wikipedia.org/wiki/Mark_Zbikowski), one of the Microsoft architects who created the MS-DOS file format. The MZ characters are an `identifier of the Portable Executable format`. When these two bytes are present at the start of a file, the Windows `OS considers it a Portable Executable format file`.

- e_magic: 0x5a4d or MZ
- e_lfanew: denotes the address from where the IMAGE_NT_HEADERS start.

The IMAGE_DOS_HEADER is generally not of much use apart from these fields, especially during malware reverse engineering. The only reason it's there is backward compatibility between MS-DOS and Windows.

## DOS_STUB
The DOS STUB contains the message that we also see in a Hex Editor: `!This program cannot be run in DOS mode`.

Note that the `size`, `hashes`, and `Entropy` found here are not related to the PE file. Instead, it is for the particular section we are analyzing. These values are calculated based on the data in a specific header.

The `size` value denotes the `size of the section in bytes`. Then we see different hashes for the section. 
Entropy is the amount of randomness found in data. The higher the value of Entropy, the more random the data is. We will learn about the utility of Entropy as we learn more about malware analysis.

The DOS STUB is a small piece of code that only runs if the PE file is incompatible with the system it is being run on. It displays the message: `!This program cannot be run in DOS mode`, mentioned above.

### DOS_STUB: RICH_HEADER

## IMAGE_NT_HEADERS
We can find details of [IMAGE_NT_HEADERS](https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-image_nt_headers32) in Microsoft Documentation. This header contains most of the vital information related to the PE file.

### IMAGE_NT_HEADERS: NT_HEADERS
Before diving into the details of `NT_HEADERS`, let's get an overview of the NT_HEADERS.

Remember, the starting address of IMAGE_NT_HEADERS is found in `e_lfanew` from the IMAGE_DOS_HEADER.

The NT_HEADERS consist of the following:
- Signature
- FILE_HEADER
- OPTIONAL_HEADER

#### Signature
The Signature is the first 4 bytes that denote the start of the NT_HEADER.

#### FILE_HEADER
- `Machine`: Type of architecture for which the PE file is written. 
  
    E.g: We can see that the architecture is i386 which means that this PE file is compatible with 32-bit Intel architecture.

- `NumberOfSections`: A PE file contains different sections where `code`, `variables`, and `other resources` are stored. This field of the IMAGE_FILE_HEADER mentions the `number of sections` the PE file has.
- `TimeDateStamp`: The time and date of the binary compilation.
- `PointerToSymbolTable and NumberOfSymbols`: These fields are not generally related to PE files. Instead, they are here due to the COFF file headers.
- `SizeOfOptionalHeader`: The size of the optional header.
- `Characteristics`: Mentions the different characteristics of a PE file.

    E.g: In our case (example program), this field tells us that:
    - PE file has `stripped relocation information`
    - PE file has `stripped line numbers`
    - PE file has `stripped local symbol information`
    - It is an executable image
    - It is compatible with a 32-bit machine

To learn more about the [FILE_HEADER](https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-image_file_header), you can check out Microsoft Documentation for it.

#### OPTIONAL_HEADER
The OPTIONAL_HEADER is also a part of the NT_HEADERS. It contains some of the most important information present in the PE headers.

- `Magic`: The Magic number tells whether the PE file is a 32-bit or 64-bit application.

    - `0x010B`: denotes a 32-bit application
    - `0x020B`: denotes a 64-bit application

- `AddressOfEntryPoint`: This is the address from where Windows will begin execution. In other words, the first instruction to be executed is present at this address.

    This is a `Relative Virtual Address (RVA)`, meaning it is at an `offset relative to the base address of the image` (`ImageBase`) once loaded into memory.

- `BaseOfCode`: Address of the `code section`, relative to `ImageBase`
- `BaseOfData`: Address of the `data section`, relative to `ImageBase`
- `ImageBase`: The ImageBase is the `preferred loading address of the PE file in memory`.

    Generally, the ImageBase for .exe files is `0x00400000`. Since Windows can't load all PE files at this preferred address, some relocations are in order when the file is loaded in memory. These `relocations are then performed relative to the ImageBase`.

- `Subsystem`: The Subsystem required to run the image.

    The Subsystem can be Windows Native, GUI (Graphical User Interface), CUI (Commandline User Interface), or some other Subsystem. We can find the complete list in [Microsoft Documentation](https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-image_optional_header32).

- `DataDirectory`: The DataDirectory is a structure that contains import and export information of the PE file (called `Import Address Table` and `Export Address Table`). This information is handy as it gives a glimpse of what the PE file might be trying to do.

### IMAGE_NT_HEADERS: IMAGE_SECTION_HEADER
The data that a PE file needs to perform its functions, like code, icons, images, User Interface elements, etc., are stored in different Sections. We can find information about these Sections in the `IMAGE_SECTION_HEADER`.

As we can see, the IMAGE_SECTION_HEADER has different sections:
- `.text`: `Contains executable code` for the application.
- `.rdata` / `.idata`: These sections often `contain the import information` of the PE file.

    Import information helps a PE file import functions from other files or Windows API.

- `.data`: `Contains initialized data` of the application.

- `.ndata`: Contains `uninitialized data`.
- `.reloc`: Contains `relocation information` of the PE file.
- `.rsrc`: The resource section contains `icons`, `images`, or `other resources` required for the application UI.

All of these different types of sections commonly include important information:
- `VirtualAddress`: Contains `this section's Relative Virtual Address (RVA)` in the memory.
- `VirtualSize`: Contains the `section's size once loaded into the memory`.
- `SizeOfRawData`: Contains the s`ection size as stored on the disk before the PE file is loaded in memory`.
- `Characteristics`: Contains the `permissions` that the section has.

    E.g: `CODE | EXECUTE | READ`, meaning that this section contains executable code, which `can be read but can't be written to`.

#### PE Base relocations

### IMAGE_NT_HEADERS: IMAGE_IMPORT_DESCRIPTOR
PE files don't contain all the code they need to perform their functions. In a Windows Operating System, PE files leverage code from the Windows API to perform many functions.

The `IMAGE_IMPORT_DESCRIPTOR` structure contains information about the different `Windows APIs that the PE file loads when executed`.

This information is handy in identifying the potential activity that a PE file might perform.

E.g: if a PE file imports CreateFile API, it indicates that it might create a file when executed.

These files are `dynamically linked libraries (DLL's)` that export Windows functions or APIs for other PE files.

We can also see that inside of the dll's section there are the values `OriginalFirstThunk` and `FirstThunk`. The Operating System uses these values to build the `Import Address Table (IAT)` of the PE file.

## Packing and Identifying packed executables
Since a PE file's information can be easily extracted using a `Hex editor` or a tool like `pe-tree`, it becomes undesirable for people who don't want their code to be reverse-engineered.

This is where the `packers` come in. A packer is a `tool to obfuscate the data in a PE file` so that it can't be read without unpacking it. In simple words, packers `pack the PE file in a layer of obfuscation` to avoid reverse engineering and `render a PE file's static analysis useless`. When the PE file is executed, it runs the unpacking routine to extract the original code and then executes it.

Legitimate software developers use packing to address piracy concerns, and malware authors use it to avoid detection.

### How to identify if a PE file is packed
#### Section header names
A PE file has a .text section, a .data section, and a .rsrc section, where only the .text section has the execute flag set because it contains the code. Now take the example of the file named zmsuz3pinwl. When we open this file in pe-tree, we find that it has `unconventional section names` (`or no names`, in this case).

![Packed PE file](/Windows_Internals/Images/Packed.png)

We might think this has something to do with the tool we use to analyze the file. Therefore, let's check it using another PE analysis tool called `pecheck`. The pecheck tool provides the same information we have been gathering from the pe-tree tool, but it is a command-line tool.

Let's see the information in the PE Sections heading in the output:

```
----------PE Sections----------

[IMAGE_SECTION_HEADER]
0x1F0      0x0   Name:                          
0x1F8      0x8   Misc:                          0x3F4000  
0x1F8      0x8   Misc_PhysicalAddress:          0x3F4000  
0x1F8      0x8   Misc_VirtualSize:              0x3F4000  
0x1FC      0xC   VirtualAddress:                0x1000    
0x200      0x10  SizeOfRawData:                 0xD3400   
0x204      0x14  PointerToRawData:              0x400     
0x208      0x18  PointerToRelocations:          0x0       
0x20C      0x1C  PointerToLinenumbers:          0x0       
0x210      0x20  NumberOfRelocations:           0x0       
0x212      0x22  NumberOfLinenumbers:           0x0       
0x214      0x24  Characteristics:               0xE0000040
Flags: IMAGE_SCN_CNT_INITIALIZED_DATA, IMAGE_SCN_MEM_EXECUTE, IMAGE_SCN_MEM_READ, IMAGE_SCN_MEM_WRITE
Entropy: 7.999788 (Min=0.0, Max=8.0)
MD5     hash: fa9814d3aeb1fbfaa1557bac61136ba7
SHA-1   hash: 8db955c622c5bea3ec63bd917db9d41ce038c3f7
SHA-256 hash: 24f922c1cd45811eb5f3ab6f29872cda11db7d2251b7a3f44713627ad3659ac9
SHA-512 hash: e122e4600ea201058352c97bb7549163a0a5bcfb079630b197fe135ae732e64f5a6daff328f789e7b2285c5f975bce69414e55adba7d59006a1f0280bf64971c
```

We see here that the section name is empty, and it is not a glitch in the tool we used to analyze the PE file.

#### Section entropy
Another thing that we might notice here is that the Entropy of the .data section and three of the four unnamed sections is `higher than seven and is approaching 8`. As we discussed in a previous task, higher Entropy represents a `higher level of randomness in data`. Random data is generally generated when the original data is obfuscated, indicating that these values `might indicate a packed executable`.

#### Section permissions
Apart from the section names, another indicator of a packed executable is the permissions of each section. For the PE file in the above terminal, we can see that the section `contains initialized data and has READ, WRITE and EXECUTE permissions`. Similarly, some `other sections also have READ, WRITE and EXECUTE permissions`. This is also usually `not found in an ordinary unpacked PE file`, where only the .text section has EXECUTE permissions.

#### SizeOfRawData & Misc_VirtualSize
Another valuable piece of information from the section headers to identify a packed executable is the `SizeOfRawData` and `Misc_VirtualSize`. In a packed executable, the `SizeOfRawData will always be significantly smaller than the Misc_VirtualSize in sections with WRITE and EXECUTE permissions`. This is because when the PE file unpacks during execution, it writes data to this section, increasing its size in the memory compared to the size on disk, and then executes it.

#### From import functions
The last important indicator of a packed executable we discuss here is its import functions. The redline PE file we analyzed earlier imported lots of functions, indicating the activity it potentially performs. However, for the PE file zmsuz3pinwl, `we will see only a handful of imports`, especially the GetProcAddress, GetModuleHandleA, and `LoadLibraryA`. These functions are often `some of the only few imports of a packed PE file because these functions provide the functionality to unpack the PE file during runtime`.

### Used tools
- [`wxHexEditor`](https://www.wxhexeditor.org/)
- [`pe-tree`](https://github.com/blackberry/pe_tree)
- [`pecheck`](https://github.com/DidierStevens/DidierStevensSuite/blob/master/pecheck.py)