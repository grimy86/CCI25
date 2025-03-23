# Pass by reference
The `ref` and `out` keywords are used to `pass arguments by reference` to functions or methods. This means that any `changes made to the parameters inside the function will affect the original values outside the function`. 

While both of them allow you to modify the arguments, there are key differences in how and when they are used.

## ref
Used to indicate that a parameter is passed by reference, and it `must be initialized before being passed` into the method. 

Key Points:
- The parameter must be initialized before it is passed to the method.
- Any changes made to the parameter inside the method will be reflected outside the method.
- It allows for both reading and writing the parameter inside the method.

Example of ref:
```cs
using System;

public class RefExample
{
    public static void ModifyValue(ref int number)
    {
        // Modifying the passed parameter
        number += 10;
    }

    public static void Main()
    {
        int x = 5;
        Console.WriteLine("Before: " + x);  // Output: Before: 5
        
        // Passing x by reference
        ModifyValue(ref x);
        
        Console.WriteLine("After: " + x);  // Output: After: 15
    }
}
```

## out
Similar to ref, but there are a few key differences:
- The parameter `does not need to be initialized before being passed` to the method. It is used primarily when you want the method to `assign a value to the parameter`, and you `don't care about its initial value`. The parameter is `considered uninitialized` until assigned a value inside the method.
- The method must assign a value to the parameter `before it returns`.
- It is used to return multiple values from a method.

```cs
using System;

public class OutExample
{
    public static void Divide(int numerator, int denominator, out int result)
    {
        if (denominator == 0)
        {
            result = 0; // Assigning a value when the denominator is 0
        }
        else
        {
            result = numerator / denominator;
        }
    }

    public static void Main()
    {
        int result;
        
        // Passing the result variable without initializing it
        Divide(10, 2, out result);
        Console.WriteLine("Result: " + result);  // Output: Result: 5
        
        Divide(10, 0, out result);
        Console.WriteLine("Result: " + result);  // Output: Result: 0
    }
}
```