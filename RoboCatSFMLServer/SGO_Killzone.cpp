#include "RoboCatServerPCH.hpp"
#include "SGO_Killzone.hpp"

void SGO_Killzone::Update()
{
	Killzone::Update();
	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ERS_Pose);

	float threshold = GetLocation().mX + 1158;

	for (GameObjectPtr go : World::sInstance->GetGameObjects())
	{
		if (go->AsPlayerPawn() != nullptr)
		{
			if (go->GetLocation().mX < threshold)
			{
				//kill the player
				go->SetDoesWantToDie(true);
			}
		}
	}
}

void SGO_Killzone::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

SGO_Killzone::SGO_Killzone(){}