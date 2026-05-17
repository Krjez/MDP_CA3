#include "RoboCatServerPCH.hpp"
#include <iostream>

bool Server::StaticInit()
{
	s_instance.reset(new Server());

	return true;
}

Server::Server()
{
	// TODO: Replace with our player pawn
	GameObjectRegistry::sInstance->RegisterCreationFunction('RCAT', RoboCatServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('YARN', YarnServer::StaticCreate);
	

	InitNetworkManager();

	// Setup latency
	float latency = 0.0f;
	string latencyString = StringUtils::GetCommandLineArg(2);
	if (!latencyString.empty())
	{
		latency = stof(latencyString);
	}
	NetworkManagerServer::sInstance->SetSimulatedLatency(latency);
}


int Server::Run()
{
	SetupWorld();

	return Engine::Run();
}

bool Server::InitNetworkManager()
{
	string portString = StringUtils::GetCommandLineArg(1);
	uint16_t port = stoi(portString);

	return NetworkManagerServer::StaticInit(port);
}


void Server::SetupWorld()
{
	// TODO: Spawn stuff here
}

void Server::DoFrame()
{
	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();

	Engine::DoFrame();

	NetworkManagerServer::sInstance->SendOutgoingPackets();

}

void Server::HandleNewClient(ClientProxyPtr inClientProxy)
{
	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->AddEntry(playerId, inClientProxy->GetName());
	SpawnPlayerPawn(playerId);
}

void Server::SpawnPlayerPawn(int inPlayerId)
{
	// TODO: Replace with our player pawn
	RoboCatPtr cat = std::static_pointer_cast<RoboCat>(GameObjectRegistry::sInstance->CreateGameObject('RCAT'));
	cat->SetColor(ScoreBoardManager::sInstance->GetEntry(inPlayerId)->GetColor());
	cat->SetPlayerId(inPlayerId);
	//gotta pick a better spawn location than this...
	cat->SetLocation(Vector3(600.f - static_cast<float>(inPlayerId), 400.f, 0.f));
}

void Server::HandleLostClient(ClientProxyPtr inClientProxy)
{
	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->RemoveEntry(playerId);
	GameObjectPtr pawnObject = GetPlayerPawn(playerId);
	if (pawnObject)
	{
		pawnObject->SetDoesWantToDie(true);
	}
}

GameObjectPtr Server::GetPlayerPawn(int inPlayerId)
{
	const auto& gameObjects = World::sInstance->GetGameObjects();
	for (int i = 0, c = (int)gameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = gameObjects[i];
		Pawn* pawn = go->AsPlayerPawn();
		if (pawn && pawn->GetPlayerId() == inPlayerId)
		{
			return go;
		}
	}

	return nullptr;
}
