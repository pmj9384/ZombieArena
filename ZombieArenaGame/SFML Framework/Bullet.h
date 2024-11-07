#include "GameObject.h"
#include "DebugBox.h"
#pragma once
class SceneGame;
class DebugBox;
class Bullet : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId = "graphics/bullet.png";

	sf::Vector2f direction;
	float speed = 0.f;
	int damage = 0;
	SceneGame* sceneGame;
	DebugBox debugBox;
public:
	Bullet(const std::string& name = "");
	~Bullet() = default;

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
	void FixedUpdate(float dt) override;
	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d);
};
