#include "RoboCatClientPCH.hpp"
#include "CGO_Killzone.hpp"

CGO_Killzone::CGO_Killzone()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("killzone"));
	mSpriteComponent->SetTextureSize(1280, 720);
}

void CGO_Killzone::Update()
{
	mMoved += mSpeed * Timing::sInstance.GetDeltaTime();
	SetLocation(Vector3(World::sInstance->GetLeadingPawnXLocation() + mMoved - 2100, 64, 0));
}