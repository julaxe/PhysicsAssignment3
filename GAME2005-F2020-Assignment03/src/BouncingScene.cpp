#include "BouncingScene.h"

#include <imgui_sdl.h>


#include "EventManager.h"
#include "Game.h"
#include "imgui.h"

#include "CollisionManager.h"

#include "TextureManager.h"

BouncingScene::BouncingScene()
{
	BouncingScene::start();
}

BouncingScene::~BouncingScene()
{
}

void BouncingScene::draw()
{
	TextureManager::Instance()->draw("background", 0.0f, 0.0f);
	
	//drawDisplayList();

	m_pBrick->Draw();
	m_GenPolygon->Draw();

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void BouncingScene::update()
{
	checkCollision();
}

void BouncingScene::clean()
{
}

void BouncingScene::handleEvents()
{
	EventManager::Instance().update();

	m_pMousePos[1] = m_pMousePos[0];
	m_pMousePos[0] = EventManager::Instance().getMousePosition();

	m_pBrick->SetPosition(m_pMousePos[0]);

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void BouncingScene::start()
{
	//background
	TextureManager::Instance()->load("../Assets/sprites/backgroundA2.png", "background");
	m_pMousePos = new glm::vec2[2];
	m_pBrick = new Brick();
	m_pNumberVertices = new int(3);
	m_GenPolygon = new GenericPolygon(*m_pNumberVertices,50);
}

void BouncingScene::checkCollision()
{
	for (int i = 0; i < 3; i++) //every line of the brick
	{
		for (int k = 0; k < *m_pNumberVertices - 1; k++)
		{
			if(CollisionManager::lineLineCheck(m_pBrick->GetVertices()[i],
				m_pBrick->GetVertices()[i+1],
				(*m_GenPolygon->GetVertices())[k],
				(*m_GenPolygon->GetVertices())[k+1]))
			{
				m_pBrick->SetColor({1,0,0,1});
				return;
			}
		}
		if(CollisionManager::lineLineCheck(m_pBrick->GetVertices()[i],
				m_pBrick->GetVertices()[i+1],
				(*m_GenPolygon->GetVertices())[*m_pNumberVertices - 1],
				(*m_GenPolygon->GetVertices())[0]))
		{
			m_pBrick->SetColor({1,0,0,1});
			return;
		}
	}
	for (int k = 0; k < *m_pNumberVertices - 1; k++)
	{
		if(CollisionManager::lineLineCheck(m_pBrick->GetVertices()[3],
			m_pBrick->GetVertices()[0],
			(*m_GenPolygon->GetVertices())[k],
			(*m_GenPolygon->GetVertices())[k+1]))
		{
			m_pBrick->SetColor({1,0,0,1});
			return;
		}
	}
	if(CollisionManager::lineLineCheck(m_pBrick->GetVertices()[3],
			m_pBrick->GetVertices()[0],
			(*m_GenPolygon->GetVertices())[*m_pNumberVertices - 1],
			(*m_GenPolygon->GetVertices())[0]))
	{
		m_pBrick->SetColor({1,0,0,1});
		return;
	}
	m_pBrick->SetColor({0,0,0,1});
}

void BouncingScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();
	
	ImGui::Begin("Physics Simulation Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	ImGui::Text("1 pixel is 1 meter");
	
	ImGui::Separator();
	if(ImGui::InputInt("Polygon", m_pNumberVertices))
	{
		m_GenPolygon->ChangePolygon(*m_pNumberVertices);
	}

	ImGui::Separator();
	if(ImGui::Button("Level 1"))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();

}
