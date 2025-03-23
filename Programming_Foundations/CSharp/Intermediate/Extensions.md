# Extension Methods
Extension methods allow you to add new methods to existing classes, structs, or interfaces without modifying their original code. This is super useful if you need to add functionality to a class but can't change its definition (like with classes from libraries or the .NET framework).

You can "extend" an existing class by writing a new method outside of the class, and it will behave like it’s part of the original class.

To create an extension method:
- You must define it inside a static class.
- The first parameter of the method must be the type you're extending, and it should be prefixed with the this keyword.

```cs
namespace ExtensionMethods
{
    public static class IntExtensions
     {
        public static bool IsGreaterThan(this int i, int value)
        {
            return i > value;
        }
    }
}

//Use case
int i = 10;
bool result = i.IsGreaterThan(100);
```