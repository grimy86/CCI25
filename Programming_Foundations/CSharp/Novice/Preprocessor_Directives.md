# Preprocessor directives
Preprocessor directives are instructions that tell the compiler how to process the source code before actual compilation begins. They do not produce executable code but instead `control how the compiler treats parts of the code`.

Think of them as the control-flow of the compilation and not of the actual code.

| Directive | Description |
|-|-|
| `#define` | Defines a symbol (not a variable). |
| `#undef` | Undefines a previously defined symbol. |
| `#if`, `#elif`, `#else`, `#endif` | Conditionally includes/excludes code. |
| `#region`, `#endregion` | Organizes code into collapsible sections. |
| `#error` | Forces a compilation error with a custom message. |
| `#warning` | Issues a compiler warning with a custom message. |
| `#pragma` | Provides special compiler instructions (e.g., disabling warnings). |
| `#line` | Modifies compiler line numbers for debugging. |

Example of usage:
```cs
class Program
{
    #region Initialization
    static void Initialize()
    {
        Console.WriteLine("Initializing...");
    }
    #endregion

    #region Cleanup
    static void Cleanup()
    {
        Console.WriteLine("Cleaning up...");
    }
    #endregion
}
```