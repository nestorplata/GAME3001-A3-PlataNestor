#pragma once
#ifndef __LIFEBAR__
#define __LIFEBAR__
#include "DisplayObject.h"
//#include <string>

class LifeBar final : public DisplayObject
{
public:
	// constructors
	LifeBar();

	LifeBar(std::string location, std::string name);


	// destructor
	~LifeBar();

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
private:
	std::string texture;
};

#endif /* defined (__LIFEBAR__) */