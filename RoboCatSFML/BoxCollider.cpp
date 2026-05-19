/*
*  Imported from CA2 and edited by:
*  Petr Sulc - GD4b - D00261476
*/

#include "RoboCatPCH.hpp"
#include "BoxCollider.hpp"

BoxCollider::BoxCollider(GameObject* parent, float width, float height, bool trigger) :
	Collider(parent, trigger)
{
	m_box_size.mX = width;
	m_box_size.mY = height;
}

BoxCollider::~BoxCollider()
{
}

bool BoxCollider::CheckCollision(Collider* other)
{
	return other->CollideWith(this);
}

bool BoxCollider::CollideWith(Collider* other)
{
	return true;
}

bool BoxCollider::CollideWith(BoxCollider* other)
{
	Vector3 min(GetAbsoluteLocation());
	Vector3 max(min + m_box_size);

	Vector3 otherMin(other->GetAbsoluteLocation());
	Vector3 otherMax(otherMin + other->m_box_size);

	float minX = std::min(std::abs(max.mX - otherMin.mX), std::abs(otherMax.mX - min.mX));
	float minY = std::min(std::abs(max.mY - otherMin.mY), std::abs(otherMax.mY - min.mY));

	Vector3 normal;
	float depth;

	if (minX < minY)
	{
		normal = { otherMin.mX - min.mX, 0, 0 };
		depth = minX;
	}
	else
	{
		normal = { 0, otherMin.mY - min.mY, 0 };
		depth = minY;
	};

	normal.Normalize2D();

	ResolveCollision(other, normal, depth);

	return true;
}

bool BoxCollider::CollideWith(CircleCollider* other)
{
	return other->CollideWith(this);
}

bool BoxCollider::CollideWith(PolygonCollider* other)
{
	return other->CollideWith(this);
}

Vector3 BoxCollider::GetBoxSize() const
{
	return m_box_size;
}