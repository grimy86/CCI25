#include <iostream>


// Forces a function to be evaluated only at compile-time.
consteval int GetFive() { return 5; }

// Static or thread-storage duration lifetime variable that be initialized at compile-time
constinit int x = 50;

void ShowConsts()
{
	// By using the const keyword you syntactically promise the compiler you won't change value of the object
	// Essentially you promise that these are read-only objects
	// However you can still break this promise
	// Evaluated at run-time
	const int maxAge{ 99 };
	std::cout << "Const maxAge before: " << maxAge << std::endl;
	// Here's how to get around it
	int* a = new int; //make a new intptr
	a = (int*)&maxAge; // cast maxAge to be an intptr to then assign it to our intptr a
	*a = 5; // This wont work on every compiler
	std::cout << "Const maxAge after: " << maxAge << std::endl;

	// Evaluated at compile-time
	constexpr int x{ 5 };

	// Pointers and const
	const int* b = a; // Before * = can't change the value at the address, we could also write int const*
	int* const c = a; // After * = can't change the address to point to something else
	const int* const d = a; // This makes both const
	int const* const e = a; // This is another way to write it

	std::cout << "constinit int x {50}: " << ::x << std::endl;

	/*
		Not strictly related to const, but often misunderstood.
		volatile tells the compiler "this variable might change unexpectedly"
		and it tells Compiler Not to Optimize the Variable
	*/
	volatile int x2 = 99;  // Prevents compiler optimizations
	std::cout << "volatile int x2 = 99: " << x2 << std::endl;

	/*
		- Use constexpr when possible for performance optimizations.
		- Avoid abusing const_cast to remove const, as it's UB (undefined behavior).
		- Use mutable carefully, only when truly needed (e.g., internal caching).
		- Use volatile only for memory-mapped hardware or multithreading scenarios.
	*/
}

class ConstGetters
{
private:
	int x, y;
	int* xptr, *yptr; // The second * makes it so that yptr is also a pointer..
	mutable int var; //Allows Modification Inside const Objects
public:
	// We use const in the signature to tell the compiler we won't modify anything in this class
	int GetX() const
	{
		var = 2; // Notice how we can modify var even tho we're inside of a const method
		return x;
	}
	// Let's go through the consts here
	// 1st const = returning a pointer of which the value can't be modified
	// 2nd const = the returning pointer's contents can't be modified
	// 3rd const = we promise not to modify any actualy entities within this class
 	const int* const getXptr() const
	{
		return xptr;
	}
	int SetX(int value)
	{
		x = value;
	}
};