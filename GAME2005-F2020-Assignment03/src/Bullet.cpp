#include "Bullet.h"
#include "TextureManager.h"
#include "Util.h"

Bullet::Bullet() {
	TextureManager::Instance()->load("../Assets/textures/bullet.png", "Bullet");

	auto size = TextureManager::Instance()->getTextureSize("Bullet");
	setWidth(size.x);
	setHeight(size.y);

	Init();
	isNotUsed();
	getRigidBody()->isColliding = false;
	setType(BULLET);
}

Bullet::~Bullet()
= default;

void Bullet::draw() {
	// alias for x and y
	if(used)
	{
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		TextureManager::Instance()->draw("Bullet", x, y, 0, 255, true);
	}
}

void Bullet::update() {
	
	if(used)
	{
		const float deltaTime = 1.0f / 60.f;
		getRigidBody()->velocity += getRigidBody()->acceleration;
		glm::vec2 pos = getTransform()->position;
		pos.x += getRigidBody()->velocity.x * deltaTime;
		pos.y += getRigidBody()->velocity.y * deltaTime;

		getTransform()->position = pos;
		if(pos.y > Config::SCREEN_HEIGHT)
		{
			isNotUsed();
		}
	}
}

void Bullet::clean() {

}

void Bullet::isBeingUsed()
{
	used = true;
}
void Bullet::isNotUsed()
{
	used = false;
}

bool Bullet::Used()
{
	return used;
}

void Bullet::Init()
{
	getTransform()->position = glm::vec2(Util::RandomRange(0,Config::SCREEN_WIDTH), 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 9.8f);
}
