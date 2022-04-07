#pragma once
#ifndef __OBSTACLE__
#define __OBSTACLE__
#include "DisplayObject.h"
//#include <string>

class Obstacle final : public DisplayObject
{
public:
	// constructors
	Obstacle();
	Obstacle(std::string, std::string);

	
	// destructor
	~Obstacle();
	
	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
private:
	std::string texture;
};

#endif /* defined (__OBSTACLE__) */