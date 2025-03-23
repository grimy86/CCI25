# Generics
Generics allow you to write a class or method that can work with any data type. Much like templates in C++.

```cs
//Define generic class
class DataStore<T> //T is commonly used but this could be anything.
{
    //Define generic field
    public T Data { get; set; }

    //Define generic method
    public void Print<T>(T data)
    {
        Console.WriteLine(data);
    }
}

//Instantiating generic class
DataStore<string> dataStore = new DataStore<string>();

//Call generic method
dataStore.Print<int>(100);
```