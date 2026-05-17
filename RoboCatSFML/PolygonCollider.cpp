#include "RoboCatPCH.hpp"
#include "PolygonCollider.hpp"

PolygonCollider::PolygonCollider(GameObject* parent, std::vector<Vector3>& vertices, bool trigger) :
	Collider(parent, trigger),
	m_vertices(vertices)
{
	Vector3 min(m_vertices[0]);
	Vector3 max(m_vertices[0]);

	for (auto& vertex : m_vertices)
	{
		min.mX = std::min(min.mX, vertex.mX);
		min.mY = std::min(min.mY, vertex.mY);
		max.mX = std::max(max.mX, vertex.mX);
		max.mY = std::max(max.mY, vertex.mY);
	}

	for (auto& vertex : m_vertices)
	{
		vertex -= min;
	}

	m_box_size = max - min;
	SetLocalOffset(min);
}

bool PolygonCollider::CheckCollision(Collider* other)
{
	return other->CollideWith(this);
}

bool PolygonCollider::CollideWith(Collider* other)
{
	return true;
}

bool PolygonCollider::CollideWith(BoxCollider* other)
{
	Vector3 firstPos(this->GetAbsoluteLocation());
	Vector3 secondPos(other->GetAbsoluteLocation());

	Vector3 boxSize(other->GetBoxSize());
	std::vector<Vector3> boxVertices
	{
		{0, 0, 0},
		{boxSize.mX, 0, 0},
		boxSize,
		{0, boxSize.mY, 0}
	};

	Vector3 normal;
	float depth;

	if (CheckPolygonSAT(firstPos, this->m_vertices, secondPos, boxVertices, normal, depth))
	{
		ResolveCollision(other, normal, depth);
		return true;
	}

	return false;
}

bool PolygonCollider::CollideWith(CircleCollider* other)
{
	Vector3 polyPos(this->GetAbsoluteLocation());
	Vector3 circlePos(other->GetCenter());

	Vector3 normal;
	float depth;

	if (CheckCircleSAT(polyPos, m_vertices, circlePos, other->GetRadius(), normal, depth))
	{
		ResolveCollision(other, normal, depth);
		return true;
	}

	return false;
}

bool PolygonCollider::CollideWith(PolygonCollider* other)
{
	Vector3 firstPos(this->GetAbsoluteLocation());
	Vector3 secondPos(other->GetAbsoluteLocation());

	Vector3 normal;
	float depth;

	if (CheckPolygonSAT(firstPos, this->m_vertices, secondPos, other->m_vertices, normal, depth))
	{
		ResolveCollision(other, normal, depth);
		return true;
	}

	return false;
}

bool PolygonCollider::CheckPolygonSAT(
	Vector3& firstPos,
	std::vector<Vector3>& firstVertices,
	Vector3& secondPos,
	std::vector<Vector3>& secondVertices,
	Vector3& outNormal,
	float& outDepth)
{
	outNormal = Vector3();
	outDepth = std::numeric_limits<float>::max();

	for (size_t i = 0; i < firstVertices.size(); i++)
	{
		Vector3 lineStart(firstVertices[i % firstVertices.size()]);
		Vector3 lineEnd(firstVertices[(i + 1) % firstVertices.size()]);
		Vector3 normal(-(lineEnd.mY - lineStart.mY), lineEnd.mX - lineStart.mX, 0);
		normal.Normalize2D();

		float min1, max1, min2, max2;
		ProjectVertices(normal, firstVertices, min1, max1);
		ProjectVertices(normal, secondVertices, min2, max2);

		float offset = Dot2D(normal, firstPos - secondPos);
		min1 += offset;
		max1 += offset;

		if (min1 > max2 || min2 > max1)
		{
			return false;
		}

		float currentDepth = std::min(max2 - min1, max1 - min2);
		if (currentDepth < outDepth)
		{
			outDepth = currentDepth;
			outNormal = normal;
		}
	}

	for (size_t i = 0; i < secondVertices.size(); i++)
	{
		Vector3 lineStart(secondVertices[i % secondVertices.size()]);
		Vector3 lineEnd(secondVertices[(i + 1) % secondVertices.size()]);
		Vector3 normal(-(lineEnd.mY - lineStart.mY), lineEnd.mX - lineStart.mX, 0);
		normal.Normalize2D();

		float min1, max1, min2, max2;
		ProjectVertices(normal, secondVertices, min1, max1);
		ProjectVertices(normal, firstVertices, min2, max2);

		float offset = Dot2D(normal, secondPos - firstPos);
		min1 += offset;
		max1 += offset;

		if (min1 > max2 || min2 > max1)
		{
			return false;
		}

		float currentDepth = std::min(max2 - min1, max1 - min2);
		if (currentDepth < outDepth)
		{
			outDepth = currentDepth;
			outNormal = normal;
		}
	}

	outDepth = std::abs(outDepth / outNormal.Length());
	outNormal.Normalize2D();

	Vector3 firstCenter(ApproximateCenter(firstVertices) + firstPos);
	Vector3 secondCenter(ApproximateCenter(secondVertices) + secondPos);

	if (Dot2D(secondCenter - firstCenter, outNormal) < 0)
	{
		outNormal *= -1;
	}

	return true;
}

void PolygonCollider::ProjectVertices(Vector3& normal, std::vector<Vector3>& vertices, float& outMin, float& outMax)
{
	float dot;
	outMin = std::numeric_limits<float>::max();
	outMax = std::numeric_limits<float>::lowest();

	for (auto& vertex : vertices)
	{
		dot = Dot2D(normal, vertex);
		if (dot < outMin) outMin = dot;
		if (dot > outMax) outMax = dot;
	}
}

Vector3 PolygonCollider::ApproximateCenter(std::vector<Vector3>& vertices)
{
	Vector3 sum;
	for (auto& vertex : vertices)
	{
		sum += vertex;
	}
	return sum * (1 / (float)vertices.size());
}

Vector3 PolygonCollider::ClosestPolygonVertex(Vector3& from, Vector3& polyPos, std::vector<Vector3>& vertices)
{
	Vector3 closest;
	float minDist = std::numeric_limits<float>::max();

	Vector3 vertOffset;
	float dist;
	for (auto& vert : vertices)
	{
		vertOffset = polyPos + vert - from;
		dist = vertOffset.LengthSq2D();
		if (dist < minDist)
		{
			closest = vert;
			minDist = dist;
		}
	}
	return closest;
}


bool PolygonCollider::CheckCircleSAT(
	Vector3& polyPos,
	std::vector<Vector3>& polyVertices,
	Vector3& circlePos,
	float circleRadius,
	Vector3& outNormal,
	float& outDepth)
{
	outNormal = Vector3();
	outDepth = std::numeric_limits<float>::max();

	for (size_t i = 0; i < polyVertices.size(); i++)
	{
		Vector3 lineStart(polyVertices[i % polyVertices.size()]);
		Vector3 lineEnd(polyVertices[(i + 1) % polyVertices.size()]);
		Vector3 normal(-(lineEnd.mY - lineStart.mY), lineEnd.mX - lineStart.mX, 0);
		normal.Normalize2D();

		float min1, max1;
		ProjectVertices(normal, polyVertices, min1, max1);
		float min2 = -circleRadius;
		float max2 = circleRadius;

		float offset = Dot2D(normal, polyPos - circlePos);
		min1 += offset;
		max1 += offset;

		if (min1 > max2 || min2 > max1)
		{
			return false;
		}

		float currentDepth = std::min(max2 - min1, max1 - min2);
		if (currentDepth < outDepth)
		{
			outDepth = currentDepth;
			outNormal = normal;
		}

	}

	Vector3 normal(ClosestPolygonVertex(circlePos, polyPos, polyVertices) + polyPos - circlePos);
	normal.Normalize2D();

	float min1, max1;
	ProjectVertices(normal, polyVertices, min1, max1);
	float min2 = -circleRadius;
	float max2 = circleRadius;

	float offset = Dot2D(normal, polyPos - circlePos);
	min1 += offset;
	max1 += offset;

	if (min1 > max2 || min2 > max1)
	{
		return false;
	}

	float currentDepth = std::min(max2 - min1, max1 - min2);
	if (currentDepth < outDepth)
	{
		outDepth = currentDepth;
		outNormal = normal;
	}

	outDepth = std::abs(outDepth / outNormal.Length());
	outNormal.Normalize2D();

	Vector3 polyCenter(ApproximateCenter(polyVertices) + polyPos);

	if (Dot2D(circlePos - polyCenter, outNormal) < 0)
	{
		outNormal *= -1;
	}

	return true;
}