// #'s are preprocessor statements
// #include copies the code
// #define literally replaces your word with the c++-defined word.
// #if will compile the code when the condition is met
// Include files inside include path folders use angular brackers(<>)
// Include files that are relative to the current file use quotes("")
// Header files from the C standard library will have a .h extension
// C++ files have none or .hpp
#include <iostream>
#include "ForwardDecls.h" // Contains void Log(const char* message); Forward Declaration
#include "PlayerObjects.h"
#include "Inheritance.cpp"

// This is a function, not to be confused with a method
// Functions can have an input and an output, the input is called a parameter and the output is called the return type.
// This function has no input and a void or empty return type.
void ThisIsAFunction() // This is the function signature
{ // This is the start of the function body
    std::cin.get(); // This is a statement
} // This is the end of the function body

void Log(const char* message); // Forward declaration, it tells the linker we're using this function but it's body is define elsewhere and it should link that object.

// This is telling the linker that this variable is in a different translation unit
// Similar to forward declaration of function body, we also don't initialize here or anything.
// Note: if the variable is static, no other translation unit can see it
extern int s_Variable; 

// main is a special function, also called the entry-point of the program
int main()
{
    // These are variables, they store data that we assign to them.
    // In order to do this we give them a name and a type, the type is important because the data we assign to them has to be of the same type.
    // However because C++ is so powerful, the only real difference for the basic types is their size in memory. E.g: 4 bytes.
    // Integer types: char, short, int, long, long long, long int, etc.
    // Floating types: float, double - Note: when assigning a float use the f postfix like so: 5.5f
    // Bool type: bool - Note: 0 = false, anything above 0 is true, so not just 1 but also 5 is true for example.
    // These types can have sub-zero or negative values, use the keyword "unsigned" for positive values only.
    // The sizeof(datatype) operator shows you the size of a data type in amount of bytes.
    int variable1 = 1;
    int variable2{ 2 };

    if (1) //This is a conditional statement, it will always evaluate to true
    {
        Log("This writes my message.");
    }
    else if (0) Log("This won't ever get printed."); // 0 always evaluates to false
    else Log("This won't ever get printed."); // 1 always evaluates to true so this condition is skipped.

    for (int i{ 0 }; i < 5; i++) // We use for loops to repeat instructions
    {
        Log("FIRST LOOP: I've been written " + std::to_string(i) + " time(s).");
    }

    int i{ 0 };
    bool condition = true;
    for (; condition;) // We use for loops to repeat instructions
    {
        if (i > 5) condition = false;
        Log("SECOND LOOP: I've been written " + std::to_string(i) + " time(s).");
        ++i;
        continue; // I will skip the rest of this for-loop, however i'm at the end of the loop but i'll still keep looping
    }

    i = 0;
    while (i < 5)
    {
        Log("THIRD LOOP: I've been written " + std::to_string(i) + " time(s).");
        i++;
        if (i == 3) break; // This will quit the loop entirely
    }

    do
    {
        Log("Do-while will print at least once and then look at the while condition!");
    } while (0);

    ShowPointers();

    { // You can just open braces in C++ to create a "block" of code.
        PlayerClass playerOne; // Stack object (Managed), deleted when out of scope
        PlayerClass* playerTwo = new PlayerClass; // Heap object (Unmanaged), has to be allocated/deleted manually
        delete playerTwo; // Manually delete/deallocate heap object

        playerOne._speed = 2;
        playerOne.Move(10, -10);
        std::cout << static_cast<int>(playerOne.GetPlayerServer()) << std::endl; // 3
    } // playerOne goes out of scope and get automatically deleted/deallocated here

    std::cout << s_Variable << std::endl; // 5

    Entity* e = new Player("Grimy"); // We can use our derived class as an instance of the parent class
    Player* p = new Player("Grimy"); // We can use our derived class as an instance of the parent class

    std::cout << "Player: " << e->GetName() << " is of type: "; // The arrow operator accesses members of a pointer
    ::ToString(e); // :: without a prefix resolves to the global namespace
    delete e, p;

    // Creates an array with 4 integers on the heap
    // Integer 1 will be at array[0], int 2 at array[1], int 3 at array[2] and int 4 at array[3]
    // This is important because deallocating array[4] will give us a memory acces violation (segfault)
    int* array = new int[4]; 
    *(array + 3) = 6; // int ptr which is at offset 0 + offset of 3 elements = 6 is the same as array[4] = 6
    std::cout << array << std::endl;      // Prints the memory address
    std::cout << array[3] << std::endl;   // Prints 6

    char* d = new char('A'); // Allocate a single char
    delete d;  // Correct
    delete[] array;  // Correct deletion of array

    ShowStrings();
    ShowConsts();

    ThisIsAFunction(); // This is a function call
    return EXIT_SUCCESS; // main has special return type, don't base yourself on main
}