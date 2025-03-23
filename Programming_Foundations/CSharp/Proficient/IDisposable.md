# The `IDisposable` interface
`IDisposable` is an interface that allows you to `release unmanaged resources` like files, database connections, network sockets, etc., when an object is no longer needed.

The C# Garbage Collector (`GC`) automatically cleans up managed resources (like objects in memory). However, GC does NOT clean up unmanaged resources (like file handles, database connections, sockets, etc.).

IDisposable ensures proper cleanup by providing a Dispose() method. Ideally this avoids any memory leaks of sorts.

## How to implement `IDisposable`
```cs
class MyResource : IDisposable
{
    private bool _disposed = false; // Track if disposed

    public void UseResource()
    {
        if (_disposed) throw new ObjectDisposedException(nameof(MyResource));
        Console.WriteLine("Using resource...");
    }

    public void Dispose()
    {
        if (!_disposed)
        {
            Console.WriteLine("Releasing resource...");
            _disposed = true;
        }
    }
}
```

For a real example take a look at my [dvConnection class (ADO.NET SqlConnection wrapper)](/Programming_Foundations/CSharp/Proficient/IDisposable.cs).

**Using using Statement (Best Practice):**
The using statement automatically calls `Dispose()`, even if an exception occurs. This is safer because we can't forget to call `Dispose()`.
```cs
using (MyResource resource = new MyResource())
{
    resource.UseResource();
}  // Dispose() is called automatically here
```

**Using Dispose() Manually:**
```cs
MyResource resource = new MyResource();
resource.UseResource();
resource.Dispose();  // Manually release the resource
```
