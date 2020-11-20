#pragma once
#include "glm/vec2.hpp"
#include "UnOrderedArray.h"
#include "Util.h"
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
		GenerateVertices();
		UpdateVerticesPosition();
	}
	void Draw()
	{
		if(NVertices >= 3)
		{
			for (int i = 0; i < NVertices-1; i++)
			{
				Util::DrawLine((*Vertices)[i], (*Vertices)[i+1], {0,0,0,1});
			}
			Util::DrawLine((*Vertices)[NVertices - 1], (*Vertices)[0], {0,0,0,1});
		}else
		{
			Util::DrawCircle(Position, radius, {0,0,0,1});
		}
	}
	void UpdateVerticesPosition()
	{
		for (int i = 0; i < NVertices; i++)
		{
			(*Vertices)[i] += Position;
		}
	}
	
	void ChangePolygon(int NumberOfVertices)
	{
		NVertices = NumberOfVertices;
		if(NVertices >= 3)
		{
			Vertices->clear();
			GenerateVertices();
			UpdateVerticesPosition();
		}
	}
	
private:
	void GenerateVertices()
	{
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
private:
	int radius;
	int NVertices;
	glm::vec2 Position;
	UnorderedArray<glm::vec2>* Vertices;
};