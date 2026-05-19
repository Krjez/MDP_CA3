/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*/

#pragma once
class SS_LobbyState : public LobbyState
{
	public:
		SS_LobbyState(StateStack& stack);
		virtual bool Update(float dt) override;
};

