#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"
#include "BulletPool.h"

struct ParamsIMGUI
{
	ParamsIMGUI(float time, int newSize)
	{
		timeToRespawn = new float(time);
		newSizePool = new int(newSize);
	}
	float* timeToRespawn;
	int* newSizePool;
};

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
	void GUI_Function() const;
	bool* showBackground;
	
	glm::vec2 m_mousePosition;

	Player* m_pPlayer;
	BulletPool* m_pBulletPool;

	ParamsIMGUI* m_paramsImGui;
	
	float timer;
};

#endif /* defined (__PLAY_SCENE__) */