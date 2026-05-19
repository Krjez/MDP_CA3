/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

#pragma once
class SGO_Killzone : public Killzone
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new SGO_Killzone()); }

	virtual void Update() override;
	virtual void HandleDying() override;
protected:
	SGO_Killzone();
};