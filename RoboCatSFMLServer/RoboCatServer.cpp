#include "RoboCatServerPCH.hpp"

RoboCatServer::RoboCatServer() : RoboCat()
{}

void RoboCatServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void RoboCatServer::Update()
{
	RoboCat::Update();

	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetPhysics().GetVelocity();
	float oldRotation = GetRotation();

	ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy(GetPlayerId());
	if (client)
	{
		MoveList& moveList = client->GetUnprocessedMoveList();
		for (const Move& unprocessedMove : moveList)
		{
			const InputState& currentState = unprocessedMove.GetInputState();

			float deltaTime = unprocessedMove.GetDeltaTime();

			ProcessInput(deltaTime, currentState);
		}

		moveList.Clear();
	}

	if (!RoboMath::Is2DVectorEqual(oldLocation, GetLocation()) ||
		!RoboMath::Is2DVectorEqual(oldVelocity, GetPhysics().GetVelocity()) ||
		oldRotation != GetRotation())
	{
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Pose);
	}
}

