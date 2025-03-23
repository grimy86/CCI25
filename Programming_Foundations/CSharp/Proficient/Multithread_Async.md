# Mulithreading / Asynchronous programming
Normally, C# runs code `line by line` (synchronously). `Multithreading` allows `multiple operations to run at the same time`, improving performance. Think of it like multitasking.

**Understanding Multithreading vs. Async:**
When you run a program.exe, Windows creates a process. A process contains everything needed to run the program. The actual code execution happens inside threads.

`Multithreading`: Uses multiple threads to perform tasks at the same time.
`Asynchronous Programming`: A single thread handles multiple tasks by switching between them instead of waiting.

**Two Ways to Run Code Concurrently:**
- Using `Threads (System.Threading)`
- Using `Tasks (System.Threading.Tasks)` (preferred for modern async code)

## Creating a Thread using `System.Threading`
Each method runs in a separate thread so they execute simultaneously.

```cs
using System;
using System.Threading;

class Program
{
    public static void Main()
    {
        
        Thread mainThread = Thread.CurrentThread; // Getting the current thread
        mainThread.Name = "___MAIN__THREAD__"; // Changing a thread's name

        Thread thread1 = new Thread(CountDown);
        Thread thread2 = new Thread(CountUp);

        thread1.Start(); // Start the first thread
        thread2.Start(); // Start the second thread
        Console.WriteLine(mainThread.Name + " is complete!");
    }

    public static void CountDown()
    {
        for (int i = 10; i >= 0; i--)
            Console.WriteLine($"Counting Down: {i}");
    }

    public static void CountUp()
    {
        for (int i = 0; i <= 10; i++)
            Console.WriteLine($"Counting Up: {i}");
    }
}
```

## Async using `System.Threading.Tasks`
 Using Task is preferred over Thread in modern C#. Task is a modern alternative to threads, it's more efficient and works well with async programming.

```cs
using System;
using System.Threading.Tasks;

class Program
{
    public static async Task Main()
    {
        Task task1 = Task.Run(() => CountDown());
        Task task2 = Task.Run(() => CountUp());

        await Task.WhenAll(task1, task2); // Wait for both tasks to complete
    }

    public static void CountDown()
    {
        for (int i = 10; i >= 0; i--)
            Console.WriteLine($"Counting Down: {i}");
    }

    public static void CountUp()
    {
        for (int i = 0; i <= 10; i++)
            Console.WriteLine($"Counting Up: {i}");
    }
}
```
> [!NOTE]
> Note however that when you're using Tasks, mixing thread-objects within task-objects like: `Thread.Sleep(500);` could cause several issues.