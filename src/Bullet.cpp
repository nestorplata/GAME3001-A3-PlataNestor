#include "Bullet.h"

#include "CollisionManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

Bullet::Bullet()
{
	TextureManager::Instance().load("../Assets/textures/bullet.png", "bullet");

	auto size = TextureManager::Instance().getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);
	

	setType(BULLET);
	getRigidBody()->isColliding = false;
}

Bullet::Bullet(glm::vec2 ShipPosition, glm::vec2 ShipDirection, float Appearing_distance)
{
	TextureManager::Instance().load("../Assets/textures/bullet.png", "bullet");

	auto size = TextureManager::Instance().getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = ShipPosition + ShipDirection * Appearing_distance;
	direction = ShipDirection;
	SpaceShip = ShipPosition;

	setType(BULLET);
	getRigidBody()->isColliding = false;
}


Bullet::~Bullet()
= default;

void Bullet::draw()
{
	TextureManager::Instance().draw("bullet",
		getTransform()->position.x, getTransform()->position.y, this, 0, 255, true);
}

void Bullet::update()
{
	getTransform()->position = getTransform()->position + direction * glm::vec2(5.0f, 5.0f);
}

void Bullet::clean()
{
}
