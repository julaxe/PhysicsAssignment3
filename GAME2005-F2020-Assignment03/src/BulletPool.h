#include "Bullet.h"
#include "DoubleLinkedList.h"
#include "UnOrderedArray.h"
#include "SoundManager.h"
#include <iostream>
class BulletPool
{
public:
	friend class LinkNode<Bullet*>;
	BulletPool(int NumberOfBullets)
	{
		List = new UnorderedArray<Bullet*>(NumberOfBullets);
		for (int i = 0; i < NumberOfBullets; i++)
		{
			List->push(new Bullet());
		}
	}
	void Update()
	{
		for (int i = 0; i < GetSize(); i++)
		{
			List->getArray()[i]->update();
		}
	}
	void Draw()
	{
		for (int i = 0; i < GetSize(); i++)
		{
			List->getArray()[i]->draw();
		}
	}
	void Use()
	{
		if(List->GetSize() > 0)
		{
			int nextBullet = NextAvailable();
			if(nextBullet != -1)
			{
				List->getArray()[nextBullet]->Init();
				List->getArray()[nextBullet]->isBeingUsed();
				std::cout << "Using bullet Number: " << nextBullet << std::endl;
			}
			else
			{
				std::cout << "Not enough bullets" << std::endl;
			}
		}
	}
	int NextAvailable()
	{
		for (int i = 0; i < GetSize(); i++)
		{
			if(!List->getArray()[i]->Used())
			{
				return i;
			}
		}
		return -1;
	}

	void checkCollision(Player* Player)
	{
		for (int i = 0; i < GetSize(); i++)
		{
			if(List->getArray()[i]->Used())
			{
				if(Player->checkDistance(List->getArray()[i]) < 
					(Player->getHeight()*0.3 + List->getArray()[i]->getHeight()*0.5))
				{
					List->getArray()[i]->isNotUsed();
					SoundManager::Instance().playSound("Hit");
				}
			}
		}
	}

	void SetNewSize(int newSize)
	{
		if(newSize> GetSize())
		{
			for (int i = 0; i < newSize - GetSize(); i++)
			{
				List->push(new Bullet());
			}
		}else if(newSize< GetSize())
		{
			for (int i = 0; i < GetSize() - newSize; i++)
			{
				List->pop();
			}
		}
	}

	float GetSize() const
	{
		return List->GetSize();
	}


private:
	UnorderedArray<Bullet*>* List;
};