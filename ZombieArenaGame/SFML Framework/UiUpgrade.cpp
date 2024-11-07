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
    {  // Ȱ��ȭ�� ��쿡�� �׸���
        sf::Vector2f playerPos = player->GetPosition();
        sf::Vector2f windowSize(1920.f, 1080.f);
        sf::Vector2f offset = windowSize * 0.5f;

        // ��� ��ġ ����
        background.setPosition(playerPos - offset);
        window.draw(background);
        for (size_t i = 0; i < upgrades.size(); ++i)
        {
            upgrades[i].setPosition(playerPos.x -750.f, playerPos.y + (120.f * i + 1) - 300.f);
            window.draw(upgrades[i]);  // �� �ؽ�Ʈ ��ü�� ���������� �׸���
        }
    }

}

void UiUpgrade::HandleUpgradeSelection()
{
    // ���콺 ��ġ �������� (��ũ�� ��ǥ -> ���� ��ǥ ��ȯ)
    sf::Vector2i mousePos = InputMgr::GetMousePosition();  // ���콺 ��ġ
    sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);  // ���� ��ǥ�� ��ȯ

    // ���׷��̵� �ؽ�Ʈ�� ��踦 Ȯ���ϰ� Ŭ�� ���θ� üũ
    for (size_t i = 0; i < upgrades.size(); ++i)
    {
        // ���׷��̵� �����ۿ� ���콺 ��ġ�� ���ԵǾ� �ִ��� üũ
        if (upgrades[i].getGlobalBounds().contains(mouseWorldPos))
        {
            
            upgrades[i].setFillColor(sf::Color::Red);

            // ���콺 ���� ��ư�� Ŭ���Ǿ��� �� ���׷��̵� ���� ó��
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // ���׷��̵� ���� ó��
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
                // ���� �簳 �� UI ��Ȱ��ȭ
                dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->ResumeGame();  // �Ͻ� ���� ����
                SetActive(false);  // UI ��Ȱ��ȭ
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
        upgrades[i].setFillColor(sf::Color::White);  // ���� �������� ����
    }
}



