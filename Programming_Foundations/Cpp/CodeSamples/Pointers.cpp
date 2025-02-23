#include <iostream>

void ShowReference();

void ShowPointers()
{
	// A pointer is an object or variable that holds an address in memory (that might have / be another object).
	// Simplified: A pointer is an integer that holds an address.
	// Types are completely meaningless for pointers.
	// When we give a pointer a type we're just saying that the data at that address is presumed to be of this type.
	// 0 is not a valid memory address, this makes the pointer point to null or a makes it a nullptr.

	int var { 8 };
	void* ptr { &var }; // You could look this up in this program's memory and see the value at this address.
	std::cout << "Our pointer = " << (int*)ptr << " and is located at: " << ptr << std::endl;
	ptr = nullptr;
	std::cout << "Our pointer = " << (int*)ptr << " and is located at: " << ptr << std::endl; // Could crash the program

	char* buffer = new char[8]; // Here we allocated 8 bytes, buffer is a pointer to the beginning of this memory.
	memset(buffer, 4, 8); // A function that fills up memory with data that we specify
	char** ptrToBuffer = &buffer; // A pointer to a pointer, this is a pointer to the pointer buffer.
	delete[] buffer; // deallocating our 8 byte buffer
	ptrToBuffer = nullptr;

	ShowReference();
}

void Increment(int& value) // Using int value would just copy that parameter onto the stack
{ // Using a reference will make it so that we're accessing the value at the memory location and actually modifying it
	// This is called "Pass by reference"
	value++; // Dereference the pointer and then increase the value
}

void ShowReference()
{
	int a = 22;
	int b = 23;
	std::cout << "Our reference = " << a << std::endl;
	int& ref = a; // This is a reference not a pointer, it's essentially just an alias.
	ref = b; // This is the same as a = 23 or ref = 23, we can't change the reference to reference something else;
	std::cout << "Our reference = " << a << std::endl;
	Increment(a);
	std::cout << "Our reference = " << a << std::endl;
}