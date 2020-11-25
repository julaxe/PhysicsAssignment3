#pragma once
#include "Brick.h"
#include "Util.h"
#include "Config.h"

//360 / N of vertices.
struct Borders
{
	Borders()
	{
		Vertices = new glm::vec2[4];
		lines = new UnorderedArray<Line>(4);
		color = {0,0,0,1};
		GenerateVertices();
		GenerateLines();
	}

	void GenerateVertices()
	{
		Vertices[0] = {0,0};
		Vertices[1] = {Config::SCREEN_WIDTH, 0};
		Vertices[2] = {Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT};
		Vertices[3] = {0, Config::SCREEN_HEIGHT};
	}
	void GenerateLines()
	{
		lines->clear();
		for (int i = 0; i < 3; i++)
		{
			lines->push(Line(Vertices[i], Vertices[i+1],color ));
		}
		lines->push(Line(Vertices[3], Vertices[0],color ));
	}

	UnorderedArray<Line>& getLines()
	{
		return (*lines);
	}
	glm::vec4 color;
	glm::vec2* Vertices;
	UnorderedArray<Line>* lines;
};

class GenericPolygon
{
public:
	GenericPolygon(int NumberOfVeritces, int Radius)
	{
		NVertices = NumberOfVeritces;
		radius = Radius;
		Vertices = new UnorderedArray<glm::vec2>(NumberOfVeritces);
		Position = {Config::SCREEN_WIDTH*0.75, Config::SCREEN_HEIGHT*0.5};
		Velocity = {0,0};
		lines = new UnorderedArray<Line>(NumberOfVeritces);
		color = {0,0,0,1}; //Black default
		MAX_VELOCITY = 300.f
		;
		GenerateVertices();
		UpdateVerticesPosition();
		GenerateLines();
	}
	void Draw()
	{
		if(NVertices >= 3)
		{
			for (int i = 0; i < NVertices; i++)
			{
				Util::DrawLine((*lines)[i].Start(), (*lines)[i].End(), (*lines)[i].Color());
			}
		}else
		{
			Util::DrawCircle(Position, radius, color);
		}
	}
	void Update()
	{
		float deltaTime = 1.f/60.0f;
		Position += Velocity*deltaTime;
		
		GenerateVertices();
		UpdateVerticesPosition();
		GenerateLines();
	}
	
	void ChangePolygon(int NumberOfVertices)
	{
		NVertices = NumberOfVertices;
		if(NVertices >= 3)
		{
			GenerateVertices();
			UpdateVerticesPosition();
			GenerateLines();
		}
	}
	
	UnorderedArray<glm::vec2>* GetVertices()
	{
		return Vertices;
	}
	UnorderedArray<Line>& getLines()
	{
		return (*lines);
	}

	void ResetColor()
	{
		for (int i = 0; i < NVertices; i++)
		{
			getLines()[i].Color() = {0,0,0,1};
		}
	}
	void Bounce(float absortion, int line)
	{
		//Bouncing with walls
		if(line == 1 || line == 3) //colliding X axis
		{
			Velocity = absortion*glm::vec2(Velocity.x*-1.f, Velocity.y);
		}
		else
		{
			Velocity = absortion*glm::vec2(Velocity.x, Velocity.y*-1.f);
		}
	}

	glm::vec2 getPosition()
	{
		return Position;
	}
	void addVelocity(glm::vec2 vel)
	{
		if(Util::magnitude(Velocity) < MAX_VELOCITY)
		{
			Velocity += vel;
		}
	}
	void FixPosition(int lineNumber) // Borders of the screen
	{
		if(lineNumber == 0)
			Position = {Position.x, radius + 1};
		else if(lineNumber == 1)
			Position = {Config::SCREEN_WIDTH - radius - 1, Position.y};
		else if(lineNumber == 2)
			Position = {Position.x , Config::SCREEN_HEIGHT - radius - 1};
		else if(lineNumber == 3)
			Position = {radius + 1, Position.y};
	}
	void FixPosition(int lineNumber, Brick* brick)
	{
		switch (lineNumber)
		{
		case 0:
			Position = {Position.x, brick->GetPosition().y - brick->GetHeight()*0.5 - radius - 1};
			break;
		case 1:
			Position = {brick->GetPosition().x + brick->GetWidth()*0.5 + radius+ 1, Position.y};
			break;
		case 2:
			Position = {Position.x, brick->GetPosition().y + brick->GetHeight()*0.5 + + radius+ 1};
			break;
		case 3:
			Position = {brick->GetPosition().x - brick->GetWidth()*0.5 - radius - 1, Position.y};
			break;
		default:
			break;
		}
	}
	glm::vec2 GetVelocity()
	{
		return Velocity;
	}
private:
	void GenerateVertices()
	{
		Vertices->clear();
		if(NVertices >= 3)
		{
			float const Constangle = 360/NVertices;
			float angle = 20;
			
			for (int i = 0; i < NVertices; i++)
			{
				glm::vec2 newVertice = {radius*cos(angle* Util::Deg2Rad), radius*sin(angle* Util::Deg2Rad)};
				Vertices->push(newVertice);
				angle += Constangle;
			}
		}
	}
	void GenerateLines()
	{
		lines->clear();
		//Generate Lines
		for (int i = 0; i < NVertices-1; i++)
		{
			lines->push(Line((*Vertices)[i], (*Vertices)[i+1], color));
		}
		lines->push(Line((*Vertices)[NVertices-1], (*Vertices)[0], color));
	}
	void UpdateVerticesPosition()
	{
		for (int i = 0; i < NVertices; i++)
		{
			(*Vertices)[i] += Position;
		}
	}
private:
	int radius;
	int NVertices;
	float MAX_VELOCITY;
	glm::vec2 Position;
	glm::vec2 Velocity;
	UnorderedArray<glm::vec2>* Vertices;
	UnorderedArray<Line>* lines;
	glm::vec4 color;
	
};