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
}

void PlayScene::update()
{
	updateDisplayList();
	//distance Label
	if (m_pPlayer->checkDistance(m_pEnemy) <= (m_pPlayer->getHeight() * 0.5f + m_pEnemy->getHeight() * 0.5f))
	{
		m_pDistanceLabel->setText("Distance = HIT!!!    " );
	}
	else {

		m_pDistanceLabel->setText("Distance = " + std::to_string(m_pPlayer->checkDistance(m_pEnemy)));
	}
	//Velocity Label
	m_pVelocityLabel->setText("Velocity = " + std::to_string(Util::magnitude(m_pPlayer->getRigidBody()->velocity)));


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
	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	
	// Enemy Sprite
	m_pEnemy = new Enemy();
	addChild(m_pEnemy);

	// Label
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pDistanceLabel = new Label("Distance", "Consolas", 40, blue, glm::vec2(400.0f, 40.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);

	m_pVelocityLabel = new Label("Velocity", "Consolas", 40, blue, glm::vec2(400.0f, 80.0f));
	m_pVelocityLabel->setParent(this);
	addChild(m_pVelocityLabel);
}
