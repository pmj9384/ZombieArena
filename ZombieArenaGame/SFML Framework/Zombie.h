#pragma once
#include "GameObject.h"

class Player;
class SceneGame;

class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};

	static const int TotalTypes = 3;
	bool dead = false;
protected:

	Types types = Types::Bloater;
	sf::Sprite body;
	std::string textureId;

	sf::Vector2f direction;

	int maxHp = 0;
	float speed = 0.f;
	int damage = 0;
	float attackInterval = 0.f;

	int hp = 0;
	float attackTimer = 0.f;

	Player* player = nullptr;
	SceneGame* sceneGame = nullptr;
	sf::Sprite zombieEffect;
	bool active = true; // 좀비공격활성화
	float deactivateTime; // 비활성화 유지 시간
	float deactivateTimer;
	float effectTimer = 0.f;
public:
	Zombie(const std::string& name = "");
	~Zombie() = default;
	float bloodEffectTime;
	sf::Sprite& GetBody() 
	{
		return body;
	}

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
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

	void SetType(Types type);

	void OnDamage(int damage);
	int GetDamage() const { return damage; }
	bool IsActive() const { return active; }
	void Deactivate(float duration);

};
