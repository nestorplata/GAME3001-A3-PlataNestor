#pragma once
#ifndef __BASE_ENEMY__
#define __BASE_ENEMY__

#include "NavigationObject.h"
#include "TargetMovement.h"
#include "TargetMovement.h"
class BaseEnemy : public NavigationObject
{
public:
	BaseEnemy();
	~BaseEnemy();

	void setState(TargetMovement);
	TargetMovement getState();

	void setLOSwithPlayer(bool);
	bool getLOSwithPlayer();

	void m_Patrol();
	void m_Idle();
	void m_RandomMovement();
	void m_TakingDamage();
	void m_Defeat();
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
};


#endif /* defined (__BASE_ENEMY__) */