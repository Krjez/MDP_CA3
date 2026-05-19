/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

#include "RoboCatServerPCH.hpp"
#include "SGO_Wall.hpp"

SGO_Wall::SGO_Wall(){}

void SGO_Wall::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}