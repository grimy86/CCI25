# Functions / Methods
A `function` is a block of code that will run whenever we call it, think of our `Main` function.

Functions that are part of a class are called `methods`. In C#, every code file (`.cs`) must have its code inside a `class`. Because of this, every function in C# belongs to a class and is, therefore, a method.

We usually use methods to make our code easier to read, organized, reusable, etc.

## Working with methods
Methods in C# have several components:
- A return `type` – Specifies what type of value the method returns.
- A name (`identifier`) – The method’s unique name.
- A list of `parameters` (optional) – Inputs that the caller can provide.
- A visibility level (access modifier) – Defines where the method can be accessed (e.g., public, private). (Not important for now.)

`Void Methods`: Methods with a void return type do not return a value, they simply execute their code.

```cs
int Add(int a, int b) 
{
    return a + b; // Returns the sum of a and b as an integer type
}
```

```cs
void PrintLine(string sentence) 
{
    Console.WriteLine(sentence); // Prints the provided sentence to the console
}
```

```cs
void PrintLine() 
{
    Console.WriteLine("I got passed 0 arguments."); // No parameters
}
```

`Calling` these functions would look something like this:
```cs
// When we call functions we pass arguments for the asked parameters.
int a = Add(5, 5);
PrintLine("int a is equal to: " + a);
PrintLine();
```