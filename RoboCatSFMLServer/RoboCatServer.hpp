#pragma once
class RoboCatServer : public RoboCat
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new RoboCatServer()); }
	virtual void HandleDying() override;
	virtual void Update() override;

protected:
	RoboCatServer();
};

