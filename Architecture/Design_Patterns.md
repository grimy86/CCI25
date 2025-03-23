# Design patterns
A design pattern is a reusable solution to a common programming problem. It helps make your code more structured, maintainable, and scalable.

- Avoid rewriting code for the same problems.
- Improve code readability and reusability.
- Make your code more flexible to changes.

**Types of design patterns:**
There are three main types of design patterns:
- Creational Patterns: How objects are created.
- Structural Patterns: How objects are structured & connected.
- Behavioral Patterns: How objects interact & communicate.

## Creational design patterns (control object creation)
These patterns provide better ways to control object creation, in a flexible way.

| Pattern |	What it Does | Example Use Case |
|-|-|-|
| Singleton | Ensures only one instance of a class exists. | Database connections, Logging |
| Factory Method | A method creates objects instead of new keyword. | Creating different payment methods (CreditCard, PayPal) |
| Abstract Factory | A factory that creates factories of related objects. | UI toolkit for Windows & Mac |
| Builder | Builds complex objects step by step. | Creating a Burger with different toppings |
| Prototype | Copies an existing object instead of creating a new one. | Copying a user profile |

## Structural Design Patterns (control class relationships)
These patterns deal with how objects are connected and structured.

| Pattern |	What it Does | Example Use Case |
|-|-|-|
| Adapter | Converts one interface into another. | Using an old API in a new system |
| Bridge | Separates abstraction from implementation. | UI themes with different rendering engines |
| Composite | Treats a group of objects like a single object. | Folder structure in Windows Explorer |
| Decorator | Adds extra behavior to objects dynamically. | Adding extra features to a car (e.g., Sunroof) |
| Facade | Provides a simple interface to a complex system. | A single API call to simplify multiple services |
| Flyweight | Uses shared objects to save memory. | Text editors where characters share styles |
| Proxy | Controls access to an object. | Security check before accessing an object |

## Behavioral Design Patterns (control object communication)
These patterns define how objects interact with each other.

| Pattern |	What it Does | Example Use Case |
|-|-|-|
| Chain of Responsibility | Passes a request through a chain of handlers. | Support ticket escalation (Level 1 → Level 2 → Manager) |
| Command | Encapsulates a request as an object. | Undo/Redo in text editors |
| Interpreter | Defines a grammar for interpreting language. | Math expression evaluator |
| Iterator | Provides a way to loop through a collection without exposing details. | Custom collections in C# |
| Mediator | Controls communication between multiple objects. | Chatroom where users communicate via a server |
| Memento | Saves an object's state for undo functionality. | Text editor undo feature |
| Observer | Notifies multiple objects when one object changes. | Stock price alerts |
| State | Changes an object's behavior based on state. | Traffic light system (Red, Yellow, Green) |
| Strategy | Allows switching between different algorithms. | Sorting (BubbleSort, QuickSort) |
| Template | Method	Defines the skeleton of an algorithm in a base class. | Cooking recipes |
| Visitor | Adds extra functionality without modifying existing classes. | Applying a discount to different products |