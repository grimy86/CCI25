# Exception handling
Exception handling is a way to manage errors and prevent your program from crashing unexpectedly. Exceptions are events that disrupt the normal flow of execution, and C# offers ways to deal with them safely.

## What is an exception?
An exception is an error that occurs during the execution of a program. It usually indicates that something went wrong, like trying to divide by zero or accessing an element outside an array's bounds.

## Types
All exceptions in C# are derived from the base class: `System.Exception`. There are many different types of exceptions that represent specific errors.

Examples include:
- `ArithmeticException`: Thrown when an arithmetic operation goes wrong, like dividing by zero.
- `FileNotFoundException`: Thrown when a file is not found in the expected location.
- `IndexOutOfRangeException`: Thrown when accessing an array element outside of its valid range.
- `TimeoutException`: Thrown when a specific time limit is exceeded during an operation.

## Throwing exceptions
The `throw` statement is used together with a `System.Exception` derived class type.


```cs
if (age < 18)
  {
    throw new ArithmeticException("Access denied - You must be at least 18 years old.");
  }
```

## Handling exceptions
While throwing exceptions is useful, handling them properly is crucial. You should `never let an exception crash your program unexpectedly` unless absolutely necessary. Always `catch` exceptions and take appropriate action, such as logging the error or showing a user-friendly message.

Use `try-catch` to handle exceptions, the try-catch block, which attempts to execute code and catches any exceptions that occur.

```cs
try
{
    int number = int.Parse("NotANumber"); // This will throw an exception
}
catch (FormatException ex)
{
    Console.WriteLine("Error: " + ex.Message);
}
```

Sometimes, you need to clean up resources (like closing files or releasing memory) regardless of whether an exception was thrown or not. The `finally` block ensures that your code runs in both cases.

```cs
try
{
    Console.WriteLine("Opening file...");
    // Code that may throw an exception
}
catch (Exception ex)
{
    Console.WriteLine("Error: " + ex.Message);
}
finally
{
    Console.WriteLine("Cleanup: Closing file...");
}
```

## Advanced: Creating User-Defined Exceptions
1. Your class has to inherit from System.Exception
2. Make sure the class is serializable, add the [Serializable] attribute
3. Provide common exception constructors
```cs
[Serializable] // Ensures that your custom exception can be serialized.
public class MyException : Exception
{
    // Default constructor
    public MyException () {}

    // Constructor with a message
    public MyException (string message) 
        : base(message) {}

    // Constructor with a message and inner exception
    public MyException (string message, Exception innerException)
        : base (message, innerException) {}    
}
```