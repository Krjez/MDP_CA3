/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

#pragma once
class SGO_Wall : public Wall
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new SGO_Wall()); }

	virtual void HandleDying() override;

protected:
	SGO_Wall();
};