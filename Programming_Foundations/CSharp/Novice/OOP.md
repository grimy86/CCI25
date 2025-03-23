# Object-Oriented Programming (OOP)
This is most likely the most confusing and important part of C#. To clear up any confusion about OOP, think of it like this:

> "An object is an instance of a user-defined data type that also holds the procedures (methods) that perform on it's data."


Before diving deeper into OOP, let's compare it to the opposite approach: `Procedural Programming`.

| Procedural Programming | Object-Oriented Programming |
|-|-|
| Focuses on functions (procedures) that operate on data. | Focuses on objects, which contain both data and behavior. |
| Data is separate from logic. | Data and logic are bundled together in objects. |
| Example: C, older programming styles. | Example: C#, Java, Python (OOP languages). |
| Less structured for large projects. | Easier to scale and maintain. |

**Example of procedural programming:**
```C
string name = "Alice";
void SayHello(string name)
{
    Console.WriteLine("Hello, " + name);
}

SayHello(name); // Function call
```

**Example of OOP:**
```cs
class Person
{
    public string Name;

    public void SayHello()
    {
        Console.WriteLine("Hello, " + Name);
    }
}

// Creating an instance (object)
Person person = new Person(); // Creating the 
person.Name = "Alice";
person.SayHello(); // Method call
```

## Why OOP?
- Faster and easier to execute
- Clear structure
- Prevents DRY "Don't Repeat Yourself"
- Easier to maintain, scale, modify and debug
- Provides modularity by making the code re-useable

## The four pillars of OOP
### 1. **Encapsulation**: keep data safe inside of objects.
`Restricting direct access` to some of the object's data. This `prevents accidental modification` and `enforces controlled access`.

```cs
class Person
{
    private int age; // Private field, cannot be accessed directly

    public int Age // Public property with validation
    {
        get { return age; }
        set
        {
            if (value >= 0)
                age = value;
            else
                Console.WriteLine("Age cannot be negative!");
        }
    }
}
```

As you can see abstraction is mostly done by using `properties`:
```cs
private string name; // field

  public string Name   // property
  {
    get { return name; }   // get method
    set { name = value; }  // set method
  }
```

### 2. **Abstraction**: hide unnecessary details
Hiding the unnecessary details from the user and `exposing only what's essential`.

```cs
class Car
{
    public void Start() // User doesn't worry about internal details
    {
        StartIgnition(); //hidden
        InjectFuel(); //hidden
        StartEngine(); //hidden

        Console.WriteLine("Car started!");
    }

    private void StartIgnition()
    {
        Debug.WriteLine("Ignition started...");
    }

    private void InjectFuel()
    {
        Debug.WriteLine("Fuel injected...");
    }

    private void StartEngine()
    {
        Debug.WriteLine("Engine started...");
    }
}
```

As you can see abstraction is mostly done by using `access modifiers`:
| Modifier | Description |
|-|-|
| `public` | The code is accessible for all classes. |
| `private` | The code is only accessible within the same class. |
| `protected` | The code is accessible within the same class, or in a class that is inherited from that class. |
| `internal` | The code is only accessible within its own assembly, but not from another assembly. |

There's also two combinations: `protected internal` and `private protected`.

### 3. **Inheritance**: reuse and extend existing code
Allows a class (`child`) to `inherit attributes and behavior` from another class (`parent`), reducing code duplication.

```cs
class Vehicle // Base class
{
    public void Drive() { Console.WriteLine("Vehicle is driving."); }
}

class Car : Vehicle { } // Inherits from Vehicle
class Truck : Vehicle { }

Car myCar = new Car();
Truck myTruck = new Truck();
myCar.Drive();   // Outputs: "Vehicle is driving."
myTruck.Drive(); // Outputs: "Vehicle is driving."
```

### 4. **Polymorphism**: one interface, many implementations
The same method can have different behaviors depending on the object using it.

```cs
class Animal // Parent or base class
{
    public virtual void MakeSound() { Console.WriteLine("Some sound..."); }
}

class Bird : Animal // Child or derived class
{
    public override void MakeSound() { Console.WriteLine("Chirp Chirp!"); }
}

class Dog : Animal // Child or derived class
{
    public override void MakeSound() { Console.WriteLine("Woof Woof!"); }
}

Animal myBird = new Bird();
Animal myDog = new Dog();
myBird.MakeSound(); // Outputs: "Chirp Chirp!"
myDog.MakeSound();  // Outputs: "Woof Woof!"
```

Another example of polymorphism are interfaces which are completely `abstract classes` that only contain method `signatures`. It's more of a contract showing what the object should be about, how you implement them is up to you.

Interfaces should always start with I, it's an unspoken rule.

```cs
interface IAnimal 
{
  void animalSound(); // interface method (does not have a body)
}

// Pig "implements" the IAnimal interface
class Pig : IAnimal 
{
  public void animalSound() 
  {
    // The body of animalSound() is provided here
    Console.WriteLine("The pig says: wee wee");
  }
}

class Program 
{
  static void Main(string[] args) 
  {
    IAnimal somePig = new Pig();  // Create a Pig object using the interface
    Pig myPig = new Pig();  // Create a Pig object
    myPig.animalSound();
  }
}
```