#include "RoboCatPCH.hpp"
#include "StateStack.hpp"

StateStack::PendingChange::PendingChange(std::function<void()> pending_call) : callback(pending_call)
{
}

StateStack::StateStack() { }

StateStack::~StateStack() = default;

void StateStack::Update(float dt)
{
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if (!(*itr)->Update(dt))
		{
			break;
		}
	}
	ApplyPendingChanges();
}

void StateStack::PopState()
{
	std::function<void()> pop_func = [this]() { m_stack.pop_back(); };

	m_pending_list.emplace_back(PendingChange(pop_func));
}

void StateStack::ClearStack()
{
	std::function<void()> clear_func = [this]() { m_stack.clear(); };

	m_pending_list.emplace_back(PendingChange(clear_func));
}

void StateStack::ApplyPendingChanges()
{
	for (PendingChange change : m_pending_list)
	{
		change.callback();
	}

	m_pending_list.clear();
}

bool StateStack::IsEmpty() const
{
	return m_stack.empty();
}