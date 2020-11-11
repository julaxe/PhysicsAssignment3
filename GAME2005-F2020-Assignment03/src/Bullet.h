#pragma once
#ifndef __Bullet__
#define __Bullet__

#include "Sprite.h"

class Bullet : public Sprite
{
public:
	Bullet();
	~Bullet();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void isBeingUsed();
	void isNotUsed();
	bool Used();
	void Init();

private:
	bool used;
};

#endif


