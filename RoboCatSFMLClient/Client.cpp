#include "RoboCatClientPCH.hpp"

bool Client::StaticInit()
{
	// Create the Client pointer first because it initializes SDL
	Client* client = new Client();
	InputManager::StaticInit();

	WindowManager::StaticInit();
	FontManager::StaticInit();
	TextureManager::StaticInit();
	RenderManager::StaticInit();
	

	HUD::StaticInit();

	s_instance.reset(client);

	return true;
}

Client::Client()
{
	GameObjectRegistry::sInstance->RegisterCreationFunction('RCAT', RoboCatClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('YARN', YarnClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('WALL', CGO_Wall::StaticCreate);

	StateStack::sInstance->PushState<MenuState>();
}

void Client::DoFrame()
{
	InputManager::sInstance->Update();

	Engine::DoFrame();

	if (NetworkManagerClient::sInstance)
	{
		NetworkManagerClient::sInstance->ProcessIncomingPackets();
	}

	StateStack::sInstance->Render();

	if (NetworkManagerClient::sInstance)
	{
		NetworkManagerClient::sInstance->SendOutgoingPackets();
	}
}

void Client::HandleEvent(sf::Event& p_event)
{
	StateStack::sInstance->HandleEvent(p_event);
}

bool Client::PollEvent(sf::Event& p_event)
{
	return WindowManager::sInstance->pollEvent(p_event);
}


