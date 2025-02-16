# Dynamic Link Libraries
The [Microsoft docs](https://learn.microsoft.com/en-us/troubleshoot/windows-client/setup-upgrade-and-drivers/dynamic-link-library) describe a `DLL` as "`a library that contains code and data that can be used by more than one program at the same time`."

Reading up on [COM objects](/Windows_Internals/Windows_API.md#history-dde-ole--com) might clear up things if you're wondering about the history behind DLL's and how they came to be what they are today.

DLLs are used as one of the core functionalities behind application execution in Windows. From the Windows documentation, "The use of DLLs helps promote modularization of code, code reuse, efficient memory usage, and reduced disk space. So, the operating system and the programs load faster, run faster, and take less disk space on the computer."

When a DLL is loaded as a function in a program, the DLL is assigned as a `dependency`. Since a program is dependent on a DLL, attackers can target the DLLs rather than the applications to control some aspect of execution or functionality.

DLLs are created no different than any other project/application; they only require slight syntax modification to work. Below is an example of a DLL from the `Visual C++ Win32 Dynamic-Link Library project`:

```cpp
#include "stdafx.h"
#define EXPORTING_DLL
#include "sampleDLL.h"
BOOL APIENTRY DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved
)
{
    return TRUE;
}
void HelloWorld()
{
    MessageBox( NULL, TEXT("Hello World"), TEXT("In a DLL"), MB_OK);
}
```

Below is the `header file` for the DLL; it will define what functions are imported and exported:

```cpp
#ifndef INDLL_H
    #define INDLL_H
    #ifdef EXPORTING_DLL
        extern __declspec(dllexport) void HelloWorld();
    #else
        extern __declspec(dllimport) void HelloWorld();
    #endif
#endif
```

### How are they used by an application?
#### load-time dynamic linking:
When loaded using load-time dynamic linking, `explicit calls to the DLL functions are made from the application`. You can only achieve this type of linking by `providing a header (.h) and import library (.lib) file`. Below is an example of calling an exported DLL function from an application.

```cpp
#include "stdafx.h"
#include "sampleDLL.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HelloWorld();
    return 0;
}
```

#### run-time dynamic linking:
When loaded using run-time dynamic linking, a `separate function` (`LoadLibrary` or `LoadLibraryEx`) is `used to load the DLL at run time`. Once loaded, you need to use `GetProcAddress to identify the exported DLL function to call`. Below is an example of loading and importing a DLL function in an application.

```cpp
...
typedef VOID (*DLLPROC) (LPTSTR);
...
HINSTANCE hinstDLL;
DLLPROC HelloWorld;
BOOL fFreeDLL;
hinstDLL = LoadLibrary("sampleDLL.dll");
if (hinstDLL != NULL)
{
    HelloWorld = (DLLPROC) GetProcAddress(hinstDLL, "HelloWorld");
    if (HelloWorld != NULL)
        (HelloWorld);
    fFreeDLL = FreeLibrary(hinstDLL);
}
...
```