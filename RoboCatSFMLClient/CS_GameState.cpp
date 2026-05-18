#include "RoboCatClientPCH.hpp"
#include "CS_GameState.hpp"

CS_GameState::CS_GameState(StateStack& stack) : GameState(stack)
{
}

void CS_GameState::Draw()
{
	RenderManager::sInstance->Render();
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
