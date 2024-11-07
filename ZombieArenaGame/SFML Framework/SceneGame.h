#pragma once
#include "Scene.h"
#include "SpawnArea.hpp"  // spawndraw

class Player;
class Zombie;
class Bullet;
class UiScore;
class UiMessage;
class Item;
class TileMap;
class UibulletCount;
class UiStart;
class ZombieCount;
class UiWave;
class UiUpgrade;
class Wave;

class SceneGame : public Scene
{
protected:
	Player* player;
	UibulletCount* uiBulletCount;
	TileMap* tileMap;
	UiScore* uiScore;
	UiMessage* uiMessage;
	UiUpgrade* uiUpgrade;
	UiStart* uiStart;
	UiWave* uiWave;
	Wave* wave;

	sf::Sprite bloodSprite;    // 피 이미지 스프라이트
	sf::Clock bloodClock;      // 피 이미지 유지 시간 관리
	bool isBloodVisible = false;

	ZombieCount* zombieCount;
	std::list<Zombie*> zombies;
	ObjectPool<Zombie> zombiePool;
	float spawnTimer = 0.f; // 좀비 스폰 타이머
	const float spawnInterval = 2.f;

	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;

	std::list<Item*> items;
	ObjectPool<Item> itemPool;

	sf::Sprite cursor;

	std::list<Wave*> waves;

	Wave* currentWave = nullptr;  // 현재 진행 중인 웨이브
	int totalZombiesKilled = 0;   // 총 처치한 좀비 수

	float ItemTimer = 0.f;

	bool isUpgradeUIVisible = false;  // 업그레이드 UI 표시 여부
	bool isPaused = false;            // 게임 일시 정지 상태
	sf::RectangleShape upgradeUI;     // 업그레이드 UI 영역
	sf::Text upgradeText;             // 업그레이드 선택 텍스트
	int selectedUpgrade = 0;          // 선택된 업그레이드 번호
	std::vector<sf::Text> upgradeOptions;

	SpawnArea spawn;  // spawndraw
	
public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init();
	void Release();
	void Enter();
	void Exit();
	void Update(float dt);
	void Draw(sf::RenderWindow& window) override;  // spawndraw

	void SpawnZombies(int count);
	void SpawnItem(int count);
	Bullet* TakeBullet();

	void ReturnBullet(Bullet* bullet);
	const std::list<Zombie*>& GetZombieList() const { return zombies; }
	const std::list<Item*>& GetItemList() const { return items; } // 리스트 추가
	void OnZombieDie(Zombie* zombie);
	void OnPlayerDie(Player* player);

	void PauseGame();
	void ResumeGame();

	void CheckWaveCompletion();
	void ApplyUpgrade(int selectedUpgrade);

};

