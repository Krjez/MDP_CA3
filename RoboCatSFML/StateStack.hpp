#pragma once

class State;

class StateStack
{
public:
	static void StaticInit();
	static std::unique_ptr<StateStack> sInstance;

public:
	~StateStack();
	void Update(float dt);
	void Render();
	void HandleEvent(const sf::Event& event);

	template<typename T> void PushState();
	void PopState();
	void ClearStack();
	
	bool IsEmpty() const;

private:
	StateStack();
	void ApplyPendingChanges();

private:
	struct PendingChange
	{
		explicit PendingChange(std::function<void()> pending_call);
		std::function<void()> callback;
	};

private:
	std::list<std::unique_ptr<State>> m_stack;
	std::list<PendingChange> m_pending_list;
};

template<typename T>
void StateStack::PushState()
{
	static_assert(std::is_base_of<State, T>::value, "T must inherit State");

	std::function<void()> push_func = [this]() { m_stack.push_back(std::make_unique<T>(*this)); };

	m_pending_list.emplace_back(PendingChange(push_func));
}



