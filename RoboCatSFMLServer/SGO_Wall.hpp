#pragma once
class SGO_Wall : public Wall
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new SGO_Wall()); }

protected:
	SGO_Wall();
};