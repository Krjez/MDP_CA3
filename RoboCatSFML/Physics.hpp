#pragma once

class Collider;
class PhysicsBody;

class Physics
{
public:
	static void StaticInit();
	static std::unique_ptr<Physics> sInstance;

public:
	typedef std::pair<Collider*, Collider*> Pair;

private:
	std::vector<Collider*> m_dynamic_object_vector;
	std::vector<Collider*> m_static_object_vector;
	std::map<const GameObject*, PhysicsBody*> m_physics_body_map;

private:
	void CheckCollision(Collider* first, Collider* second, std::vector<Pair>& collisions);
	Physics();
public:
	void Register(Collider* shape);
	void Unregister(Collider* shape);
	void Register(PhysicsBody* body);
	void Unregister(PhysicsBody* body);

	PhysicsBody* GetPhysicsBody(const GameObject* go);

	void EvaluateAllCollisions(std::vector<Pair>& result);
	void HandleCollisions();
	void SimulateAllBodies(float dt);
};