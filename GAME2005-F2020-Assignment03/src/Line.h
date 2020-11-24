#pragma once
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

class Line
{
public:
	Line()
	{
		vertices = new glm::vec2[2];
		collisionPoint = {0,0};
		colliding = false;
	}
	Line(glm::vec2 start, glm::vec2 end, glm::vec4 color)
	{
		vertices = new glm::vec2[2];
		vertices[0] = start;
		vertices[1] = end;
		this->color = color;
		collisionPoint = {0,0};
		colliding = false;
	}
	glm::vec2& Start()
	{
		return vertices[0];
	}
	glm::vec2& End()
	{
		return vertices[1];
	}
	glm::vec4& Color()
	{
		return color;
	}
	bool& isColliding()
	{
		return colliding;
	}
	glm::vec2& PointOfCollision()
	{
		return collisionPoint;
	}
private:
	glm::vec2* vertices;
	glm::vec4 color;
	bool colliding;
	glm::vec2 collisionPoint;
};