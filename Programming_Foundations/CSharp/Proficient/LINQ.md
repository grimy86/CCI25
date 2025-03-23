# Language Integrated Query (LINQ)
A feature in C# that lets you `query collections` (arrays, lists, databases, XML, etc.) using a simple and readable syntax.

Basic LINQ query:
```cs
int[] numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

// Find even numbers using LINQ
var evens = from num in numbers 
            where num % 2 == 0 
            select num;

foreach (var num in evens)
{
    Console.WriteLine(num);
}
```

Same as:
```cs
int[] numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

var evens = numbers.Where(num => num % 2 == 0);

foreach (var num in evens)
{
    Console.WriteLine(num);
}
```

Example with objects:
```cs
class Person 
{
    public string Name { get; set; }
    public int Age { get; set; }
}

var people = new List<Person>
{
    new Person { Name = "Alice", Age = 25 },
    new Person { Name = "Bob", Age = 30 },
    new Person { Name = "Charlie", Age = 20 }
};

// Find people older than 25, ordered by age
var result = people.Where(p => p.Age > 25)
                   .OrderBy(p => p.Age)
                   .Select(p => p.Name);

foreach (var name in result)
{
    Console.WriteLine(name);
}
```

## LINQ Methods (Method Syntax)
LINQ has built-in extension methods to make queries shorter:

| Method | Description | Example |
|-|-|-|
| Where | Filters data | `list.Where(x => x > 5)` |
| Select | Transforms each element | `list.Select(x => x * 2)` |
| OrderBy | Sorts in ascending order | `list.OrderBy(x => x)` |
| OrderByDescending | Sorts in descending order | `list.OrderByDescending(x => x)` |
| First /FirstOrDefault | Gets the first element | `list.FirstOrDefault()` |
| Last /LastOrDefault | Gets the last element | `list.LastOrDefault()` |
| Count | Counts elements | `list.Count()` |
| Sum | Adds up all values | `list.Sum()` |