#pragma once
class SS_LobbyState : public LobbyState
{
	public:
		SS_LobbyState(StateStack& stack);
		virtual bool Update(float dt) override;
};

