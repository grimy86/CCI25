# The SOLID principles
SOLID is a set of five principles introduced by Robert C. Martin to help create maintainable, scalable, and testable object-oriented software.

These are principles, not design patterns. Principles guide software design, while patterns provide reusable solutions.

- Single Responsibility Principle (SRP): Each class should focus on a single task or responsibility.
- Open/Closed Principle (OCP): You should extend functionality using interfaces, not modifying existing code.
- Liskov Substitution Principle (LSP): Subclasses should follow the behavior of their base classes.
- Interface Segregation Principle (ISP): Interfaces should focus on a single task or responsibility, avoiding class dependency.
- Dependency Inversion Principle (DIP): Depend on interfaces instead of concrete classes.

## Single Responsibility Principle (SRP)
A class should have only one reason to change.

- Each class should focus on a single task or responsibility.
- If a class has multiple responsibilities, split it into smaller classes.

```cs
// ❌ Violating SRP: Handles both data and file operations
public class Report
{
    public string Content { get; set; }
    public void SaveToFile(string path) { /* Saves content to a file */ }
}

// ✔ Following SRP: Separate responsibilities into two classes
public class Report
{
    public string Content { get; set; }
}

public class ReportSaver
{
    public void SaveToFile(Report report, string path) { /* Saves content to a file */ }
}
```

## Open/Closed Principle (OCP)
Software should be open for extension, but closed for modification.

- You should extend functionality without modifying existing code.
- Use inheritance or interfaces to add new behaviors.

```cs
// ❌ Violating OCP: Modifying the existing class to add new behavior
public class PaymentProcessor
{
    public void ProcessPayment(string type)
    {
        if (type == "CreditCard") { /* Process credit card */ }
        else if (type == "PayPal") { /* Process PayPal */ }
    }
}

// ✔ Following OCP: Using abstraction for extensibility
public interface IPaymentMethod { void Pay(); }

public class CreditCardPayment : IPaymentMethod { public void Pay() { /* Credit card logic */ } }
public class PayPalPayment : IPaymentMethod { public void Pay() { /* PayPal logic */ } }

public class PaymentProcessor
{
    public void ProcessPayment(IPaymentMethod paymentMethod) { paymentMethod.Pay(); }
}
```

## Liskov Substitution Principle (LSP)
A subclass should be able to replace its superclass without breaking the program.

- Subclasses should follow the behavior of their base classes.
- Avoid breaking expected behavior when using inheritance.

```cs
// ❌ Violating LSP: Square incorrectly inherits from Rectangle
public class Rectangle
{
    public virtual double Width { get; set; }
    public virtual double Height { get; set; }

    public double Area() => Width * Height;
}

public class Square : Rectangle
{
    public override double Width
    {
        set { base.Width = base.Height = value; } // Unexpected side effect
    }

    public override double Height
    {
        set { base.Width = base.Height = value; } // Unexpected side effect
    }
}

// ✔ Following LSP: Separate Square and Rectangle using a common interface
public interface IShape
{
    double Area();
}

public class RectangleProper : IShape
{
    public double Width { get; set; }
    public double Height { get; set; }
    
    public double Area() => Width * Height;
}

public class SquareProper : IShape
{
    public double Side { get; set; }
    
    public double Area() => Side * Side;
}
```

## Interface Segregation Principle (ISP)
Clients should not be forced to depend on methods they do not use.

- Large interfaces should be split into smaller, more specific ones.
- Classes should only implement the methods they need.

```cs
// ❌ Violating ISP: A printer interface forces all classes to implement every method
public interface IPrinter
{
    void Print();
    void Scan();
    void Fax();
}

public class BasicPrinter : IPrinter
{
    public void Print() { /* Works */ }
    public void Scan() { throw new NotImplementedException(); } // ❌ Unnecessary
    public void Fax() { throw new NotImplementedException(); }  // ❌ Unnecessary
}

// ✔ Following ISP: Split into multiple interfaces
public interface IPrinter { void Print(); }
public interface IScanner { void Scan(); }
public interface IFax { void Fax(); }

public class BasicPrinter : IPrinter { public void Print() { /* Works */ } }
```

## Dependency Inversion Principle (DIP)
High-level modules should not depend on low-level modules. Both should depend on abstractions.

- Depend on interfaces instead of concrete classes.
- Helps with decoupling and makes the code more testable.

```cs
// ❌ Violating DIP: The EmailService directly depends on a concrete class
public class EmailService
{
    private readonly SmtpClient _smtpClient = new SmtpClient(); // Tight coupling
    public void SendEmail() { _smtpClient.Send(); }
}

// ✔ Following DIP: Depend on an abstraction (interface)
public interface IEmailSender { void Send(); }

public class SmtpEmailSender : IEmailSender { public void Send() { /* Email logic */ } }

public class EmailService
{
    private readonly IEmailSender _emailSender;
    public EmailService(IEmailSender emailSender) { _emailSender = emailSender; }
    public void SendEmail() { _emailSender.Send(); }
}
```