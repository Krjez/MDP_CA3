#pragma once

class LobbyState : public State
{
public:
	LobbyState(StateStack& stack);
	virtual bool Update(float dt) override;
};