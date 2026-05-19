/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

#pragma once
class CGO_Killzone : public Killzone
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new CGO_Killzone()); }

protected:
	CGO_Killzone();

private:
	SpriteComponentPtr mSpriteComponent;
};