#include "RoboCatPCH.hpp"

GameObject::GameObject() :
	mIndexInWorld(-1),
	mDoesWantToDie(false),
	mRotation(0.f),
	mNetworkId(0),
	mColor(Colors::White),
	mTextureSize(128.f, 128.f, 0.f),
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

uint32_t GameObject::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & ERS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 location = GetLocation();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		inOutputStream.Write(GetRotation());

		inOutputStream.Write(GetScale());

		writtenState |= ERS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ERS_Color)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(GetColor());

		writtenState |= ERS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ERS_Texture)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(GetTextureSize());

		writtenState |= ERS_Texture;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	return writtenState;
}

void GameObject::Read(InputMemoryBitStream& inInputStream)
{
	bool stateBit;

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 location;
		inInputStream.Read(location.mX);
		inInputStream.Read(location.mY);
		SetLocation(location);

		float rotation;
		inInputStream.Read(rotation);
		SetRotation(rotation);

		float scale;
		inInputStream.Read(scale);
		SetScale(scale);
	}

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 color;
		inInputStream.Read(color);
		SetColor(color);
	}

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 textureSize;
		inInputStream.Read(textureSize);
		SetTextureSize(textureSize);
		SetTextureRect(textureSize.mX, textureSize.mY);
	}
}

void GameObject::SetRotation(float inRotation)
{
	//should we normalize using fmodf?
	mRotation = inRotation;
}
