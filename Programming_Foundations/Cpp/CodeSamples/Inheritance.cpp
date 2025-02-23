#pragma once
#include <iostream>
#include <string>

class IPrintable // There is no interface keyword in C++, any class implementing a pure virtual func is an interface.
{
public:
	virtual std::string GetClassName() = 0;
};

class Entity : public IPrintable
{
public:
	struct positionVec2 { float x, y; };
	positionVec2 _currentPos{ 0,0 };

	// Marking this function as virtual means we can change it in the derived classes
	// A vtable (virtual table) is created when a class has at least one virtual function
	// A vptr (virtual table pointer) is added to objects of such classes to reference the vtable
	// A single vptr is stored per object, not per class
	// Virtual functions introduce a small performance cost, but it's usually negligible
	virtual std::string GetName() { return "Entity"; }

	// We can also force the sub-class to provide it's own definition of a virtual function instead of defining a body in the base class.
	// This is called a pure virtual function and is used a lot in "interface" classes
	virtual std::string GetNamePureVirtualFunc() = 0;

	virtual std::string GetClassName() override { return "Entity"; } // GetClassName implementation from IPrintable

	void Move(positionVec2 newPos)
	{
		_currentPos.x = newPos.x;
		_currentPos.y = newPos.y;
		// or just _currentPos = newPos
	}
};

class Player : public Entity // Inherits currentpos, move, IPrintable, etc.
{
private:
	std::string _name;

public:
	// This line is a constructor with an initializer list
	// Using an initializer list (: _name(name)) is more efficient than assigning inside the constructor body
	// It's the equivalent of
	/*
		Player(const std::string& name)
		{
			_name = name; // This causes extra work (default init + assignment)
		}
	*/
#pragma region Constructors
	Player() { _name = "Unknown"; } // Default
	Player(const std::string& name) : _name(name) {} // Constructor inizializer list
	/*
		Player(const std::string& name) : _name(name) {}
		==
		Player(const std::string& name){ _name = name; }
	*/
#pragma endregion

	// Marking the functions as overriden isn't necessary but it makes it more readable.
	std::string GetName() override { return _name; }
	std::string GetNamePureVirtualFunc() override { return _name; }
	virtual std::string GetClassName() override { return "Entity.Player"; } // Override, otherwise this would return "Entity" in the player class because of inheritance.
};

static void ToString(IPrintable* obj)
{
	std::cout << obj->GetClassName() << std::endl; // The arrow operator accesses members of a pointer
}
