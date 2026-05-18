#pragma once

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

public:
	State(StateStack& stack);
	virtual ~State();
	virtual void Draw() = 0;
	virtual bool Update(float dt) = 0;
	virtual bool HandleEvent(const sf::Event& event) = 0;

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