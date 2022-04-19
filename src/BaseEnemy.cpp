#include "BaseEnemy.h"

#include "SoundManager.h"
#include "TextureManager.h"

BaseEnemy::BaseEnemy()
{
	m_fireCounter = 0;
	m_fireCounterMax = 100;
	//TextureManager::Instance().load("../Assets/textures/Circle2.png", "circle2");

	//const auto size = TextureManager::Instance().getTextureSize("circle2");
	//setWidth(size.x);
	//setHeight(size.y);
	getTransform()->position = glm::vec2(500.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setCurrentHeading(0.0f);
	setCurrentDirection(glm::vec2(1.0f, 0.0f));

	life = 150;
	setType(BASE_ENEMY);
}

BaseEnemy::~BaseEnemy()
= default;

void BaseEnemy::draw()
{
	//Draw Sword
	//if (m_isSword)
	//{


	//}

}

void BaseEnemy::update()
{

}

void BaseEnemy::clean()
{
}

void BaseEnemy::m_Patrol()
{	
	if (!getLOSwithPlayer())
	{
		if (m_isGoingUp)
		{
			getTransform()->position = getTransform()->position + glm::vec2(0.0f, -5.0f);
			setCurrentHeading(-90);

			if (getTransform()->position.y < 125)
			{
				m_isGoingUp = false;
				m_isGoingLeft = true;

			}
		}
		else if (m_isGoingLeft)
		{
			getTransform()->position = getTransform()->position + glm::vec2(-5.0f, 0.0f);
			this->setCurrentHeading(180);

			if (getTransform()->position.x < 100)
			{
				m_isGoingLeft = false;
			}
		}
		else
		{
			if (getTransform()->position.y < 500)
			{
				setCurrentHeading(90);

				getTransform()->position = getTransform()->position + glm::vec2(0.0f, 5.0f);

			}
			else if (getTransform()->position.x < 400)
			{
				getTransform()->position = getTransform()->position + glm::vec2(5.0f, 0.0f);
				setCurrentHeading(0);

			}
			else
			{
				m_isGoingUp = true;
			}

		}
	}


}

void BaseEnemy::m_Idle()
{
	if (m_isTargetIdle)
	{
		getTransform()->position.y = getTransform()->position.y - 1;
		m_isTargetIdle = false;
	}
	else
	{
		getTransform()->position.y =getTransform()->position.y + 1;
		m_isTargetIdle = true;
	}
}

void BaseEnemy::m_RandomMovement()
{
}

void BaseEnemy::m_TakingDamage()
{
	if(life>0)
	{
		life = life - 30;
		std::cout << "30 damage Done to the Enemy" << std::endl;
		glm::vec2 position = glm::vec2((rand() % 5 + 1) * 100, (rand() % 5 + 1) * 100);
	}
	else {
		getTransform()->position = glm::vec2(800, 800);
	}


}

void BaseEnemy::m_Attack()
{

	m_isSword = true;



}

void BaseEnemy::m_Defeat()
{
	std::cout << "Enemy is Dead" << std::endl;
	

}

void BaseEnemy::m_drawSword()
{
	if (m_isSword)
	{
		if (m_rotation < 135)
		{
			m_rotation = m_rotation + 2;
			//m_isRunning = true;
		}
		else
		{
			m_rotation = 45;
		}
		float z = sin((getCurrentHeading()  + m_rotation ) * Util::Deg2Rad);
		float w = cos((getCurrentHeading() + m_rotation) * Util::Deg2Rad);
		m_SwordPoint = getTransform()->position + glm::vec2(z, -w) * 100.0f * 0.75f;
		Util::DrawLine(getTransform()->position, m_SwordPoint, glm::uvec4(1, 0, 0, 1));
		if (m_rotation == 91)
		{
			hit = true;
		}
		else {
			hit = false;
		}
	}
	else {
		m_rotation = 45;

	}

}

bool BaseEnemy::m_DamageDealt()
{
	return hit;
}

void BaseEnemy::m_ifHasLOS()
{
	if (m_isLOSwithPlayer && j==0)
	{
		std::cout << "Enemy has LOS" << std::endl;
		j = 1;
	}
	if (!m_isLOSwithPlayer && j==1)
	{
		std::cout << "Enemy Doesn't have LOS" << std::endl;
		j = 0;
	}


}


void BaseEnemy::setState(TargetMovement MovementType)
{
	state = MovementType;
}

TargetMovement BaseEnemy::getState()
{
	return state;
}

void BaseEnemy::setLOSwithPlayer(bool thing)
{
	m_isLOSwithPlayer = thing;
}

void BaseEnemy::setisSword(bool is)
{
	m_isSword = is;
}


bool BaseEnemy::getLOSwithPlayer()
{
	return m_isLOSwithPlayer;
}

bool BaseEnemy::getisSword()
{
	return m_isSword;
}







