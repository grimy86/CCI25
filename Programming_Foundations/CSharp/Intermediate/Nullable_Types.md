# Nullable value types
Some value types (like int, float, bool, etc.) cannot have a `null` value by default. However, sometimes you might want to represent the absence of a value, especially when working with databases or optional fields.

To allow value types to hold null, C# provides nullable value types using `?`:
```cs
int? age = null;  // Nullable int
double? price = 99.99;  // Nullable double
bool? isAvailable = null;  // Nullable bool
```

## How it works internally
A nullable value type (`T?`) is actually a struct called `Nullable<T>`. This struct has two properties:

`HasValue` – Returns true if the variable has a value.
`Value` – Retrieves the actual value if HasValue is true.

```cs
[Serializable]
public struct Nullable<T> where T : struct
{        
    public bool HasValue { get; }
      
    public T Value { get; }
        
    // other implementation
}
```
Think about this: `int? i = null;` is the same as `nullable<int> i = null;`.

## Null-Coalescing Operator (`??`)
Instead of checking HasValue, you can provide a default value using `??`:

```cs
int? count = null;
int result = count ?? 0;  // If count is null, assign 0
Console.WriteLine(result); // Output: 0
```

## Null-Conditional Operator (`?.`)
You can also use null-conditional access (`?.`) to safely handle nullable types:

```cs
int? length = null;
Console.WriteLine(length?.ToString()); // Doesn't throw error, just prints empty
```

##  Explicitly Converting Nullable to Non-Nullable
If you directly assign a nullable type to a non-nullable type, it will cause a compilation error unless you explicitly handle null cases.
```cs
int? nullableNumber = null;
int nonNullableNumber = nullableNumber ?? -1; // Assign -1 if null
```
