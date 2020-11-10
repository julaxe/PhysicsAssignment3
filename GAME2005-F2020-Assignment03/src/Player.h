#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "Sprite.h"
#include "Label.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void moveStopX();
	void moveStopY();

	float checkDistance(GameObject* pGameObject);

private:
	const float ACELLERATION = 10.0f;
	glm::vec2 m_direction; 
};

#endif /* defined (__PLAYER__) */