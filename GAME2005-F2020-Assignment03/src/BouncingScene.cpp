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
	for (int i = 0; i < CollisionPoints->GetSize(); i++)
	{
		Util::DrawCircle((*CollisionPoints)[i], 10, {0,0,0,1});
	}

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
	CollisionPoints = new UnorderedArray<glm::vec2>(3);
}

void BouncingScene::checkCollision() //Line by Line
{
	CollisionPoints->clear();
	m_GenPolygon->ResetColor();
	for (int i = 0; i < 4; i++) //every line of the brick
	{
		bool LineColliding = false; // bool for every Brick Line Color
		for (int k = 0; k < *m_pNumberVertices; k++)
		{
			if(CollisionManager::lineLineCheck(m_pBrick->getLines()[i].Start(),
				m_pBrick->getLines()[i].End(),
				m_GenPolygon->getLines()[k].Start(),
				m_GenPolygon->getLines()[k].End()))
			{
				m_GenPolygon->getLines()[k].Color() = {1,0,0,1}; //Turn Red
				LineColliding = true;
				//Check exactly position
				CollisionPoints->push(CollisionPoint(m_pBrick->getLines()[i],m_GenPolygon->getLines()[k]));
			}
		}
		
		if(LineColliding)
			m_pBrick->getLines()[i].Color() = {1,0,0,1}; //Turn Red;
		else
			m_pBrick->getLines()[i].Color() = {0,0,0,1}; //Turn Red
	}
}

//Algebra
void BouncingScene::CollisionPointAlg(Line line1, Line line2)
{
	float l1x0 = line1.Start().x;
	float l1x1 = line1.End().x;
	float l1y0 = line1.Start().y;
	float l1y1 = line1.End().y;

	float l2x0 = line2.Start().x;
	float l2x1 = line2.End().x;
	float l2y0 = line2.Start().y;
	float l2y1 = line2.End().y;


	//m = y1-y0/x1-x0
	float l1m = (l1y1 - l1y0)/(l1x1-l1x0);
	float l2m = (l2y1 - l2y0)/(l2x1-l2x0);

	//point of intersection

	//Line equation  y - y0 = m(x - x0)
	//y = mx - mx0 + y0
	//m1x - m1l1x0 + l1y0 = m2x - m2l2x0 + l2y0
	//(m1 - m2)x = -m2l2x0 + l2y0 + m1l1x0 - l1y0
	//x = (-m2l2x0 + l2y0 + m1l1x0 - l1y0) / (m1 - m2)
	//y = m1x - m1l1x0 + l1y0
	float x = (-l2m*l2x0 + l2y0 + l1m*l1x0 - l1y0)/(l1m - l2m);
	float y = l1m*x - l1m*l1x0 + l1y0;

	Util::DrawCircle({x,y},10,{0,0,0,1});
}

glm::vec2 BouncingScene::CollisionPoint(Line line1, Line line2)
{
	//Directions of each line. (unit vector)
	//Line1
	glm::vec2 directionL1 = Util::normalize({line1.End().x - line1.Start().x,
							line1.End().y - line1.Start().y});
	//Line2
	glm::vec2 directionL2 = Util::normalize({line2.End().x - line2.Start().x,
							line2.End().y - line2.Start().y});

	float scale = 1; //how much is going to increase every cycle
	glm::vec2 L1Iterator = line1.Start();
	glm::vec2 L2Iterator = line2.Start();

	bool collision = false;

	while(Util::magnitude(line1.End() - L1Iterator) > 1 && !collision)
	{
		L2Iterator = line2.Start();
		float differenceL2 = Util::magnitude(line2.End() - L2Iterator);
		
		while(differenceL2 > 1 && !collision)
		{
			if(Util::magnitude(L1Iterator - L2Iterator) < 2)
				collision = true;
			
			L2Iterator += directionL2*scale;
			differenceL2 = Util::magnitude(line2.End() - L2Iterator);
		}
		L1Iterator += directionL1*scale;
	}
	if(collision)
		return L1Iterator;
	return line1.Start() + (line1.End()-line1.Start())*0.5f;
	
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
