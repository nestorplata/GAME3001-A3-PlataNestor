#pragma once
#ifndef __BULLET__
#define __BULLET__
#include "DisplayObject.h"
//#include <string>

class Bullet final : public DisplayObject
{
public:
	// constructors
	Bullet();
	Bullet(glm::vec2 ShipPosition, glm::vec2 ShipDirection, float Appearing_distance);

	// destructor
	~Bullet();

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;

	
private:
	std::string texture;
	glm::vec2 direction;
	glm::vec2 SpaceShip;

	bool Colided;
};

#endif /* defined (__BULLET__) */