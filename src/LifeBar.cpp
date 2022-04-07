#include "LifeBar.h"


#include "SoundManager.h"
#include "TextureManager.h"

LifeBar::LifeBar()
{
	TextureManager::Instance().load("../Assets/textures/obstacle.png", "LifeBar");

	auto size = TextureManager::Instance().getTextureSize("LifeBar");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);
	getRigidBody()->isColliding = false;
	texture = "LifeBar";
}

LifeBar::LifeBar(std::string location, std::string name)
{
	TextureManager::Instance().load(location, name);

	auto size = TextureManager::Instance().getTextureSize(name);
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);
	getRigidBody()->isColliding = false;
	texture = name;
}


LifeBar::~LifeBar()
= default;

void LifeBar::draw()
{
	TextureManager::Instance().draw(texture,
		getTransform()->position.x, getTransform()->position.y, this, 0, 255, true);
}

void LifeBar::update()
{
	//setWidth(getWidth());
}

void LifeBar::clean()
{
}
