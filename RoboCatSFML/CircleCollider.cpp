#include "RoboCatPCH.hpp"
#include "CircleCollider.hpp"

CircleCollider::CircleCollider(GameObject* parent, float radius, bool trigger) :
	Collider(parent, trigger),
	m_radius(radius)
{
	m_box_size.mX = radius * 2;
	m_box_size.mY = radius * 2;
}

bool CircleCollider::CheckCollision(Collider* other)
{
	return other->CollideWith(this);
}

bool CircleCollider::CollideWith(Collider* other)
{
	return true;
}

bool CircleCollider::CollideWith(BoxCollider* other)
{
	Vector3 center(GetCenter());
	Vector3 boxMin(other->GetAbsoluteLocation());
	Vector3 boxMax(boxMin + other->GetBoxSize());
	Vector3 closest(std::clamp(center.mX, boxMin.mX, boxMax.mX), std::clamp(center.mY, boxMin.mY, boxMax.mY), 0);

	Vector3 offset(closest - center);
	float depth = m_radius - offset.Length2D();

	if (depth > 0)
	{
		if (depth == m_radius)
		{
			offset = center - (boxMin + (other->GetBoxSize() * 0.5f));
		}
		offset.Normalize2D();
		ResolveCollision(other, offset, depth);
		return true;
	}

	return false;
}

bool CircleCollider::CollideWith(CircleCollider* other)
{
	float combinedRadius = m_radius + other->m_radius;

	Vector3 offset(GetCenter() - other->GetCenter());
	float depth = combinedRadius - offset.Length2D();

	if (depth > 0)
	{
		offset.Normalize2D();
		offset *= -1;
		ResolveCollision(other, offset, depth);
		return true;
	}
	return false;
}

bool CircleCollider::CollideWith(PolygonCollider* other)
{
	return other->CollideWith(this);
}

float CircleCollider::GetRadius() const
{
	return m_radius;
}

Vector3 CircleCollider::GetCenter() const
{
	return GetAbsoluteLocation() + Vector3(m_radius, m_radius, 0);
}
