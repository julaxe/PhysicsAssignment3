#include "Brick.h"
#include "Config.h"
#include "Util.h"

Brick::Brick()
{
	height = 150.f;
	width = 75.f;
	color = {0,0,0,1};
	Position = {Config::SCREEN_WIDTH * 0.2, Config::SCREEN_HEIGHT * 0.7};
	Vertices = new glm::vec2[4];
	lines = new UnorderedArray<Line>(4);
	readyToCollide = true;
	time = 0.0f;
	
	GenerateVertices();
	GenerateLines();
	UpdateLinesPoisition();
}

Brick::~Brick()
{
	//Delete pointers? clean arrays?
}

void Brick::Draw()
{
	for (int i = 0; i < 4; i++)
	{
		Util::DrawLine((*lines)[i].Start(), (*lines)[i].End(), (*lines)[i].Color());
	}
}

void Brick::Update()
{

}


glm::vec2 Brick::GetPosition()
{
	return Position;
}

float Brick::GetHeight()
{
	return height;
}
float Brick::GetWidth()
{
	return width;
}

void Brick::GenerateVertices()
{
	//Generate Vertices
	Vertices[0] = {width * -0.5, height * -0.5};
	Vertices[1] = {width * 0.5, height * -0.5};
	Vertices[2] = {width * 0.5, height * 0.5};
	Vertices[3] = {width * -0.5, height * 0.5};
}

void Brick::GenerateLines()
{
	lines->clear();
	//Generate Lines
	for (int i = 0; i < 3; i++)
	{
		lines->push(Line(Vertices[i], Vertices[i+1], color));
	}
	lines->push(Line(Vertices[3], Vertices[0], color));
}

void Brick::UpdateLinesPoisition()
{
	for (int i = 0; i < 4; i++)
	{
		(*lines)[i].Start() += Position;
		(*lines)[i].End() += Position;
	}
}

void Brick::SetPosition(glm::vec2 newPos)
{
	Position = newPos;
	GenerateLines();
	UpdateLinesPoisition();
}

glm::vec2* Brick::GetVertices()
{
	return Vertices;
}

void Brick::SetColor(glm::vec4 newColor)
{
	color = newColor;
}

UnorderedArray<Line>& Brick::getLines()
{
	return (*lines);
}

