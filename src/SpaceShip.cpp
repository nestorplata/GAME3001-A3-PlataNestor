#include "SpaceShip.h"

#include "Game.h"
#include "TextureManager.h"
#include "Util.h"

SpaceShip::SpaceShip()
{
	//normal texture
	TextureManager::Instance().load("../Assets/textures/ncl_small.png", "space_ship");

	
	const auto size = TextureManager::Instance().getTextureSize("space_ship");
	setWidth(size.x);
	setHeight(size.y);


	getTransform()->position = glm::vec2(100.0f, 400.0f);
	getRigidBody()->bounds = glm::vec2(getWidth(), getHeight());
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->acceleration = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;



	// starting motion properties
	setCurrentHeading(0.0f);
	setCurrentDirection(glm::vec2(1.0f, 0.0f));
	m_maxSpeed = 20.0f; // a maximum number of pixels moved per frame
	m_turnRate = 5.0f; // a maximum number of degrees to turn each time-step
	m_accelerationRate = 4.0f; // a maximum number of pixels to add to the velocity each frame
	m_rotation = 75;
	setLOSDistance(75.0f);
	setLOSColour(glm::uvec4(1, 0, 0, 1));
	Agent::updateWhiskers(45.0f);

	setType(AGENT);
}

SpaceShip::~SpaceShip()
= default;

void SpaceShip::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	const auto size = TextureManager::Instance().getTextureSize("space_ship");

	// draw the target
	TextureManager::Instance().draw("space_ship", x, y, getCurrentHeading(), 255, isCentered());

	//Draw Sword
	if (m_isSword ||m_isRunning)
	{
		float z = sin((getCurrentHeading() - m_rotation + 105) * Util::Deg2Rad);
		float w = cos((getCurrentHeading() - m_rotation + 105) * Util::Deg2Rad);
		m_SwordPoint = getTransform()->position + glm::vec2(z, -w) * getLOSDistance() * 0.75f;
		Util::DrawLine(getTransform()->position + getCurrentDirection() * 20.0f, m_SwordPoint, getLOSColour());

	}
	//std::cout << getCurrentDirection().x << ", " << getCurrentDirection().y <<std::endl;


}

void SpaceShip::update()
{

	//LookWhereYoureGoing(getTransform()->position);
	if (m_isSword||m_isRunning)
	{
		if (m_rotation > -45)
		{
			m_rotation = m_rotation - 2;
			m_isRunning = true;
		}
		else
		{
			m_rotation = 75;
			m_isRunning = false;
		}
	}
}

void SpaceShip::clean()
{
}

float SpaceShip::getMaxSpeed() const
{
	return m_maxSpeed;
}

float SpaceShip::getTurnRate() const
{
	return m_turnRate;
}

float SpaceShip::getAccelerationRate() const
{
	return m_accelerationRate;
}

glm::vec2 SpaceShip::getDesiredVelocity() const
{
	return m_desiredVelocity;
}

bool SpaceShip::getisSword()
{
	return m_isSword;
}

glm::vec2 SpaceShip::getSwordPoint()
{
	return m_SwordPoint;
}

bool SpaceShip::getisRunning()
{
	return m_isRunning;
}

void SpaceShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void SpaceShip::setTurnRate(const float angle)
{
	m_turnRate = angle;
}

void SpaceShip::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void SpaceShip::setDesiredVelocity(const glm::vec2 target_position)
{
	m_desiredVelocity = Util::normalize(target_position - getTransform()->position);
}

void SpaceShip::setisSword(bool is)
{
	m_isSword = is;
}

void SpaceShip::moveSword()
{
	if (m_isSword) {

	}

}

//void SpaceShip::Seek()
//{
//
//	setDesiredVelocity(getTargetPosition());
//
//	const glm::vec2 steering_direction = getDesiredVelocity() - getCurrentDirection();
//
//	LookWhereYoureGoing(steering_direction);
//
//	getRigidBody()->acceleration = getCurrentDirection() * getAccelerationRate();
//}

void SpaceShip::LookWhereYoureGoing(const glm::vec2 target_direction)
{
	if (getCollisionWhiskers()[0])
		std::cout << "not moving up";

	/*float target_rotation = Util::signedAngle(getCurrentDirection(),
		target_direction) - 90;

	const float turn_sensitivity = 3.0f;

	if (getCollisionWhiskers()[0])
	{
		target_rotation += getTurnRate() * turn_sensitivity;
	}
	else if (getCollisionWhiskers()[4])
	{
		target_rotation -= getTurnRate() * turn_sensitivity;
	}
	setCurrentHeading(Util::lerpUnclamped(getCurrentHeading(),
		getCurrentHeading() + target_rotation, 
		getTurnRate() * TheGame::Instance().getDeltaTime()));
	
	if (getCollisionWhiskers()[0] == false && getCollisionWhiskers()[4] == false)
	{
		if (getCollisionWhiskers()[1])
		{
			setCurrentHeading(getCurrentHeading() + getTurnRate());
		}
		else if (getCollisionWhiskers()[3])
		{
			setCurrentHeading(getCurrentHeading() - getTurnRate());
		}
	}

	
	if (getCollisionWhiskers()[0] && getCollisionWhiskers()[1] == false)
	{
		setCurrentHeading(getCurrentHeading() + getTurnRate()/2);
	}
	else if (getCollisionWhiskers()[1])
	{
		setCurrentHeading(getCurrentHeading() + getTurnRate());
	}
	else if (getCollisionWhiskers()[4] && getCollisionWhiskers()[3] == false)
	{
		setCurrentHeading(getCurrentHeading() - getTurnRate()/2);
	}
	else if (getCollisionWhiskers()[3])
	{
		setCurrentHeading(getCurrentHeading() - getTurnRate());
	}
	else if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setCurrentHeading(getCurrentHeading() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setCurrentHeading(getCurrentHeading() - getTurnRate());
		}
	}*/
	updateWhiskers(getWhiskerAngle());
}

//void SpaceShip::m_move()
//{
//	Seek();
//	
//	//                                   final Position     position term    velocity term     acceleration term
//	// kinematic equation for motion --> Pf            =      Pi     +     Vi*(time)    +   (0.5)*Ai*(time * time)
//
//	const float dt = TheGame::Instance().getDeltaTime();
//
//	// compute the position term
//	const glm::vec2 initial_position = getTransform()->position;
//
//	// compute the velocity term
//	const glm::vec2 velocity_term = getRigidBody()->velocity * dt;
//
//	// compute the acceleration term
//	const glm::vec2 acceleration_term = getRigidBody()->acceleration * 0.5f;// *dt;
//	
//	
//	// compute the new position
//	glm::vec2 final_position = initial_position + velocity_term + acceleration_term;
//
//	getTransform()->position = final_position;
//
//	// add our acceleration to velocity
//	getRigidBody()->velocity += getRigidBody()->acceleration;
//
//	// clamp our velocity at max speed
//	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, getMaxSpeed());
//}
