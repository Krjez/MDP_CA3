#include "RoboCatPCH.hpp"

RoboCat::RoboCat() :
	GameObject(),
	m_physics_body(this, 1, 800, 400, 0.001f, 0.7f),
	m_collider(this, 64.f),
	mMaxRotationSpeed(100.f),
	mLastMoveTimestamp(0.f),
	mThrustDir(0.f)
{
	m_collider.SetLayer(CollisionLayer::kPlayer);
	m_collider.SetIgnoreLayers(CollisionLayer::kPlayer);
}

void RoboCat::ProcessInput(float inDeltaTime, const InputState& inInputState)
{
	//turning...
	float newRotation = GetRotation() + inInputState.GetDesiredHorizontalDelta() * mMaxRotationSpeed * inDeltaTime;
	SetRotation(newRotation);

	//moving...
	float inputForwardDelta = inInputState.GetDesiredVerticalDelta();
	mThrustDir = inputForwardDelta;

	Vector3 direction = GetForwardVector() * mThrustDir;
	m_physics_body.Accelerate(direction, Timing::sInstance.GetDeltaTime());
}

uint32_t RoboCat::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & ECRS_PlayerId)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetPlayerId());

		writtenState |= ECRS_PlayerId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	if (inDirtyState & ECRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 velocity = m_physics_body.GetVelocity();
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		inOutputStream.Write(GetRotation());

		writtenState |= ECRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	//always write mThrustDir- it's just two bits
	if (mThrustDir != 0.f)
	{
		inOutputStream.Write(true);
		inOutputStream.Write(mThrustDir > 0.f);
	}
	else
	{
		inOutputStream.Write(false);
	}

	if (inDirtyState & ECRS_Color)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetColor());

		writtenState |= ECRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	return writtenState;
}



