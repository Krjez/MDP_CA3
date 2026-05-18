#include "RoboCatPCH.hpp"
#include "Killzone.hpp"

Killzone::Killzone() :
	GameObject(),
	mSpeed(3),
	mMoved(0)
{
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