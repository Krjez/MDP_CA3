#include "RoboCatServerPCH.hpp"
#include "SS_GameState.hpp"

SS_GameState::SS_GameState(StateStack& stack) : GameState(stack), m_obstacle_distance(1000.f), m_last_obstacle(500.f), m_start_line(), m_start_time(0)
{
	SpawnStartLine();
}

bool SS_GameState::Update(float dt)
{
	GameState::Update(dt);

	if(m_start_time > 0)
	{
		m_start_time -= dt;
		if(m_start_time <= 0)
		{
			WallPtr start_line = m_start_line.lock();
			if (start_line)
			{
				start_line->SetDoesWantToDie(true);
			}
		}
		return false;
	}

	int currentX = World::sInstance->GetLeadingPawnXLocation();
	if (currentX - m_last_obstacle > m_obstacle_distance)
	{
		m_last_obstacle = currentX;
		SpawnObstacle(currentX + 800);
	}

	
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
		RequestStackPush<SS_LobbyState>();
	}
	
	if (playersAlive <= 1)
	{
		for (GameObjectPtr go : World::sInstance->GetGameObjects())
		{
			if (go->AsPlayerPawn() != nullptr)
			{
				ScoreBoardManager::sInstance->IncScore(go->AsPlayerPawn()->GetPlayerId(), 1);
			}
		}
		static_cast<Server*>(&*Engine::s_instance)->RestartWorld();
		SpawnStartLine();
		m_obstacle_distance = 1000.f;
		m_last_obstacle = 500.f;
	}
	

	return false;
}

void SS_GameState::SpawnObstacle(float x)
{
	float randY = RoboMath::GetRandomFloat() * 600.f;
	float width = 200.f;
	float height = 400.f - RoboMath::GetRandomFloat() * 100.f;


	WallPtr wallTop = std::static_pointer_cast<Wall>(GameObjectRegistry::sInstance->CreateGameObject('WALL'));
	wallTop->SetLocation(Vector3(x, 0-randY, 0.f));
	wallTop->SetCollider(width, height);
	wallTop->SetTextureSize(Vector3(width, height, 0));


	WallPtr wallBot = std::static_pointer_cast<Wall>(GameObjectRegistry::sInstance->CreateGameObject('WALL'));
	wallBot->SetLocation(Vector3(x, 720 - randY, 0.f));
	wallBot->SetCollider(width, height);
	wallBot->SetTextureSize(Vector3(width, height, 0));
}

void SS_GameState::SpawnStartLine()
{
	WallPtr start_line = std::static_pointer_cast<Wall>(GameObjectRegistry::sInstance->CreateGameObject('WALL'));
	start_line->SetLocation(Vector3(900, 64, 0.f));
	start_line->SetCollider(128, 720);
	start_line->SetTextureSize(Vector3(128, 720, 0));
	m_start_time = 5;
	m_start_line = start_line;
}
