/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*/

#include "RoboCatPCH.hpp"
#include "Component.hpp"

Component::Component(GameObject* parent) : m_parent(parent), m_local_offset(0,0,0)
{
}

const Vector3& Component::GetParentLocation() const 
{
	return m_parent->GetLocation();
}

void Component::SetParentLocation(const Vector3& inLocation) { m_parent->SetLocation(inLocation); }

const Vector3& Component::GetLocalOffset() const { return m_local_offset; }

void Component::SetLocalOffset(const Vector3& inOffset) { m_local_offset = inOffset; }

const Vector3 Component::GetAbsoluteLocation() const { return m_parent->GetLocation() + m_local_offset; }

const GameObject* Component::GetParent() const { return m_parent; }

GameObject* Component::GetParent() { return m_parent; }
