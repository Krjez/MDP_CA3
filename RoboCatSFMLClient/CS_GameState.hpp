#pragma once
class CS_GameState : public GameState
{
	public:
		CS_GameState(StateStack& stack);
		virtual void Draw() override;
		virtual bool HandleEvent(const sf::Event& event) override;

private:
	Background m_background;
};

