/*
*  Imported from CA2 and edited by:
*  Petr Sulc - GD4b - D00261476
*/

#pragma once

class MenuState : public State
{
public:
	MenuState(StateStack& stack);
	virtual void Draw() override;
	virtual bool Update(float dt) override;
	virtual bool HandleEvent(const sf::Event& event) override;

private:
	gui::Container m_gui_container;
};