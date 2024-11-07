#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"


Zombie::Zombie(const std::string& name) : GameObject(name)
{
}

sf::FloatRect Zombie::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Zombie::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Zombie::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Zombie::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Zombie::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetType(types);

}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::MC);
	SetPosition({ 0.f,0.f });
	SetRotation({ 0.f});
	SetScale({ 1.f,1.f });

}

void Zombie::Update(float dt)
{
	if (!active) // 공격 비활성화 타이머
	{
		deactivateTimer += dt;

		if (deactivateTimer >= deactivateTime)
		{
			this->active = true; 
			deactivateTimer = 0.f; 
		}
		return;
	}
	const float MIN_DISTANCE = 20.0f;
	if (player != nullptr)
	{
		float distance = Utils::Distance(position, player->GetPosition());
		if (distance > MIN_DISTANCE)
		{
			direction = Utils::GetNormal(player->GetPosition() - position);
			SetRotation(Utils::Angle(direction));
			SetPosition(position + direction * speed * dt);

		}
	}
	//hitBox.UpdateTr(body, body.getLocalBounds());
}

void Zombie::Draw(sf::RenderWindow& window)
{

	window.draw(body);
}

void Zombie::SetType(Types type)
{
	this->types = type;
	switch (this->types)
	{
		case Types::Bloater:
			textureId = "graphics/bloater.png";
			speed = 100.f;
			maxHp = 50;
			damage = 10;
			break;
		case Types::Chaser:
			textureId = "graphics/Chaser.png";
			speed = 75.f;
			maxHp = 20;
			damage = 10;

			break;	
		case Types::Crawler:
			textureId = "graphics/Crawler.png";
			speed = 50.f;
			maxHp = 10;
			damage = 10;

				break;
	default:
		break;


	}
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	hp = maxHp;
}

void Zombie::OnDamage(int d)
{
	hp -= d;
	if (hp <= 0 && sceneGame != nullptr)
	{
		this->active = false;
		sceneGame->OnZombieDie(this);
	}
}

void Zombie::Deactivate(float duration)
{
	active = false;
	deactivateTime = duration; // 비활성화 유지 시간 설정
	deactivateTimer = 0.f;
}
