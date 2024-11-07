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

	sf::Sprite bloodSprite;    // �� �̹��� ��������Ʈ
	sf::Clock bloodClock;      // �� �̹��� ���� �ð� ����
	bool isBloodVisible = false;

	ZombieCount* zombieCount;
	std::list<Zombie*> zombies;
	ObjectPool<Zombie> zombiePool;
	float spawnTimer = 0.f; // ���� ���� Ÿ�̸�
	const float spawnInterval = 2.f;

	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;

	std::list<Item*> items;
	ObjectPool<Item> itemPool;

	sf::Sprite cursor;

	std::list<Wave*> waves;

	Wave* currentWave = nullptr;  // ���� ���� ���� ���̺�
	int totalZombiesKilled = 0;   // �� óġ�� ���� ��

	float ItemTimer = 0.f;

	bool isUpgradeUIVisible = false;  // ���׷��̵� UI ǥ�� ����
	bool isPaused = false;            // ���� �Ͻ� ���� ����
	sf::RectangleShape upgradeUI;     // ���׷��̵� UI ����
	sf::Text upgradeText;             // ���׷��̵� ���� �ؽ�Ʈ
	int selectedUpgrade = 0;          // ���õ� ���׷��̵� ��ȣ
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
	const std::list<Item*>& GetItemList() const { return items; } // ����Ʈ �߰�
	void OnZombieDie(Zombie* zombie);
	void OnPlayerDie(Player* player);

	void PauseGame();
	void ResumeGame();

	void CheckWaveCompletion();
	void ApplyUpgrade(int selectedUpgrade);

};

