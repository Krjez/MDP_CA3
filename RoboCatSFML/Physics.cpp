#include "RoboCatPCH.hpp"
#include "Physics.hpp"

std::unique_ptr<Physics> Physics::sInstance;

void Physics::StaticInit()
{
	sInstance.reset(new Physics());
}


void Physics::CheckCollision(Collider* first, Collider* second, std::vector<Pair>& collisions)
{
	if (first->CheckLayers(second))
	{
		if (first->BoundingBoxOverlap(second))
		{
			if (first->CheckCollision(second))
			{
				collisions.emplace_back(Pair(first, second));
			}
		}
	}
}

Physics::Physics() : m_next_collider_id(0), m_proxy(false), m_physics_body_map()
{
}

void Physics::Register(Collider* shape)
{
	shape->AssignId(m_next_collider_id);
	++m_next_collider_id;

	if (m_physics_body_map[shape->GetParent()])
	{
		m_dynamic_object_vector.emplace_back(shape);
	}
	else
	{
		m_static_object_vector.emplace_back(shape);
	}
}

void Physics::Unregister(Collider* shape)
{
	if (m_physics_body_map[shape->GetParent()])
	{
		auto size = m_dynamic_object_vector.size();
		for (int i = 0; i < size; i++)
		{
			if (shape == m_dynamic_object_vector[i])
			{
				std::swap(m_dynamic_object_vector[i], m_dynamic_object_vector[size - 1]);
				m_dynamic_object_vector.pop_back();
				return;
			}
		}
	}
	else
	{
		auto size = m_static_object_vector.size();
		for (int i = 0; i < size; i++)
		{
			if (shape == m_static_object_vector[i])
			{
				std::swap(m_static_object_vector[i], m_static_object_vector[size - 1]);
				m_static_object_vector.pop_back();
				return;
			}
		}
	}
}

void Physics::Register(PhysicsBody* body)
{
	m_physics_body_map[body->GetParent()] = body;
}

void Physics::Unregister(PhysicsBody* body)
{
	m_physics_body_map.erase(body->GetParent());
}

PhysicsBody* Physics::GetPhysicsBody(const GameObject* go)
{
	return m_physics_body_map[go];
}

void Physics::EvaluateAllCollisions(std::vector<Pair>& result)
{
	std::vector<Collider*>::iterator inner;
	for (std::vector<Collider*>::iterator iter = m_dynamic_object_vector.begin(); iter != m_dynamic_object_vector.end(); iter++)
	{
		for (++(inner = iter); inner != m_dynamic_object_vector.end(); ++inner)
		{
			CheckCollision(*iter, *inner, result);
		}

		for (auto& static_obj : m_static_object_vector)
		{
			CheckCollision(*iter, static_obj, result);
		}
	}
}

void Physics::HandleCollisions()
{
	std::vector<Physics::Pair> collisions;
	Physics::sInstance->EvaluateAllCollisions(collisions);
	for (auto& pair : collisions)
	{
		pair.first->GetParent()->HandleCollision(pair.second->GetParent());
		pair.second->GetParent()->HandleCollision(pair.first->GetParent());
	}
}

void Physics::SimulateAllBodies(float dt)
{
	for (auto& entry : m_physics_body_map)
	{
		entry.second->Simulate(dt);
	}
}
