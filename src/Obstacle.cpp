#include "Obstacle.h"


#include "SoundManager.h"
#include "TextureManager.h"

Obstacle::Obstacle()
{
	TextureManager::Instance().load("../Assets/textures/obstacle.png", "obstacle");

	auto size = TextureManager::Instance().getTextureSize("obstacle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(OBSTACLE);
	getRigidBody()->isColliding = false;
}

Obstacle::Obstacle( std::string location, std::string name)
{
	TextureManager::Instance().load(location, name);

	auto size = TextureManager::Instance().getTextureSize(name);
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(OBSTACLE);
	getRigidBody()->isColliding = false;
	texture = name;
}

Obstacle::~Obstacle()
= default;

void Obstacle::draw()
{
	TextureManager::Instance().draw(texture,
		getTransform()->position.x, getTransform()->position.y,this, 0, 255, true);
}

void Obstacle::update()
{
}

void Obstacle::clean()
{
}
