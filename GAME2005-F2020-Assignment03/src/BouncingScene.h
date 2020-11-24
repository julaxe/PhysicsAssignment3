#pragma once
#include "Scene.h"
#include "GenericPolygon.h"
#include "Brick.h"
class BouncingScene : public Scene
{
public:
	BouncingScene();
	~BouncingScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void checkCollision();
	void CollisionPointAlg(Line line1, Line line2);
	glm::vec2 CollisionPoint(Line line1, Line line2);
private:
	// IMGUI Function
	void GUI_Function() const;
	glm::vec2* m_pMousePos;
	
	Brick* m_pBrick;
	GenericPolygon* m_GenPolygon;
	UnorderedArray<glm::vec2>* CollisionPoints;
	int* m_pNumberVertices;

};
