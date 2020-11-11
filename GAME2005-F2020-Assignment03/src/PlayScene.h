#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"
#include "BulletPool.h"

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
	
	glm::vec2 m_mousePosition;

	Player* m_pPlayer;
	BulletPool* m_pBulletPool;

	float timer;
};

#endif /* defined (__PLAY_SCENE__) */