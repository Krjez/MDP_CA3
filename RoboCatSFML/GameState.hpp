/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*/

#pragma once

class GameState : public State
{
public:
	GameState(StateStack& stack);
	virtual bool Update(float delta_time) override;
};

