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
    if (!waveActive) return;  // ���̺갡 Ȱ��ȭ���� ������ ������Ʈ���� ����

    waveTimer += dt;  // ��� �ð� ������Ʈ

    // �ֱ������� ���� ����
    if (waveTimer >= spawnInterval && zombiesSpawned < zombiesToSpawn)
    {
        Scene* currentScene = SCENE_MGR.GetCurrentScene();
        SceneGame* sceneGame = dynamic_cast<SceneGame*>(currentScene);

        if (sceneGame)
        {
            SpawnZombies(sceneGame);  // ���� ����
        }

        waveTimer = 0.f;  // Ÿ�̸� �ʱ�ȭ
    }

    // ��� ���� �����Ǿ����� ���̺� ����
    if (zombiesSpawned >= zombiesToSpawn && zombiesKilled >= totalZombiesToKill)
    {
        waveActive = false;  // ���̺� ��Ȱ��ȭ
    }
}

void Wave::StartWave()
{
    waveActive = true;                  // ���̺� Ȱ��ȭ
    zombiesSpawned = 0;                 // ������ ���� �� �ʱ�ȭ
    waveTimer = 0.f;                    // Ÿ�̸� �ʱ�ȭ
    totalZombiesToKill = zombiesToSpawn; // �̹� ���̺꿡�� �׿��� �� �� ���� ��
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
        sceneGame->SpawnZombies(1);  // �� ���� �� ������ ���� ����
        zombiesSpawned++;  // ������ ���� �� ����
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
