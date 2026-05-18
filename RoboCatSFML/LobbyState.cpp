#include "RoboCatPCH.hpp"
#include "LobbyState.hpp"


LobbyState::LobbyState(StateStack& stack) : State(stack) { }

bool LobbyState::Update(float dt)
{
	return false;
}

