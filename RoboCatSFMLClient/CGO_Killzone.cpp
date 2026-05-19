/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

#include "RoboCatClientPCH.hpp"
#include "CGO_Killzone.hpp"

CGO_Killzone::CGO_Killzone()
{
	mSpriteComponent.reset(new SpriteComponent(this, 2));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("cat"));
	mSpriteComponent->SetTextureSize(128, 128);
	mSpriteComponent->GetSprite().setScale(10,10);
}