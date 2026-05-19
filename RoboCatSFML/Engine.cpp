/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

#include "RoboCatPCH.hpp"

std::unique_ptr<Engine> Engine::s_instance;

Engine::Engine() : m_should_keep_running(true)
{
	SaveManager::StaticInit();

	SocketUtil::StaticInit();

	srand(static_cast<uint32_t>(time(nullptr)));

	GameObjectRegistry::StaticInit();

	Physics::StaticInit();

	World::StaticInit();

	StateStack::StaticInit();

	ScoreBoardManager::StaticInit();
}

Engine::~Engine()
{
	SocketUtil::CleanUp();
}

int Engine::Run()
{
	return DoRunLoop();
}

void Engine::HandleEvent(sf::Event& p_event)
{
	// Default implementation does nothing, up to derived classes to handle them, if they so choose
	(void)p_event;
}

bool Engine::PollEvent(sf::Event& p_event)
{
	return false;
}

int Engine::DoRunLoop()
{
	//Main message loop
	bool quit = false;

	sf::Event current_event;

	while (!quit && m_should_keep_running)
	{
		while (PollEvent(current_event))
		{
			if (current_event.type == sf::Event::Closed)
			{
				quit = true;
			}
			else
			{
				HandleEvent(current_event);
			}
		}

		Timing::sInstance.Update();
		DoFrame();
	}
	return 0;
}

void Engine::DoFrame()
{
	StateStack::sInstance->Update(Timing::sInstance.GetDeltaTime());

	if(StateStack::sInstance->IsEmpty())
	{
		SetShouldKeepRunning(false);
	}
}




