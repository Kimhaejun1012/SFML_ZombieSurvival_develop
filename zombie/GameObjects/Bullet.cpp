#include "stdafx.h"
#include "Bullet.h"
#include "Zombie.h"
#include "SceneMgr.h"
#include "SceneMgr.h"
#include "Scene.h"


#include "InputMgr.h"
Bullet::Bullet(const std::string textureId, const std::string n)
	: SpriteGo(textureId, n)
{
}

Bullet::~Bullet()
{
}

void Bullet::SetZombieList(const std::list<Zombie*>* list)
{
	zombies = list;
}

void Bullet::SetZombiePool(ObjectPool<Zombie> pool)
{
	//zombies = pool.GetUseList();
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed)
{
	sprite.setRotation(Utils::Angle(dir));
	SetPosition(pos);

	direction = dir;
	this->speed = speed;
}

void Bullet::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void Bullet::Release()
{
	SpriteGo::Release();
}

void Bullet::Reset()
{
	SpriteGo::Reset();
//
	maxDamage = 25;
	damage = 25;
//
	sprite.setRotation(0.f);
	SetPosition(0.f, 0.f);
	direction = { 0.f , 0.f };
	speed = 0.f;
	range = 2000.f;
}

void Bullet::Update(float dt)
{
	SpriteGo::Update(dt);
	
	Move(dt);
	HitZombie();
}

void Bullet::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Bullet::Move(float dt)
{
	range -= speed * dt;
	if (range < 0)
	{
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		pool->Return(this);		// 풀로 회수
		//SetActive(false);
		return;
	}

	position += direction * speed * dt;
	sprite.setPosition(position);

}

void Bullet::HitZombie()
{
	if (zombies != nullptr)
	{
		for (Zombie* zombie : *zombies)
		{
			if (sprite.getGlobalBounds().intersects(zombie->sprite.getGlobalBounds()))
			{
				//std::cout << damage << std::endl;
				zombie->OnHitBullet(damage);

				SCENE_MGR.GetCurrScene()->RemoveGo(this);
				pool->Return(this);		// 풀로 회수
				//SetActive(false);
				break;
			}
		}
	}
}

void Bullet::SetDamage(int number)
{
	damage = number;
}