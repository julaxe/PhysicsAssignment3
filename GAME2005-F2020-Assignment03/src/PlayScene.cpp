#include "PlayScene.h"

#include <imgui_sdl.h>
#include "imgui.h"

#include "Game.h"
#include "EventManager.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 0.0f, 0.0f);
	
	drawDisplayList();

	
	m_pBulletPool->Draw();
	
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void PlayScene::update()
{
	updateDisplayList();
	m_pBulletPool->Update();
	m_pBulletPool->checkCollision(m_pPlayer);
	const float deltaTime = 1.0f / 60.f;
	
	if(timer >= *m_paramsImGui->timeToRespawn) // 0.1 seconds
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
	//background
	TextureManager::Instance()->load("../Assets/sprites/backgroundA2.png", "background");

	//ImGUI params
	m_paramsImGui = new ParamsIMGUI(0.1, 10);
	timer = 0;
	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	

	// Bullet Pool
	m_pBulletPool = new BulletPool(10);

	SoundManager::Instance().load("../Assets/audio/thud2.wav", "Hit", SOUND_SFX);
	
}

void PlayScene::GUI_Function() const
{
	
	// Always open with a NewFrame
	ImGui::NewFrame();
	
	ImGui::Begin("Physics Simulation Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	ImGui::Text("1 pixel is 1 meter");
	
	ImGui::Separator();
	ImGui::DragFloat("Delay", m_paramsImGui->timeToRespawn,0.01f,0.01f, 3.f);
	if(ImGui::InputInt("Pool Size", m_paramsImGui->newSizePool))
	{
		m_pBulletPool->SetNewSize(*m_paramsImGui->newSizePool);
	}

	
	
	ImGui::Separator();
	if(ImGui::Button("Level 2"))
	{
		TheGame::Instance()->changeSceneState(BOUNCING_SCENE);
	}
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();

	
}
