# Partials
Partials allows us to split up "definitions" into multiple files. When compiled, the compiler combines all parts into a single class file.

## Partial classes
- When working on large classes, allowing multiple developers to work on different parts.
- When using auto-generated code (e.g., UI frameworks like WPF, WinForms, Blazor).
- To organize related methods in separate files while keeping them under the same class.

**Person.cs:**
```cs
public partial class Person
{
    public string FirstName { get; set; }
    public string LastName { get; set; }

    public void PrintFullName()
    {
        Console.WriteLine($"{FirstName} {LastName}");
    }
}
```

**Person_2.cs:**
```cs
public partial class Person
{
    public int Age { get; set; }

    public void PrintAge()
    {
        Console.WriteLine($"Age: {Age}");
    }
}
```

## Partial methods
A partial method is a method that is `declared` (much like `forward declarations in C++`) in one part of a partial class and optionally implemented in another part. If no implementation is provided, the compiler removes the declaration.

- Must be in a partial class
- Must return void (cannot return a value)
- Cannot have access modifiers (public, private, etc.)
- Cannot be virtual, abstract, or override
- Must be partial in both declaration and implementation

**User_Declaration.cs:**
```cs
public partial class User
{
    public string Name { get; set; }

    partial void OnNameChanged(); // Partial method declaration

    public void ChangeName(string newName)
    {
        Name = newName;
        OnNameChanged(); // Calls the method if implemented
    }
}
```

**User_Definition.cs:**
```cs
public partial class User
{
    partial void OnNameChanged()
    {
        Console.WriteLine($"Name changed to: {Name}");
    }
}
```