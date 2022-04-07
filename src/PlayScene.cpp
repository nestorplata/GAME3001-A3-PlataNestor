#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"

// required for scene
#include "Renderer.h"
#include "Util.h"
#include "Config.h"
#include <fstream>
//#include <cmath>

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	if (m_isGridEnabled)
	{
		glm::vec2 LeftTopCorner = glm::vec2(m_pSpaceShip->getTransform()->position.x - m_pSpaceShip->getWidth() / 2,
			m_pSpaceShip->getTransform()->position.y - m_pSpaceShip->getHeight() / 2);
		Util::DrawRect(LeftTopCorner, m_pSpaceShip->getWidth(), m_pSpaceShip->getHeight());

		Util::DrawCircle(m_pTarget->getTransform()->position, m_pTarget->getWidth()/2, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	}

	if (m_isShortestPathEnabled)
	{
		Util::DrawLine(m_pSpaceShip->getTransform()->position, ShortestpathNode, glm::vec4(1, 0, 1, 1));
		Util::DrawLine(ShortestpathNode, m_pTarget->getTransform()->position, glm::vec4(1, 0, 1, 1));
	}
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);

	if (enemiesDefeated == 1)
	{
		removeChild(m_pEnemiesLeft);
		m_pEnemiesLeft = new Label("Enemies Left: 0", "Consolas", 20, green, glm::vec2(300.0f, 20.0f));
		m_pEnemiesLeft->setParent(this);
		addChild(m_pEnemiesLeft);

		removeChild(m_pEnemiesDefeated);
		m_pEnemiesDefeated = new Label("Enemies Defeated: 1", "Consolas", 20, blue, glm::vec2(300.0f, 50.0f));
		m_pEnemiesDefeated->setParent(this);
		addChild(m_pEnemiesDefeated);
	}
}

void PlayScene::update()
{
	updateDisplayList();


	m_checkAgentLOS(m_pSpaceShip, m_pTarget);
	switch (m_LOSMode)
	{
	case 0:
		m_checkAllNodesWithTarget(m_pTarget); // target
		break;
	case 1:
		m_checkAllNodesWithTarget(m_pSpaceShip); // space ship
		break;
	case 2:
		m_checkAllNodesWithBoth(); // both
		break;
	case 3:
		break;
	}

	switch (MovementType)
	{
	case IDLE:
		//m_pTarget->setState(IDLE);
		m_pTarget->m_Idle();
		break;

	case MOVE_RANDOMLY:
		for (auto path_node : m_pGrid)
		{
			bool LOSWithTarget = m_checkPathNodeLOS(path_node, m_pTarget);

			if (LOSWithTarget && CollisionManager::Distance(path_node->getTransform()->position, m_pTarget->getTransform()->position) < 1000 && Choosen == NULL)
			{
				int random = rand() % 10;
				if (random == 0)
					Choosen = path_node;

			}
		}

		if (Choosen)
		{
			glm::vec2 difference = Choosen->getTransform()->position - m_pTarget->getTransform()->position;
			m_pTarget->getTransform()->position = m_pTarget->getTransform()->position + glm::vec2(difference.x / 20, difference.y / 20);

			if (CollisionManager::Distance(Choosen->getTransform()->position, m_pTarget->getTransform()->position) < 5)
			{
				Choosen = NULL;
			}
		}
		break;

	case PATROL:
		//m_pTarget->setState(PATROL);
		m_pTarget->m_Patrol();
		break;

	case TAKING_DAMAGE:
		//m_pTarget->setState(TAKING_DAMAGE);
		m_pTarget->m_TakingDamage();

		break;

	case DEFEAT:
		//m_pTarget->setState(DEFEAT);
		m_pTarget->m_Defeat();
		break;
	}

	if (m_pEnemyLifeBar->getWidth() <= 0)
	{
		SoundManager::Instance().setSoundVolume(100);
		if (m_deathsoundplayed == false)
		{
			std::cout << "enemy death"<<std::endl;
			SoundManager::Instance().playSound("death2", 0, 3);
			m_deathsoundplayed = true;
		}

		MovementType == DEFEAT;
		enemiesDefeated = 1;
	}
	else if(CollisionManager::circleAABBCheck(m_pSpaceShip, m_pTarget))
	{
		SoundManager::Instance().playSound("punch", 0, 2);

		MovementType = TAKING_DAMAGE;
		m_pEnemyLifeBar->setWidth(m_pEnemyLifeBar->getWidth() - 30);
		m_pEnemyLifeBar->getTransform()->position.x =m_pEnemyLifeBar->getTransform()->position.x + 15.0;

	}
	else if(MovementType!=IDLE){
		MovementType = PATROL;
	}

	m_pTarget->m_ifHasLOS();
	


}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}

	//debugging
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_H) && m_isKeyHdown)
	{
		if (m_isGridEnabled)
			m_isGridEnabled = false;
		else
			m_isGridEnabled = true;
		m_toggleGrid(m_isGridEnabled);
		m_isKeyHdown = false;

	}//debug grid

	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_H))
	{
		m_isKeyHdown = true;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_P) && m_isKeyPdown) //debug Patrol
	{
		if (MovementType == IDLE)
		{
			MovementType = PATROL;
			std::cout << "Target Patrolling" << std::endl;
		}
		else if(MovementType !=IDLE)
		{
			MovementType = IDLE;

			std::cout << "Target Idleing" << std::endl;

		}

		//m_pTarget->setState(MovementType);
		m_isKeyPdown = false;

	}

	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_P))
	{
		m_isKeyPdown = true;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_K) && m_isKeyKdown) //debug player life
	{
		if (m_pSpaceShipLifeBar->getWidth() > 0)
		{
			std::cout << "15 damage points dealt to Player" << std::endl;
			m_pSpaceShipLifeBar->setWidth(m_pSpaceShipLifeBar->getWidth() - 15);
			m_pSpaceShipLifeBar->getTransform()->position.x = m_pSpaceShipLifeBar->getTransform()->position.x - 7.5;
			m_isKeyKdown = false;
		}
		else {
			std::cout << "Player is dead" << std::endl;

		}

	}

	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_K))
	{
		m_isKeyKdown = true;
	}

	//attacking
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_DOWN) && m_isLowerFacedown)
	{
		m_pSpaceShip->setisSword(true);
		SoundManager::Instance().playSound("slash", 0);
		SoundManager::Instance().setSoundVolume(75);
		m_isLowerFacedown = false;

	}

	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_DOWN))
	{
		m_pSpaceShip->setisSword(false);
		m_isLowerFacedown = true;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_RIGHT) && m_isRightFacedown)
	{
		m_createBullets();
		m_pSpaceShip->getTransform()->position = m_pSpaceShip->getTransform()->position - glm::vec2(10.0f, 10.0f) * m_pSpaceShip->getCurrentDirection();
		SoundManager::Instance().playSound("fire", 0);
		SoundManager::Instance().setSoundVolume(50);


		m_isRightFacedown = false;
	}

	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_RIGHT))
	{

		m_isRightFacedown = true;
	}

	//SpaceShip Movement
	glm::vec2 SpaceShipPosition = m_pSpaceShip->getTransform()->position;
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		SpaceShipPosition = SpaceShipPosition + glm::vec2(0.0f, -5.0f);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		SpaceShipPosition = SpaceShipPosition + glm::vec2(0.0f, 5.0f);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		SpaceShipPosition = SpaceShipPosition + glm::vec2(-5.0f, 0.0f);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		SpaceShipPosition = SpaceShipPosition + glm::vec2(5.0f, 0.0f);
	}

	glm::vec2 Displacement =   SpaceShipPosition - m_pSpaceShip->getTransform()->position;

	m_pSpaceShip->getTransform()->position = SpaceShipPosition;

	
	if (Displacement == glm::vec2(0.0f, 0.0f))
	{
		if (m_isPlayerIdle)
		{
			m_pSpaceShip->getTransform()->position.y = m_pSpaceShip->getTransform()->position.y + 1;
			m_isPlayerIdle = false;
		}
		else
		{
			m_pSpaceShip->getTransform()->position.y = m_pSpaceShip->getTransform()->position.y - 1;
			m_isPlayerIdle = true;
		}
	}
	else if (Displacement != glm::vec2(0.0f, 0.0f))
	{
		SoundManager::Instance().playSound("ufoengine", 0, 0);

	}

	if (Displacement.x == -5 && Displacement.y == -5)
		angle = -135;
	else if (Displacement.x == -5 && Displacement.y == 5)
		angle = 135;
	else if (Displacement.x == 5 && Displacement.y == -5)
		angle = -45;
	else if (Displacement.x == 5 && Displacement.y == 5)
		angle = 45;
	else if (Displacement.x == 5)
		angle = 0;
	else if (Displacement.x == -5)
		angle = 180;
	else if (Displacement.y == 5)
		angle = 90;
	else if (Displacement.y == -5)
		angle = -90;
	m_pSpaceShip->setCurrentHeading(angle);
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";



	// Create new obstacles from a file
	m_createObstaclesFromFile();

	// Setup a few more fields
	m_LOSMode = 2; // future enum?
	m_obstacleBuffer = 0;
	MovementType = IDLE;
	srand(time(NULL));
	m_pathNodeLOSDistance = 1000;
	m_setPathNodeLOSDistance(m_pathNodeLOSDistance);

	//setup the Grid
	m_isGridEnabled = false;
	m_buildGrid();
	m_toggleGrid(m_isGridEnabled);

	m_pSpaceShipLifeBar = new LifeBar();
	m_pSpaceShipLifeBar->getTransform()->position = glm::vec2(100.0f, 37.5f);
	m_pSpaceShipLifeBar->setWidth(150);
	m_pSpaceShipLifeBar->setHeight(25);
	addChild(m_pSpaceShipLifeBar, 5);

	m_pEnemyLifeBar = new LifeBar("../Assets/textures/obstacle2.png", "EnemyBar");
	m_pEnemyLifeBar->getTransform()->position = glm::vec2(500.0f, 37.5f);
	m_pEnemyLifeBar->setWidth(150);
	m_pEnemyLifeBar->setHeight(25);
	addChild(m_pEnemyLifeBar, 5);

	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(400.0f, 500.0f);
	addChild(m_pTarget, 3);

	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->getTransform()->position = glm::vec2(40.0f, 200.0f);
	addChild(m_pSpaceShip, 4);

	m_pEnemiesLeft = new Label("Enemies Left: 1", "Consolas", 20, green, glm::vec2(300.0f, 20.0f));
	m_pEnemiesLeft->setParent(this);
	addChild(m_pEnemiesLeft);

	m_pEnemiesDefeated = new Label("Enemies Defeated: 0", "Consolas", 20, blue, glm::vec2(300.0f, 50.0f));
	m_pEnemiesDefeated->setParent(this);
	addChild(m_pEnemiesDefeated);



	// preload sounds
	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/thunder.ogg", "thunder", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/engine.ogg", "engine", SOUND_SFX);

	SoundManager::Instance().load("../Assets/audio/ufoengine.ogg", "ufoengine", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/fire.ogg", "fire", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/motor.ogg", "motor", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/slash.ogg", "slash", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/death.ogg", "death", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/death2.ogg", "death2", SOUND_SFX);

	SoundManager::Instance().load("../Assets/audio/punch.ogg", "punch", SOUND_SFX);

	SoundManager::Instance().load("../Assets/audio/back.ogg", "back", SOUND_MUSIC);

	SoundManager::Instance().playMusic("back", -1, 0);


	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));


}

void PlayScene::m_buildGrid()
{
	const auto tile_size = Config::TILE_SIZE;
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);

	m_clearNodes(); // we will need clear nodes because we will rebuild/redraw the grid if we move an obstacle

	// lay out a grid of path_nodes
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			PathNode* path_node = new PathNode();
			path_node->getTransform()->position = glm::vec2((col * tile_size) + offset.x, (row * tile_size) + offset.y);
			bool keep_node = true;
			for (auto obstacle : m_pObstacles)
			{
				// determine which path_nodes to keep
				if (CollisionManager::AABBCheckWithBuffer(path_node, obstacle, m_obstacleBuffer))
				{
					keep_node = false;
				}
			}
			if (keep_node)
			{
				addChild(path_node, 1);
				m_pGrid.push_back(path_node);
			}
			else
			{
				delete path_node;
			}
		}
	}

	// if Grid is supposed to be hidden - make it so!
	m_toggleGrid(m_isGridEnabled);
}

void PlayScene::m_toggleGrid(const bool state)
{
	for (auto path_node : m_pGrid)
	{
		path_node->setVisible(state);
	}
}

bool PlayScene::m_checkAgentLOS(Agent * agent, DisplayObject * target_object)
{
	bool has_LOS = false; // default - no LOS
	agent->setHasLOS(has_LOS);
	glm::vec4 LOSColour;

	// if ship to target distance is less than or equal to LOS Distance
	const auto AgentToTargetDistance = Util::getClosestEdge(agent->getTransform()->position, target_object);
	if (AgentToTargetDistance <= agent->getLOSDistance()) // we are in range
	{
		std::vector<DisplayObject*> contact_list;
		for (auto display_object : getDisplayList())
		{
			// check if the display_object is closer to the spaceship than the target
			const auto AgentToObjectDistance = Util::getClosestEdge(agent->getTransform()->position, display_object);
			if (AgentToObjectDistance > AgentToTargetDistance) continue;
			if ((display_object->getType() != AGENT) && (display_object->getType() != PATH_NODE) && (display_object->getType() != TARGET))
			{
				contact_list.push_back(display_object);
			}
		}

		const glm::vec2 agentEndPoint = agent->getTransform()->position + agent->getCurrentDirection() * agent->getLOSDistance();
		has_LOS = CollisionManager::LOSCheck(agent, agentEndPoint, contact_list, target_object);

		LOSColour = (target_object->getType() == AGENT) ? glm::vec4(0, 0, 1, 1) : glm::vec4(0, 1, 0, 1);

		
		agent->setHasLOS(has_LOS, LOSColour);
	}
	return has_LOS;
}

bool PlayScene::m_checkPathNodeLOS(PathNode * path_node, DisplayObject * target_object)
{
	// check angle to target so we can still use LOS distance for path_nodes
	const auto target_direction = target_object->getTransform()->position - path_node->getTransform()->position;
	const auto normalized_direction = Util::normalize(target_direction);
	path_node->setCurrentDirection(normalized_direction);
	return m_checkAgentLOS(path_node, target_object);
}

void PlayScene::m_checkAllNodesWithTarget(DisplayObject * target_object)
{
	for (auto path_node : m_pGrid)
	{
		m_checkPathNodeLOS(path_node, target_object);
	}
}

void PlayScene::m_checkAllNodesWithBoth()
{
	int Shortestdistance= m_pathNodeLOSDistance* m_pathNodeLOSDistance;
	int ShortestMidPoint= m_pathNodeLOSDistance* m_pathNodeLOSDistance/2;
	for (auto path_node : m_pGrid)
	{
		bool LOSWithSpaceShip = m_checkPathNodeLOS(path_node, m_pSpaceShip);
		bool LOSWithTarget = m_checkPathNodeLOS(path_node, m_pTarget);
		path_node->setHasLOS(LOSWithSpaceShip, glm::vec4(0, 0, 1, 1));
		path_node->setHasLOS(LOSWithTarget, glm::vec4(0, 1, 0, 1));
		path_node->setHasLOS(LOSWithSpaceShip && LOSWithTarget, glm::vec4(0, 1, 1, 1));
		

		if (LOSWithSpaceShip && LOSWithTarget)
		{
			if (CollisionManager::Distance(m_pSpaceShip->getTransform()->position, ShortestpathNode)< 40.0f ||
				CollisionManager::Distance(m_pTarget->getTransform()->position, ShortestpathNode) < 40.0f)
			{
				m_pTarget->setLOSwithPlayer(true);
			}
			else {
				m_pTarget->setLOSwithPlayer(false);
			}

			
			if (CollisionManager::squaredDistance(m_pSpaceShip->getTransform()->position, path_node->getTransform()->position) ==
				CollisionManager::squaredDistance(path_node->getTransform()->position, m_pTarget->getTransform()->position))
			{
				glm::vec2 ship = m_pSpaceShip->getTransform()->position;
				glm::vec2 target = m_pTarget->getTransform()->position;

				glm::vec2 MidPoint = glm::vec2((ship.x + target.x) / 2 , (ship.y + target.y) / 2);

				if (CollisionManager::squaredDistance(MidPoint, path_node->getTransform()->position) < ShortestMidPoint)
				{
					ShortestMidPoint = CollisionManager::squaredDistance(MidPoint, path_node->getTransform()->position);
					ShortestpathNode = path_node->getTransform()->position;
				}
			}
			else {
				if (CollisionManager::squaredDistance(m_pSpaceShip->getTransform()->position, path_node->getTransform()->position) < Shortestdistance)
				{
					Shortestdistance = CollisionManager::squaredDistance(m_pSpaceShip->getTransform()->position, path_node->getTransform()->position);
					ShortestpathNode = path_node->getTransform()->position;

				}
				else if (CollisionManager::squaredDistance(path_node->getTransform()->position, m_pTarget->getTransform()->position) < Shortestdistance)
				{
					Shortestdistance = CollisionManager::squaredDistance(path_node->getTransform()->position, m_pTarget->getTransform()->position);
					ShortestpathNode = path_node->getTransform()->position;

				}

				
			}
		}
	}

}

void PlayScene::m_setPathNodeLOSDistance(const int dist)
{
	for (auto path_node : m_pGrid)
	{
		path_node->setLOSDistance(static_cast<float>(dist));
	}
}

void PlayScene::m_clearNodes()
{
	m_pGrid.clear();
	for (auto display_object : getDisplayList())
	{
		if (display_object->getType() == PATH_NODE)
		{
			removeChild(display_object);
		}
	}
}

void PlayScene::m_createObstaclesFromFile()
{

	std::ifstream inFile("../Assets/data/obstacles.txt");

	std::cout << "Mountian" << std::endl;
	Obstacle* obstacle = new Obstacle("../Assets/textures/water.png", "water");
	float x, y, w, h;
	inFile >> x >> y >> w >> h;
	obstacle->getTransform()->position = glm::vec2(x, y);
	obstacle->setWidth(w);
	obstacle->setHeight(h);
	addChild(obstacle, 1);
	m_pObstacles.push_back(obstacle);

	for (int i = 0; i < 3; i++)
	{
		std::cout << "Wall" << std::endl;
		Obstacle* obstacle2 = new Obstacle("../Assets/textures/bricks2.png", "bricks2");
		inFile >> x >> y >> w >> h;
		obstacle2->getTransform()->position = glm::vec2(x, y);
		obstacle2->setWidth(w);
		obstacle2->setHeight(h);
		addChild(obstacle2, 0);
		m_pObstacles.push_back(obstacle2);
	}


	for (int i = 0; i < 3; i++)
	{
		std::cout << "grass" << std::endl;
		Obstacle* obstacle3 = new Obstacle("../Assets/textures/grass2.png", "grass2");
		inFile >> x >> y >> w >> h;
		obstacle3->getTransform()->position = glm::vec2(x, y);
		obstacle3->setWidth(w);
		obstacle3->setHeight(h);
		addChild(obstacle3, 0);
		m_pObstacles.push_back(obstacle3);
	}

	for (int i = 0; i < 4; i++)
	{
		std::cout << "rocks" << std::endl;
		Obstacle* obstacle4 = new Obstacle("../Assets/textures/rocks2.png", "rocks2");
		inFile >> x >> y >> w >> h;
		obstacle4->getTransform()->position = glm::vec2(x, y);
		obstacle4->setWidth(w);
		obstacle4->setHeight(h);
		addChild(obstacle4, 0);
		m_pObstacles.push_back(obstacle4);
	}
	std::cout << "water" << std::endl;
	Obstacle* obstacle5 = new Obstacle("../Assets/textures/mountain.png", "mountain");
	inFile >> x >> y >> w >> h;
	obstacle5->getTransform()->position = glm::vec2(x, y);
	obstacle5->setWidth(w);
	obstacle5->setHeight(h);
	addChild(obstacle5, 0);
	m_pObstacles.push_back(obstacle5);

	inFile.close();
}

void PlayScene::m_createBullets()
{
	Bullet* bullet = new Bullet(m_pSpaceShip->getTransform()->position, m_pSpaceShip->getCurrentDirection(), 30.0f);
	addChild(bullet, 1);
	m_pBullets.push_back(bullet);

}

void PlayScene::GUI_Function()
{
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);

	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Assignment 3 Debug Properties", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Separator();

	if (ImGui::Checkbox("Toggle Grid", &m_isGridEnabled))
	{
		m_toggleGrid(m_isGridEnabled);
	}

	ImGui::Separator();
	if (ImGui::Button("Node LOS Target", { 300, 20 }))
	{
		m_LOSMode = 0;
	}

	if (m_LOSMode == 0)
	{
		ImGui::SameLine();
		ImGui::Text("<Active>");
	}

	if (ImGui::Button("Node LOS SpaceShip", { 300, 20 }))
	{
		m_LOSMode = 1;
	}

	if (m_LOSMode == 1)
	{
		ImGui::SameLine();
		ImGui::Text("<Active>");
	}

	if (ImGui::Button("Node LOS to both Target and SpaceShip", { 300, 20 }))
	{
		m_LOSMode = 2;
	}

	if (m_LOSMode == 2)
	{
		ImGui::SameLine();
		ImGui::Text("<Active>");
		ImGui::Checkbox("Toggle Find Shortest Path", &m_isShortestPathEnabled);
	}

	if (ImGui::SliderInt("Path Node LOS Distance", &m_pathNodeLOSDistance, 0, 1000))
	{
		m_setPathNodeLOSDistance(m_pathNodeLOSDistance);
	}


	ImGui::Separator();
	// spaceship properties

	static int shipPosition[] = { m_pSpaceShip->getTransform()->position.x, m_pSpaceShip->getTransform()->position.y };
	if (ImGui::SliderInt2("Ship Position", shipPosition, 0, 600))
	{
		 m_pSpaceShip->getTransform()->position.x = shipPosition[0];
		m_pSpaceShip->getTransform()->position.y = shipPosition[1];
	}

	// allow the ship to rotate
	static int angle;
	if (ImGui::SliderInt("Ship Direction", &angle, -360, 360))
	{
		m_pSpaceShip->setCurrentHeading(angle);
	}

	ImGui::Separator();

	// Target properties

	static int targetPosition[] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y };
	if (ImGui::SliderInt2("Target Position", targetPosition, 0, 600))
	{
		//targetPosition[0]
		m_pTarget->getTransform()->position.x = targetPosition[0];
		m_pTarget->getTransform()->position.y = targetPosition[1];
	}

	ImGui::Separator();


	if (ImGui::SliderInt("Obstacle Buffer", &m_obstacleBuffer, 0, 100))
	{
		m_buildGrid();
	}

	ImGui::Separator();
	// Add Obstacle Position Control for all obstacles
	for (unsigned i = 0; i < m_pObstacles.size(); ++i)
	{
		int obstaclePosition[] = { m_pObstacles[i]->getTransform()->position.x, m_pObstacles[i]->getTransform()->position.y };
		std::string label = "Obstacle" + std::to_string(i + 1) + " Position";
		if (ImGui::SliderInt2(label.c_str(), obstaclePosition, 0, 800))
		{
			m_pObstacles[i]->getTransform()->position.x = obstaclePosition[0];
			m_pObstacles[i]->getTransform()->position.y = obstaclePosition[1];
			//if (i == 1)
			//{
			//	m_pMountain->getTransform()->position = glm::vec2(obstaclePosition[0], obstaclePosition[1]);
			//}
			m_buildGrid();
		}
	}



	ImGui::End();
}