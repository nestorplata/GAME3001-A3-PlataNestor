#include "Target.h"

#include "SoundManager.h"
#include "TextureManager.h"


Target::Target()
{
	TextureManager::Instance().load("../Assets/textures/Ship3.png","Enemy");

	const auto size = TextureManager::Instance().getTextureSize("Enemy");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(500.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;


	
	setType(TARGET);
}

Target::~Target()
= default;

void Target::draw()
{

	//TextureManager::Instance().draw("space_ship", x, y, getCurrentHeading(), 255, isCentered());


	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance().draw("Enemy", x, y, getCurrentHeading(), 255, isCentered());
}

void Target::update()
{
	//switch(state)
	//{
	//case MOVE_TO_PLAYER:
	//	m_isSword = false;
	//}
}

void Target::clean()
{
}

void Target::m_move()
{
	
}

void Target::m_checkBounds()
{
}

void Target::m_reset()
{
}
