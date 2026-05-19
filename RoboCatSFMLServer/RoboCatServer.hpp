/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

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

