/*
* Imported from CA2 and edited by:
* Petr Sulc - GD4b - D00261476
*/

#include "RoboCatPCH.hpp"
#include "State.hpp"

State::State(StateStack& stack) : m_stack(&stack) { }

State::~State() { }

void State::RequestStackPop()
{
	m_stack->PopState();
}

void State::RequestStackClear()
{
	m_stack->ClearStack();
}