# Lambda
A lambda expression is just a `shortcut for writing small functions` without naming them.

Since lambda expressions are the opposite of named methods they're also called `anonymous functions`, often confused with anonymous delegate methods.

Instead of writing this:
```cs
int MultiplyByFive(int num)
{
    return num * 5;
}
```

You can write:
```cs
num => num * 5;
```

This means:
1. Take an input num
2. Multiply it by 5
3. Return the result

The lambda expression `does not execute on its own`. Instead, we use it inside other methods, variables or delegates.

```cs
Func<int, int> multiply = num => num * 5;
Console.WriteLine(multiply(3));  // Output: 15
// or
Action<string> greet = name => Console.WriteLine("Hello, " + name);
greet("Alice");  // Output: Hello, Alice
```

## Two Types of Lambdas
**Expression Lambda:**
Expression lambda contains a single expression in the lambda body.
```cs
(num) => num * 5;
```

**Statement Lambda:**
Statement lambda encloses one or more statements in the lambda body. We use curly braces `{ }` to wrap the statements.
```cs
(num) => 
{
    int result = num * 5;
    return result;
};
```

**Key Differences:**
| Feature | Expression Lambda | Statement Lambda |
|-|-|-|
| Syntax Complexity | Simple (single expression) | Supports multiple statements |
| Implicit Return | Yes (return type inferred) | No (must use explicit `return`) |
| Suitable for | Short, single-line logic | Complex logic requiring multiple lines   |
| Readability | High for simple computations | Better for structured, complex behavior |

## Use cases
1. Writing Easy and Simple Delegate Code.
2. Performing quick and simple calculations.
3. We can pass a lambda expression as a parameter in a method call.

**Syntax recap:** (parameterList) => lambda body
- `parameterList` - list of input parameters
- `=>` - a lambda operator
- `lambda body` - can be an expression or statement