#pragma once
#include "GameObject.h"
#include "Zombie.h"

class Zombie;

class Wave 
{
public:
    enum class Types 
    {
        none,
        Wave1,
        Wave2,
        Wave3,
        Wave4,
        Wave5,
    };
    static const int TotalTypes = 5;
    Wave* currentWave = nullptr;

protected:
    Types types;
    int zombiesToSpawn;
    int zombiesSpawned;   
    float waveTimer;    
    bool waveActive;   
    float spawnInterval;   

    int totalZombiesToKill;
    int zombiesKilled;
public:
  
    Wave();

    virtual ~Wave() = default;

    Types GetType() const { return types; }

    void SetType(Types type);

    // ������Ʈ �޼���
    void Update(float dt);

    // ���̺� ����
    void StartWave();

    // ���̺갡 �Ϸ�Ǿ����� Ȯ��
    bool IsWaveComplete() const;

    // ���� ����
    void SpawnZombies(SceneGame* sceneGame);

    // ���̺갡 Ȱ��ȭ �������� Ȯ��
    bool IsActive() const { return waveActive; }

    void Reset();

    void AddZombieToKill();  // ���� �߰�
    void ZombieKilled();
    int GetTotalZombiesToKill() const
    {
        return totalZombiesToKill;
    }
};

