/*
* Imported from CA2 and edited by:
* Petr Sulc - GD4b - D00261476
*/

#pragma once

class PhysicsBody : public Component
{
public:
	PhysicsBody(GameObject* parent, float mass, float acceleration, float maxSpeed, float drag, float elasticity, float grip = 0);
	~PhysicsBody();

	void SetValues(float mass, float acceleration, float maxSpeed, float drag, float elasticity, float grip = 0);

	void Accelerate(Vector3 dir, float dt);
	void ApplyImpulse(float strength, Vector3 normal);
	void Move(Vector3 delta);
	void Simulate(float dt);

	Vector3 GetPosition() const;
	void SetPosition(Vector3 pos);

	Vector3 GetVelocity() const;
	Vector3 GetDrag() const;
	float GetMass() const;
	float GetElasticity() const;
	float GetGrip() const;

	void SetVelocity(float x, float y, float z);
	void ClampVelocity(float upper_limit);

	void SetAsKinematic();
	bool IsKinematic() const;

	void Reset();

private:
	bool m_kinematic;
	float m_mass;
	Vector3 m_velocity;
	float m_acceleration;
	float m_max_speed;
	float m_linear_drag;
	float m_elasticity;
	float m_grip;
};

