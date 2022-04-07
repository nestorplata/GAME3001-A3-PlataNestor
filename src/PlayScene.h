#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Heuristic.h"
#include "Label.h"

#include "Target.h"
#include "SpaceShip.h"
#include "Obstacle.h"
#include "PathNode.h"
#include "Bullet.h"
#include "LifeBar.h"

#include <stdlib.h> 
#include <time.h>
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;


	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color red = { 255, 0, 0, 255 };
	const SDL_Color green = { 0, 255, 0, 255 };

	bool m_isGridEnabled;
	bool m_isKeyHdown = true;
	bool m_isKeyKdown = true;
	bool m_isKeyPdown = true;
	bool m_isLowerFacedown = true;
	bool m_isRightFacedown = true;



	bool m_isShortestPathEnabled =false;
	bool m_isTargetIdle = true;
	bool m_isPlayerIdle = true;

	bool m_isGoingLeft =false;
	bool m_isGoingUp=true;

	bool m_isPlayerDetected;

	bool m_deathsoundplayed= false;
	
	int enemiesDefeated;
	// Game Objects
	Target* m_pTarget;
	SpaceShip* m_pSpaceShip;
	LifeBar* m_pSpaceShipLifeBar;
	LifeBar* m_pEnemyLifeBar;

	Label* m_pEnemiesLeft;
	Label* m_pEnemiesDefeated;

	std::vector<PathNode*> m_pGrid;
	std::vector<PathNode*> m_pPatrolCorners[4];

	PathNode* Choosen;

	std::vector<Obstacle*> m_pObstacles;	
	std::vector<Bullet*> m_pBullets;


	TargetMovement MovementType;

	void m_buildGrid();

	void m_toggleGrid(const bool state);
	bool m_checkAgentLOS(Agent* agent, DisplayObject* target_object);
	bool m_checkPathNodeLOS(PathNode* path_node, DisplayObject* target_object);
	void m_checkAllNodesWithTarget(DisplayObject* target_object);
	void m_checkAllNodesWithBoth();
	void m_setPathNodeLOSDistance(int dist);
	int m_LOSMode;
	void m_clearNodes();
	void m_createObstaclesFromFile();
	void m_createBullets();


	int m_obstacleBuffer;
	int m_pathNodeLOSDistance;
	int angle;
	glm::vec2 ShortestpathNode;
};

#endif /* defined (__PLAY_SCENE__) */