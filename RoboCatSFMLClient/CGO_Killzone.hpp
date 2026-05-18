#pragma once
class CGO_Killzone : public Killzone
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new CGO_Killzone()); }
	virtual void Update() override;

protected:
	CGO_Killzone();

private:
	SpriteComponentPtr mSpriteComponent;
};