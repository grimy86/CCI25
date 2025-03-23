# Pattern matching
`Pattern matching` in C# is a powerful feature that allows you to `check whether an expression conforms to a certain structure or type` and, in some cases, extract values from it. It simplifies complex conditional logic, making the code more readable and expressive.

Benefits:
- Reduces the need for lengthy if-else or switch statements.
- Allows for more readable and declarative code.
- Helps in performing type checks, null checks, and property comparisons concisely.

## Value checks
Used to check if an expression is equal to a specific constant (e.g., null, numbers, or specific values).

```cs
void IsNull(object obj)
{
    if (obj is null)
    {
        throw new ArgumentNullException(nameof(obj));
    }
}
```

## Type checks
Checks if an object is of a certain type and, if so, casts it to that type in a single step. Eliminates the need for separate type checking and casting.

```cs
string IsType(object obj)
{
    if (obj is T someObject)
    {
        return $"{obj} is the right type.";
    }
    else
    {
        return $"{obj} is not the right type.";
    }
}
```

## Property checks
Allows checking whether an object’s properties match specific values. Checks both type and property values in one step.

```cs
string IsSpecificProperty(object obj)
{
    if (obj is object { PropertyNumber: 1, PropertyCharacter: 'A' } specificObject)
    {
        return $"{obj} has number: {obj.PropertyNumber} and character {obj.PropertyCharacter}";
    }
    return string.Empty;
}
```

## `var` pattern checks
Matches any expression and assigns it to a variable. Always matches and stores the value, useful for debugging or intermediate calculations.

```cs
var ReturnDetails(object obj)
{
    if (obj is var someObject)
    {
        return $"obj details: {someObject}";
    }
    return string.Empty;
}
```