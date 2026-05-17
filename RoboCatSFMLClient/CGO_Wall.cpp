#include "RoboCatClientPCH.hpp"
#include "CGO_Wall.hpp"

CGO_Wall::CGO_Wall()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("wall"));
}