/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*/

#include "RoboCatClientPCH.hpp"
#include "CS_GameState.hpp"

CS_GameState::CS_GameState(StateStack& stack) : GameState(stack), m_background()
{

}

void CS_GameState::Draw()
{
	RenderManager::sInstance->Render();
}

bool CS_GameState::Update(float delta_time)
{
	GameState::Update(delta_time);

	int playersAlive = 0;
	for (GameObjectPtr go : World::sInstance->GetGameObjects())
	{
		if (go->AsPlayerPawn() != nullptr)
		{
			playersAlive++;
		}
	}

	if (playersAlive == 0)
	{
		RequestStackClear();
		RequestStackPush<CS_LobbyState>();
	}

	return false;
}

bool CS_GameState::HandleEvent(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		InputManager::sInstance->HandleInput(EIA_Pressed, event.key.code);
		break;
	case sf::Event::KeyReleased:
		InputManager::sInstance->HandleInput(EIA_Released, event.key.code);
		break;
	default:
		break;
	}

    return true;
}
