# Class relationships
In object-oriented programming, classes can interact with each other in different ways. The primary relationships between classes are `Association`, `Composition`, and `Aggregation`. Understanding these relationships helps design cleaner, more maintainable code.

### Association
Association is a "uses a" relationship, where one `class uses another` class to perform a task. The classes involved in an association can exist independently. In association, one class might use another class’s methods or behaviors, but neither class owns the other.

Key Points:
- Classes can interact without ownership.
- The lifetime of classes is independent.
- Often implemented via references, pointers, or method parameters.

```cs
public class Student
{
    public int StudentId { get; set; }
    public string FirstName { get; set; }
}

public class StudentRepository
{
    public Student GetStudent(int studentId) // Actively using the Student class
    {
        return new Student();
    }
}
```

### Composition
Composition is a "has a" relationship, where one `class contains a reference to another` class. In this relationship, the containing class (parent) owns the contained class (child). If the parent class is deleted, the child class will also be deleted.

Key Points:
- The parent class owns the child class.
- The child class cannot exist without the parent class.
- Deleting the parent also deletes the child.

Example:
```cs
public class Address
{
    public string Street { get; set; }
    public string City { get; set; }
}

public class Student
{
    public int StudentId { get; set; }
    public Address HomeAddress { get; set; } // Including the Address class
}
```
Here, the Student class owns the Address class. If the Student object is deleted, the `Address object will also be deleted`, indicating a composite relationship.

### Aggregation
Aggregation is a special type of composition, but in this relationship, the `child class can exist independently of the parent class`. The parent class holds a reference to the child class, but the child can live without the parent.

Key Points:
- Aggregation is a "has a" relationship.
- The parent contains a reference to the child, but the child can exist independently.
- Deleting the parent does not delete the child.

Example:
```cs
public class Course
{
    public int CourseId { get; set; }
    public string CourseName { get; set; }
}

public class Student
{
    public int StudentId { get; set; }
    public Course EnrolledCourse { get; set; }
}
```
In this example, the Student class has a reference to the Course class. However, if the Student is deleted, the `Course can still exist independently`, indicating an aggregation relationship.