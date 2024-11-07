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

    // 업데이트 메서드
    void Update(float dt);

    // 웨이브 시작
    void StartWave();

    // 웨이브가 완료되었는지 확인
    bool IsWaveComplete() const;

    // 좀비 스폰
    void SpawnZombies(SceneGame* sceneGame);

    // 웨이브가 활성화 상태인지 확인
    bool IsActive() const { return waveActive; }

    void Reset();

    void AddZombieToKill();  // 좀비 추가
    void ZombieKilled();
    int GetTotalZombiesToKill() const
    {
        return totalZombiesToKill;
    }
};

