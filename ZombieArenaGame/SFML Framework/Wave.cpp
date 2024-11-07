#include "stdafx.h"
#include "Wave.h"
#include "Zombie.h"
#include "SceneGame.h"


Wave::Wave() : types(Types::Wave1), zombiesToSpawn(0), zombiesSpawned(0),
waveTimer(0.f), waveActive(false), spawnInterval(1.f) {}


void Wave::SetType(Types type)
{
    types = type;

    switch (type)
    {

    case Types::Wave1:
        zombiesToSpawn = 5;
        spawnInterval = 2.f;
        totalZombiesToKill = 1;
        break;
    case Types::Wave2:
        zombiesToSpawn = 10;
        spawnInterval = 1.8f;
        totalZombiesToKill = 10;
        break;
    case Types::Wave3:
        zombiesToSpawn = 20;
        spawnInterval = 1.6f;
        totalZombiesToKill = 20;
        break;
    case Types::Wave4:
        zombiesToSpawn = 30;
        spawnInterval = 1.4f;
        totalZombiesToKill = 30;
        break;
    case Types::Wave5:
        zombiesToSpawn = 40;
        spawnInterval = 1.2f;
        totalZombiesToKill = 40;
        break;

    }

}

void Wave::Update(float dt)
{
    if (!waveActive) return;  // 웨이브가 활성화되지 않으면 업데이트하지 않음

    waveTimer += dt;  // 경과 시간 업데이트

    // 주기적으로 좀비를 스폰
    if (waveTimer >= spawnInterval && zombiesSpawned < zombiesToSpawn)
    {
        Scene* currentScene = SCENE_MGR.GetCurrentScene();
        SceneGame* sceneGame = dynamic_cast<SceneGame*>(currentScene);

        if (sceneGame)
        {
            SpawnZombies(sceneGame);  // 좀비 스폰
        }

        waveTimer = 0.f;  // 타이머 초기화
    }

    // 모든 좀비가 스폰되었으면 웨이브 종료
    if (zombiesSpawned >= zombiesToSpawn && zombiesKilled >= totalZombiesToKill)
    {
        waveActive = false;  // 웨이브 비활성화
    }
}

void Wave::StartWave()
{
    waveActive = true;                  // 웨이브 활성화
    zombiesSpawned = 0;                 // 스폰된 좀비 수 초기화
    waveTimer = 0.f;                    // 타이머 초기화
    totalZombiesToKill = zombiesToSpawn; // 이번 웨이브에서 죽여야 할 총 좀비 수
    zombiesKilled = 0;
}




bool Wave::IsWaveComplete() const
{
    return zombiesKilled >= totalZombiesToKill;
}

void Wave::SpawnZombies(SceneGame* sceneGame)
{
    if (sceneGame && zombiesSpawned < zombiesToSpawn)
    {
        sceneGame->SpawnZombies(1);  // 한 번에 한 마리씩 좀비 스폰
        zombiesSpawned++;  // 스폰된 좀비 수 증가
    }
}

void Wave::Reset()
{
    waveActive = false;
    zombiesSpawned = 0;
    waveTimer = 0.f;
    totalZombiesToKill = 0;
    zombiesKilled = 0;

}

void Wave::AddZombieToKill()
{
    totalZombiesToKill++;
}

void Wave::ZombieKilled()
{
    zombiesKilled++;
}
