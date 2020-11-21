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
	GenerateVertices();
	UpdateVerticesPosition();
}

Brick::~Brick()
{
}

void Brick::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		Util::DrawLine(Vertices[i], Vertices[i+1], color);
	}
	Util::DrawLine(Vertices[3], Vertices[0], color);
}

void Brick::Update()
{
	
}

void Brick::GenerateVertices()
{
	Vertices[0] = {width * -0.5, height * -0.5};
	Vertices[1] = {width * 0.5, height * -0.5};
	Vertices[2] = {width * 0.5, height * 0.5};
	Vertices[3] = {width * -0.5, height * 0.5};
}

void Brick::UpdateVerticesPosition()
{
	for (int i = 0; i < 4; i++)
	{
		Vertices[i] += Position;
	}
}

void Brick::SetPosition(glm::vec2 newPos)
{
	Position = newPos;
	GenerateVertices();
	UpdateVerticesPosition();
}

glm::vec2* Brick::GetVertices()
{
	return Vertices;
}

void Brick::SetColor(glm::vec4 newColor)
{
	color = newColor;
}

