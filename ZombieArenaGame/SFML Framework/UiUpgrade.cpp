#include "stdafx.h"
#include "UiUpgrade.h"
#include "SceneGame.h"
#include "Player.h"
#include "InputMgr.h"


UiUpgrade::UiUpgrade(const std::string& name, Player* player)
	: GameObject(name), player(player), isActive(false)
{
}

void UiUpgrade::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiUpgrade::SetRotation(float angle)
{
	rotation = angle;
}

void UiUpgrade::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiUpgrade::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiUpgrade::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiUpgrade::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;

	upgrades.resize((int)Upgrade::Count);
	upgrades[0].setString("1-INCREASED RATE OF FIRE");
	upgrades[1].setString("2-INCREASED CLIP SIZE(NEXT RELOAD)");
	upgrades[2].setString("3-INCREASED MAX HEALTH");
	upgrades[3].setString("4-INCREASED RUN SPEED");
	upgrades[4].setString("5-MORE AND BETTER HEALTH PICKUPS");
	upgrades[5].setString("6-MORE AND BETTER AMMO PICKUPS");

    
}

void UiUpgrade::Release()
{
}

void UiUpgrade::Reset()
{
    sf::Vector2f playerPos = player->GetPosition();
    sf::Vector2f windowSize(1920.f, 1080.f);
    sf::Vector2f offset = windowSize * 0.5f;

	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));
	background.setPosition(playerPos - offset);

	float textSize = 100.f;
	sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");

	int count = (int)Upgrade::Count;
	for (int i = 0; i < count; ++i)
	{
		upgrades[i].setFont(font);
		upgrades[i].setCharacterSize(textSize);
		Utils::SetOrigin(upgrades[i], Origins::ML);
		upgrades[i].setPosition(position.x+ 50.f, position.y + (120.f * i + 1) + 200.f);
	}
    SetPosition(playerPos - offset);
}

void UiUpgrade::Update(float dt)
{

}

void UiUpgrade::Draw(sf::RenderWindow& window)
{
    if (isActive)
    {  // 활성화된 경우에만 그리기
        sf::Vector2f playerPos = player->GetPosition();
        sf::Vector2f windowSize(1920.f, 1080.f);
        sf::Vector2f offset = windowSize * 0.5f;

        // 배경 위치 설정
        background.setPosition(playerPos - offset);
        window.draw(background);
        for (size_t i = 0; i < upgrades.size(); ++i)
        {
            upgrades[i].setPosition(playerPos.x -750.f, playerPos.y + (120.f * i + 1) - 300.f);
            window.draw(upgrades[i]);  // 각 텍스트 객체를 개별적으로 그리기
        }
    }

}

void UiUpgrade::HandleUpgradeSelection()
{
    // 마우스 위치 가져오기 (스크린 좌표 -> 월드 좌표 변환)
    sf::Vector2i mousePos = InputMgr::GetMousePosition();  // 마우스 위치
    sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);  // 월드 좌표로 변환

    // 업그레이드 텍스트의 경계를 확인하고 클릭 여부를 체크
    for (size_t i = 0; i < upgrades.size(); ++i)
    {
        // 업그레이드 아이템에 마우스 위치가 포함되어 있는지 체크
        if (upgrades[i].getGlobalBounds().contains(mouseWorldPos))
        {
            
            upgrades[i].setFillColor(sf::Color::Red);

            // 마우스 왼쪽 버튼이 클릭되었을 때 업그레이드 선택 처리
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // 업그레이드 선택 처리
                switch (i)
                {
                case 0:
                    selectedUpgrade = Upgrade::RateOfFire;
                    player->IncreaseRateOfFire();
                    break;
                case 1:
                    selectedUpgrade = Upgrade::ClipSize;
                    player->IncreaseClipSize(10);
                    break;
                case 2:
                    selectedUpgrade = Upgrade::MaxHealth;
                    player->IncreaseMaxHealth(10.f);
                    break;
                case 3:
                    selectedUpgrade = Upgrade::RunSpeed;
                    player->IncreaseRunSpeed();
                    break;
                case 4:
                    selectedUpgrade = Upgrade::HealthPickups;
                    player->IncreaseHealthPickups();
                    break;
                case 5:
                    selectedUpgrade = Upgrade::AmmoPickups;
                    player->IncreaseAmmoPickups();
                    break;
                }
                // 게임 재개 및 UI 비활성화
                dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->ResumeGame();  // 일시 정지 해제
                SetActive(false);  // UI 비활성화
                ResetUpgradeState();
            }
        
        }
        else
        {
            upgrades[i].setFillColor(sf::Color::White);
        }
    }
}

void UiUpgrade::SetActive(bool active)
{
isActive = active;
}

void UiUpgrade::ResetUpgradeState()
{
    for (size_t i = 0; i < upgrades.size(); ++i)
    {
        upgrades[i].setFillColor(sf::Color::White);  // 원래 색상으로 리셋
    }
}



