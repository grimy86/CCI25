#include "PlayerObjects.h"
#include <iostream>
#include <cstdint>

// Define the static member variable outside the class
PlayerClass::ServerLocation PlayerClass::_playerServer = PlayerClass::ServerLocation::England;

PlayerClass::PlayerClass()
{
	std::cout << "An instance of the Player Class has been created and allocated to: " << this << " ." << std::endl;
}

PlayerClass::~PlayerClass()
{
	std::cout << "An instance of the Player Class has been removed and deallocated from: " << this << " ." << std::endl;
}

void PlayerClass::Move(int posX, int posY) // Move definition
{
	_positionX = posX * _speed;
	_positionY = posY * _speed;
}

// Get/Set player level
PlayerClass::ServerLocation  PlayerClass::GetPlayerServer() { return _playerServer; }
void PlayerClass::SetPlayerServer(ServerLocation location) { _playerServer = location; };

