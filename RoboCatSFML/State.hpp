/*
* Imported from CA2 and edited by:
* Petr Sulc - GD4b - D00261476
*/

#pragma once

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

public:
	State(StateStack& stack);
	virtual ~State();
	virtual void Draw() { };
	virtual bool Update(float dt) = 0;
	virtual bool HandleEvent(const sf::Event& event) { return true; };

protected:
	template<typename T>
	void RequestStackPush();
	void RequestStackPop();
	void RequestStackClear();

private:
	StateStack* m_stack;
};

template<typename T>
void State::RequestStackPush()
{
	m_stack->PushState<T>();
}