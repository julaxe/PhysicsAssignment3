#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	m_pBulletPool->Draw();
}

void PlayScene::update()
{
	updateDisplayList();
	m_pBulletPool->Update();
	m_pBulletPool->checkCollision(m_pPlayer);
	const float deltaTime = 1.0f / 60.f;
	
	if(timer >= 0.1f) // 3 seconds
	{
		timer = 0;
		m_pBulletPool->Use();
	}
	timer += deltaTime;
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{	

	EventManager::Instance().update();

		
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->moveLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{		
		m_pPlayer->moveRight();
	}
	else
	{
		m_pPlayer->moveStopX();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_pPlayer->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		m_pPlayer->moveDown();
	}

	else
	{
		m_pPlayer->moveStopY();
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	timer = 0;
	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);

	// Bullet Pool
	m_pBulletPool = new BulletPool(10);
	
}
