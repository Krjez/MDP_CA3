#include "RoboCatClientPCH.hpp"
#include "Background.hpp"

Background::Background() : m_sprite(this, -100)
{
	m_sprite.SetTexture(TextureManager::sInstance->GetTexture("background"));
	m_sprite.SetTextureSize(256000, 1000);
}
