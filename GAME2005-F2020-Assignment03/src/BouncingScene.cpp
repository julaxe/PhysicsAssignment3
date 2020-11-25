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
	Util::DrawLine(m_pMousePos[0], m_pMousePos[1], {1,0,0,1});
	for (int i = 0; i < CollisionPoints->GetSize(); i++)
	{
		Util::DrawCircle((*CollisionPoints)[i].Position, 10, {0,0,0,1});
	}

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void BouncingScene::update()
{
	CollisionPoints->clear();
	
	if(checkCollision(m_pBrick->getLines(), m_GenPolygon->getLines()))
	{
		for (int i = 0; i < CollisionPoints->GetSize(); i++)
		{
			BounceWithCollisionLines((*CollisionPoints)[i], true);
		}
		
		
		//add velocity
		glm::vec2 velocityBrick = (m_pMousePos[0] - m_pMousePos[1])/(1.f/60.f);
		m_GenPolygon->addVelocity(velocityBrick);
		m_pBrick->ReadyToCollide() = false;
	}
	CollisionPoints->clear();
	
	if(checkCollision(m_borders->getLines(), m_GenPolygon->getLines()))
	{
		for (int i = 0; i < CollisionPoints->GetSize(); i++)
		{
			BounceWithCollisionLines((*CollisionPoints)[i], false);
		}
	}

	m_pBrick->Update();
	m_GenPolygon->Update();
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
	m_pNumberVertices = new int(4);
	m_GenPolygon = new GenericPolygon(*m_pNumberVertices,50);
	m_borders = new Borders();
	CollisionPoints = new UnorderedArray<CPoints>(3);
	Absorbtion = new float(0.9f);
}

void BouncingScene::BounceWithCollisionLines(CPoints collisionPoint, bool isBrick)
{
	if(isBrick)
	{
		m_GenPolygon->FixPosition(collisionPoint.Line, m_pBrick);
		m_GenPolygon->Bounce(*Absorbtion, collisionPoint.Line);
	}else
	{
		m_GenPolygon->FixPosition(collisionPoint.Line);
		m_GenPolygon->Bounce(*Absorbtion, collisionPoint.Line);
	}
}

bool BouncingScene::checkCollision(UnorderedArray<Line>& lines1, UnorderedArray<Line>& lines2) //Line by Line
{
	bool collision = false;
	m_GenPolygon->ResetColor();
	for (int i = 0; i < 4; i++) //every line of the brick
	{
		bool LineColliding = false; // bool for every Brick Line Color
		for (int k = 0; k < *m_pNumberVertices; k++)
		{
			if(CollisionManager::lineLineCheck(lines1[i].Start(),
				lines1[i].End(),
				lines2[k].Start(),
				lines2[k].End()))
			{
				lines2[k].Color() = {1,0,0,1}; //Turn Red
				collision = true;
				LineColliding = true;
				//Check exactly position
				CollisionPoints->push(CPoints(CollisionPoint(lines1[i],lines2[k]), i));
				break;
			}
		}
		
		if(LineColliding)
			lines1[i].Color() = {1,0,0,1}; //Turn Red;
		else
			lines1[i].Color() = {0,0,0,1}; //Turn Black
	}
	return collision;
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
	ImGui::InputFloat("Energy Loss", Absorbtion, 0.05f);
	

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
