#pragma once
#include "DebugBox.h"

class SceneGame;
class DebugBox;
class Zombie;
class Item;
class HitBox;

class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId = "graphics/player.png";

	sf::Vector2f direction;
	sf::Vector2f look;

	float speed = 200.f;

	SceneGame* sceneGame;

	float shootDelay = 0.5f;
	float shootTimer = 0.f;

	DebugBox debugBox;

	sf::RectangleShape healthBar;
	int maxHp = 100;
	int hp = 100;

	int bulletCount = 10;
	int maxBulletCount = 100;

	float rateOfFire;        // 사격 속도
	int clipSize;            // 탄창 크기
	int maxHealth;           // 최대 체력
	float runSpeed;          // 이동 속도
	int healthPickupBonus;   // 체력 아이템 효과
	int ammoPickupBonus;     // 탄약 아이템 효과

	HitBox* hitBox;
public:

	Player(const std::string& name = "");
	~Player() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Shoot();

	void UpdateHealthBar();
	void FixedUpdate(float dt) override;
	void OnDamage(int damageAmount);

	void IncreaseHealth(int amount); // 체력증가
	int GetHealth()const { return hp; }
	void IncreaseBulletCount(int count);
	int GetBulletCount() const;
	void AddBullets(int count);
	void OnPickup(Item* item);

	void IncreaseSpeed(float amount);        // 이동 속도 증가
	void IncreaseMaxHealth(int amount);      // 최대 체력 증가
	void IncreaseClipSize(int amount);       // 총알 한 번에 장전할 수 있는 수 증가
	void IncreaseAmmoPickups(int amount);    // 아이템 획득 시 총알 수 증가

	//업그레이드
	void IncreaseRateOfFire();
	void IncreaseRunSpeed();
	void IncreaseHealthPickups();
	void IncreaseAmmoPickups();
};
