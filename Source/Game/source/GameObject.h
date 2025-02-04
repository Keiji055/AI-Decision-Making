#pragma once
#include "Sprite.h"
//#include "tge\math\Vector.h"
#include "CommonUtilities/Vector.hpp"

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() {};

	void Init(const CommonUtilities::Vector2f& aStartPosition = CommonUtilities::Vector2f(100.0f,100.0f), std::string aPath = "");
	virtual void Render(Tga::SpriteDrawer& aSpriteDrawer);
	virtual void Update(float aDeltaTime) {};
	void UpdateTransform(const CommonUtilities::Vector2f& aPosition, const float aRotation);
	CommonUtilities::Vector2f GetPosition() const;
	Sprite& GetSprite() { return mySprite; }
	void ResetPosition();
	void SetSpawnPosition(const CommonUtilities::Vector2f& aStartPosition) { myOriginalPosition = aStartPosition; }
	CommonUtilities::Vector2f GetForwardVector() const { return CommonUtilities::Vector2f(cosf(mySprite.GetRotation()), sinf(mySprite.GetRotation())); }

	void TakeDamage(int amountOfDamage = 1);
	void ResetHealth() { myHealth = myMaxHealth; }
	int GetHealth() const { return myHealth; }
	void SetHealth(int aHealth) { myHealth = aHealth; if (myHealth > myMaxHealth){ myHealth = myMaxHealth; } }
	int GetMaxHealth() const { return myMaxHealth; }
private:
	CommonUtilities::Vector2f myPosition;
	Sprite mySprite;
	bool mySpriteAdded;
	int myMaxHealth = 5;
	int myHealth;
	CommonUtilities::Vector2f myOriginalPosition;
};
