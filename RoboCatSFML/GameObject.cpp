#include "RoboCatPCH.hpp"

GameObject::GameObject() :
	mIndexInWorld(-1),
	mDoesWantToDie(false),
	mRotation(0.f),
	mNetworkId(0),
	mColor(Colors::White),
	mScale(1.0f)
{
}


Vector3 GameObject::GetForwardVector()	const
{
	return Vector3(sinf(RoboMath::ToRadians(mRotation)), -cosf(RoboMath::ToRadians(mRotation)), 0.f);
}

void GameObject::SetNetworkId(int inNetworkId)
{
	//this doesn't put you in the map or remove you from it
	mNetworkId = inNetworkId;

}

void GameObject::SetRotation(float inRotation)
{
	//should we normalize using fmodf?
	mRotation = inRotation;
}
