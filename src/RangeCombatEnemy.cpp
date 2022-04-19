#include "RangeCombatEnemy.h"

#include "SoundManager.h"
#include "TextureManager.h"
#include "PlayScene.h"


RangeCombatEnemy::RangeCombatEnemy(Scene* scene)
{
	std::cout << "RangeCombatEnemyCreated" << std::endl;
	m_pScene = scene;
	TextureManager::Instance().load("../Assets/textures/Ship3.png", "Enemy");

	const auto size = TextureManager::Instance().getTextureSize("Enemy");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(500.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setState(PATROL);

	setType(TARGET);
}

RangeCombatEnemy::~RangeCombatEnemy()
= default;

void RangeCombatEnemy::draw()
{

	//TextureManager::Instance().draw("space_ship", x, y, getCurrentHeading(), 255, isCentered());


	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance().draw("Enemy", x, y, getCurrentHeading(), 255, isCentered());
}

void RangeCombatEnemy::update()
{
	dynamic_cast<PlayScene*>(m_pScene)->m_RangeCombatEnemyBehaviour();
}

void RangeCombatEnemy::clean()
{
}

void RangeCombatEnemy::m_move()
{

}

void RangeCombatEnemy::m_checkBounds()
{
}

void RangeCombatEnemy::m_reset()
{
}