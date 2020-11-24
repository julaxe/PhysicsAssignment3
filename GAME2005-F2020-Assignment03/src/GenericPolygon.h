#pragma once
#include "UnOrderedArray.h"
#include "Util.h"
#include "Config.h"
#include "Line.h"
//360 / N of vertices.

class GenericPolygon
{
public:
	GenericPolygon(int NumberOfVeritces, int Radius)
	{
		NVertices = NumberOfVeritces;
		radius = Radius;
		Vertices = new UnorderedArray<glm::vec2>(NumberOfVeritces);
		Position = {Config::SCREEN_WIDTH*0.5, Config::SCREEN_HEIGHT*0.5};
		lines = new UnorderedArray<Line>(NumberOfVeritces);
		color = {0,0,0,1}; //Black default
		
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
	
private:
	void GenerateVertices()
	{
		Vertices->clear();
		if(NVertices >= 3)
		{
			float const Constangle = 360/NVertices;
			float angle = 0;
			
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
	glm::vec2 Position;
	UnorderedArray<glm::vec2>* Vertices;
	UnorderedArray<Line>* lines;
	glm::vec4 color;
	
};