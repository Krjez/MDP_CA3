#include "RoboCatServerPCH.hpp"
#include "SGO_Wall.hpp"

SGO_Wall::SGO_Wall(){}

void SGO_Wall::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}