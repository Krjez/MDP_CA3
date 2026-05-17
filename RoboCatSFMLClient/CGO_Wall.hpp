#pragma once
class CGO_Wall : public Wall
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new CGO_Wall()); }

protected:
	CGO_Wall();

private:
	SpriteComponentPtr mSpriteComponent;
};