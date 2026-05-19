#include "RoboCatServerPCH.hpp"
#include "SS_LobbyState.hpp"

SS_LobbyState::SS_LobbyState(StateStack& stack) : LobbyState(stack)
{
}

bool SS_LobbyState::Update(float dt)
{
	bool allReady = true;

	auto& entries = ScoreBoardManager::sInstance->GetEntries();
	for (auto& entry : entries)
	{
		if (!entry.IsReady())
		{
			allReady = false;
			break;
		}
	}

	if (allReady && entries.size() >= 1)
	{
		RequestStackClear();
		RequestStackPush<SS_GameState>();
		std::cout << "All players are ready, starting the game!" << std::endl;
	}

    return false;
}
