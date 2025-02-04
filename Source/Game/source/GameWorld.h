#pragma once
#include <vector>
#include <CommonUtilities/InputHandler.h>

class Wall;
class StateStackRobot;
class DesitionTreeRobot;
class GameObject;

class GameWorld
{
public:
	GameWorld(); 
	~GameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render();



private:
	Tga::Vector2f myResolution;
	//std::array<Wall, 4> myWalls;

	std::vector<std::shared_ptr<Wall>> myWalls;

	std::shared_ptr<StateStackRobot> myCar;
	std::shared_ptr<DesitionTreeRobot> myCar2;
	std::vector<std::shared_ptr<GameObject>> myGameObjects;
	std::shared_ptr<GameObject> myHealthPack;
	std::shared_ptr<GameObject> myHealth2Pack;
};