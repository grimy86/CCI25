# Type conversion and parsing
Conversion is the process of going from one data type to another. This can be done in a couple of different ways:
- `Casting`: convert compatible types (e.g., `int → double`).
- `as` conversion: `safe type conversion` between compatible reference types or nullable value types. It `attempts to cast` an object to a specified type and returns `null if the conversion fails, instead of throwing an exception like a direct cast ((Type)obj)` would.
- Conversion `methods`: hanging between more diverse types, including incompatible types (e.g., `string → int`).
- `Parsing`: exclusively for converting strings into numeric types (`string → int, double, etc.`).

### Casting compatible types
- Implicitly casting (safe or automatic) by the programming language:

    ```cs
    int num = 2147483647;
    long bigNum = num;
    ```

- Explicit (manual) casting by us:

    ```cs
    double x = 1234.7;
    a = (int)x;

    //Derivative
    Giraffe g = new Giraffe();
    Animal a = g; // class Giragge : Animal <- base
    ```

### As conversion
```cs
object obj = someValue;
SomeType variable = obj as SomeType;


object obj = 123;  // Integer
string str = obj as string;

if (str == null)
{
    Console.WriteLine("Casting failed!"); // Output: Casting failed!
}
```

### Conversion methods
- Handles `null` values gracefully (returns 0 instead of an exception).
- Works for different types, including bool, DateTime, etc.
- Use when converting between different types (e.g., string to int, double to bool).

```cs
string strNum = "42";
int num = Convert.ToInt32(strNum); // Converts string to int
```

| Type conversion methods |
|-|
| `ToBoolean` |
| `ToByte` |
| `ToChar` |
| `ToDateTime` |
| `ToDecimal` |
| `ToDouble` |
| `ToInt16` |
| `ToInt32` |
| `ToInt64` |
| `ToSbyte` |
| `ToSingle` |
| `ToString` |
| `ToType` |
| `ToUInt16` |
| `ToUInt32` |
| `ToUInt64` |

### Parsing strings
Using `Parse()`:
```cs
string strNum = "42";
int num = int.Parse(strNum); // Returns an exception if the parse fails.
```

Using `TryParse()` is `safer` because it returns true if parsing succeeds, false otherwise.
```cs
string strNum = "42";
bool success = int.TryParse(strNum, out int num);
```