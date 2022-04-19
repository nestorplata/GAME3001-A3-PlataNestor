#pragma once
#ifndef __BASE_ENEMY__
#define __BASE_ENEMY__

#include "NavigationObject.h"
#include "TargetMovement.h"
#include "Agent.h"
#include "Util.h"
//#include "Scene.h"

class BaseEnemy : public Agent
{
public:
	BaseEnemy();
	~BaseEnemy();

	void setState(TargetMovement);
	TargetMovement getState();

	void setLOSwithPlayer(bool);
	void setisSword(bool is);


	bool getLOSwithPlayer();
	bool getisSword();


	void m_Patrol();
	void m_Idle();
	void m_RandomMovement();
	void m_TakingDamage();
	void m_Attack();
	void m_Defeat();


	void m_drawSword();
	bool m_DamageDealt();

	void m_ifHasLOS();


	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;


private:

	TargetMovement state;
	bool m_isLOSwithPlayer;
	int j = 0;



	bool m_isGoingUp = true;
	bool m_isGoingLeft = false;
	bool m_isTargetIdle =true;
	//Hitten
	float life;
	bool takingdamage;

	//Sword Variables
	int m_fireCounter;
	int m_fireCounterMax;

	bool m_isSword;
	bool hit;
	bool m_isRunning;

	glm::vec2 m_SwordPoint;
	float m_rotation;

	//float m_currentHeading; // angle the ship is looking
	//glm::vec2 m_currentDirection;
};


#endif /* defined (__BASE_ENEMY__) */