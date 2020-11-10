#include "Player.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player()
{
	TextureManager::Instance()->load("../Assets/textures/circle.png", "circle");
	
	auto size = TextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}

void Player::update()
{
	const float deltaTime = 1.0f / 60.f;

	if (Util::magnitude(m_direction) > 0)
	{
		getRigidBody()->acceleration = Util::normalize(m_direction) * ACELLERATION;
	}
	else if (Util::magnitude(getRigidBody()->velocity) > 0)
	{
		getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity) * -ACELLERATION;
		if (Util::magnitude(getRigidBody()->velocity) <= ACELLERATION )
		{
			getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
			getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
		}
	}

		getRigidBody()->velocity += getRigidBody()->acceleration;
		glm::vec2 pos = getTransform()->position;
		pos.x += getRigidBody()->velocity.x * deltaTime;
		pos.y += getRigidBody()->velocity.y * deltaTime;

		getTransform()->position = pos; 
}

void Player::clean()
{

}

void Player::moveLeft() {
	m_direction.x = -1;
}

void Player::moveRight() {
	m_direction.x = 1;
}

void Player::moveUp()
{
	m_direction.y = -1;
}

void Player::moveDown()
{
	m_direction.y = 1;
}

void Player::moveStopX()
{
	m_direction.x = 0;
}

void Player::moveStopY()
{
	m_direction.y = 0;
}

float Player::checkDistance(GameObject* pGameObject) {

	float a = pGameObject->getTransform()->position.x - getTransform()->position.x;
	float b = pGameObject->getTransform()->position.y - getTransform()->position.y;
	return sqrt(a*a + b*b);
}
