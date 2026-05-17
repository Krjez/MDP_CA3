#include "RoboCatPCH.hpp"



std::unique_ptr< World > World::sInstance;

void World::StaticInit()
{
	sInstance.reset(new World());
}

World::World()
{
}


void World::AddGameObject(GameObjectPtr inGameObject)
{
	mGameObjects.push_back(inGameObject);
	inGameObject->SetIndexInWorld((int)mGameObjects.size() - 1);
}


void World::RemoveGameObject(GameObjectPtr inGameObject)
{
	int index = inGameObject->GetIndexInWorld();

	int lastIndex = (int)mGameObjects.size() - 1;
	if (index != lastIndex)
	{
		mGameObjects[index] = mGameObjects[lastIndex];
		mGameObjects[index]->SetIndexInWorld(index);
	}

	inGameObject->SetIndexInWorld(-1);

	mGameObjects.pop_back();
}


void World::Update()
{
	//update all game objects- sometimes they want to die, so we need to tread carefully...

	for (int i = 0, c = (int)mGameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = mGameObjects[i];


		if (!go->DoesWantToDie())
		{
			go->Update();
		}
		//you might suddenly want to die after your update, so check again
		if (go->DoesWantToDie())
		{
			RemoveGameObject(go);
			go->HandleDying();
			--i;
			--c;
		}
	}
}

float World::GetLeadingPawnXLocation()
{
	float maxDistanceX = 0.f;

	for (GameObjectPtr go : mGameObjects)
	{
		if (go->AsPlayerPawn() != nullptr)
		{
			float distanceX = go->GetLocation().mX;

			if (distanceX > maxDistanceX)
			{
				maxDistanceX = distanceX;
			}
		}
	}
	return maxDistanceX;
}
