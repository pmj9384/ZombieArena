#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "DebugBox.h"
#include "Zombie.h"
#include "Item.h"

Player::Player(const std::string& name)
	: GameObject(name)
{

}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(angle);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(s);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetOrigin(Origins::MC);

	int maxHp = 100;
	int hp = maxHp;
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setSize(sf::Vector2f(static_cast<float>(hp) / maxHp * 300.f, 80.f));
	healthBar.setPosition(position.x - healthBar.getSize().x / 2, position.y + body.getGlobalBounds().height / 2 + 600.f);
}

void Player::Release()
{
}

void Player::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(originPreset);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	direction = { 1.f, 0.f };
	hp = maxHp; // ü���� �ִ�ġ�� ����
	UpdateHealthBar();

	shootTimer = shootDelay;
	bulletCount = 10;
	clipSize = 10;
	maxHealth = 100;
	runSpeed = 1.0f;
	healthPickupBonus = 0;
	ammoPickupBonus = 0;
}

void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)
	{
		 Utils::Normalize(direction);
	}

	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWorldPos - position);

	SetRotation(Utils::Angle(look));
	SetPosition(position + direction * speed * dt);

	shootTimer += dt;
	if (shootTimer > shootDelay && InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		Shoot();
		shootTimer = 0.f;
	
	}


	debugBox.SetBounds(body.getGlobalBounds());
	UpdateHealthBar();

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(healthBar);
	debugBox.Draw(window);
}

void Player::Shoot()
{
	//Bullet* bullet = sceneGame->TakeBullet();
	//bullet->Fire(position, look,500.f,10);
	if (bulletCount > 0)
	{
		Bullet* bullet = sceneGame->TakeBullet(); 
		// �Ѿ� �߻� ���� ����
		bullet->Fire(position, look, 500.f, 10);  

		bulletCount--; // �Ѿ� ���� ����
	}
	else
	{

	}
}

void Player::UpdateHealthBar()
{
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setSize(sf::Vector2f(static_cast<float>(hp) / maxHp * 300.f, 80.f));
	healthBar.setPosition(position.x - healthBar.getSize().x / 2 -800, position.y + body.getGlobalBounds().height / 2 + -550.f);
}

void Player::FixedUpdate(float dt)
{
	if (sceneGame == nullptr)
		return;


	const auto& zombieList = sceneGame->GetZombieList();

	for (auto zombie : zombieList)
	{
		if (!zombie->IsActive())
			continue;

		auto playerPoints = Utils::GetShapePoints(body);
		auto zombiePoints = Utils::GetShapePoints(zombie->GetBody());

		const sf::Transform& playerTransform = body.getTransform();
		const sf::Transform& zombieTransform = zombie->GetBody().getTransform();
		if (Utils::PolygonsIntersect(playerPoints, playerTransform, zombiePoints, zombieTransform))
		{
			OnDamage(zombie->GetDamage());  // ������ �������� �޾� ü�� ����
			zombie->Deactivate(0.2f); // 0.2���� ���� ��Ȱ��ȭ
			break;  
		}
	}

	const auto& itemList = sceneGame->GetItemList();

	for (auto item : itemList)
	{
		if (!item->IsActive())
			continue;

		auto playerPoints = Utils::GetShapePoints(body);
		auto itemPoints = Utils::GetShapePoints(item->GetBody());

		const sf::Transform& playerTransform = body.getTransform();
		const sf::Transform& itemTransform = item->GetBody().getTransform();

		if (Utils::PolygonsIntersect(playerPoints, playerTransform, itemPoints, itemTransform))
		{

			OnPickup(item);  // �������� ȹ��
			item->SetActive(false);
			break;
		}
	}
}

void Player::OnDamage(int damageAmount)
{
	std::cout << "Damage taken: " << damageAmount << std::endl;
	hp -= damageAmount;
	if (hp <= 0)
	{
		hp = 0;
		sceneGame->OnPlayerDie(this);
	}
	UpdateHealthBar();


}

void Player::IncreaseHealth(int amount)
{
	hp += amount;
	if (hp > maxHp) // ü���� �ִ�ġ�� �ʰ����� �ʵ���
	hp = maxHp;
	
	UpdateHealthBar();
}

void Player::IncreaseBulletCount(int count)
{
	bulletCount += count;
}

int Player::GetBulletCount() const
{
	return bulletCount;
}

void Player::AddBullets(int count)
{
	bulletCount += count;
	if (bulletCount > maxBulletCount)
	{
		bulletCount = maxBulletCount; 
	}
}



void Player::OnPickup(Item* item)
{
	item->OnPickup(this);
}

void Player::IncreaseSpeed(float amount)
{
	speed += amount;
}

void Player::IncreaseMaxHealth(int amount)
{
	maxHp += amount;
	hp = maxHp; // �ִ� ü���� ������Ų �� ���� ü���� �ִ� ü������ ����
	UpdateHealthBar();
}

void Player::IncreaseClipSize(int amount)
{
	maxBulletCount += amount;
	if (bulletCount > maxBulletCount) 
	{
		bulletCount = maxBulletCount; // ���� �Ѿ� ���� �ִ� �Ѿ� ���� �ʰ����� �ʵ���
	}
}

void Player::IncreaseAmmoPickups(int amount)
{
	bulletCount += amount;
	if (bulletCount > maxBulletCount) 
	{
		bulletCount = maxBulletCount; // ���� �Ѿ� ���� �ִ� �Ѿ� ���� �ʰ����� �ʵ���
	}
}

void Player::IncreaseRateOfFire()
{
	shootDelay *= 0.8f;
}

void Player::IncreaseRunSpeed()
{
	speed *= 2.f;
}

void Player::IncreaseHealthPickups()
{
	healthPickupBonus += 10;
}

void Player::IncreaseAmmoPickups()
{
	ammoPickupBonus += 10;
}



