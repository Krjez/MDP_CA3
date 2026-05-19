/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*/

#include "RoboCatPCH.hpp"
#include "GameState.hpp"

GameState::GameState(StateStack& stack) : State(stack)
{
}

bool GameState::Update(float dt)
{
	World::sInstance->Update();
	Physics::sInstance->SimulateAllBodies(Timing::sInstance.GetDeltaTime());
	Physics::sInstance->HandleCollisions();

	return true;
}