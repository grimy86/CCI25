# Dependency Injection (DI)
Dependency Injection is a technique that helps us write flexible, maintainable, and testable code by `providing objects (dependencies) from outside a class instead of creating them inside the class`. This `reduces tight coupling` between components, making it easier to change implementations without modifying too much code.

Not to be confused with `WPF's dependency properties`.

Instead of a class creating its own dependencies, they are "injected" from the outside. This makes it easy to replace components when needed, for example, using a different database provider or mocking a service for testing.

Benefits:
- Loose Coupling – Classes depend on abstractions (interfaces) instead of concrete implementations.
- Better Testability – Mock dependencies for unit tests instead of relying on actual implementations.
- Easier Maintenance – Change implementations without modifying dependent classes.
- Reusability – Components can be used in different applications without modification.

## Constructor Injection
Dependencies are provided through the class constructor.

```cs
public interface IMessageService
{
    void SendMessage(string message);
}

public class EmailService : IMessageService
{
    public void SendMessage(string message)
    {
        Console.WriteLine($"Email sent: {message}");
    }
}

public class Notification
{
    private readonly IMessageService _messageService;

    public Notification(IMessageService messageService)
    {
        _messageService = messageService;
    }

    public void Notify(string message)
    {
        _messageService.SendMessage(message);
    }
}

// Usage:
public class Program
{
    static void Main(string[] args)
    {
        IMessageService emailService = new EmailService();
        Notification notification = new Notification(emailService);
        notification.Notify("Hello via Email!");
    }
}
```

## Property Injection
Dependencies are set via public properties instead of the constructor.

```cs
public class Notification
{
    public IMessageService MessageService { get; set; }

    public void Notify(string message)
    {
        MessageService?.SendMessage(message);
    }
}

// Usage:
public class Program
{
    static void Main(string[] args)
    {
        var notification = new Notification();
        notification.MessageService = new EmailService();
        notification.Notify("Hello via Email!");
    }
}
```

## Method Injection
Dependencies are passed as method parameters.

```cs
public class Notification
{
    public void Notify(string message, IMessageService messageService)
    {
        messageService.SendMessage(message);
    }
}

// Usage:
public class Program
{
    static void Main(string[] args)
    {
        Notification notification = new Notification();
        notification.Notify("Hello via Email!", new EmailService());
    }
}
```

## Using an IoC Container
Manually injecting dependencies works, but in real projects, we use `IoC (Inversion of Control)` containers like the built-in .NET DI container.

```cs
public void ConfigureServices(IServiceCollection services)
{
    services.AddScoped<IMessageService, EmailService>();
    services.AddScoped<Notification>();
}
```

## WPF Dependency Properties (DP)
A Dependency Property is an advanced property system used in Windows Presentation Foundation (WPF) that `allows properties to be automatically updated` based on styles, data bindings, animations, and inheritance. It is different from regular C# properties because it `stores values in a property store` rather than in a private field.

Dependency properties are useful because they:
- Enable data binding (e.g., binding UI elements to data)
- Support styles and triggers (change properties dynamically)
- Work with animations (WPF animations can modify dependency properties)
- Allow default values and value inheritance (values can be inherited from parent controls)

A normal property does not support these features, but a dependency property does.

### Creating a Dependency Property
A dependency property must be registered in a class that inherits from `DependencyObject`.

- The property is registered using DependencyProperty.Register.
- We store the property in a static DependencyProperty field.
- We wrap it in a normal C# property (MyText) that uses GetValue and SetValue.

Example:
```cs
using System.Windows;
using System.Windows.Controls;

public class MyCustomControl : Control
{
    // Registering a Dependency Property
    public static readonly DependencyProperty MyTextProperty =
        DependencyProperty.Register(
            "MyText",                // Name of the property
            typeof(string),          // Data type
            typeof(MyCustomControl), // Class that owns the property
            new PropertyMetadata("Default Value") // Default value
        );

    // CLR Wrapper for Dependency Property
    public string MyText
    {
        get { return (string)GetValue(MyTextProperty); }
        set { SetValue(MyTextProperty, value); }
    }
}
```

### Attached Dependency Properties
An `Attached Property` is a special kind of dependency property that is declared in one class but used by other controls.

A common example is the Grid.Column property:
```xml
<Grid>
    <Button Grid.Column="0">Click</Button>
    <Button Grid.Column="1">Clack</Button>
</Grid>
```

The Grid.Column property does not belong to Button, but the Grid class allows Button to use it.

### Creating an Attached Dependency Property
With this, other elements can use Grid.Column, even though it's defined in the Grid class.

```cs
public class Grid
{
    public static readonly DependencyProperty ColumnProperty =
        DependencyProperty.RegisterAttached(
            "Column", 
            typeof(int), 
            typeof(Grid)
        );

    // Getter
    public static int GetColumn(DependencyObject obj)
    {
        return (int)obj.GetValue(ColumnProperty);
    }

    // Setter
    public static void SetColumn(DependencyObject obj, int value)
    {
        obj.SetValue(ColumnProperty, value);
    }
}
```