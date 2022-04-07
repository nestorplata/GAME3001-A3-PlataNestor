#include "Target.h"

#include "SoundManager.h"
#include "TextureManager.h"


Target::Target()
{
	TextureManager::Instance().load("../Assets/textures/Circle.png","circle");

	const auto size = TextureManager::Instance().getTextureSize("circle");
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
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance().draw("circle", x, y, 0, 255, isCentered());
}

void Target::update()
{
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
