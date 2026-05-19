#include "RoboCatPCH.hpp"
#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody(GameObject* parent, float mass, float acceleration, float maxSpeed, float drag, float elasticity, float grip) :
	Component(parent),
	m_mass(mass),
	m_acceleration(acceleration),
	m_max_speed(maxSpeed),
	m_linear_drag(drag),
	m_velocity(),
	m_elasticity(elasticity),
	m_kinematic(false),
	m_grip(grip)
{
	Physics::sInstance->Register(this);
}

PhysicsBody::~PhysicsBody()
{
	Physics::sInstance->Unregister(this);
}

void PhysicsBody::SetValues(float mass, float acceleration, float maxSpeed, float drag, float elasticity, float grip)
{
	m_mass = mass;
	m_acceleration = acceleration;
	m_max_speed = maxSpeed;
	m_linear_drag = drag;
	m_elasticity = elasticity;
	m_grip = grip;
}

void PhysicsBody::Accelerate(Vector3 dir, float dt)
{
	m_velocity += dir * (dt * m_acceleration / m_mass);
}

void PhysicsBody::ApplyImpulse(float strength, Vector3 normal)
{
	m_velocity += (strength / m_mass) * normal;
	m_velocity.FloorToInt();
}

void PhysicsBody::Move(Vector3 delta)
{
	SetParentLocation(GetParentLocation() + delta);
}

void PhysicsBody::Simulate(float dt)
{
	m_velocity += GetDrag() * (dt / m_mass);

	if (m_velocity.LengthSq() > m_max_speed * m_max_speed)
	{
		m_velocity.Normalize();
		m_velocity *= m_max_speed;
	}

	m_velocity.FloorToInt();
	Move(m_velocity * dt);
}

Vector3 PhysicsBody::GetPosition() const
{
	return GetParentLocation();
}

void PhysicsBody::SetPosition(Vector3 pos)
{
	SetParentLocation(pos);
}


Vector3 PhysicsBody::GetVelocity() const
{
	return m_velocity;
}

Vector3 PhysicsBody::GetDrag() const
{
	return Vector3(m_velocity * -m_linear_drag);
}

float PhysicsBody::GetMass() const
{
	return m_mass;
}

float PhysicsBody::GetElasticity() const
{
	return m_elasticity;
}

float PhysicsBody::GetGrip() const
{
	return m_grip;
}

void PhysicsBody::SetVelocity(float x, float y, float z = 0)
{
	m_velocity.mX = x;
	m_velocity.mY = y;
	m_velocity.mZ = z;
}

void PhysicsBody::ClampVelocity(float upper_limit)
{
	if (m_velocity.LengthSq() > upper_limit * upper_limit)
	{
		m_velocity.Normalize();
		m_velocity *= upper_limit;
	}
}

void PhysicsBody::SetAsKinematic()
{
	m_kinematic = true;
}

bool PhysicsBody::IsKinematic() const
{
	return m_kinematic;
}

void PhysicsBody::Reset()
{
	m_velocity = { 0, 0, 0 };
}
