/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*/

#pragma once
class SS_GameState : public GameState
{
public:
	SS_GameState(StateStack& stack);
	virtual bool Update(float dt) override;
	void SpawnObstacle(float x);

	void SpawnStartLine();

private:
	float m_obstacle_distance;
	float m_last_obstacle;
	std::weak_ptr<Wall> m_start_line;
	float m_start_time;

};

