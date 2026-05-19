/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*/

#pragma once

class LobbyState : public State
{
public:
	LobbyState(StateStack& stack);
	virtual bool Update(float dt) override;
};