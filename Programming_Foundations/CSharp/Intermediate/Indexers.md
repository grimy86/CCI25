# Indexers
An indexer is a special kind of property that allows you to access an object as if it were an array, even though it's a custom class or struct. It enables the use of the square bracket `[]` syntax for getting or setting values within an object.


## What does it do?
An indexer allows you to treat your class like an array or collection. It lets you get or set values from a collection inside the object using an index, just like you would with an array.

Recap:
- Indexers allow you to use the [] syntax for accessing elements inside a class or struct.
- They work like properties, but with an index parameter.
- Indexers can be defined to access any internal collection like arrays, lists, or dictionaries inside the class.

```cs
public class MyClass
{
    private int[] numbers = { 1, 2, 3, 4, 5 };

    public int this[int index]  // Indexer definition
    {
        get
        {
            return numbers[index];  // Return value at the given index
        }
        set
        {
            numbers[index] = value;  // Set value at the given index
        }
    }
}
```
