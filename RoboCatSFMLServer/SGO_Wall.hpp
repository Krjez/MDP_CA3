#pragma once
class SGO_Wall : public Wall
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new SGO_Wall()); }

	virtual void HandleDying() override;

protected:
	SGO_Wall();
};