#include "RoboCatClientPCH.hpp"
#include "CGO_Wall.hpp"

CGO_Wall::CGO_Wall()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("wall"));
}

void CGO_Wall::SetTextureRect(float width, float height)
{
	mSpriteComponent->SetTextureSize(width, height);
}

CGO_Wall::~CGO_Wall() = default;
