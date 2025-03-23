# Delegates
A delegate is like a `function pointer in C or C++`, meaning it can store `references to methods` and call them dynamically.

There are three steps involved while working with delegates:
1. Declare a delegate type (defines the method signature).
2. Assign a method to the delegate.
3. Call the delegate just like a method.

```cs
// 1. Declare a delegate
public delegate void MyDelegate(string msg);

// 2. Create a target method matching the delegate signature
static void MethodA(string message) //Notice how the function parameters match the delegate signature.
{
    
    Console.WriteLine(message);
}

// 3. Assign the method to the delegate and invoke it
//Instantiation & referencing
MyDelegate del = new MyDelegate(MethodA);
// or 
MyDelegate del = MethodA; 
// or set lambda expression 
MyDelegate del = (string msg) =>  Console.WriteLine(msg);

//Invocation
del.Invoke("Hello World!");
// or 
del("Hello World!");
```
![delegates](/Programming_Foundations/CSharp/Images/Delegates.png)

## Passing delegates
You can even pass a delegate as an argument to another method.

```cs
static void InvokeDelegate(MyDelegate del) // MyDelegate type parameter
    {
        del("Hello World");
    }
```

## Multicast Delegate
The delegate can `point to multiple methods`. A delegate that points multiple methods is called a multicast delegate.

This is done by adding functions to an invocation list using operators:
- `+`, add a function to the list
- `+=`, add a function to the list
- `-`, remove a function from the list
- `-=`, remove a function from the list

```cs
class Program
{
    static void Main(string[] args)
    {
        MyDelegate del1 = ClassA.MethodA;
        MyDelegate del2 = ClassB.MethodB;
        MyDelegate del = del1 + del2; // combines del1 + del2
        MyDelegate del3 = (string msg) => Console.WriteLine("Called lambda expression: " + msg);
        del += del3; // combines del1 + del2 + del3
        del = del - del2; // removes del2
        del -= del1 // removes del1
    }
}
```

## Generic delegates
A generic delegate can be defined the same way as a delegate but using generic type parameters or return type. The generic type must be specified when you set a target method.

```cs
public delegate T add<T>(T param1, T param2); // generic delegate
```

## Built-in generic delegates: `Func`, `Action` And `Predicate`
Whenever we use delegates, we have to declare a delegate, initialize it, and then call a method with a reference variable.

- `Func` delegate takes zero or more parameters, `returns a value`.
- `Action` takes zero or more parameters, is `void`.
- `Predicate`  takes zero or more parameters, returns `bool`.

```cs
Func<int, int, int> add = (a, b) => a + b;  // Takes two ints, returns an int
Action<string> print = message => Console.WriteLine(message);  // Takes a string, returns void
Predicate<int> isEven = num => num % 2 == 0;  // Takes an int, returns bool
```

## Anonymous methods
An anonymous method is a method without a name. Instead of defining a separate named method, you can `define an inline method directly inside a delegate`.

```cs
public delegate void Greet(string name);

static void Main()
{
    Greet greet = delegate (string name) 
    { 
        Console.WriteLine("Hello, " + name); 
    };

    greet("Alice");  // Output: Hello, Alice
}
```

Limitations of anonymous methods:
- No reusability
- No jump statements like goto, break or continue.
- No ref or out parameters of an outer method.
- No access unsafe code.
- Cannot be used on the left side of the is operator.

## Use cases of delegates
- Event Handling (e.g., Button Click in UI apps).
- Callbacks (executing a method after another completes).
- LINQ & Functional Programming (higher-order functions).
- Strategy Pattern & Custom Logic Switching.