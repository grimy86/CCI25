#pragma once
#include <cstdint>

class PlayerClass
{
public:
	// An enum is a way to group related constant integers and make code more readable
	enum ServerLocation : uint8_t // This specifies the type of integer we want the enum to be, by default they're 32-bit integers
	{
		UK = 2, // By default enum values start at 0 and go upwards
		England,
		GreatBritain = 6
	};

private:
	static ServerLocation _playerServer; // Initialize these in the .cpp file or constructor

public:
	int _positionX, _positionY;
	int _speed;

	// Constructor, automatically get's called when we create / allocate an object of this class type (also called an instance)
	PlayerClass();
	// Destructor, automatically get's called when we delete / deallocate an object of this class type (also called an instance)
	~PlayerClass();

	void Move(int posX, int posY); // We define this in a .cpp file
	// Get/Set player level
	static ServerLocation GetPlayerServer();
	static void SetPlayerServer(ServerLocation location);

	struct Vec2
	{
		float x;
		float y;

		// Will add two of these vectors togheter
		void Add(const Vec2& other)
		{
			x += other.x;
			y += other.y;
		}
	};
};

// The technical difference between a class and a struct is minimal
// However, the usage is very different
// A used more for plain-old-data objects, usually without functions but they're acceptable
// It's used to be just a collection of types that make up a structure
// No inheritance on structs, that's what classes are for
struct PlayerStruct // Public by default
{
	int _positionX, _positionY;
	int _speed;

	void Move(int posX, int posY)
	{
		_positionX = posX * _speed;
		_positionY = posY * _speed;
	}
};

class StaticClass
{
	// Let's say this class only has static methods like:
	static int Add(int x, int y)
	{
		return x + y;
	}
	// Then we should hide the constructor like so:
// private:, we could use private here but deleting the constructor is enough.
	StaticClass() = delete;
};