#include "RoboCatPCH.hpp"
#include "Killzone.hpp"

Killzone::Killzone() :
	GameObject(),
	mSpeed(20),
	mMoved(0),
	mMaxX(-10000)
{
}

void Killzone::Update()
{
	mMoved += mSpeed * Timing::sInstance.GetDeltaTime();
	float newX = World::sInstance->GetLeadingPawnXLocation() + mMoved - 1680;
	mMaxX = std::max(mMaxX, newX);
	SetLocation(Vector3(mMaxX, 300, 0));
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