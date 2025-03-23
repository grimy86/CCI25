# Method Hiding
When a derived class defines a method with the same name as a method in the base class `without using virtual and override`, the derived method hides the base method instead of overriding it. This is called `method hiding`.

Example:
```cs
class Person
{
    public void Greet() 
    {
        Console.WriteLine("Hi! I am a person.");
    }
}

class Employee : Person
{
    public void Greet() 
    {
        Console.WriteLine("Hello! I am an employee.");
    }
}

class Program
{
    static void Main()
    {
        Person p1 = new Person();
        p1.Greet(); // Calls Person.Greet()

        Person p2 = new Employee();
        p2.Greet(); // Still calls Person.Greet() (not Employee.Greet())

        Employee emp = new Employee();
        emp.Greet(); // Calls Employee.Greet()
    }
}
```

Output:
```
Hi! I am a person.
Hi! I am a person.
Hello! I am an employee.
```

- Even though Employee has its own Greet() method, `Person p2 = new Employee();` still calls `Person.Greet() instead of Employee.Greet()`.
- This happens `because Greet() is not virtual`, so method resolution is based on the type of reference (Person or Employee) rather than the actual object type.

## Intended method hiding using the `new` Keyword
If we intend to hide the base class method, we should use the `new` keyword. This tells the compiler that we are aware of the hiding behavior and prevents warnings.

Example:
```cs
class Person
{
    public void Greet()
    {
        Console.WriteLine("I am a person!");
    }
}

class Employee : Person
{
    public new void Greet() // Hides the base class method
    {
        Console.WriteLine("I am the Manager!");
    }
}

class Program
{
    static void Main()
    {
        Person p1 = new Person();
        p1.Greet(); // Calls Person.Greet()

        Person p2 = new Employee();
        p2.Greet(); // Still calls Person.Greet() because p2 is of type Person

        Employee emp = new Employee();
        emp.Greet(); // Calls Employee.Greet()
    }
}
```

Output:
```
I am a person!
I am a person!
I am the Manager!
```

- The new keyword explicitly tells the compiler that we are hiding the base method (removes warnings).
- Even with new, the base method is still called when using a base class reference (`Person p2 = new Employee();`).
- A derived class reference (`Employee emp = new Employee();`) calls the derived class method.