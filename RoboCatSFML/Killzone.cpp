#include "RoboCatPCH.hpp"
#include "Killzone.hpp"

Killzone::Killzone() :
	GameObject(),
	mSpeed(3),
	mMoved(0)
{
}

void Killzone::Update()
{
	mMoved += mSpeed * Timing::sInstance.GetDeltaTime();
	SetLocation(Vector3(World::sInstance->GetLeadingPawnXLocation() + mMoved - 2100, 64, 0));
}

uint32_t Killzone::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = GameObject::Write(inOutputStream, inDirtyState);
	return writtenState;
}

void Killzone::Read(InputMemoryBitStream& inInputStream)
{
	GameObject::Read(inInputStream);
}