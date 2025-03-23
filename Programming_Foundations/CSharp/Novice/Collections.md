# Data collections
In C#, data collections are used to store and manage `multiple values in a single structure`. Each type of collection serves a unique purpose, depending on how you want to manage, access, and modify the data.

## Summary

| Collection | Description | When to Use |
|-|-|-|
| `Array` | Fixed-size, indexed collection | When the size is known and unchanging |
| `List` | Dynamic-sized, indexed collection | When the size may change dynamically |
| `Dictionary` | Key-value pairs, fast lookup | When you need fast access to values by unique keys |
| `Enum` | Named constants | When you have a set of related constant values |
| `Queue` | FIFO (First In First Out) | When you need a queue-like structure |
| `Stack` | LIFO (Last In First Out) | When you need a stack-like structure |
| `HashSet` | Unordered, unique elements | When duplicates should be avoided |
| `SortedList` | Key-value pairs, sorted by key | When you need a sorted key-value collection |
## Arrays
An array is a fixed-size collection that holds elements of the same type.

Characteristics:
- Fixed size – once defined, the size cannot change.
- Indexed – elements are accessed using an index (0-based).
- Homogeneous – all elements must be of the same type.

```cs
int[] numbers = new int[3]; // Creates an array of 3 integers
numbers[0] = 1;
numbers[1] = 2;
numbers[2] = 3;

Console.WriteLine(numbers[0]); // Output: 1
```

## Enums
An enum (short for enumeration) is a special "class" that represents a set of named constants.

Characteristics:
- Named values – enums allow you to represent a set of related constants with meaningful names.
- Underlying type – by default, the underlying type is int, but you can specify a different base type.
- Readable code – makes code more readable and maintainable by replacing magic numbers with names.

```cs
enum Days { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday }

Days today = Days.Monday;  
Console.WriteLine(today); // Output: Monday

int dayNumber = (int)Days.Wednesday;  
Console.WriteLine(dayNumber); // Output: 3
```

## Lists
A list is a dynamic collection that can grow or shrink in size. It is part of the `System.Collections.Generic` namespace.

Characteristics:
- Flexible size – the list can change size as needed.
- Indexed – elements are accessed using an index (0-based).
- Homogeneous – all elements must be of the same type.
- Better performance than arrays when dealing with resizing.

```cs
List<int> numbers = new List<int>();  
numbers.Add(1);  
numbers.Add(2);  
numbers.Add(3);  

Console.WriteLine(numbers[0]); // Output: 1
numbers.Remove(2); // Removes 2 from the list
```

## Dictionaries (Dicts)
A dictionary is a collection of key-value pairs, where each key is unique. It is part of the `System.Collections.Generic` namespace.

Characteristics:
- Key-value pairs – each element is a pair of a key and its associated value.
- Fast lookups – keys are hashed for quick access.
- No fixed size – similar to lists, dictionaries can grow or shrink.

```cs
Dictionary<string, int> phoneBook = new Dictionary<string, int>();  
phoneBook.Add("Alice", 123456789);
phoneBook.Add("Bob", 987654321);  

Console.WriteLine(phoneBook["Alice"]); // Output: 123456789
```

## Queues
A queue is a first-in, first-out (FIFO) collection. Elements are added at the end and removed from the front.

Characteristics:
- FIFO – the first element added is the first one to be removed.
- Often used in scenarios like task scheduling or buffering.

```cs
Queue<string> queue = new Queue<string>();  
queue.Enqueue("Task 1");  
queue.Enqueue("Task 2");  

Console.WriteLine(queue.Dequeue()); // Output: Task 1
```

## Stacks
A stack is a last-in, first-out (LIFO) collection. Elements are added and removed from the top.

Characteristics:
- LIFO – the last element added is the first one to be removed.
- Often used in scenarios like undo functionality or call stack tracking.

```cs
Stack<string> stack = new Stack<string>();  
stack.Push("Task 1");  
stack.Push("Task 2");

Console.WriteLine(stack.Pop()); // Output: Task 2
```

## HashSet
A HashSet is an unordered collection that only allows unique elements.

Characteristics:
- No duplicates – automatically removes duplicates when adding elements.
- Unordered – elements are stored without any specific order.

```cs
HashSet<int> uniqueNumbers = new HashSet<int>();  
uniqueNumbers.Add(1);  
uniqueNumbers.Add(2);  
uniqueNumbers.Add(2); // Duplicate, won't be added

Console.WriteLine(uniqueNumbers.Count); // Output: 2
```

## SortedList
A SortedList is a collection of key-value pairs that maintains the keys in sorted order.

Characteristics:
- Sorted by key – the keys are sorted in ascending order.
- Uses a binary search for efficient lookup.

```cs
SortedList<int, string> sortedList = new SortedList<int, string>();  
sortedList.Add(3, "Three");  
sortedList.Add(1, "One");  
sortedList.Add(2, "Two");

Console.WriteLine(sortedList[1]); // Output: One
```