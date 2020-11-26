#pragma once
#include "Line.h"
#include "UnOrderedArray.h"

class Brick
{
public:
	Brick();
	~Brick();

	void Draw();
	void Update();

	void SetPosition(glm::vec2 newPos);
	glm::vec2 GetPosition();
	void SetVelocity(glm::vec2 newVel);
	glm::vec2 GetVelocity();
	glm::vec2* GetVertices();
	void SetColor(glm::vec4 newColor);
	UnorderedArray<Line>& getLines();
	
	
	
	float GetHeight();
	float GetWidth();
private:
	
	void GenerateVertices();
	void GenerateLines();
	void UpdateLinesPoisition();
private:

	glm::vec4 color;
	float height;
	float width;
	glm::vec2 Position;
	glm::vec2 Velocity;
	glm::vec2* Vertices;
	UnorderedArray<Line>* lines;
};
