#pragma once

class Pawn
{
public:
	Pawn() : mPlayerId(-1) {}

	void SetPlayerId(uint32_t inPlayerId) { mPlayerId = inPlayerId; }
	uint32_t GetPlayerId() const { return mPlayerId; }

	virtual void ProcessInput(float inDeltaTime, const InputState& inInputState) = 0;

private:
	uint32_t mPlayerId;
};

