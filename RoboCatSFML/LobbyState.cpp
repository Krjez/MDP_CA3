/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*/

#include "RoboCatPCH.hpp"
#include "LobbyState.hpp"


LobbyState::LobbyState(StateStack& stack) : State(stack) { }

bool LobbyState::Update(float dt)
{
	return false;
}

