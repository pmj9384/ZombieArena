#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "bullet.h"
#include "Item.h"
#include "UiScore.h"
#include "UiMessage.h"
#include "UibulletCount.h"
#include "UiStart.h"
#include "UiWave.h"
#include "ZombieCount.h"
#include "Wave.h"
#include "UiUpgrade.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game), currentWave(nullptr)
{
}

void SceneGame::Init()
{

	AddGo(new TileMap("TileMap"));
	player = AddGo(new Player("Player"));
	uiScore = AddGo(new UiScore("fonts/zombiecontrol.ttf"));
	uiMessage = AddGo(new UiMessage("fonts/zombiecontrol.ttf"));
	uiStart = AddGo(new UiStart("fonts/zombiecontrol.ttf"));
	uiBulletCount = AddGo(new UibulletCount("fonts/zombiecontrol.ttf",player));
	uiWave = AddGo(new UiWave("fonts/zombiecontrol.ttf"));
	zombieCount = AddGo(new ZombieCount("fonts/zombiecontrol.ttf"));

	bloodSprite.setTexture(TEXTURE_MGR.Get("graphics/blood.png"));
	Utils::SetOrigin(bloodSprite, Origins::MC);
	
	auto size = FRAMEWORK.GetWindowSize();
	// 스폰 객체
	spawn.SetPosition(0.0f, 0.0f);  // spawndraw
	spawn.SetSize(20.f * 50.f, 20.f * 50.f); // spawndraw
	spawn.SetOrigin(Origins::MC); // spawndraw
	spawn.SetDrawable(false); // 테두리 온오프

	sf::Vector2f playerPos = player->GetPosition();

	uiMessage->SetActive(false);

	uiScore->SetPosition(playerPos + sf::Vector2f(750.f, -500.f));  // 위치 설정
	uiBulletCount->SetPosition(playerPos + sf::Vector2f(-850.f, 450.f));

	uiWave->SetPosition(playerPos + sf::Vector2f(430.f, 480.f));  // 위치 설정
	zombieCount->SetPosition(playerPos + sf::Vector2f(770.f, 480.f));
	uiStart->SetPosition(playerPos);

	currentWave = new Wave();
	currentWave->SetType(Wave::Types::Wave1);
	
	uiUpgrade = AddGo(new UiUpgrade("UpgradeUI", player));
	uiUpgrade->SetActive(false);
	uiUpgrade->SetOrigin(Origins::MC);

	sf::Vector2f windowSize(1920.f, 1080.f);
	sf::Vector2f offset = windowSize * 0.5f;

	uiUpgrade->SetPosition(playerPos - offset);

	isPaused = true;

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
	for (auto& zombie : zombies)
	{
		delete zombie;
	}
	zombies.clear();

	if (currentWave != nullptr)
	{
		delete currentWave;
		currentWave = nullptr;
	}
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png")); // 마우스 ui
	Utils::SetOrigin(cursor, Origins::MC);
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter(0.f, 0.f);


	Scene::Enter();
}

void SceneGame::Exit()
{
	FONT_MGR.Unload("fonts/DS-DIGI.ttf");

	for (auto zombie : zombies)
	{
		RemoveGo(zombie);
		zombiePool.Return(zombie);
	}
	zombies.clear();
	for (auto bullet : bullets)
	{
		RemoveGo(bullet);
		bulletPool.Return(bullet);
	}
	Scene::Exit();
}



void SceneGame::Update(float dt)
{
	sf::Vector2i mousePos = InputMgr::GetMousePosition(); // mouse pos
	sf::Vector2f worldMousePos = FRAMEWORK.GetWindow().mapPixelToCoords(mousePos, uiView); //mouse pos
	cursor.setPosition(worldMousePos);


	if (isPaused)
	{
		if (uiUpgrade->isActive)  //ui upgrade
		{
			// 업그레이드 화면에서 마우스 입력 처리
			uiUpgrade->HandleUpgradeSelection();
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			// 일시 정지 해제
			isPaused = false;

			// "Start" 메시지 숨기기
			uiStart->SetActive(false);
		}
		
		return; // 일시 정지 상태에서는 이후 코드를 실행하지 않음
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) 
	{
		isPaused = true;
		uiStart->SetActive(true);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		// 점수 및 기타 UI 초기화
		uiScore->Reset();
		uiBulletCount->Reset();
		player->Reset();
		uiWave->Reset();
		/*wave->Reset();*/
		//// 플레이어 초기화 및 활성화
		player->SetActive(true);
		zombieCount->Reset();
		// 게임을 일시 정지 상태로 설정
		isPaused = true;
		uiStart->SetActive(true);
	}

	Scene::Update(dt);
	// wave update 
	if (currentWave != nullptr)
	{
		Wave* wave = dynamic_cast<Wave*>(currentWave);
		if (wave != nullptr) 
		{
			wave->Update(dt);
			// 웨이브가 완료되었는지 확인
			if (wave->IsWaveComplete()) 
			{
				// 다음 웨이브로 이동
				wave->Reset();
				zombieCount->Reset();
				Wave::Types nextType = static_cast<Wave::Types>(static_cast<int>(wave->GetType()) + 1);
				if (nextType <= Wave::Types::Wave5) 
				{
					wave->SetType(nextType);
					wave->StartWave();

					if (uiUpgrade && !uiUpgrade->IsActive())
					{

						uiUpgrade->SetActive(true);  // UI 활성화

						dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->PauseGame();
						isPaused = true;

					}
				
				}
				else 
				{
					// 모든 웨이브가 완료된 경우
				}
			}
			uiWave->SetWave(static_cast<int>(wave->GetType()));
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}

	if (isBloodVisible && bloodClock.getElapsedTime().asSeconds() > 3.0f)
	{
		isBloodVisible = false;
	}

	spawnTimer += dt;  //좀비 스폰 타이머

	if (zombies.size() < currentWave->GetTotalZombiesToKill() && spawnTimer >= spawnInterval)
	{
		SpawnZombies(1);
		spawnTimer = 0.f;
	}

	ItemTimer += dt; 

    const float ITEM_SPAWN_DELAY = 2.0f; //생성 시간

    if (ItemTimer >= ITEM_SPAWN_DELAY)
    {
        SpawnItem(1); 
        ItemTimer = 0.f;
    }
	if (player != nullptr)
	{
		player->Update(dt);
		

		if (player->GetHealth() <= 0)
		{
			OnPlayerDie(player); // 플레이어가 죽으면 메서드 호출
			return; // 조기 반환
		}

		TileMap* tileMap = static_cast<TileMap*>(FindGo("TileMap"));
		sf::FloatRect bounds = tileMap->GetGlobalBounds();
		sf::Vector2f playerPos = player->GetPosition();

		if (playerPos.x < bounds.left) 
		{
			playerPos.x = bounds.left;
		}
		else if (playerPos.x > bounds.left + bounds.width)
		{
			playerPos.x = bounds.left + bounds.width;
		}

		if (playerPos.y < bounds.top) 
		{
			playerPos.y = bounds.top;
		}
		else if (playerPos.y > bounds.top + bounds.height)
		{
			playerPos.y = bounds.top + bounds.height;
		}
		//zombie wave update
		if (currentWave != nullptr && !currentWave->IsWaveComplete())
		{
			currentWave->Update(dt);
		}

		player->SetPosition(playerPos);
		uiBulletCount->Update();

		uiScore->SetPosition(playerPos + sf::Vector2f(750.f, -500.f));  // 위치 설정
		uiBulletCount->SetPosition(playerPos + sf::Vector2f(-850.f, 450.f));

		uiWave->SetPosition(playerPos + sf::Vector2f(430.f, 480.f));  // 위치 설정
		zombieCount->SetPosition(playerPos + sf::Vector2f(770.f, 480.f));

		/*CheckWaveCompletion();*/

		worldView.setCenter(player->GetPosition());
	}

	TileMap* tileMap = static_cast<TileMap*>(FindGo("TileMap"));
	sf::FloatRect bounds = tileMap->GetGlobalBounds();
	for (auto& zombie : zombies)
	{
		if (zombie->IsActive())
		{
			zombie->Update(dt); 
			sf::Vector2f zombiePos = zombie->GetPosition();


			if (zombiePos.x < bounds.left)
			{
				zombiePos.x = bounds.left;
			}
			else if (zombiePos.x > bounds.left + bounds.width)
			{
				zombiePos.x = bounds.left + bounds.width;
			}

			if (zombiePos.y < bounds.top)
			{
				zombiePos.y = bounds.top;
			}
			else if (zombiePos.y > bounds.top + bounds.height)
			{
				zombiePos.y = bounds.top + bounds.height;
			}

			zombie->SetPosition(zombiePos);
		}
	}


}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	spawn.Draw(window); // spawndraw

	if (isBloodVisible)
	{
		window.draw(bloodSprite);
	}
	if (uiMessage->IsActive()) // 메시지가 활성화된 경우에만 그리기
	{
		uiMessage->Draw(window);
	}
	if (uiStart->IsActive())
	{
		uiStart->Draw(window);
	}

	window.setView(uiView); // 마우스 ui
	window.draw(cursor); // 마우스 ui
	window.setView(saveView); // 마우스 ui

}

void SceneGame::SpawnZombies(int count)
{
	TileMap* tileMap = static_cast<TileMap*>(FindGo("TileMap"));
	sf::FloatRect bounds = tileMap->GetGlobalBounds();
	for (int i = 0; i < count; ++i)
	{
		Zombie* zombie = zombiePool.Take();
		zombies.push_back(zombie);
		
		Zombie::Types zombieType =(Zombie::Types) Utils::RandomRange(0, Zombie::TotalTypes -1);
		zombie->SetType(zombieType);

		sf::Vector2f pos;

		//do {
		//	pos = {
		//		Utils::RandomRange(bounds.left, bounds.left + bounds.width),
		//		Utils::RandomRange(bounds.top, bounds.top + bounds.height)
		//	};
		//} while (Utils::Distance(pos, player->GetPosition()) < 200.f);

		pos = spawn.Spawn();
		zombieCount->AddCount(1);
		zombie->SetPosition(pos);
		AddGo(zombie);
		zombie->SetActive(true);
	}

}

void SceneGame::SpawnItem(int count)
{
	TileMap* tileMap = static_cast<TileMap*>(FindGo("TileMap"));
	sf::FloatRect bounds = tileMap->GetGlobalBounds();

	for (int i = 0; i < count; ++i)
	{
		Item* item = itemPool.Take();
		items.push_back(item);

		Item::Types itemType = (Item::Types)Utils::RandomRange(0, Item::TotalTypes - 1);
		item->SetType(itemType);

		sf::Vector2f pos;
	/*	do {
			pos = {
				Utils::RandomRange(bounds.left, bounds.left + bounds.width),
				Utils::RandomRange(bounds.top, bounds.top + bounds.height)
			};
		} while (Utils::Distance(pos, player->GetPosition()) < 50.f);*/
		pos = spawn.Spawn();
		item->SetPosition(pos);

		AddGo(item);
		item->SetActive(true);
	}

}

Bullet* SceneGame::TakeBullet()
{
	Bullet* bullet = bulletPool.Take();
	bullets.push_back(bullet);
	AddGo(bullet);
	return bullet;
}

void SceneGame::ReturnBullet(Bullet* bullet)
{
	RemoveGo(bullet);
	bulletPool.Return(bullet);
	bullets.remove(bullet);
}

void SceneGame::OnZombieDie(Zombie* zombie)
{
	bloodSprite.setPosition(zombie->GetPosition());
	isBloodVisible = true;
	bloodClock.restart();

	zombie->SetActive(false);  // 좀비를 비활성화
	zombie->Reset();
	RemoveGo(zombie);
	zombiePool.Return(zombie);
	zombies.remove(zombie);
	if (currentWave != nullptr)
	{
		currentWave->ZombieKilled();  // 웨이브에 킬 추가
		uiScore->AddScore(100);
	}

}

void SceneGame::OnPlayerDie(Player* player)
{
	player->SetActive(false);

	uiMessage->SetActive(true);
	uiMessage->SetPosition(player->GetPosition());
	// 게임 일시 정지
	isPaused = true;
}

void SceneGame::PauseGame()
{
	isPaused = true;
}

void SceneGame::ResumeGame()
{
	isPaused = false;
/*	uiUpgrade->SetActive(false); */ // UiUpgrade 객체 비활성화

}

void SceneGame::CheckWaveCompletion()
{
	if (wave->IsWaveComplete())
	{
		// 웨이브 완료 시 업그레이드 UI 활성화
		uiUpgrade->SetActive(true);
		isPaused = true;  // 게임 일시 정지
	}
}

void SceneGame::ApplyUpgrade(int selectedUpgrade)
{
	//switch (selectedUpgrade)
	//{
	//case Upgrade::RateOfFire:
	//	player->IncreaseRateOfFire();
	//	break;
	//case Upgrade::ClipSize:
	//	player->IncreaseClipSize();
	//	break;
	//case Upgrade::MaxHealth:
	//	player->IncreaseHealth(2.f);
	//	break;
	//case Upgrade::RunSpeed:
	//	player->IncreaseSpeed(0.2f);
	//	break;
	//case Upgrade::HealthPickups:
	//	player->IncreaseHealthPickupChance();
	//	break;
	//case Upgrade::AmmoPickups:
	//	player->IncreaseAmmoPickupChance();
	//	break;
	//}

	//// 업그레이드 후 UI 비활성화하고 게임 재개
	//uiUpgrade->SetActive(false);
	//isPaused = false;  // 게임 재개
}






