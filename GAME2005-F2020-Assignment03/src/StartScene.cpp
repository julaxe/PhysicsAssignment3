#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	TextureManager::Instance()->draw("background", 0.0f, 0.0f);
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	TextureManager::Instance()->load("../Assets/sprites/backgroundA2.png", "background");


	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color strongGreen = { 10, 115, 20, 255 };
	m_pStartLabel = new Label("THE VACUUM FOREST", "Consolas", 60, strongGreen, glm::vec2(400.0f, 200.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pStudent1 = new Label("Julian Escobar 101286557", "Consolas", 20, strongGreen, glm::vec2(400.0f, 270.0f));
	m_pStudent1->setParent(this);
	addChild(m_pStudent1);

	m_pStudent2 = new Label("Lucas Krespi 101289546", "Consolas", 20, strongGreen, glm::vec2(400.0f, 290.0f));
	m_pStudent2->setParent(this);
	addChild(m_pStudent2);

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f);

	m_pStartButton->addEventListener(CLICK, [&]()-> void
		{
			m_pStartButton->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pStartButton->setAlpha(128);
		});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pStartButton->setAlpha(255);
		});
	addChild(m_pStartButton);

	
}

