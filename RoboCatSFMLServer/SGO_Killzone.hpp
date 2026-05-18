#pragma once
class SGO_Killzone : public Killzone
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new SGO_Killzone()); }

	virtual void Update() override;

protected:
	SGO_Killzone();
};