#include "RoboCatClientPCH.hpp"
#include "CGO_Killzone.hpp"

CGO_Killzone::CGO_Killzone()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("killzone"));
	mSpriteComponent->SetTextureSize(1280, 720);
}