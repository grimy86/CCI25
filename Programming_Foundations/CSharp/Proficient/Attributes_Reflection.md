# Attributes
Attributes are `special markers (metadata)` that you can attach to classes, methods, properties, etc., to `provide extra information about them`. They `don’t change how the code runs` but help at runtime or compile-time.

Think of them like stickers or labels on your code that provide instructions to the compiler or runtime. You add attributes above the code element you want to annotate, using square brackets `[ ]` like so:
```cs
// Here, [Obsolete] tells the compiler to warn when someone tries to use OldMethod.
[Obsolete("This method is outdated, use NewMethod instead")]
void OldMethod() {
    Console.WriteLine("This is old.");
}
```

## Predefined or Built-in Attributes
- `Obsolete`: Marks something as outdated

    ```cs
    [Obsolete("Use NewMethod instead", true)]  // true = treat as error
    void OldMethod() {}
    ```

- `Conditional`: Runs code only in specific conditions (like Debug mode)

    ```cs
    #define DEBUG
    using System;
    using System.Diagnostics;

    public class MyClass
    {
        [Conditional("DEBUG")]
        public static void DebugMessage(string msg) {
            Console.WriteLine(msg);
        }
    }
    ```

- `AttributeUsage`: Controls where an attribute can be applied

    ```cs
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Class)]
    class MyCustomAttribute : Attribute {}
    ```

## User-defined Attributes
You can create your own attributes by inheriting from `System.Attribute`.

Let’s say for example that we want to track bugs in our code:
```cs
[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, AllowMultiple = true)]
public class BugInfo : Attribute {
    public int BugID { get; }
    public string Developer { get; }
    public string LastReview { get; }

    public BugInfo(int bugID, string developer, string lastReview) {
        BugID = bugID;
        Developer = developer;
        LastReview = lastReview;
    }
}
```

Now, we can use this on a class or method:
```cs
[BugInfo(101, "Alice", "2024-03-06")]
class MyProgram {}

[BugInfo(202, "Bob", "2024-02-28")]
void FixBug() {}
```

At runtime, we can read this attribute using Reflection (a way to examine metadata):
```cs
Type type = typeof(MyProgram);
foreach (var attr in type.GetCustomAttributes(false)) {
    BugInfo bug = (BugInfo)attr;
    Console.WriteLine($"Bug {bug.BugID}, Reported by {bug.Developer}, Last Reviewed: {bug.LastReview}");
}
```

# Reflection
Imagine you have a toolbox that allows you to peek inside your own C# program while it’s running. This tool is called `Reflection`, it is found in the `System.Reflection` namespace and it helps you:

- View attribute information at runtime (like metadata on classes/methods).
- Examine types inside an assembly (which means analyzing a compiled .exe or .dll).
- Use "late binding" (calling methods/properties on objects without knowing them at compile time).
- Create and use new types dynamically (useful in frameworks and dependency injection).
- See details about classes, methods, and properties at runtime
- Modify and interact with objects dynamically
- Work with attributes (extra data attached to classes/methods)


**Again, define a Custom Attribute:**
```cs
using System;

// Define a custom attribute
[AttributeUsage(AttributeTargets.Class)] // Only for classes
public class HelpAttribute : Attribute 
{
    public string Url { get; } // Read-only property

    public HelpAttribute(string url) // Constructor sets the URL
    {
        Url = url;
    }
}

// Apply the custom attribute to a class
[Help("https://docs.microsoft.com/en-us/dotnet/csharp/")]
class MyClass { }
```

**Read the Attribute Using Reflection:**
```cs
using System;
using System.Reflection;

class Program
{
    static void Main()
    {
        // Get type information of MyClass
        Type type = typeof(MyClass);

        // Retrieve attributes applied to MyClass
        object[] attributes = type.GetCustomAttributes(false);

        foreach (var attribute in attributes)
        {
            if (attribute is HelpAttribute help)
            {
                Console.WriteLine($"Help URL: {help.Url}");
            }
        }
    }
}
```

Output: `Help URL: https://docs.microsoft.com/en-us/dotnet/csharp/`