#include <string>
class Entity
{
private:
	std::string _name;
	int _age;
public:
	Entity(const std::string& name)
		: _name(name) {}
	Entity(const int age)
		: _name("Unknown"), _age(age) {}
};

void PrintEntity(const Entity& entity)
{
	// Printing
}

void initEntities()
{
	Entity a(22); // Clearest way of creating class objects
	Entity b{22};
	Entity c = 22;
	Entity d = Entity(22);
	Entity e = (Entity)22;

	PrintEntity(a); // No conversion
	PrintEntity(22); // Explicit entity conversion
	PrintEntity(std::string("Unknown")); // explicit string constructor -> implicit entity conversion
	PrintEntity((std::string)"Unknown"); // explicit string cast -> implicit entity conversion
	PrintEntity(Entity("Unknown")); // explicit entity constructor -> implicit string conversion
}