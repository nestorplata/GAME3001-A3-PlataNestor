#pragma once
#ifndef __SPACE_SHIP__
#define __SPACE_SHIP__

#include "Agent.h"
#include"Sprite.h"
class SpaceShip final : public Agent
{
public:
	SpaceShip();
	~SpaceShip();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// getters and setters (accessors and mutators)
	float getMaxSpeed() const;
	float getTurnRate() const;
	float getAccelerationRate() const;
	glm::vec2 getDesiredVelocity() const;
	bool getisSword();
	glm::vec2 getSwordPoint();
	bool getisRunning();

	void setMaxSpeed(float speed);
	void setTurnRate(float angle);
	void setAccelerationRate(float rate);
	void setDesiredVelocity(glm::vec2 target_position);
	void setisSword(bool is);

	// public functions
	//void Seek();
	void LookWhereYoureGoing(glm::vec2 target_direction);

private:
	// private movement variables
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	
	// where we want to go
	glm::vec2 m_desiredVelocity;

	//sword variables
	bool m_isSword;
	bool m_isRunning;

	glm::vec2 m_SwordPoint;
	float m_rotation;

	// private functions
	/*void m_move();*/
	void moveSword();
};


#endif /* defined (__SPACE_SHIP__) */