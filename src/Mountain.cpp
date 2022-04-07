#include "Mountain.h"

#include "SoundManager.h"
#include "TextureManager.h"

Mountain::Mountain()
{
	TextureManager::Instance().load("../Assets/textures/mountain.png", "mountain");

	auto size = TextureManager::Instance().getTextureSize("mountain");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 400.0f);

	setType(OBSTACLE);
	getRigidBody()->isColliding = false;
}

Mountain::~Mountain()
= default;

void Mountain::draw()
{
	TextureManager::Instance().draw("mountain",
		getTransform()->position.x, getTransform()->position.y, this, 0, 128, true);
}

void Mountain::update()
{
}

void Mountain::clean()
{
}
