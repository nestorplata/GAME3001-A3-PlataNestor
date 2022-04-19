#pragma once
#ifndef __CLOSE_COMBAT_ENEMY__
#define __CLOSE_COMBAT_ENEMY__

#include "NavigationObject.h"
#include "BaseEnemy.h"

class CloseCombatEnemy final : public BaseEnemy
{
public:
	CloseCombatEnemy(Scene* scene);
	~CloseCombatEnemy();

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


#endif /* defined (__CLOSE_COMBAT_ENEMY__) */