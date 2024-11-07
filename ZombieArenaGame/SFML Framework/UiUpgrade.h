#pragma once
#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
class Player;
class  inputMgr;

enum class Upgrade
{
	RateOfFire,
	ClipSize,
	MaxHealth,
	RunSpeed,
	HealthPickups,
	AmmoPickups,
	Count,
};

class UiUpgrade : public GameObject
{
protected:
	std::vector<sf::Text> upgrades;
	sf::Sprite background;
	sf::Vector2f position;
	float rotation;
	sf::Vector2f scale;
	Origins originPreset;

	 // UI 활성화 여부
	Player* player;

	Upgrade selectedUpgrade = Upgrade::RateOfFire;

public:
	bool isPaused;
	bool isActive;
	UiUpgrade(const std::string& name = "", Player* player = nullptr);
	~UiUpgrade() = default;

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

	void HandleUpgradeSelection(); // 업그레이드 선택 처리
	bool IsActive() const { return isActive; }
	void Show() { isActive = true; }
	void Hide() { isActive = false; }
	void SetActive(bool active);
	void ResetUpgradeState();
};
