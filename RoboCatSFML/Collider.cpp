/*
* Imported from CA2 and edited by:
* Petr Sulc - GD4b - D00261476
*/

#include "RoboCatPCH.hpp"
#include "Collider.hpp"

Collider::Collider(GameObject* parent, bool trigger) :
	Component(parent),
	m_is_trigger(trigger),
	m_layer(),
	m_ignore_layers()
{
	Physics::sInstance->Register(this);
}

Collider::~Collider()
{
	if (Physics::sInstance)
	{
		Physics::sInstance->Unregister(this);
	}
}

bool Collider::CheckCollision(Collider* other)
{
	return other->CollideWith(this);
}

bool Collider::IsTrigger() const
{
	return m_is_trigger;
}

CollisionLayer Collider::GetLayer() const
{
	return m_layer;
}

void Collider::SetLayer(CollisionLayer layer)
{
	m_layer = layer;
}

void Collider::SetIgnoreLayers(unsigned int layers)
{
	m_ignore_layers = layers;
}

bool Collider::CheckLayers(Collider* other) const
{
	if (m_ignore_layers & other->m_layer || other->m_ignore_layers & m_layer)
	{
		return false;
	}

	return true;
}

bool Collider::BoundingBoxOverlap(Collider* other)
{
	Vector3 min(GetAbsoluteLocation());
	Vector3 max(min + m_box_size);

	Vector3 otherMin(other->GetAbsoluteLocation());
	Vector3 otherMax(otherMin + other->m_box_size);

	return (min.mX <= otherMax.mX && max.mX >= otherMin.mX && min.mY <= otherMax.mY && max.mY >= otherMin.mY);
}

void Collider::ResolveCollision(Collider* other, Vector3& normal, float& depth)
{
	if (m_is_trigger || other->m_is_trigger)
		return;

	float elasticity;
	Vector3 relativeVelocity;
	float combinedMass;
	float strength;

	PhysicsBody* body = Physics::sInstance->GetPhysicsBody(GetParent());;
	PhysicsBody* otherBody = Physics::sInstance->GetPhysicsBody(other->GetParent());;

	if (body && otherBody)
	{
		if (body->IsKinematic() && !otherBody->IsKinematic())
		{
			otherBody->Move(normal * depth);
		}
		else if (!body->IsKinematic() && otherBody->IsKinematic())
		{
			body->Move(normal * -depth);
		}
		else
		{
			body->Move(normal * -(depth / 2.f));
			otherBody->Move(normal * (depth / 2.f));
		}


		if (body->IsKinematic() && otherBody->IsKinematic() ||
			!body->IsKinematic() && !otherBody->IsKinematic())
		{
			elasticity = (body->GetElasticity() + otherBody->GetElasticity()) / 2.f;
		}
		else if (body->IsKinematic())
		{
			elasticity = otherBody->GetElasticity();
		}
		else
		{
			elasticity = body->GetElasticity();
		}

		relativeVelocity = body->GetVelocity() - otherBody->GetVelocity();
		float speedOnNormal = Dot2D(relativeVelocity, normal);

		if (-speedOnNormal >= 0.f) return;

		float firstMass = body->IsKinematic() ? 0 : (1 / body->GetMass());
		float secondMass = otherBody->IsKinematic() ? 0 : (1 / otherBody->GetMass());

		combinedMass = firstMass + secondMass;
		strength = -(1 + elasticity) * speedOnNormal / (combinedMass == 0 ? 1 : combinedMass);

		Vector3 gripAxis(-normal.mY, normal.mX, 0);
		if (!body->IsKinematic())
		{
			Vector3 firstGrip = ProjectedOnto2D(otherBody->GetVelocity(), gripAxis) * 0.001f * otherBody->GetGrip();
			body->ApplyImpulse(strength, (normal + firstGrip).NormalizedCopy());
		}
		if (!otherBody->IsKinematic())
		{
			Vector3 secondGrip = ProjectedOnto2D(body->GetVelocity(), gripAxis) * 0.001f * body->GetGrip();
			otherBody->ApplyImpulse(-strength, (normal + secondGrip).NormalizedCopy());
		}
	}
	else if (body)
	{
		body->Move(normal * -depth);

		elasticity = body->GetElasticity();
		relativeVelocity = body->GetVelocity();
		combinedMass = 1 / body->GetMass();
		strength = -(1 + elasticity) * Dot2D(relativeVelocity, normal) / combinedMass;
		body->ApplyImpulse(strength, normal);
	}
	else
	{
		otherBody->Move(normal * depth);

		elasticity = otherBody->GetElasticity();
		relativeVelocity = otherBody->GetVelocity();
		combinedMass = 1 / otherBody->GetMass();
		strength = -(1 + elasticity) * Dot2D(relativeVelocity, normal) / combinedMass;
		otherBody->ApplyImpulse(strength, normal);
	}
}
