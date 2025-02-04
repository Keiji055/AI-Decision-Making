#include "stdafx.h"

#include "GameWorld.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include "PollingStation.h"
#include "CommonUtilities/Vector.hpp"
#include "Wall.h"
#include "StateStackRobot.h"
#include "DesitionTreeRobot.h"


using namespace CommonUtilities;


GameWorld::GameWorld()
{
}

GameWorld::~GameWorld() 
{

}


void GameWorld::Init()  
{
	auto& engine = *Tga::Engine::GetInstance();
	Tga::Vector2ui intResolution = engine.GetRenderSize();
	myResolution = { (float)intResolution.x, (float)intResolution.y };
	
	myWalls.resize(2);
	myWalls[0] = std::make_shared<Wall>();
	myWalls[1] = std::make_shared<Wall>();

	myHealthPack = std::make_shared<GameObject>();
	myHealthPack->Init(CommonUtilities::Vector2f(50, 50), "Sprites/health.png");
	myHealthPack->GetSprite().Init("Sprites/health.png", { 50, 50 }, 0.2f);
	PollingStation::Get().AddHealthPackPosition(myHealthPack->GetPosition());


	myHealth2Pack = std::make_shared<GameObject>();
	myHealth2Pack->Init(CommonUtilities::Vector2f(1200, 650), "Sprites/health.png");
	myHealth2Pack->GetSprite().Init("Sprites/health.png", { 1200, 650 }, 0.2f);
	PollingStation::Get().AddHealthPack2Position(myHealth2Pack->GetPosition());

	myCar2 = std::make_shared<DesitionTreeRobot>();
	myCar2->Init(CommonUtilities::Vector2f(900,100), "Sprites/robotTree.png");
	myCar2->SetSpawnPosition(CommonUtilities::Vector2f(1200, 100));
	PollingStation::Get().AddSecondRobot(myCar2);

	myCar = std::make_shared<StateStackRobot>();
	myCar->Init(CommonUtilities::Vector2f(800, 500), "Sprites/robotState.png");
	myCar->SetSpawnPosition(CommonUtilities::Vector2f(100, 800));
	PollingStation::Get().AddFirstRobot(myCar);

	myWalls[0]->Init(CommonUtilities::Vector2f(500, 500), "Sprites/rock.png", 100, 100);
	myWalls[1]->Init(CommonUtilities::Vector2f(1000,100), "Sprites/rock.png", 100, 100);
	myWalls[0]->GetSprite().Init("Sprites/rock.png", { 500, 500 }, 0.05f);
	myWalls[1]->GetSprite().Init("Sprites/rock.png", { 1000, 100 }, 0.05f);

	for (auto& wall: myWalls)
	{
		myGameObjects.push_back(wall);
	}

	myGameObjects.push_back(myCar);
	myGameObjects.push_back(myCar2);
	myGameObjects.push_back(myHealthPack);
	myGameObjects.push_back(myHealth2Pack);

	PollingStation::Get().Init(myWalls);

}
void GameWorld::Update(float aTimeDelta)
{
	//myGameObjects[0]->Update(aTimeDelta);
	myCar->Update(aTimeDelta);
	myCar2->Update(aTimeDelta);
	/*for (const auto& gameObject : myGameObjects)
	{
		gameObject->Update(aTimeDelta);
	}*/
}

void GameWorld::Render()
{
	auto &engine = *Tga::Engine::GetInstance();
	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());

	for (const auto& gameObject : myGameObjects)
	{
		gameObject->Render(spriteDrawer);
	}
}