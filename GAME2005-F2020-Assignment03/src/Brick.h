#pragma once
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

class Brick
{
public:
	Brick();
	~Brick();

	void Draw();
	void Update();
	
	void GenerateVertices();
	void UpdateVerticesPosition();

	void SetPosition(glm::vec2 newPos);

	glm::vec2* GetVertices();
	void SetColor(glm::vec4 newColor);
	
private:
	glm::vec4 color;
	float height;
	float width;
	glm::vec2 Position;
	glm::vec2* Vertices;
};
