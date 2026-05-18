#include "RoboCatServerPCH.hpp"
#include "SGO_Killzone.hpp"

void SGO_Killzone::Update()
{
	mMoved += mSpeed * Timing::sInstance.GetDeltaTime();
	float gap = World::sInstance->GetLeadingPawnXLocation();

	for (GameObjectPtr go : World::sInstance->GetGameObjects())
	{
		if (go->AsPlayerPawn() != nullptr)
		{
			float distanceFromLeader = gap - go->GetLocation().mX;

			if (distanceFromLeader < mMoved)
			{
				//kill the player
				go->DoesWantToDie();
			}
		}
	}
}

SGO_Killzone::SGO_Killzone(){}