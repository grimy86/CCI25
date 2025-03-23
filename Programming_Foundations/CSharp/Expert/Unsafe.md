# Unsafe
The unsafe keyword allows you to write code that uses `pointers`, enabling `direct memory access`. By default, C# runs in a safe mode to prevent memory manipulation errors, but using the unsafe modifier, you can work with pointers `similar to languages like C and C++`.

Unsafe code is typically used in performance-critical applications, like system-level programming or when working with unmanaged code.

Key Points:
- `Pointer Declaration`: You can declare pointers like `int* p;`, which stores the address of a variable.
- `Unsafe Code Block`: Code inside a method or block marked as unsafe can use pointers.
- `Fixed Keyword`: To use pointers with arrays, the fixed keyword locks the array in memory so the pointer can safely access it.
- `Compiling Unsafe Code`: To compile unsafe code, the /unsafe option must be enabled in the compiler or project settings.

```cs
unsafe {
   int var = 20;
   int* p = &var;
   Console.WriteLine("Data: {0}, Address: {1}", var, (int)p);
}
```