# Control flow
Simply said, control flow statements allow us to alter the execution of our programs based on certain conditions.

## If, if-else, else-if & ternary operator
Used to control the execution based on a singular or limited amount of conditions.

```cs
if (condition) 
{
  // block of code to be executed if the condition is True
}
```
```cs
if (condition)
{
  // block of code to be executed if the condition is True
} 
else 
{
  // block of code to be executed if the condition is False
}
```
```cs
if (condition)
{
  // block of code to be executed if condition1 is True
} 
else if (condition2) 
{
  // block of code to be executed if the condition1 is false and condition2 is True
} 
else
{
  // block of code to be executed if the condition1 is false and condition2 is False
}
```

```cs
variable = (condition) ? expressionTrue :  expressionFalse;
```

## Switch
Used to control the execution based on multiple conditions. The expression gets evaluated once and then the code with the matching case gets executed.

```cs
switch(expression) 
{
  case x:
    // code block
    break;
  case y:
    // code block
    break;
  default:
    // code block
    break;
}
```

## While & do-while loop
Used to keep execution certain statements while the condition evaluates to true. A common way to infinetly loop execution is to use `while (true)`.

The do-while loop will execute atleast once, even if the condition is false.

```cs
while (condition) 
{
  // code block to be executed
}
```
```cs
do 
{
  // code block to be executed
}
while (condition);
```

## For & foreach loop
Used when you know the specific amount of loops you would like to do.

- `Statement 1`: is executed (one time) before the execution of the code block. Usually this is the initialization of some `indexer`.
- `Statement 2`: defines the `condition` for executing the code block.
- `Statement 3`: is `executed (every time) after` the code block has been executed.

```cs
for (statement 1; statement 2; statement 3) 
{
  // code block to be executed
}
```

Typically a for-loop looks like this:
```cs
for (int i = 0; i < 5; i++) 
{
  Console.WriteLine(i);
}
```

A foreach loop is typically used to go through a collection:
```cs
foreach (type variableName in arrayName) 
{
  // code block to be executed
}
```

## Break & continue
- `Break`: jumps out of a loop
- `Continue`: skips one iteration and continues to the next iteration

```cs
while (i < 10) 
{
  if (i == 4) 
  {
    i++;
    continue;
  }
  Console.WriteLine(i);
  i++;
}
```