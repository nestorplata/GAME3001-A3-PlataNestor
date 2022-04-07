#pragma once
#ifndef __MOUNTAIN__
#define __MOUNTAIN__
#include "DisplayObject.h"

class Mountain final : public DisplayObject
{
public:
	// constructors
	Mountain();

	// destructor
	~Mountain();

	// life cycle functions
	void draw() override;
	void update() override;
	void clean() override;
private:

};

#endif /* defined (__MOUNTAIN__) */