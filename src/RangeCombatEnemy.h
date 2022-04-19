#pragma once
#ifndef __RANGE_COMBAT_ENEMY__
#define __RANGE_COMBAT_ENEMY__

#include "NavigationObject.h"
#include "BaseEnemy.h"

class RangeCombatEnemy final : public BaseEnemy
{
public:
	RangeCombatEnemy(Scene* scene);
	~RangeCombatEnemy();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_move();
	void m_checkBounds();
	void m_reset();

	Scene* m_pScene;

};


#endif /* defined (__RANGE_COMBAT_ENEMY__) */
